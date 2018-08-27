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
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HEPDSWPrimaryGeneratorAction_h
#define HEPDSWPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "Rtypes.h"
#include "TF1.h"
#include "TMath.h"

class G4Event;
class HEPDSWDetectorConstruction;
class HEPDSWPrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HEPDSWPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  HEPDSWPrimaryGeneratorAction(HEPDSWDetectorConstruction*);
  ~HEPDSWPrimaryGeneratorAction();

public:
  void SetDefaultKinematic();
  void SetParticle(G4String part);
  void SetEnergy(G4double ene);
  void SetSpot();
  void SetBeam(G4double Xpos,G4double Ypos,G4double theta);
  void SetBeamEReso(G4double ereso);
  void SetPowerLaw(G4double aEmin,G4double aEmax,G4double aGamma);
  void SetFlat(G4double aEmin,G4double aEmax);
  void SetMuonGeneration(G4double adX, G4double adY, G4double aEmin, G4double aEmax);

  inline void SetRandomPosition() { random = true;}
  inline void SetDirectionToCenter() { centerpointing = true;}

  virtual
  void GeneratePrimaries(G4Event*);
  G4ParticleGun* GetParticleGun() {return fParticleGun;};

private:
  G4double SpectrumPowerLaw(G4double Emin,G4double Emax, G4double gamma);
  G4double FlatSpectrum(G4double Emin,G4double Emax);

  G4ThreeVector          position;
  G4ThreeVector          direction;
  G4ParticleGun*         fParticleGun;
  HEPDSWDetectorConstruction*  fDetector;
  G4bool                 muon;
  G4bool                 random;
  G4bool                 nuclei_beam;
  G4bool                 centerpointing;
  G4bool                 beam;
  G4bool                 beam_reso;
  G4bool                 powerlaw;
  G4bool                 flat;

  G4double eminPL,emaxPL,gammaPL;
  G4double eminFlat,emaxFlat;

  G4double xrange_Muon_gen,yrange_Muon_gen,emin_Muon,emax_Muon;

  Double_t costhe_par[3];
  TF1 *fun_mu_costhe;
  TF1 *fun_mu_ke;

  G4double               beam_energy;
  G4double               beam_ereso;

  HEPDSWPrimaryGeneratorMessenger* fGunMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


