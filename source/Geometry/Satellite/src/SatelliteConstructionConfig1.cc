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
//          Filippo Ambroglini : filippo.ambroglini@pg.infn.it
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SatelliteConstructionConfig1.hh"


#include "G4NistManager.hh"
#include "HEPDSWMaterial.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SatelliteConstructionConfig1::SatelliteConstructionConfig1()
  :fSolidBlanket(0),fSolidWall(0),fSolidLatWall(0),fSolidUpWall(0),
   fLogicBlanket1(0),fLogicBlanket2(0),fLogicWall(0),fLogicLatWall(0),fLogicUpWall(0),
   fPhysiBlanket1(0),fPhysiBlanket2(0),fPhysiWall(0),fPhysiLatWall(0),fPhysiUpWall(0)
{
  pMaterial     = new HEPDSWMaterial();
  fBlanket_X  = 254*mm;
  fBlanket_Y  = 238*mm;
  fBlanket_Z  = 0.075*mm;

  fWall_X = 345*mm;
  fWall_Y = 490*mm;
  fWall_Z = 3.5*mm;

  fWallHole_X = 237*mm;
  fWallHole_Y = 218*mm;
  fWallHole_Z = 4*mm;


  ComputeObjectsPositioning();
  
  // materials
  blanket1Material        = "mylar";
  blanket2Material        = "Kapton";
  wallMaterial           = "Aluminium";
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SatelliteConstructionConfig1::~SatelliteConstructionConfig1()
{
  if (pMaterial) delete pMaterial;
}

void SatelliteConstructionConfig1::ComputeObjectsPositioning(){

  transWallHole_X = fWall_X/2.-fWallHole_X/2.-68.5*mm;
  transWallHole_Y = fWall_Y/2.-fWallHole_Y/2.-44*mm;

  fPhysiBlanket_Z = 386.57*mm;

  fPhysiWall_X = +14.5*mm;
  fPhysiWall_Y = -92*mm;
  fPhysiWall_Z = fPhysiBlanket_Z+fBlanket_Z/2.+fWall_Z/2.;

}


void SatelliteConstructionConfig1::SetBlanketMaterial(G4String aMat){
  blanket1Material=aMat; 
}    
void SatelliteConstructionConfig1::SetWallMaterial(G4String aMat){
  wallMaterial=aMat; 
}    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
void SatelliteConstructionConfig1::Builder(G4VPhysicalVolume* motherVolume)
{

  pMaterial->DefineMaterials();
  G4Material* blanket1Mat = pMaterial->GetMaterial(blanket1Material);
  G4Material* blanket2Mat = pMaterial->GetMaterial(blanket2Material);
  G4Material* wallMat = pMaterial->GetMaterial(wallMaterial);

  G4RotationMatrix* myRot = new G4RotationMatrix;

  fSolidBlanket = new G4Box("fSolidThermalBlanket",fBlanket_X/2.,fBlanket_Y/2.,fBlanket_Z/2);

  G4ThreeVector transWallHole(transWallHole_X,transWallHole_Y,0);
  fSolidWall = new G4SubtractionSolid("fSolidWall",
				      new G4Box("Wall",fWall_X/2.,fWall_Y/2.,fWall_Z/2.*mm),
					      new G4Box("WallHole",fWallHole_X/2.,fWallHole_Y/2.,fWallHole_Z/2.),
					      myRot,transWallHole);
  fSolidLatWall = new G4Box("fSolidLatWall", fWall_X/2., 2./2.*mm, 400./2.*mm);
  fSolidUpWall = new G4Box("fSolidUpWall", fWall_X/2., 3.1/2.*cm, fWall_Z/2.*mm);

  fLogicBlanket1 = new G4LogicalVolume(fSolidBlanket,blanket1Mat,"fLogicThermalBlanket1");
  fLogicBlanket2 = new G4LogicalVolume(fSolidBlanket,blanket2Mat,"fLogicThermalBlanket2");
  fLogicWall = new G4LogicalVolume(fSolidWall,wallMat,"fLogicWall");
  fLogicLatWall = new G4LogicalVolume(fSolidLatWall, wallMat, "fLogicLatWall");
  fLogicUpWall = new G4LogicalVolume(fSolidUpWall, wallMat, "fLogicUpWall");

  G4double suppLYSO_offset = 5.*mm;
  
  fPhysiBlanket1 = new G4PVPlacement(0,
				    G4ThreeVector(0,0,fPhysiBlanket_Z + fWall_Z + 2.*fBlanket_Z+suppLYSO_offset),
				    "SatelliteThermalBlanket1",
				    fLogicBlanket1,
				    motherVolume,
				    false,0,true);

  fPhysiBlanket2 = new G4PVPlacement(0,
				    G4ThreeVector(0,0,fPhysiBlanket_Z + fBlanket_Z + fWall_Z+suppLYSO_offset),
				    "SatelliteThermalBlanket2",
				    fLogicBlanket2,
				    motherVolume,
				    false,0,true);

  fPhysiWall = new G4PVPlacement(0,
				 G4ThreeVector(fPhysiWall_X,fPhysiWall_Y,fPhysiWall_Z+suppLYSO_offset),
				 "SatelliteWall",
				 fLogicWall,
				 motherVolume,
				 false,0,true);

  fPhysiLatWall = new G4PVPlacement(0,
				    G4ThreeVector(1.45*cm,18.5*cm, 19.*cm+suppLYSO_offset),
				 "SatelliteLatWall",
				 fLogicLatWall,
				 motherVolume,
				 false,0,true);

  fPhysiUpWall = new G4PVPlacement(0,
				    G4ThreeVector(1.45*cm,16.85*cm, fPhysiWall_Z+suppLYSO_offset),
				 "SatelliteUpWall",
				 fLogicUpWall,
				 motherVolume,
				 false,0,true);
  					       


  //Visualization Attribute

  G4VisAttributes* attGray = new G4VisAttributes(G4Colour::Gray());
  attGray->SetVisibility(true);
  attGray->SetForceAuxEdgeVisible(true);
  fLogicWall->SetVisAttributes(attGray);
  fLogicLatWall->SetVisAttributes(attGray);
  fLogicUpWall->SetVisAttributes(attGray);

  G4VisAttributes* attYellow = new G4VisAttributes(G4Colour::Yellow());
  attYellow->SetVisibility(true);
  attYellow->SetForceAuxEdgeVisible(true);
  fLogicBlanket1->SetVisAttributes(attYellow);
  fLogicBlanket2->SetVisAttributes(attYellow);


}


