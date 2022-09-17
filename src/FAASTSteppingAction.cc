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
// $Id: FAASTSteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file FAASTSteppingAction.cc
/// \brief Implementation of the FAASTSteppingAction class

#include "FAASTSteppingAction.hh"
#include "FAASTDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "FAASTZGBParameters.hh"
//extern int spectrum[NUMBIN];

FAASTSteppingAction::FAASTSteppingAction()
	: G4UserSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSteppingAction::~FAASTSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void FAASTSteppingAction::UserSteppingAction(const G4Step* aStep)
void FAASTSteppingAction::UserSteppingAction(const G4Step*  )
{
      // ------------------------------
      // We can get any infomation from every step, but it is super inefficient;
      // Here I leave the codes for demostrating purpose
      // The best way is to use Sensitive detector
      // ------------------------------
/*
	if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma")
	{
		// get volume of the current step
		G4StepPoint *preStep;
		preStep = aStep->GetPreStepPoint();

		G4StepPoint *postStep;
		postStep = aStep->GetPostStepPoint();

		if (postStep->GetPhysicalVolume())
		{
			G4String prename = preStep->GetPhysicalVolume()->GetName();
			G4String postname = postStep->GetPhysicalVolume()->GetName();

            if ((prename == "Tube") &&(postname == "Detector") )
			{
				G4double Energy11=aStep->GetTrack()->GetTotalEnergy();
                if(Energy11/keV>5){//set a threshold for the energy detector
	//				int sub = ceil((aStep->GetTrack()->GetKineticEnergy()) * 1000);
					int sub = ceil(Energy11/keV/INTERVAL);
						if (sub < 0)
						sub = 0;
						if (sub > NUMBIN)
						sub = NUMBIN;
					
					spectrum[sub] ++;
				
					
				}
			}
		}
	}
*/	

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

