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

#ifndef CollimatorConstruction_h
#define CollimatorConstruction_h 1

#include "globals.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"



class G4IntersectionSolid;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class HEPDSWMaterial;
class G4UniformMagField;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CollimatorConstruction 
{
public:
  
  CollimatorConstruction();
  ~CollimatorConstruction();
  
  void SetCollimatorMaterial(G4String aMat);

  void Builder(G4VPhysicalVolume* motherVolume);
  
private:

  void ComputeObjectsPositioning();

  G4String boxMaterial;
  G4String collimatorMaterial;

  G4double fBox_X;
  G4double fBox_Y;
  G4double fBox_Z;

  G4double fRmin1Coll;
  G4double fRmaxColl;
  G4double fRmin2Coll;
  G4double fHeigth1Coll;
  G4double fHeigth2Coll;
  G4double fStartColl;
  G4double fStopColl;

  G4double fPlane_X;
  G4double fPlane_Y;
  G4double fPlane_Z;
  G4double fStartPlane_hol;
  G4double fStopPlane_hol;

  
  G4double fPhysiCollimator_Z;

  HEPDSWMaterial*  pMaterial;

  G4Tubs* fSolidColl1;
  G4Tubs* fSolidColl2;
  G4Box*  fSolidPlane_tot;
  G4Tubs* fSolidPlane_hol;
  G4SubtractionSolid*  fSolidPlane;

  G4LogicalVolume* fLogicColl1;
  G4LogicalVolume* fLogicColl2;
  G4LogicalVolume* fLogicPlane;

  G4VPhysicalVolume* fPhysiColl1;
  G4VPhysicalVolume* fPhysiColl2;
  G4VPhysicalVolume* fPhysiPlane;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif














				
				
				
