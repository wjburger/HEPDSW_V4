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
/// \file electromagnetic/TestEm3/src/HEPDSWPrimaryGeneratorAction.cc
/// \brief Implementation of the HEPDSWPrimaryGeneratorAction class
//
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HEPDSWPrimaryGeneratorAction.hh"

#include "HEPDSWPrimaryGeneratorMessenger.hh"
#include "HEPDSWDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

Double_t Muon_Flux(Double_t *x, Double_t *par) {

   // theta angle depuis zenith a terre
   // ce_muon energie cinetique du muon (GeV)
   //  printf("theta %5.2lf\n",par[0]);

  Double_t ce_muon = x[0];

  //  printf("ce_muon %5.2lf\n",ce_muon);

  Double_t costheta = par[0];

  Double_t ppar[5] = { 0.102573, -0.068287, 0.958633, 0.0407253, 0.817285 };
  
  Double_t arg = costheta*costheta + ppar[0]*ppar[0] + ppar[1]*TMath::Power(costheta,ppar[2])+ ppar[3]*TMath::Power(costheta,ppar[4]);
  arg /= (1 + ppar[0]*ppar[0] + ppar[1]*ppar[1] + ppar[3]*ppar[3]);

  Double_t costheta_prod = TMath::Sqrt(arg);

  Double_t arg1 = ce_muon*(1 + (3.64/(ce_muon*TMath::Power(costheta_prod,1.29))));
  arg1 = 0.14*TMath::Power(arg1,-2.7);

  Double_t arg2 = ( (1/(1+((1.1*ce_muon*costheta_prod)/115))) + (0.054/(1+((1.1*ce_muon*costheta_prod)/850))) );

  Double_t dIdE = arg1*arg2;

  return(dIdE);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPrimaryGeneratorAction::HEPDSWPrimaryGeneratorAction(HEPDSWDetectorConstruction* det)
  :position(0),direction(0),fDetector(det)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  SetDefaultKinematic();

  costhe_par[0] = 0.000655538;
  costhe_par[1] = -0.00281641;
  costhe_par[2] = 0.0109114;
  fun_mu_costhe = new TF1("mu_ang","pol2",0.7,1.);
  fun_mu_costhe->SetParameter(0,costhe_par[0]);
  fun_mu_costhe->SetParameter(1,costhe_par[1]);
  fun_mu_costhe->SetParameter(2,costhe_par[2]);

  xrange_Muon_gen = 0;
  yrange_Muon_gen = 0; 
  emin_Muon = 0.05;
  emax_Muon = 1000;  

  //  fun_mu_ke = new TF1("muflux",&HEPDSWPrimaryGeneratorAction::Muon_Flux,0.05,1000,1);

  muon= false;
  random=false;
  beam=false;
  beam_reso=false;
  nuclei_beam=false;
  centerpointing=false;
  powerlaw = false;
  flat=false;
  //create a messenger for this class
  fGunMessenger = new HEPDSWPrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPrimaryGeneratorAction::~HEPDSWPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPrimaryGeneratorAction::SetDefaultKinematic()
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  fParticleGun->SetParticleEnergy(1.*GeV);
  G4double zposition = 0.5*(fDetector->GetWorldSizeZ());
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm, zposition));
}

void HEPDSWPrimaryGeneratorAction::SetEnergy(G4double ene)
{
  beam_energy = ene;
  fParticleGun->SetParticleEnergy(ene);
}

void HEPDSWPrimaryGeneratorAction::SetBeamEReso(G4double ereso){
  //  G4cout << "set beam reso " << G4endl;
  beam_reso = true;
  beam_ereso = ereso;
}

void HEPDSWPrimaryGeneratorAction::SetParticle(G4String part)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = part;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
}

void HEPDSWPrimaryGeneratorAction::SetBeam(G4double Xpos,G4double Ypos,G4double theta){
  beam=true;
  position = G4ThreeVector(Xpos,Ypos,0.5*(fDetector->GetWorldSizeZ()));
  G4double phi = 0;
  direction = G4ThreeVector(cos(phi)*sin(theta),sin(phi)*sin(theta),-cos(theta));

}


//for nuclei test beam
void HEPDSWPrimaryGeneratorAction::SetSpot(){nuclei_beam=true;}


void HEPDSWPrimaryGeneratorAction::SetMuonGeneration(G4double dX,G4double dY, G4double Emin, G4double Emax){
  muon=true;
  xrange_Muon_gen = dX;
  yrange_Muon_gen = dY;
  emin_Muon = Emin;
  emax_Muon = Emax; 
  fun_mu_ke = new TF1("muflux",Muon_Flux,((Double_t) emin_Muon/1000),((Double_t) emax_Muon/1000),1);
  fun_mu_ke->SetNpx(1000);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "mu+";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
}

void HEPDSWPrimaryGeneratorAction::SetPowerLaw(G4double aEmin,G4double aEmax,G4double aGamma){
  powerlaw = true;
  eminPL = aEmin;
  emaxPL = aEmax;
  gammaPL = aGamma;
}

void HEPDSWPrimaryGeneratorAction::SetFlat(G4double aEmin,G4double aEmax){
  flat = true;
  eminFlat = aEmin;
  emaxFlat = aEmax;
  G4cout << " flat " << " emin " << eminFlat << " emax " << emaxFlat << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  //
  //randomize the beam, if requested.
  if(random){
    G4double phi = 2*CLHEP::pi*G4RandFlat::shoot();
    G4double theta = std::sqrt(G4RandFlat::shoot());
    theta = std::acos(theta);
    G4double Xmax = 0.5*(fDetector->GetWorldSizeX());
    G4double Ymax = 0.5*(fDetector->GetWorldSizeY());
    G4double Zmax = 0.5*(fDetector->GetWorldSizeZ());
    //    G4cout << "xmax " << Xmax << " ymax " << Ymax << " theta " << theta << " cos theta " << atheta << " cos theta " << cos(theta) << G4endl;
    position = G4ThreeVector(-Xmax+2*Xmax*G4RandFlat::shoot(),-Ymax+2*Ymax*G4RandFlat::shoot(),Zmax);
    if(powerlaw)
      fParticleGun->SetParticleEnergy(SpectrumPowerLaw(eminPL,emaxPL,gammaPL));
    if(flat)
      fParticleGun->SetParticleEnergy(FlatSpectrum(eminFlat,emaxFlat));
    if(centerpointing)
      direction = -1*position;
    else
      direction = G4ThreeVector(cos(phi)*sin(theta),sin(phi)*sin(theta),-cos(theta));
    fParticleGun->SetParticlePosition(position);
    fParticleGun->SetParticleMomentumDirection(direction.unit());
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  else if(beam){
    G4String particleName;
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    const G4String& nome = particle->GetParticleName();
    G4double masse = particle->GetPDGMass(); 
    G4double charge = particle->GetPDGCharge();
    //G4cout << nome << " masse " << masse << " charge " << charge << G4endl;
    fParticleGun->SetParticlePosition(position);
    if(flat)
      fParticleGun->SetParticleEnergy(FlatSpectrum(eminFlat,emaxFlat));
    if (beam_reso) {
      G4double new_beam_energy = G4RandGauss::shoot(beam_energy,beam_ereso);
      G4double denergy = new_beam_energy - beam_energy;
      printf("beam energy %6.2lf MeV de %6.2lf MeV\n",beam_energy,denergy);
      fParticleGun->SetParticleEnergy(new_beam_energy);
    }
    fParticleGun->SetParticleMomentumDirection(direction.unit());
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  else if(nuclei_beam){
    G4String particleName;
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    const G4String& nome = particle->GetParticleName();
    G4double masse = particle->GetPDGMass();
    G4double charge = particle->GetPDGCharge();
    //G4cout << nome << " masse " << masse << " charge " << charge << G4endl;
    G4double Xmax = 2.*cm;
    G4double Ymax = 2.*cm;
    G4double Xpos = 999.*cm;
    G4double Ypos = 999.*cm;
    Xpos = -Xmax+2.*Xmax*G4RandFlat::shoot();
    Ypos = -Ymax+2.*Ymax*G4RandFlat::shoot();
    while (sqrt(pow(Xpos,2)+pow(Ypos,2))>2.*cm){
      Xpos = -Xmax+2.*Xmax*G4RandFlat::shoot();
      Ypos = -Ymax+2.*Ymax*G4RandFlat::shoot();
    }
    G4double Zpos = 196.*cm;
    Xpos-=1.75*cm;
    Ypos-=1.8*cm;
    position = G4ThreeVector(Xpos,Ypos,Zpos);
    G4double theta = 0.*deg;
    G4double phi = 0.*deg;
    direction = G4ThreeVector(cos(phi)*sin(theta),sin(phi)*sin(theta),-cos(theta));
    
    fParticleGun->SetParticlePosition(position);
    if(flat)
      fParticleGun->SetParticleEnergy(FlatSpectrum(eminFlat,emaxFlat));
    if (beam_reso) {
      G4double new_beam_energy = G4RandGauss::shoot(beam_energy,beam_ereso);
      G4double denergy = new_beam_energy - beam_energy;
      printf("beam energy %6.2lf MeV de %6.2lf MeV\n",beam_energy,denergy);
      fParticleGun->SetParticleEnergy(new_beam_energy);
    }
    fParticleGun->SetParticleMomentumDirection(direction.unit());
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }


  else{
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }

  if(muon){
    G4double phi = 2*CLHEP::pi*G4RandFlat::shoot();
    Double_t cosang = fun_mu_costhe->GetRandom(0.65,1.00);
    G4double theta = ((G4double) TMath::ACos(cosang));
    G4double Xmax = 0.5*(xrange_Muon_gen);
    G4double Ymax = 0.5*(yrange_Muon_gen);
    G4double Zmax = 0.5*(fDetector->GetWorldSizeZ());
    position = G4ThreeVector(-Xmax+2*Xmax*G4RandFlat::shoot(),-Ymax+2*Ymax*G4RandFlat::shoot(),Zmax);
    fun_mu_ke->SetParameter(0,cosang);
    G4double ke = ((G4double) fun_mu_ke->GetRandom());
    ke *= 1000; // GeV -> MeV
    fParticleGun->SetParticleEnergy(ke);
    if(centerpointing)
      direction = -1*position;
    else
      direction = G4ThreeVector(cos(phi)*sin(theta),sin(phi)*sin(theta),-cos(theta));
    fParticleGun->SetParticlePosition(position);
    fParticleGun->SetParticleMomentumDirection(direction.unit());
    fParticleGun->GeneratePrimaryVertex(anEvent);
    G4cout << "ev " << anEvent->GetEventID() << " x " << position.x() << " y " << position.y() << " z " << position.z() << " ke " << ke << " dir x " << direction.x() << " dir y " << direction.y() << " dir z " << direction.z() << G4endl; 
  }
  
}

G4double HEPDSWPrimaryGeneratorAction::SpectrumPowerLaw(G4double Emin,G4double Emax, G4double gamma){
  G4double energy;
  if(gamma == 0.){
    energy = CLHEP::RandFlat::shoot(Emin, Emax);
    return energy;
  }
  G4double alpha = 1. + gamma; //integral spectral index
  if (alpha == 0.) {
    energy = exp(log(Emin) + CLHEP::RandFlat::shoot(0., 1.) * (log(Emax) - log(Emin)));
  }
  else {
    if (Emin == 0.)
      Emin = 1.E-10;
    energy = pow((CLHEP::RandFlat::shoot(0., 1.) * (pow(Emax, alpha) - pow(Emin, alpha)) + pow(Emin, alpha)),1./alpha);
  }
  return energy;

}

G4double HEPDSWPrimaryGeneratorAction::FlatSpectrum(G4double Emin,G4double Emax)
{
  G4double energy;
  energy = CLHEP::RandFlat::shoot(Emin, Emax);
  G4cout << " energie " << energy << G4endl;
  return energy;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

