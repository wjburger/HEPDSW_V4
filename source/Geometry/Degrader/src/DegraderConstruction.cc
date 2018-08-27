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
//          W.J. Burger : william.burger@tifpa.infn.it
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DegraderConstruction.hh"
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
#include "DegraderSD.hh"

#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DegraderConstruction::DegraderConstruction()
  :fSolidDegrader(0), fLogicDegrader(0), fPhysiDegrader(0)
{
  pMaterial     = new HEPDSWMaterial();
  fDegrader_X  = 15.0*cm;
  fDegrader_Y  = 15.0*cm;
  fDegrader_Z  = 2.5*cm;  // two alternatives: 1.6 cm (51 MeV), 2.5 cm (37 MeV)

  ComputeObjectsPositioning();
  
  // materials
  degraderMaterial        = "Water_Solid";
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DegraderConstruction::~DegraderConstruction()
{
  if (pMaterial) delete pMaterial;
}

void DegraderConstruction::ComputeObjectsPositioning(){

  fPhysiDegrader_Z = 0*mm;

}

void DegraderConstruction::SetDegraderMaterial(G4String aMat){
  degraderMaterial=aMat; 
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
void DegraderConstruction::Builder(G4VPhysicalVolume* motherVolume, G4double pos_Z, G4double dz)
{
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String degraderSDname = "/hepd/degrader";
  DegraderSD* degraderSD = new DegraderSD(degraderSDname);
  SDman->AddNewDetector(degraderSD);
  G4SDStructure* sdtree = SDman->GetTreeTop();
  sdtree->ListTree();

  pMaterial->DefineMaterials();
  G4cout << " ici 1" << G4endl;
  G4Material* degraderMat = pMaterial->GetMaterial(degraderMaterial);
  G4cout << " ici 2" << G4endl;

  G4RotationMatrix* myRot = new G4RotationMatrix;
  fDegrader_Z = dz; 
  G4cout << " ici 3 fDegrader_Z "<< fDegrader_Z << "mm" << G4endl;

  fSolidDegrader = new G4Box("fSolidDegrader",fDegrader_X/2.,fDegrader_Y/2.,fDegrader_Z/2);  
  G4cout << " ici 4" << G4endl;

  fLogicDegrader = new G4LogicalVolume(fSolidDegrader,degraderMat,"fLogicDegrader");
  fLogicDegrader->SetSensitiveDetector(degraderSD);
  G4cout << " ici 5" << G4endl;

  fPhysiDegrader_Z = pos_Z - fDegrader_Z/2 - 1*cm;

  G4cout << "zpos degrader cm " << fPhysiDegrader_Z/cm << G4endl;

  fPhysiDegrader = new G4PVPlacement(0,
				    G4ThreeVector(0,0,fPhysiDegrader_Z),
				    "Degrader",
				    fLogicDegrader,
				    motherVolume,
				    false,0,true);

  //Visualization Attribute
  

  G4VisAttributes* attGreen = new G4VisAttributes(G4Colour::Green());
  attGreen->SetVisibility(true);
  attGreen->SetForceAuxEdgeVisible(true);
  fLogicDegrader->SetVisAttributes(attGreen);


}


