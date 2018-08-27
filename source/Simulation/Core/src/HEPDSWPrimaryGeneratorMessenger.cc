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
/// \file electromagnetic/TestEm3/src/HEPDSWPrimaryGeneratorMessenger.cc
/// \brief Implementation of the HEPDSWPrimaryGeneratorMessenger class
//
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HEPDSWPrimaryGeneratorMessenger.hh"

#include "HEPDSWPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPrimaryGeneratorMessenger::HEPDSWPrimaryGeneratorMessenger(HEPDSWPrimaryGeneratorAction* Gun):fAction(Gun)
{
  fGunDir = new G4UIdirectory("/hepd/gun/");
  fGunDir->SetGuidance("gun control");
   
  fDefaultCmd = new G4UIcmdWithoutParameter("/hepd/gun/setDefault",this);
  fDefaultCmd->SetGuidance("set/reset kinematic defined in PrimaryGenerator");
  fDefaultCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fRndmCmd = new G4UIcmdWithoutParameter("/hepd/gun/random",this);
  fRndmCmd->SetGuidance("random position of initial point");
  fRndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPntngCmd = new G4UIcmdWithoutParameter("/hepd/gun/toCenter",this);
  fPntngCmd->SetGuidance("direction of particle always pointing to center");
  fPntngCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //for nuclei test beam
  fSpotCmd = new G4UIcmdWithoutParameter("/hepd/gun/spot",this);
  fSpotCmd->SetGuidance("enable or disable the beam spot");
  fSpotCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fEnrgCmd = new G4UIcmdWithADoubleAndUnit("/hepd/gun/energy",this);
  fEnrgCmd->SetGuidance("Set the energy of the particle");
  fEnrgCmd->SetParameterName("Energy",false);
  fEnrgCmd->SetUnitCategory("Energy");
  fEnrgCmd->AvailableForStates(G4State_Idle);  

  fPartCmd = new G4UIcmdWithAString("/hepd/gun/particle",this);
  fPartCmd->SetGuidance("Set the particle type");
  fPartCmd->SetParameterName("Particle Type",false);
  fPartCmd->AvailableForStates(G4State_Idle);  

  G4UIparameter* param;

  fBeamCmd = new G4UIcommand("/hepd/gun/beam",this);
  fBeamCmd->AvailableForStates(G4State_Idle);  
  param = new G4UIparameter("X",'d',false);
  param->SetGuidance("X position");
  fBeamCmd->SetParameter(param);
  param = new G4UIparameter("Y",'d',false);
  param->SetGuidance("Y position");
  fBeamCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("length unit");
  fBeamCmd->SetParameter(param);
  param = new G4UIparameter("Theta",'d',false);
  param->SetGuidance("Theta angle");
  fBeamCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("angle unit");
  fBeamCmd->SetParameter(param);

  fTBeamCmd = new G4UIcommand("/hepd/gun/tbeam",this);
  fTBeamCmd->AvailableForStates(G4State_Idle);  
  param = new G4UIparameter("position",'s',false);
  param->SetGuidance("beam position A1 - D6");
  fTBeamCmd->SetParameter(param);
  param = new G4UIparameter("Theta",'d',false);
  param->SetGuidance("Theta angle");
  fTBeamCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("angle unit");
  fTBeamCmd->SetParameter(param);

  //fBeamEResoCmd = new G4UIcommand("/hepd/gun/ereso",this);
  //fBeamEResoCmd->SetGuidance("Set energy resolution ERESO (percent)");
  //fBeamEResoCmd->AvailableForStates(G4State_Idle);  
  //param = new G4UIparameter("EResolution %",'d',false);
  //param->SetGuidance("beam energy resolution");
  //fBeamEResoCmd->SetParameter(param);
  fBeamEResoCmd = new G4UIcmdWithADoubleAndUnit("/hepd/gun/ereso",this);
  fBeamEResoCmd->SetGuidance("Set energy resolution DeltaE (MeV)");
  fBeamEResoCmd->SetParameterName("Energy",false);
  fBeamEResoCmd->SetUnitCategory("Energy");
  fBeamEResoCmd->AvailableForStates(G4State_Idle);
  

  fMuonCmd = new G4UIcommand("/hepd/gun/muon",this);
  fMuonCmd->AvailableForStates(G4State_Idle);  
  param = new G4UIparameter("dX",'d',false);
  param->SetGuidance("dX half-range for X gen");
  fMuonCmd->SetParameter(param);
  param = new G4UIparameter("dY",'d',false);
  param->SetGuidance("dY half-range for Y gen");
  fMuonCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("length unit");
  fMuonCmd->SetParameter(param);
  param = new G4UIparameter("keMin",'d',false);
  param->SetGuidance("min ke generated");
  fMuonCmd->SetParameter(param);
  param = new G4UIparameter("keMax",'d',false);
  param->SetGuidance("max ke generated");
  fMuonCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("energy unit");
  fMuonCmd->SetParameter(param);


  fPowerLawCmd = new G4UIcommand("/hepd/gun/powerlaw",this);
  fPowerLawCmd->SetGuidance("Set the power law with Emin Emax [unit]  Gamma");
  fPowerLawCmd->AvailableForStates(G4State_Idle);  
  param = new G4UIparameter("Emin",'d',false);
  param->SetGuidance("E min");
  fPowerLawCmd->SetParameter(param);
  param = new G4UIparameter("Emax",'d',false);
  param->SetGuidance("E max");
  fPowerLawCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("E unit");
  fPowerLawCmd->SetParameter(param);
  param = new G4UIparameter("gamma",'d',false);
  param->SetGuidance("gamma");
  fPowerLawCmd->SetParameter(param);

  fFlatCmd = new G4UIcommand("/hepd/gun/flat",this);
  fFlatCmd->SetGuidance("Flat Spectra between Emin Emax [unit]");
  fFlatCmd->AvailableForStates(G4State_Idle);
  param = new G4UIparameter("Emin",'d',false);
  param->SetGuidance("E min");
  fFlatCmd->SetParameter(param);
  param = new G4UIparameter("Emax",'d',false);
  param->SetGuidance("E max");
  fFlatCmd->SetParameter(param);
  param = new G4UIparameter("unit",'s',false);
  param->SetGuidance("E unit");
  fFlatCmd->SetParameter(param);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPrimaryGeneratorMessenger::~HEPDSWPrimaryGeneratorMessenger()
{
  delete fDefaultCmd;
  delete fMuonCmd;
  delete fRndmCmd;
  delete fEnrgCmd;
  delete fSpotCmd;
  delete fPntngCmd;
  delete fBeamCmd;
  delete fPowerLawCmd;
  delete fFlatCmd;
  delete fGunDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fDefaultCmd )
    { fAction->SetDefaultKinematic();}
  if( command == fRndmCmd )
    { fAction->SetRandomPosition();}   
  if( command == fPntngCmd )
    { fAction->SetDirectionToCenter();}
  if( command == fEnrgCmd )
    { fAction->SetEnergy(fEnrgCmd->GetNewDoubleValue(newValue));}
  if( command == fSpotCmd )
    { fAction->SetSpot();}
  if( command == fPartCmd )
    {
      if(newValue=="He"||newValue=="C"||newValue=="O"){
        G4IonTable* ionTable = (G4IonTable*)(G4ParticleTable::GetParticleTable()->GetIonTable());
        G4int Z,A;
        if(newValue=="He"){Z=2; A=4;}
        if(newValue=="C"){Z=6;A=12;}
        if(newValue=="O"){Z=8;A=16;}
        G4ParticleDefinition* ion = ionTable->GetIon(Z,A,0.);
        fAction->SetParticle(ion->GetParticleName());
      }
      else{fAction->SetParticle(newValue);}
    }
  
  if( command == fMuonCmd )
    {
      G4double dX,dY,Emin,Emax;
      G4String unit_l,unit_e;
      std::istringstream is(newValue);
      is >> dX >> dY  >> unit_l >> Emin >> Emax >> unit_e;
      dX*= G4UIcommand::ValueOf(unit_l);
      dY*= G4UIcommand::ValueOf(unit_l);
      Emin*= G4UIcommand::ValueOf(unit_e);
      Emax*= G4UIcommand::ValueOf(unit_e);
      fAction->SetMuonGeneration(dX,dY,Emin,Emax);
      G4cout << "fMuonCmd: dx dy (mm) " << dX << " " << dY << " emin emax (MeV) " << Emin << " " << Emax << G4endl;
    }
  if( command == fBeamCmd )
    {
      G4double Xpos,Ypos,theta;
      G4String unit_l,unit_a;
      std::istringstream is(newValue);
      is >> Xpos >> Ypos >> unit_l >> theta >> unit_a;
      Xpos*= G4UIcommand::ValueOf(unit_l);
      Ypos*= G4UIcommand::ValueOf(unit_l);
      theta*= G4UIcommand::ValueOf(unit_a);
      fAction->SetBeam(Xpos,Ypos,theta);
    }

  if( command == fTBeamCmd )
    {
      G4double Xpos = -999;
      G4double Ypos = -999;
      G4double theta;
      G4String pos,unit_a;
      std::istringstream is(newValue);
      is >> pos >> theta >> unit_a;
      theta*= G4UIcommand::ValueOf(unit_a);
      G4cout << "pos " << pos << G4endl;
      if (pos == "a1" || pos == "A1" ) {
        Xpos = +17.5;
        Ypos = -78.0;
      }
      if (pos == "a2" || pos == "A2" ) {
        Xpos = +17.5;
        Ypos = -48.0;
      }
      if (pos == "a3" || pos == "A3" ) {
        Xpos = +17.5;
        Ypos = -18.0;
      }
      if (pos == "a4" || pos == "A4" ) {
        Xpos = +17.5;
        Ypos = +18.0;
      }
      if (pos == "a5" || pos == "A5" ) {
        Xpos = +17.5;
        Ypos = +48.0;
      }
      if (pos == "a6" || pos == "A6" ) {
        Xpos = +17.5;
        Ypos = +78.0;
      }
      if (pos == "b1" || pos == "B1" ) {
        Xpos = +57.5;
        Ypos = -78.0;
      }
      if (pos == "b2" || pos == "B2" ) {
        Xpos = +57.5;
        Ypos = -48.0;
      }
      if (pos == "b3" || pos == "B3" ) {
        Xpos = +57.5;
        Ypos = -18.0;
      }
      if (pos == "b4" || pos == "B4" ) {
        Xpos = +57.5;
        Ypos = +18.0;
      }
      if (pos == "b5" || pos == "B5" ) {
        Xpos = +57.5;
        Ypos = +48.0;
      }
      if (pos == "b6" || pos == "B6" ) {
        Xpos = +57.5;
        Ypos = +78.0;
      }
      if (pos == "c1" || pos == "C1" ) {
        Xpos = -17.5;
        Ypos = -78.0;
      }
      if (pos == "c2" || pos == "C2" ) {
        Xpos = -17.5;
        Ypos = -48.0;
      }
      if (pos == "c3" || pos == "C3" ) {
        Xpos = -17.5;
        Ypos = -18.0;
      }
      if (pos == "c4" || pos == "C4" ) {
        Xpos = -17.5;
        Ypos = +18.0;
      }
      if (pos == "c5" || pos == "C5" ) {
        Xpos = -17.5;
        Ypos = +48.0;
      }
      if (pos == "c6" || pos == "C6" ) {
        Xpos = -17.5;
        Ypos = +78.0;
      }
      if (pos == "d1" || pos == "D1" ) {
        Xpos = -57.5;
        Ypos = -78.0;
      }
      if (pos == "d2" || pos == "D2" ) {
        Xpos = -57.5;
        Ypos = -48.0;
      }
      if (pos == "d3" || pos == "D3" ) {
        Xpos = -57.5;
        Ypos = -18.0;
      }
      if (pos == "d4" || pos == "D4" ) {
        Xpos = -57.5;
        Ypos = +18.0;
      }
      if (pos == "d5" || pos == "D5" ) {
        Xpos = -57.5;
        Ypos = +48.0;
      }
      if (pos == "d6" || pos == "D6" ) {
        Xpos = -57.5;
        Ypos = +78.0;
      }
      if (Xpos == -999 || Ypos == -999)
        G4cout << "erreur non valid test beam position !!!!" << G4endl;
      else
        fAction->SetBeam(Xpos,Ypos,theta);
    }
  if( command == fBeamEResoCmd )
    {
      G4double ERESO;
      std::istringstream is(newValue);
      is >> ERESO;
      fAction->SetBeamEReso(ERESO);
    }
  if( command == fPowerLawCmd )
    {
      G4double Emin,Emax,gamma;
      G4String unit;
      std::istringstream is(newValue);
      is >> Emin >> Emax >> unit >> gamma;
      Emin*= G4UIcommand::ValueOf(unit);
      Emax*= G4UIcommand::ValueOf(unit);
      fAction->SetPowerLaw(Emin,Emax,gamma);
    }
  if( command == fFlatCmd )
    {
      G4double Emin,Emax;
      G4String unit;
      std::istringstream is(newValue);
      is >> Emin >> Emax >> unit;
      Emin*= G4UIcommand::ValueOf(unit);
      Emax*= G4UIcommand::ValueOf(unit);
      fAction->SetFlat(Emin,Emax);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

