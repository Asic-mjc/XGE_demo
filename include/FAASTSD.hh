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
// $Id: FAASTSD.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file FAASTSD.hh
/// \brief Definition of the FAASTSD class

#ifndef FAASTSD_h
#define FAASTSD_h 1

#include "G4VSensitiveDetector.hh"
#include "FAASTSDHit.hh"
#include <fstream>          //新增代码，用于包含标准C++文件输入输出头文件
using namespace std;        //新增代码，用于引入C++标准名字空间


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

/// FAAST sensitive detector

class FAASTSD : public G4VSensitiveDetector
{
public:
    FAASTSD(G4String name);
    virtual ~FAASTSD();
    
    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	void EndOfEvent(G4HCofThisEvent*);
	
private:
    FAASTSDHitsCollection* fHitsCollection;//实例化自己的HitsCollection,获取指针
    G4int fHCID;    

public:
    
	G4int particle;
	G4int flg_trackID;
	fstream datafile2;    
	int count;



};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
