//该头文件用于参数声明
#ifndef FAASTZGBParameters_h
#define FAASTZGBParameters_h 1

#include "globals.hh"

//Geometry Parameters-------------------------------------------
// World
  	extern const G4double WORLD_X;	
	extern const G4double WORLD_Y;	
	extern const G4double WORLD_Z;
	
// Tube
  	extern const G4double TUBE_X;	
	extern const G4double TUBE_Y;	
	extern const G4double TUBE_Z;

// Base
	extern const G4double BASEWIDTHX;
	extern const G4double BASETHICKNESSY;
	extern const G4double BASETOTALLENGTHZ; 
	
// Target
    extern const G4double TargetWIDTHX;//Target(X)
    extern const G4double TargetTHICKNESSY;//Target thickness(Y)
    extern const G4double TargetTOTALLENGTHZ;//Target length(Z)

	
// substrate 2
    extern const G4double DIAMOND2THICKNESSY;//substrate thickness
	
	 	
// Energy spectrum Detector Parameters -----------------------------------------
	extern const G4double DETECTOR_RMIN;
	extern const G4double DETECTOR_RMAX;
	extern const G4double DETECTOR_HZ;
    extern const G4double RPOSITION;
    extern const G4double DETECTORSTARTALANGLE;//能谱探测器放置角度,-90°在Y轴负方向上,0°在Z轴正方向上,+90°在Y轴正方向上

		
// OTHER Parameters -----------------------------------------	
    extern const G4double KVP;//Simulation voltage

// Root filename
    extern const G4String RootFileName;
	


#endif
