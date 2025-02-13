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
/// 本类参考 electromagnetic/TestEm2/src/PhysicsListMessenger.cc
///  Implementation of the PhysicsListMessenger class
//
// $Id: FAASTPhysicsListMessenger.cc 2016/09/17 12:26:46 zangb $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "FAASTPhysicsListMessenger.hh"

#include "FAASTPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTPhysicsListMessenger::FAASTPhysicsListMessenger(FAASTPhysicsList* pPhys)
:G4UImessenger(),fFAASTPhysicsList(pPhys)
{
  fPhysDir = new G4UIdirectory("/FAASTS/phys/");
  fPhysDir->SetGuidance("physics list commands");
   
  fListCmd = new G4UIcmdWithAString("/FAASTS/phys/addPhysics",this);  
  fListCmd->SetGuidance("Add modula physics list.");
  fListCmd->SetParameterName("PList",false);
//  fListCmd->SetCandidates("emlivermore empenelope emlowenergy");
  fListCmd->AvailableForStates(G4State_PreInit);
//  fListCmd->SetToBeBroadcasted(false);    //多线程设置,参考MIT 22UserInterface2.pdf P22
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTPhysicsListMessenger::~FAASTPhysicsListMessenger()
{
  delete fListCmd;
  delete fPhysDir;    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTPhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{       
  if( command == fListCmd )
   { fFAASTPhysicsList->AddPhysicsList(newValue);}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
