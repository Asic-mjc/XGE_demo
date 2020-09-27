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
// $Id: FAASTSPSDHit.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTSPSDHit.hh
/// \brief Definition of the FAASTSPSDHit class
// 本文件来源于HandOn4 DriftChamberHit.hh 2018/03/28 15:22:42
#ifndef FAASTSPSDHit_h
#define FAASTSPSDHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

/// SPSDetector hit
///
/// It records:
/// - the Volume ID
/// - the particle Energy
/// - the particle local and global positions

class FAASTSPSDHit : public G4VHit
{
public:
    FAASTSPSDHit();
    FAASTSPSDHit(G4int z);
    FAASTSPSDHit(const FAASTSPSDHit &right);
    virtual ~FAASTSPSDHit();

    const FAASTSPSDHit& operator=(const FAASTSPSDHit &right);
    int operator==(const FAASTSPSDHit &right) const;
    
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
    
    virtual void Draw();
    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;
    virtual void Print();

    void SetVolumeID(G4int z) { fVolumeID = z; }
    G4int GetVolumeID() const { return fVolumeID; }

    void SetEnergy(G4double e) { fEnergy = e; }
    G4double GetEnergy() const { return fEnergy; }

    void SetTrackID(G4int trackID) { fTrackID = trackID; }
    G4int GetTrackID() const { return fTrackID; }
    
	void SetParticleName(G4String	particlename) { fParticleName = particlename; }
    G4String GetParticleName() const { return fParticleName; }
    
	void SetFlagBoundary(G4int	flagboundary) { fflagBoundary = flagboundary; }
    G4int GetFlagBoundary() const { return fflagBoundary; }        
    
private:
    G4int fVolumeID;
    G4double fEnergy;
    G4int fTrackID;
    G4String fParticleName;
    G4int fflagBoundary; 
};

typedef G4THitsCollection<FAASTSPSDHit> FAASTSPSDHitsCollection;

extern G4ThreadLocal G4Allocator<FAASTSPSDHit>* FAASTSPSDHitAllocator;

inline void* FAASTSPSDHit::operator new(size_t)
{
    if (!FAASTSPSDHitAllocator)
        FAASTSPSDHitAllocator = new G4Allocator<FAASTSPSDHit>;
    return (void*)FAASTSPSDHitAllocator->MallocSingle();
}

inline void FAASTSPSDHit::operator delete(void* aHit)
{
    FAASTSPSDHitAllocator->FreeSingle((FAASTSPSDHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
