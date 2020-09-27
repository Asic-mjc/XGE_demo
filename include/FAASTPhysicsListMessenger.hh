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
/// 本类参考  electromagnetic/TestEm2/include/PhysicsListMessenger.hh
///  Definition of the PhysicsListMessenger class
//
// $Id: FAASTPhysicsListMessenger.hh 2016/09/17 12:26:29 zangb$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef FAASTPhysicsListMessenger_h
#define FAASTPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class FAASTPhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class FAASTPhysicsListMessenger: public G4UImessenger
{
public:
  
  FAASTPhysicsListMessenger(FAASTPhysicsList* );
  virtual ~FAASTPhysicsListMessenger();
    
  virtual void SetNewValue(G4UIcommand*, G4String);
    
private:
  
  FAASTPhysicsList* fFAASTPhysicsList;
    
  G4UIdirectory*             fPhysDir;        
  G4UIcmdWithAString*        fListCmd;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

