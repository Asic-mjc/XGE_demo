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
// $Id: FAASTSimulation.cc 2015/12/31 22:18:19 $
//
/// \file FAASTSimulation.cc
/// \brief Main program of the FAAST example

#include "FAASTDetectorConstruction.hh"
#include "FAASTActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"//用于随机数引擎

#include "FAASTDetectorConstruction.hh"
#include "FAASTPhysicsList.hh"
#include "FAASTPrimaryGeneratorAction.hh"

#include "FAASTZGBParameters.hh"//参数设置

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
/*	
	for(int i = 0; i < KVP; i ++)
 	{
 		spectrum[i] = 0;
 	}
*/ 
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  //<-----------------------------随机数引擎和随机种子的产生----------------------------->
  
  // Choose the Random engine
  //Method 1 利用秒作为随机种子

    //CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    // Randomisation!!!!!!!!!!!!
	G4Random::setTheEngine(new CLHEP::RanecuEngine); //selection of a random engine
 	G4long seed=time(0); //returns time in seconds as an integer
	CLHEP::HepRandom::setTheSeed(seed);//changes the seed of the random engine
	CLHEP::HepRandom::showEngineStatus();//shows the actual seed

    //<-----------------------------随机数引擎和随机种子完成----------------------------->
  
    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new FAASTDetectorConstruction());

  // Physics list
  G4VUserPhysicsList* physicsList = new FAASTPhysicsList;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  runManager->SetUserInitialization(new FAASTActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    
//	if (ui->IsGUI()) {
//        UImanager->ApplyCommand("/control/execute gui.mac");
//    } 
    
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
