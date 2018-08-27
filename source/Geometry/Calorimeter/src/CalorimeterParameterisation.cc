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
///
// \file parallel/ParN02/src/ExN02ChamberParameterisation.cc
/// \brief Implementation of the ExN02ChamberParameterisation class
//
//
// $Id: ExN02ChamberParameterisation.cc 66241 2012-12-13 18:34:42Z gunter $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
   #include "CalorimeterParameterisation.hh"
 
   #include "G4VPhysicalVolume.hh"
   #include "G4ThreeVector.hh"
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
   
   CalorimeterParameterisation::CalorimeterParameterisation(  
    G4int NoScinPlanes, 
    G4double startZ,          //  Z of center of first 
    G4double spacingZ,        //  Z spacing of centers
    G4double widthScinPlane)
   {
      fNoScinPlanes = NoScinPlanes; 
      fStartZ     =  startZ; 
      fHalfWidth  =  widthScinPlane*0.5;
      fSpacing    =  spacingZ;
      if( NoScinPlanes > 0 ){
         if (spacingZ < widthScinPlane) {
          G4Exception("CalorimeterParameterisation::HEPDCalorimeterParameterisation()",
                      "InvalidSetup", FatalException,
                      "Width>Spacing");
         }
      }
    
   }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
   CalorimeterParameterisation::~CalorimeterParameterisation()
   {}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
   
   void CalorimeterParameterisation::ComputeTransformation
   (const G4int copyNo, G4VPhysicalVolume* physVol) const
   {
   G4double      Zposition= fStartZ + (copyNo+1) * fSpacing;
   G4ThreeVector origin(0,0,Zposition);
   physVol->SetTranslation(origin);
   physVol->SetRotation(0);
   } 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
