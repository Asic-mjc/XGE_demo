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
// $Id: FAASTActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file FAASTActionInitialization.cc
/// \brief Implementation of the FAASTActionInitialization class

#include "FAASTActionInitialization.hh"
#include "FAASTPrimaryGeneratorAction.hh"
#include "FAASTRunAction.hh"
#include "FAASTEventAction.hh"
#include "FAASTSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTActionInitialization::FAASTActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTActionInitialization::~FAASTActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTActionInitialization::BuildForMaster() const // 多线程模式下调用, I didn't use this in current code
{
  //SetUserAction(new FAASTRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTActionInitialization::Build() const
{
  //SetUserAction(new FAASTPrimaryGeneratorAction);
  SetUserAction(new FAASTRunAction);
  
  G4VUserPrimaryGeneratorAction* gen_action = new FAASTPrimaryGeneratorAction();
  SetUserAction(gen_action);
 
  FAASTEventAction* eventAction = new FAASTEventAction;
  SetUserAction(eventAction);
  
  SetUserAction(new FAASTSteppingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
