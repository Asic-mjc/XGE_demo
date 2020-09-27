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
// $Id: FAASTDetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file FAASTDetectorConstruction.hh
/// \brief Definition of the FAASTDetectorConstruction class

#ifndef FAASTDetectorConstruction_h
#define FAASTDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Tubs;
class G4Orb;
class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class FAASTDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    FAASTDetectorConstruction();
    virtual ~FAASTDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();
    
  public:
  
  	G4Box*             solidWorld;
	G4LogicalVolume*   logicWorld;
	
	G4Box* solidTube;
    G4LogicalVolume* logicTube;
    G4VPhysicalVolume* physiTube;   // pointer to the physical Tube 
     	 
	G4Box*             solidBase;   // pointer to the solid Base
	G4LogicalVolume*   logicBase;   // pointer to the logical Base
	G4VPhysicalVolume* physiBase;   // pointer to the physical Base
	
    // Target
    G4Box*             	solidTarget;
    G4LogicalVolume*   	logicTarget;
    G4VPhysicalVolume* 	physiTarget;
	
	
	//Detector
	G4Tubs*            solidDetector;
	G4LogicalVolume*   logicDetector;
	G4VPhysicalVolume* physiDetector; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

