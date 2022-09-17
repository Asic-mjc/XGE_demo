/// \file FAASTSPSD.cc
/// \brief Implementation of the FAASTSPSD class
#include "FAASTDetectorConstruction.hh"
#include "FAASTSPSD.hh"
#include "FAASTSPSDHit.hh"
#include "G4RunManager.hh"

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

#include "FAASTZGBParameters.hh"//参数头文件


#include <stdio.h>
#include <math.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSD::FAASTSPSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
    G4String HCname = "FAASTCollection";  //HitsCollection的“预”名称
    collectionName.insert(HCname);
     
    particle = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSD::~FAASTSPSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSPSD::Initialize(G4HCofThisEvent* hce )
{
	//=========================================================================
	//This is invoked at the begining of each event
	//=========================================================================
	
	
    //
    // 3. 构建hitCollection，并将它注册到G4HCofThisEvent* hce
    // 
    //=================================	
    	
	//1.利用灵敏探测器的名字和上面定义的HitsCollection的“预”名称实例化一个hitCollection.
		//（1）它是在FAASTSPSDHit.hh中定义的   typedef G4THitsCollection<FAASTSPSDHit> FAASTSPSDHitsCollection;
	//2.从G4SDManager中获取hitCollection的CollectionID.
		// (1)而且利用<0判断，保证获取ID这个函数只在第一次初始化的时候调用一次，它是一个耗内存的操作，不能多次调用，这种<0的判断思路在G4中很常用。
	//3.利用CollectionID(fHitsCollection)和实例化的fHitsCollection注册到G4HCofThisEvent* hce
	
	fHitsCollection = new FAASTSPSDHitsCollection(SensitiveDetectorName,collectionName[0]);
    if (fHCID<0)
    { fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }
    hce->AddHitsCollection(fHCID,fHitsCollection);
	
	particle++;	
    flag_Boundary = -1; // flag to avoid writing more than once the same photon in the idea detector.
    flag_trackID_Boundary=-1;//flag to avoid recording the boundary track
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool FAASTSPSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	
	//获取判断条件参数    
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    // copynumber获取
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
	G4VPhysicalVolume* physical = touchable->GetVolume();//To get the current volume
    G4int copyNo0 = physical->GetCopyNo(); //To get the preStepPoint physical volume copy number   

	const G4Track* pTrack=step->GetTrack();  	
  	G4int trackID = pTrack->GetTrackID();  
	
    // Total Energy when the track was created
    G4double TotalEnergy =pTrack->GetVertexKineticEnergy();//GetKineticEnergy();

	// particleName
	G4ParticleDefinition * particleType = pTrack->GetDefinition();
  	G4String	particleName =	particleType->GetParticleName();



	if (preStepPoint->GetStepStatus() == fGeomBoundary) {		
		if (particleName=="gamma"){
            flag_Boundary = 0;	//	flag_Boundary=0 stands for the particle come in, not produce inside
            flag_trackID_Boundary=trackID;
        }
    }
    else{
        flag_Boundary = 1;
    }

    if(flag_trackID_Boundary == trackID){
        flag_Boundary = 0;
    }

	//insert the acquied data into hitCollection
    // ref:HandOn4 DriftChamberSD.cc 2018/03/28 15:22:42
	FAASTSPSDHit* hit = new FAASTSPSDHit(copyNo0);
	hit->SetEnergy(TotalEnergy);	
	hit->SetTrackID(trackID);
	hit->SetParticleName(particleName); 
	hit->SetFlagBoundary(flag_Boundary);
	
	fHitsCollection->insert(hit);	

   
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSPSD::EndOfEvent(G4HCofThisEvent* )
{
  //This is invoked at the end of each event
  


}

















