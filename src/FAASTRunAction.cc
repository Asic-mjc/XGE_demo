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
// $Id: RunAction.cc 74204 2013-10-01 07:04:43Z ihrivnac $
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
// 本文件来源于HandOn4 RunAction.cc 2018/03/28 16:55:53
#include "FAASTRunAction.hh"
#include "Analysis.hh"
//#include "Run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <math.h>
#include "FAASTZGBParameters.hh"

#include <stdio.h>

#include <G4UImessenger.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTRunAction::FAASTRunAction()
 : G4UserRunAction()
{
  
    //
    //  Create an output file containing the histograms
    // 
    //================================================================
	
    //
    // 1. Create analysis manager
    // 
    //=================================    

  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;
    filename += RootFileName;//Define root file name
    filename += ".root";



  // Default settings
	analysisManager->SetVerboseLevel(1);
    analysisManager->SetFileName(filename);

    //
    // 2. Book histograms
    // 
    //================================= 

    //parameters of histogram
    NbinsSpectrum = G4int(KVP/0.1);
    
	//
    // 2.1 Book histograms of Total(=Target+Substrate)
    // 
    //================================= 
    

    //  Creating 1D histograms of spectrum generated in total
    // h1 Id = 0
      analysisManager -> CreateH1("EnSp-Total","Energy spectrum of Total", NbinsSpectrum, 0., KVP);

    //  Creating 1D histograms of spectrum generated in target
    // h1 Id = 1
    analysisManager -> CreateH1("EnSp-Target","Energy spectrum of Target", NbinsSpectrum, 0., KVP);

    //  Creating 1D histograms of spectrum generated in substrate
    // h1 Id = 2
    analysisManager -> CreateH1("EnSp-Substrate","Energy spectrum of Substrate", NbinsSpectrum, 0., KVP);

    //
    //  Book histograms of flux and energy spectrum detector
    //
    //=================================
    //  Creating 1D histograms


    G4String titleTotal ="FluxSpectrumTotal";
    G4String titleTarget = "FluxSpectrumTarget";
    G4String titleSubstrate = "FluxSpectrumSubstrate";

    G4String discriptionTotal = "FluxSpectrumTotal";
    G4String discriptionTarget = "FluxSpectrumTarget";
    G4String discriptionSubstrate = "FluxSpectrumSubstrate";
    // h1 Id = 3
    analysisManager -> CreateH1(titleTotal,discriptionTotal, NbinsSpectrum, 0., KVP);
    // h1 Id = 4
    analysisManager -> CreateH1(titleTarget,discriptionTarget, NbinsSpectrum, 0., KVP);
    // h1 Id = 5
    analysisManager -> CreateH1(titleSubstrate,discriptionSubstrate, NbinsSpectrum, 0., KVP);


 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTRunAction::~FAASTRunAction()
{
	//
    // 1.delete G4AnalysisManager by user
    // 
    //=================================
     
	delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTRunAction::BeginOfRunAction(const G4Run* /*run*/)
{

    
	//inform the runManager to save random number seed
	//G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
	//
    // 1.Get analysis manager
    // 
    //=================================  
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	//
    // 2.Open an output file
    // 
    //=================================

	// The default file name is set in FAASTRunAction::FAASTRunAction(),
	// it can be overwritten in a macro
	analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FAASTRunAction::EndOfRunAction(const G4Run* /*run*/)
{
      
	//
    // 3.Write and close output file
    // 
    //=================================

    
	// save histograms & ntuple
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

