//该文件用于参数赋值
#include "FAASTZGBParameters.hh"
#include "G4SystemOfUnits.hh"

//Geometry Parameters-------------------------------------------
//World
    const G4double WORLD_X = 0.25 *cm;
    const G4double WORLD_Y = 0.25 *cm;
    const G4double WORLD_Z = 0.25*cm;
	
//Tube----------------------------------------------------------
    const G4double TUBE_X = 0.219 *cm;
    const G4double TUBE_Y = 0.219 *cm;
    const G4double TUBE_Z = 0.219 *cm;
	
//Base----------------------------------------------------------
    const G4double BASEWIDTHX = 1 *mm;//Base width(X)
    const G4double BASETHICKNESSY = 0.3*mm;//Base thickness(Y)
    const G4double BASETOTALLENGTHZ = 1 *mm; //Base length(Z)
	
// Target-------------------------------------------------------
    const G4double TargetWIDTHX = 500 *um;//Target width(X)
    const G4double TargetTHICKNESSY = 5.0 *um;//Target thickness(Y)
    const G4double TargetTOTALLENGTHZ = 500*um; //Target length(Z)

		
// Flux and Energy spectrum Detector Parameters -----------------------------------------
	const G4double DETECTOR_RMIN = 0. *um;
    const G4double DETECTOR_RMAX = 1.0 *mm;
	const G4double DETECTOR_HZ = 0.001 *mm;
    const G4double RPOSITION = 0.105*cm;
    const G4double DETECTORSTARTALANGLE = -90;//能谱探测器放置角度,-90°在Y轴负方向上,0°在Z轴正方向上,+90°在Y轴正方向上

	
// Other Parameters -----------------------------------------
    const G4double KVP=120;//simulation voltage

// Root filename
    const G4String RootFileName="120keV-5um";

