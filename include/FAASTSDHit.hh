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
// $Id: FAASTSDHit.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTSDHit.hh
/// \brief Definition of the FAASTSDHit class
// 本文件来源于HandOn4 DriftChamberHit.hh 2018/03/28 15:22:42
#ifndef FAASTSDHit_h
#define FAASTSDHit_h 1

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

class FAASTSDHit : public G4VHit
{
public:
    FAASTSDHit();
    FAASTSDHit(G4int z);
    FAASTSDHit(const FAASTSDHit &right);
    virtual ~FAASTSDHit();

    const FAASTSDHit& operator=(const FAASTSDHit &right);
    int operator==(const FAASTSDHit &right) const;
    
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

    void SetVertexVolumeName(G4String v) { fVertexVolumeName = v; }
    G4String GetVertexVolumeName() const { return fVertexVolumeName; }
    
private:
    G4int fVolumeID;
    G4double fEnergy;
    G4String fVertexVolumeName;
   
};

typedef G4THitsCollection<FAASTSDHit> FAASTSDHitsCollection;

extern G4ThreadLocal G4Allocator<FAASTSDHit>* FAASTSDHitAllocator;

inline void* FAASTSDHit::operator new(size_t)
{
    if (!FAASTSDHitAllocator)
        FAASTSDHitAllocator = new G4Allocator<FAASTSDHit>;
    return (void*)FAASTSDHitAllocator->MallocSingle();
}

inline void FAASTSDHit::operator delete(void* aHit)
{
    FAASTSDHitAllocator->FreeSingle((FAASTSDHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
