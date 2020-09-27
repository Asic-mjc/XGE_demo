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
// $Id: FAASTPhysicsList.hh 73076 2013-08-16 07:45:30Z gcosmo $
//
/// \file medical/FAAST/include/FAASTPhysicsList.hh
/// \brief Definition of the FAASTPhysicsList class
//

#ifndef FAASTPhysicsList_h
#define FAASTPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class FAASTPhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class FAASTPhysicsList: public G4VModularPhysicsList
{
public:
  FAASTPhysicsList();
  ~FAASTPhysicsList();
  
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  void AddDecay();


     
//  void ConstructEM();
//  void ConstructHad();
//  void ConstructGeneral();
  virtual void SetCuts();
  
  void AddPhysicsList(const G4String& name);
  
  
private:

  G4String emName;
  G4VPhysicsConstructor*  emPhysicsList;
  FAASTPhysicsListMessenger*  fMessenger;
  
  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;
  
  

};
#endif



