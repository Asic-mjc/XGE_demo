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
// $Id: FAASTSD.cc 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTSD.cc
/// \brief Implementation of the FAASTSD class

#include "FAASTSD.hh"
//#include "FAASTHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4StepPoint.hh"
#include "Randomize.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include "FAASTZGBParameters.hh"//全局参数设置

//用于创建时间精确的时间来命名文件
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSD::FAASTSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
    G4String HCname = "FAASTCollection";  //HitsCollection的“预”名称
    collectionName.insert(HCname);
     
    particle = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSD::~FAASTSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSD::Initialize(G4HCofThisEvent* hce )
{
	//=========================================================================
	//This is invoked at the begining of each event
	//=========================================================================
	
	
    //
    // 3. 构建hitCollection，并讲它注册到G4HCofThisEvent* hce
    // 
    //=================================	
    	
	//1.利用灵敏探测器的名字和上面定义的HitsCollection的“预”名称实例化一个hitCollection.
		//（1）它是在FAASTSPSDHit.hh中定义的   typedef G4THitsCollection<FAASTSPSDHit> FAASTSPSDHitsCollection;
	//2.从G4SDManager中获取hitCollection的CollectionID.
        // (1) 而且利用<0判断，保证获取ID这个函数只在第一次初始化的时候调用一次，它是一个耗内存的操作，不能多次调用，这种<0的判断思路在G4中很常用。
	//3.利用CollectionID(fHitsCollection)和实例化的fHitsCollection注册到G4HCofThisEvent* hce
	
	fHitsCollection = new FAASTSDHitsCollection(SensitiveDetectorName,collectionName[0]);
    if (fHCID<0)
    { fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }
    hce->AddHitsCollection(fHCID,fHitsCollection);
	
	particle++;	
    flg_trackID = -1; // flag to avoid writing more than once the same photon in the ideal detector.
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool FAASTSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	//获取判断条件参数    
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    //G4StepPoint* postStepPoint = step->GetPostStepPoint();
    // copynumber获取
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
	G4VPhysicalVolume* physical = touchable->GetVolume();//To get the current volume
    G4int copyNo0 = physical->GetCopyNo(); //To get the preStepPoint physical volume copy number   
	// particleName
    const G4Track* pTrack = step->GetTrack();
	G4ParticleDefinition * particleType = pTrack->GetDefinition();
  	G4String	particleName =	particleType->GetParticleName();
    G4int trackID = pTrack->GetTrackID();
    G4String VertexName = pTrack -> GetLogicalVolumeAtVertex()->GetName();
  	
	if (flg_trackID==trackID) return true;   
	
	//judgement
	if (particleName=="gamma"){
		flg_trackID = trackID;

		// Total Energy
		//G4double TotalEnergy = step->GetPreStepPoint()->GetTotalEnergy();
		G4double TotalEnergy =pTrack->GetKineticEnergy();
		count++;  
	

			 
		//insert the acquied data into hitCollection
        // ref: HandOn4 DriftChamberSD.cc 2018/03/28 15:22:42
		FAASTSDHit* hit = new FAASTSDHit(copyNo0);
        hit-> SetEnergy(TotalEnergy);
        hit-> SetVertexVolumeName(VertexName);

		fHitsCollection->insert(hit);		
}
   
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSD::EndOfEvent(G4HCofThisEvent* )
{
  //This is invoked at the end of each event

    if ((particle)%30 == 0)
        {
            G4cout << "+++ Particle #: " << particle << G4endl;
            G4cout << "+++ Count #: "<< count << endl;
            G4cout << "+++ Count Ratio = "<< (G4double(count))/particle << endl;
        }


}



















