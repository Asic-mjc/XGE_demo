
/// \file FAASTSPSD.hh
/// \brief Definition of the FAASTSPSD class

#ifndef FAASTSPSD_h
#define FAASTSPSD_h 1

#include "G4VSensitiveDetector.hh"
#include "FAASTSPSDHit.hh"
#include <fstream>
#include <iostream>
#include <time.h>

//#include "FAASTZGBParameters.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class FAASTDetectorConstruction;
class FAASTEventAction;
class FAASTRunAction;

using namespace std;

/// FAAST Spatial pixel sensitive detector

class FAASTSPSD : public G4VSensitiveDetector
{
public:
    FAASTSPSD(G4String name);
    virtual ~FAASTSPSD();
    
    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	void EndOfEvent(G4HCofThisEvent*);
	

    
private:
    FAASTSPSDHitsCollection* fHitsCollection;//实例化自己的HitsCollection,获取指针
    G4int fHCID;
    
public:
	G4int particle;
	G4int flag_Boundary;
    G4int flag_trackID_Boundary;
	fstream datafile2;    

	
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
