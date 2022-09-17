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
// $Id: FAASTDetectorConstruction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file FAASTDetectorConstruction.cc
/// \brief Implementation of the FAASTDetectorConstruction class

#include "FAASTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4GeometryManager.hh"  //以下四个头文件用于读取现有的几何体,清理现有的几何体
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"//注册灵敏探测器需要
#include "G4VSensitiveDetector.hh"
#include "FAASTSD.hh"
#include "FAASTSPSD.hh"

#include "G4VisAttributes.hh"//change the color of geomtry
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"//为了调用pi

#include "FAASTZGBParameters.hh"//全局参数设置

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTDetectorConstruction::FAASTDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FAASTDetectorConstruction::~FAASTDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* FAASTDetectorConstruction::Construct()
{  
  // Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();
	G4String name;   
	G4double  a,z,density; 
	G4double temperature, pressure;
	//G4int  ncomponents;//, natoms;

	G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* Base_mat = nist->FindOrBuildMaterial("G4_Be");

	
    G4Material* Target_mat = nist->FindOrBuildMaterial("G4_W");
    G4Material* Detector_mat = nist->FindOrBuildMaterial("G4_Si");

	
  //
  // examples of vacuum
  //

	density     = universe_mean_density;
	pressure    = 3.e-18*pascal;
	temperature = 2.73*kelvin;
	G4Material* Vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole,
									density,kStateGas,temperature,pressure);
                                    
  // Option to switch on/off checking of volumes overlaps
  //
	G4bool checkOverlaps = true;
	
	///////////////
	G4GeometryManager::GetInstance()->OpenGeometry();//清理现有的几何体  如果有的话
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();  //清理现有的几何体  如果有的话

  // ------------------------------
  // World
  // ------------------------------
	G4double world_sizeX = WORLD_X;
	G4double world_sizeY = WORLD_Y;
	G4double world_sizeZ = WORLD_Z;

  
	solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size
      
	logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
	G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  // ------------------------------
  // Tube
  // ------------------------------
 	G4double Tube_sizeX = TUBE_X;
	G4double Tube_sizeY = TUBE_Y;
	G4double Tube_sizeZ = TUBE_Z;

  
	solidTube =    
    new G4Box("Tube",                       //its name
			0.5*Tube_sizeX, 0.5*Tube_sizeY, 0.5*Tube_sizeZ);     //its size
      
	logicTube =                         
    new G4LogicalVolume(solidTube,          //its solid
                        Vacuum,           //its material
                        "Tube");            //its name
                                   
	physiTube = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicTube,            //its logical volume
                      "Tube",               //its name
                      logicWorld,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //------------------------------ 
  // Base 1 cubic base
  //------------------------------
  
	G4double Base_x = BASEWIDTHX; 
	G4double Base_Thickness = BASETHICKNESSY;
	G4double Base_z = BASETOTALLENGTHZ;
	   
	solidBase = new G4Box("Base",0.5*Base_x,0.5*Base_Thickness,0.5*Base_z);
	logicBase = new G4LogicalVolume(solidBase,Base_mat,"Base",0,0,0);
	
	G4double BasePos_x = 0.0 *cm;
	G4double BasePos_y = -Base_Thickness/2;
	G4double BasePos_z = 0.0 *cm;	 
	G4ThreeVector BasePos = G4ThreeVector(BasePos_x,BasePos_y,BasePos_z);
	G4RotationMatrix Base_rotm  = G4RotationMatrix();
    Base_rotm.rotateX(0. *deg);
	G4Transform3D Base_transform = G4Transform3D(Base_rotm,BasePos);	
	physiBase = new G4PVPlacement(Base_transform,        //transform
                                  logicBase,     // its logical volume                                  
                                  "Base",        // its name
                                  logicTube,      // its mother  volume
                                  false,           // no boolean operations
                                  0);              // copy number 


  //------------------------------
  // Target
  //------------------------------

    G4double TargetWidthX 			= TargetWIDTHX;//Target_WIDTH_X;
    G4double TargetThicknessY		= TargetTHICKNESSY;
    G4double TargetTotalLengthZ		= TargetTOTALLENGTHZ;
    
    solidTarget = new G4Box("Target",TargetWidthX/2,TargetThicknessY/2,TargetTotalLengthZ/2);
    logicTarget = new G4LogicalVolume(solidTarget,Target_mat,"Target");
	

    G4double positionx=	0.0 *cm;
    G4double positiony= (0.5*Base_Thickness-0.5*TargetThicknessY);
    G4double positionz= 0.0 *cm;//这里不用考虑平移,因为母体移动,子体也会随着移动

    G4ThreeVector position = G4ThreeVector(positionx,positiony,positionz);//设置放置位置

    G4RotationMatrix rotmG11 = G4RotationMatrix();
    rotmG11.rotateX(0 *deg);//控制绕Z轴旋转角度,这里只能设为0°,因为子体已经随母体旋转了
    rotmG11.rotateY(0 *deg);//控制绕Z轴旋转角度,这里只能设为0°,因为子体已经随母体旋转了
    G4Transform3D transform = G4Transform3D(rotmG11,position); //将旋转控制和平移控制整合

    physiTarget = new G4PVPlacement(transform,       // 旋转和位置控制
                                logicTarget,     // its logical　volume
                                "Target",        // its name
                                logicBase,      // its mother  volume
                                false,           // no boolean operations
                                7777,               // copy number
                                checkOverlaps);  // check for overlaps



  // ------------------------------
  // Detectors
  // ------------------------------
	G4double Detector_rmin =  DETECTOR_RMIN, Detector_rmax = DETECTOR_RMAX;
	G4double Detector_hz = DETECTOR_HZ;    
	G4double Detector_phimin = 0.*deg, Detector_phimax = 360.*deg;
	solidDetector = new G4Tubs("Detector",
									 Detector_rmin, 
									 Detector_rmax,  
									 Detector_hz/2,
									 Detector_phimin, 
									 Detector_phimax);
				
	logicDetector = new G4LogicalVolume(solidDetector,         //its solid
										Detector_mat ,          			//its material
										"Detector");            //its name
	G4double R = RPOSITION;


    G4double detectorstartangle = DETECTORSTARTALANGLE;
    G4double rottheta= detectorstartangle *deg;


    G4double DetectorPos_x = 0.0 *cm;
    G4double DetectorPos_y = R*sin(rottheta) ;
    G4double DetectorPos_z = R*cos(rottheta) ;

    G4ThreeVector Detector_pos = G4ThreeVector(DetectorPos_x,DetectorPos_y,DetectorPos_z);
    G4RotationMatrix Detector_rotm  = G4RotationMatrix();
    //Detector_rotm.rotateY(-90*deg);
    Detector_rotm.rotateX(-rottheta);//绕X轴旋转

    G4Transform3D Detector_transform = G4Transform3D(Detector_rotm,Detector_pos);

    physiDetector = new G4PVPlacement(Detector_transform,        //transform
                      logicDetector,             //its logical volume
                      "Detector",                //its name
                     logicTube,              //its mother  volume
                      false,                   //no boolean operation
                      9999,                       //copy number
                      checkOverlaps);          //overlaps checking

  // ------------------------------
  // Set the visibility of the geometry
  // ------------------------------
	G4VisAttributes* BoxVisAttributes= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    logicWorld  ->SetVisAttributes(BoxVisAttributes);
    BoxVisAttributes-> SetVisibility(true);
	
    G4VisAttributes* logicTubeVisAttributes= new G4VisAttributes(G4Colour(0.5,0.5,1));
    logicTube  ->SetVisAttributes(logicTubeVisAttributes);
    logicTubeVisAttributes -> SetVisibility(true);//invisible setting
	
    G4VisAttributes* logicBaseVisAttributes= new G4VisAttributes(G4Colour(0.6,0.6,0.6));
    logicBase  ->SetVisAttributes(logicBaseVisAttributes);
    logicBaseVisAttributes -> SetVisibility(true);
	
    G4VisAttributes* logicTargetVisAttributes= new G4VisAttributes(G4Colour(47./255,151./255,193./255));
    logicTarget  ->SetVisAttributes(logicTargetVisAttributes);
    logicTargetVisAttributes  ->SetForceSolid(true);//几何体实心显示

	G4VisAttributes* logicDetectorVisAttributes= new G4VisAttributes(G4Colour(1.,0.,1.));//pink
	logicDetector ->SetVisAttributes(logicDetectorVisAttributes);
    logicDetectorVisAttributes -> SetVisibility(true);


  // ------------------------------
  //always return the physical World
  // ------------------------------
  return physWorld;
}


void FAASTDetectorConstruction::ConstructSDandField()
{
    
//Sensitive detector registration

  //------------------------------------------------------------------
  //----------------------Set sensitive detectors---------------------
  //------------------------------------------------------------------

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String SDname;
    
    G4VSensitiveDetector* aFAASTSubstrate
      = new FAASTSPSD(SDname="/FAASTSubstrate");//substrate
    SDman->AddNewDetector(aFAASTSubstrate);  
	logicBase->SetSensitiveDetector(aFAASTSubstrate);
    
	G4VSensitiveDetector* aFAASTTarget
      = new FAASTSPSD(SDname="/FAASTTarget");//target
    SDman->AddNewDetector(aFAASTTarget); 
    logicTarget->SetSensitiveDetector(aFAASTTarget);
    
    G4VSensitiveDetector* aFAASTSD 
      = new FAASTSD(SDname="/FAASTSD");//flux and spectrum detector
    SDman->AddNewDetector(aFAASTSD);
    logicDetector->SetSensitiveDetector(aFAASTSD);

   
}    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
