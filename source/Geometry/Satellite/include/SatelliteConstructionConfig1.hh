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
/// \file electromagnetic/TestEm3/include/SatelliteConstructionConfig1.hh
/// \brief Definition of the SatelliteConstructionConfig1 class
//
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SatelliteConstructionConfig1_h
#define SatelliteConstructionConfig1_h 1

#include "globals.hh"
#include <vector>

class G4Box;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class HEPDSWMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SatelliteConstructionConfig1
{
public:
  
  SatelliteConstructionConfig1();
  ~SatelliteConstructionConfig1();

  void SetBlanketMaterial(G4String aMat);
  void SetWallMaterial(G4String aMat);

  void Builder(G4VPhysicalVolume* motherVolume);

private:
  void ComputeObjectsPositioning();

  G4String blanket1Material;
  G4String blanket2Material;
  G4String wallMaterial;

  G4double fBlanket_X;
  G4double fBlanket_Y;
  G4double fBlanket_Z;

  G4double fWall_X;
  G4double fWall_Y;
  G4double fWall_Z;

  G4double fWallHole_X;
  G4double fWallHole_Y;
  G4double fWallHole_Z;

  G4double transWallHole_X;
  G4double transWallHole_Y;

  G4double fPhysiBlanket_Z;

  G4double fPhysiWall_X;
  G4double fPhysiWall_Y;
  G4double fPhysiWall_Z;

  HEPDSWMaterial*  pMaterial;

  G4Box* fSolidBlanket;
  G4SubtractionSolid* fSolidWall;
  G4Box* fSolidLatWall;
  G4Box* fSolidUpWall;

  G4LogicalVolume* fLogicBlanket1;
  G4LogicalVolume* fLogicBlanket2;
  G4LogicalVolume* fLogicWall;
  G4LogicalVolume* fLogicLatWall;
  G4LogicalVolume* fLogicUpWall;

  G4VPhysicalVolume* fPhysiBlanket1;
  G4VPhysicalVolume* fPhysiBlanket2;
  G4VPhysicalVolume* fPhysiWall;
  G4VPhysicalVolume* fPhysiLatWall;
  G4VPhysicalVolume* fPhysiUpWall;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

