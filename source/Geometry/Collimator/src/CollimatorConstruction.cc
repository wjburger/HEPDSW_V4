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
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CollimatorConstruction.hh"
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

CollimatorConstruction::CollimatorConstruction()
  :fSolidColl1(0),fSolidColl2(0), fLogicColl1(0), fLogicColl2(0), fPhysiColl1(0), fPhysiColl2(0)
{
  pMaterial     = new HEPDSWMaterial();

  fRmin1Coll=16.4*mm;
  fRmaxColl=23.*mm;
  fRmin2Coll=3.*mm;
  fHeigth1Coll=280.*mm;
  fHeigth2Coll=5.*mm;
  fStartColl=0.*deg;
  fStopColl=360.*deg;
  

  fPlane_X = 40.*cm; //check correct number
  fPlane_Y = 40.*cm; //check correct number
  fPlane_Z = 5.1*cm;
  fStartPlane_hol = 0.*deg;
  fStopPlane_hol = 360.*deg;
  
  ComputeObjectsPositioning();
  
  // materials
  collimatorMaterial = "brass";
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CollimatorConstruction::~CollimatorConstruction()
{
  if (pMaterial) delete pMaterial;
}

void CollimatorConstruction::ComputeObjectsPositioning(){

  fPhysiCollimator_Z = 0*mm;

}

void CollimatorConstruction::SetCollimatorMaterial(G4String aMat){
  collimatorMaterial=aMat; 
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
void CollimatorConstruction::Builder(G4VPhysicalVolume* motherVolume)
{
  
  pMaterial->DefineMaterials();

  G4Material* Cu = new G4Material("Copper",29.,63.550*g/mole,8.96*g/cm3);
  G4Material* Zn = new G4Material("Zinc",30.,65.409*g/mole,7.14*g/cm3);
  G4Material* brass= new G4Material("brass",8.5*g/cm3, 2);
  brass->AddMaterial(Cu,70*perCent);
  brass->AddMaterial(Zn,30*perCent);

  G4Material* C = new G4Material("Carbon",6.,12.01*g/mole,2.267*g/cm3);
  
  fSolidColl1 = new G4Tubs("fSolidColl1",fRmin1Coll,fRmaxColl,fHeigth1Coll/2.,fStartColl,fStopColl);
  fSolidColl2 = new G4Tubs("fSolidColl2",fRmin2Coll,fRmaxColl,fHeigth2Coll/2.,fStartColl,fStopColl);
  fLogicColl1 = new G4LogicalVolume(fSolidColl1,brass,"fLogicColl1");
  fLogicColl2 = new G4LogicalVolume(fSolidColl2,brass,"fLogicColl2");
  fPhysiColl1 = new G4PVPlacement(0,G4ThreeVector(-1.75*cm,-1.8*cm,76.45*cm),"fPhysiColl1",fLogicColl1,motherVolume,false,0,true); //3C position
  fPhysiColl2 = new G4PVPlacement(0,G4ThreeVector(-1.75*cm,-1.8*cm,62.2*cm),"fPhysiColl2",fLogicColl2,motherVolume,false,0,true); //3C position
  
  fSolidPlane_tot = new G4Box("fSolidPlane_tot",fPlane_X/2.,fPlane_Y/2.,fPlane_Z/2.);
  fSolidPlane_hol = new G4Tubs("fSolidPlane_hol",0.,fRmaxColl,fPlane_Z/2.,fStartPlane_hol,fStopPlane_hol);
  fSolidPlane = new G4SubtractionSolid("fSolidPlane",fSolidPlane_tot,fSolidPlane_hol,0,G4ThreeVector(0,0,0));
  fLogicPlane = new G4LogicalVolume(fSolidPlane,C,"fLogicPlane"); //check correct material
  fPhysiPlane = new G4PVPlacement(0,G4ThreeVector(-1.75*cm,-1.8*cm,86.15*cm),"fPhysiPlane",fLogicPlane,motherVolume,false,0,true);

  

  G4VisAttributes * attBrown = new G4VisAttributes(G4Colour::Brown());
  attBrown->SetVisibility(true);
  attBrown->SetForceAuxEdgeVisible(true);
  fLogicColl1->SetVisAttributes(attBrown);
  fLogicColl2->SetVisAttributes(attBrown);

  G4VisAttributes * attGrey = new G4VisAttributes(G4Colour::Grey());
  attGrey->SetVisibility(true);
  attGrey->SetForceAuxEdgeVisible(true);
  fLogicPlane->SetVisAttributes(attGrey);
  


}


