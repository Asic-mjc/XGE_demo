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
// $Id: FAASTRunAction.hh 74204 2013-10-01 07:04:43Z ihrivnac $
// 
/// \file FAASTRunAction.hh
/// \brief Definition of the FAASTRunAction class
// 本文件来源于HandOn4 RunAction.hh 2018/03/28 16:55:53
#ifndef FAASTRunAction_h
#define FAASTRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class FAASTRunAction : public G4UserRunAction
{
  public:
    FAASTRunAction();
    virtual ~FAASTRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
//    virtual G4Run* GenerateRun();

public:
	
    G4String filename;
    G4int NbinsSpectrum;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

