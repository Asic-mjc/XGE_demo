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
// $Id: EventAction.cc 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTEventAction.cc
/// \brief Implementation of the FAASTEventAction class
// ref: HandOn4 EventAction.cc 2018/03/28 15:22:42
#include "FAASTEventAction.hh"

#include "FAASTSPSDHit.hh"
#include "FAASTSDHit.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "FAASTZGBParameters.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTEventAction::FAASTEventAction()
: G4UserEventAction(), 
  fDHC1ID(-1), fDHC2ID(-1), fDHC3ID(-1)
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTEventAction::~FAASTEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTEventAction::BeginOfEventAction(const G4Event*)
{
    //
    // 1. 获取hitCollection的ID号 fDHC1ID
    // 
    //=================================
 
    if (fDHC1ID==-1) {
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fDHC1ID = sdManager->GetCollectionID("FAASTTarget/FAASTCollection");
        fDHC2ID = sdManager->GetCollectionID("FAASTSubstrate/FAASTCollection");
        fDHC3ID = sdManager->GetCollectionID("FAASTSD/FAASTCollection");
    }
    
    flg_trackID=-1;
}     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTEventAction::EndOfEventAction(const G4Event* event)
{
    //
    // 2. 获取G4HCofThisEvent指针
    // 
    //=================================	
 
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    
    // 判断G4HCofThisEvent对象中是否存有hitCollection指针，if it is 0（没有），exit
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("FAASTEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }   

    //
    // 3. Get hits collections 指针
    // 
    //=================================
 
    // 第二步 通过上面获取的hitCollection的ID号（fDHC1ID）从G4HCofThisEvent容器中去获取hitCollection的指针（dHC1），下面就利用hitCollection的指针（dHC1）取出数据。
    FAASTSPSDHitsCollection* dHC1 = static_cast<FAASTSPSDHitsCollection*>(hce->GetHC(fDHC1ID));//target
	FAASTSPSDHitsCollection* dHC2 = static_cast<FAASTSPSDHitsCollection*>(hce->GetHC(fDHC2ID));//substrate
    FAASTSDHitsCollection* dHC3 = static_cast<FAASTSDHitsCollection*>(hce->GetHC(fDHC3ID));//Flux and energy spectrum detector
   
    // 判断从G4HCofThisEvent容器中去获取hitCollection的指针是否存在， 如果为0（没有），退出 
    if ((!dHC1) || (!dHC2)|| (!dHC3))

    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n"; 
        G4Exception("FAASTEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }   
    
    //
    // 4. Fill histograms
    // 
    //=================================

    
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
    // Fill histograms from the target datas
    G4int n_hit1 = dHC1->entries();

	
	for (G4int i=0;i<n_hit1;i++)
	{
		FAASTSPSDHit* hit1 = (*dHC1)[i];
		G4double fEnergy = hit1->GetEnergy();
		G4String particleName = hit1->GetParticleName();
        G4int trackID = hit1->GetTrackID();
        G4int flagBoundary = hit1->GetFlagBoundary();
		


		
		if ((flagBoundary!=0)&&(particleName=="gamma"))
		{
			if(flg_trackID != trackID)
			{
                flg_trackID = trackID;
                analysisManager->FillH1(0, fEnergy/keV);
                analysisManager->FillH1(1, fEnergy/keV);
            }
        }
    }

	
	
    flg_trackID=-1;//再次复位，防止上面的target的记录结果影响substrate的记录

    // Fill histograms from substrate datas
    G4int n_hit2 = dHC2->entries();
	
	for (G4int i=0;i<n_hit2;i++)
	{
		FAASTSPSDHit* hit2 = (*dHC2)[i];
		G4double fEnergy = hit2->GetEnergy();
		G4String particleName = hit2->GetParticleName();
        G4int trackID = hit2->GetTrackID();
        G4int flagBoundary = hit2->GetFlagBoundary();
				

        if ((flagBoundary!=0)&&(particleName=="gamma"))
        {
            if(flg_trackID != trackID)
            {
                flg_trackID = trackID;
                analysisManager->FillH1(0, fEnergy/keV);
                analysisManager->FillH1(2, fEnergy/keV);
            }
        }


    }    

    // Fill histograms histograms of flux and energy spectrum detector
      G4int n_hit3 = dHC3->entries();
      for (G4int i=0;i<n_hit3;i++){
          FAASTSDHit* hit3 = (*dHC3)[i];
          G4double fEnergy = hit3->GetEnergy();

          G4String fVertexVolumeName = hit3-> GetVertexVolumeName();

          // fill flux spectrum of Total
          if((fVertexVolumeName == "Target")||(fVertexVolumeName == "Base")){
            analysisManager-> FillH1(3, fEnergy/keV);
          }

          // fill flux spectrum of Target
          if(fVertexVolumeName == "Target"){
              analysisManager-> FillH1(4, fEnergy/keV);
          }

          // fill flux spectrum of Substrate
          if(fVertexVolumeName == "Base"){
              analysisManager-> FillH1(5, fEnergy/keV);
          }

      }

    
    //
    // Print diagnostics: UI command /run/printProgress can be used
    // to set frequency of how often info should be dumpled
    // 
    
    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
    
    G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    G4ThreeVector momentum = primary->GetMomentumDirection();
    G4cout << G4endl
           << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
           << primary->GetG4code()->GetParticleName()
           <<" , Energy is: "<<primary->GetKineticEnergy()/keV <<" keV"<< G4endl;//<< " , Momentum is " << primary->GetMomentum()
    //G4cout << "theta ="<< momentum.theta()/deg<<"	"<<"phi  ="<< momentum.phi()/deg<<G4endl;
    G4cout << ">>> The elctron incident angle is: "<< momentum.phi()/deg + 90 <<" deg"<<" (0 degree is normal incident angle)"<< G4endl;

		      
		   
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
