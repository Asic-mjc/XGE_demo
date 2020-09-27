//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: FAASTPhysicsList.cc 75679 2013-11-05 09:08:41Z gcosmo $
//
/// \file medical/FAAST/src/FAASTPhysicsList.cc
/// \brief Implementation of the FAASTPhysicsList class
// 

//ref:TestE2

#include "FAASTPhysicsList.hh"
#include "FAASTPhysicsListMessenger.hh"

#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"
#include "G4ProcessManager.hh"

//#include "PhysListEmStandard.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"

#include "G4Decay.hh"
//#include "G4VAtomDeexcitation.hh"
//#include "G4UAtomicDeexcitation.hh"

#include "G4UnitsTable.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Hadrons
#include "G4Proton.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
FAASTPhysicsList::FAASTPhysicsList():G4VModularPhysicsList(),emPhysicsList(0),fMessenger(0)
{

  G4LossTableManager::Instance()->SetVerbose(1);//这句的目的是什么？
  
  fMessenger = new FAASTPhysicsListMessenger(this);//Messager类在target class 中instantiated

  defaultCutValue = 0.2*micrometer;

  fCutForGamma     = defaultCutValue;
  fCutForElectron  = defaultCutValue;
  fCutForPositron  = defaultCutValue; 

  SetVerboseLevel(1);
  if (verboseLevel > -1) {
    G4cout << "-----> verboseLevel is: <" << verboseLevel << ">" << G4endl;
  }

  // EM physics
  emName = G4String("empenelope");
  emPhysicsList = new G4EmPenelopePhysics;//注意:虽然下面有很多物理过程选项,但是没有起作用,因为void FAASTPhysicsList::AddPhysicsList(const G4String& name)函数只在Messenger.cc中调用
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
FAASTPhysicsList::~FAASTPhysicsList()
{
   delete emPhysicsList;
   delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//构建粒子
void FAASTPhysicsList::ConstructParticle()
{
	if(verboseLevel>0){
        G4cout << "### PhysicsList Construct Particles" << G4endl;
    }
	emPhysicsList->ConstructParticle();//物理过程类中已经有定义,只需调用,参考TestE2,而TestEm18就是单独再定义一次,这样也可以
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//物理过程
void FAASTPhysicsList::ConstructProcess()
{
	if (verboseLevel>0) {
		G4cout << "### Construct Process"<< G4endl;
  }
  
	// transportation
	//
	// AddTransportation();
	// electromagnetic physics list
	//	
	emPhysicsList->ConstructProcess(); 
	
	AddDecay();
  

//参考来源：David
    G4VModularPhysicsList::ConstructProcess();
    G4EmParameters* param = G4EmParameters::Instance();
    param->SetMinEnergy(0.1*keV);//--->Set the min kinetic energy for EM tables
    param->SetMaxEnergy(1.0*GeV);//--->Set the max kinetic energy for EM tables
    //param->SetNumberOfBinsPerDecade(10);//Default value of penelope and livermore is 20;emstandard is 10 
    param->SetVerbose(1);
    param->SetFluo(true);
    param->SetAuger(true);
    param->SetAugerCascade(true);//???--->Enable/Disable simulation of cascade of Auger electrons
    param->SetPixe(true);
    param->SetDeexcitationIgnoreCut(true);//???--->Enable/Disable usage of cuts in de-excitation module
    param->SetDeexActiveRegion("Target", true, true, true);//???? --->set deexcitation flags per G4Region The meaning of parameters:[region name][flagFluo][flagAuger][flagPIXE]

}
//ConstructGeneral--->衰变,与电子,光子无关,参考MIT 11Physics2,第6页
void FAASTPhysicsList::AddDecay()
{
  // Add Decay Process
/*
  G4Decay* fDecayProcess = new G4Decay();

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (fDecayProcess->IsApplicable(*particle) && !particle->IsShortLived()) { 

      pmanager ->AddProcess(fDecayProcess);

      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);

    }
  }
*/
}
// *** Processes and models
void FAASTPhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>-1) {
    G4cout << "----> PhysicsList::DefaultPhysicsList: <" << emName << ">" << G4endl;
  }

  if (name == emName){
	      //输出检验是否是设置的物理过程
    G4cout << "----> PhysicsList::ChangePhysicsList: <" << name << ">" << G4endl;
     return;

  }if (name == "emlivermore") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmLivermorePhysics;
    //输出检验是否是设置的物理过程
    G4cout << "----> PhysicsList::ChangePhysicsList: <" << name << ">" << G4endl;

  } else if (name == "emstandard") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics(); 

  } else if (name == "emstandard_opt1") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt2") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option2();

  } else if (name == "emstandard_opt3") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option3();
    
  } else if (name == "empenelope"){
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmPenelopePhysics();

  } else if (name == "emlowenergy"){
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmLowEPPhysics();//from TestEm2 physics process 
  }  else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}
//阈值
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void FAASTPhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "FAASTPhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }  
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV, 1*MeV);
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma 
  SetCutValue(fCutForGamma, "gamma");
  SetCutValue(fCutForElectron, "e-");
  SetCutValue(fCutForPositron, "e+");
  
  if (verboseLevel>3) DumpCutValuesTable();

}

