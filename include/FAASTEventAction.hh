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
// $Id: EventAction.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTEventAction.hh
/// \brief Definition of the FAASTEventAction class
// 本文件来源于HandOn4 EventAction.hh 2018/03/28 15:22:42

#ifndef FAASTEventAction_h
#define FAASTEventAction_h 1


#include "G4UserEventAction.hh"
#include "globals.hh"

/// FAASTEvent action

class FAASTEventAction : public G4UserEventAction
{
public:
    FAASTEventAction();
    virtual ~FAASTEventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
private:
    G4int fDHC1ID;
    G4int fDHC2ID;
    G4int fDHC3ID;

	G4int flg_trackID;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
