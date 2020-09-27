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
// $Id: FAASTSPSDHit.cc 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTSPSDHit.cc
/// \brief Implementation of the FAASTSPSDHit class
// ref: HandOn4 FAASTSPSDHit.cc 2018/03/28 15:22:42
#include "FAASTSPSDHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<FAASTSPSDHit>* FAASTSPSDHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSDHit::FAASTSPSDHit()
: G4VHit(), fVolumeID(-1), fEnergy(0.), fTrackID(0), fflagBoundary(0)
{
	fParticleName=" ";
	}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSDHit::FAASTSPSDHit(G4int z)
: G4VHit(), fVolumeID(z), fEnergy(0.), fTrackID(0), fflagBoundary(0)
{
		fParticleName=" ";
	}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSDHit::~FAASTSPSDHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTSPSDHit::FAASTSPSDHit(const FAASTSPSDHit &right)
: G4VHit() {
    fVolumeID = right.fVolumeID;
    fEnergy = right.fEnergy;
    fTrackID = right.fTrackID;    
    fParticleName = right.fParticleName;
    fflagBoundary =right.fflagBoundary;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const FAASTSPSDHit& FAASTSPSDHit::operator=(const FAASTSPSDHit &right)
{
    fVolumeID = right.fVolumeID;
    fEnergy = right.fEnergy;
    fTrackID = right.fTrackID;    
    fParticleName = right.fParticleName;
    fflagBoundary =right.fflagBoundary;        
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int FAASTSPSDHit::operator==(const FAASTSPSDHit &/*right*/) const
{
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSPSDHit::Draw()
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const std::map<G4String,G4AttDef>* FAASTSPSDHit::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store
      = G4AttDefStore::GetInstance("FAASTSPSDHit",isNew);

    if (isNew) {
        (*store)["HitType"] 
          = G4AttDef("HitType","Hit Type","Physics","","G4String");
        
        (*store)["ID"] 
          = G4AttDef("ID","ID","Physics","","G4int");
        
        (*store)["Energy"] 
          = G4AttDef("Energy","Energy","Physics","G4BestUnit","G4double");
        
        (*store)["Pos"] 
          = G4AttDef("Pos", "Position", "Physics","G4BestUnit","G4ThreeVector");
    }
    return store;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4AttValue>* FAASTSPSDHit::CreateAttValues() const
{
    std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
    
    values
      ->push_back(G4AttValue("HitType","FAASTSPSDHit",""));
    values
      ->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fVolumeID),""));
    values
      ->push_back(G4AttValue("Energy",G4BestUnit(fEnergy,"Energy"),""));
    
    return values;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTSPSDHit::Print()
{
    G4cout << "  Volume[" << fVolumeID << "] : Energy " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
