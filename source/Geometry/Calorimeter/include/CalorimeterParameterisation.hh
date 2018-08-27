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
/// \file parallel/ParN02/include/ExN02ChamberParameterisation.hh
/// \brief Definition of the ExN02ChamberParameterisation class
//
//
// $Id: ExN02ChamberParameterisation.hh 73400 2013-08-27 09:52:57Z gcosmo $
//
//
//  A parameterisation that describes a series of boxes along Z
//    The boxes have equal width, & their lengths are a linear equation.
//    They are spaced an equal distance apart, starting from given location.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef CalorimeterParameterisation_H
#define CalorimeterParameterisation_H 1
 
   #include "globals.hh"
   #include "G4VPVParameterisation.hh"
   
   class G4VPhysicalVolume;
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
   
   class CalorimeterParameterisation : public G4VPVParameterisation
   { 
     public:
     
       CalorimeterParameterisation(G4int    NoScinPlanes, 
                                    G4double startZ, 
                                    G4double spacing,
                                    G4double widthScinPlane);
   
       virtual 
      ~CalorimeterParameterisation();
      
       void ComputeTransformation (const G4int copyNo,
                                   G4VPhysicalVolume* physVol) const;

   private:
 
      G4int    fNoScinPlanes;   
      G4double fStartZ;
      G4double fHalfWidth;    //  The half-width of each tracker chamber
      G4double fSpacing;      //  The distance between the chambers' center
 };
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#endif
