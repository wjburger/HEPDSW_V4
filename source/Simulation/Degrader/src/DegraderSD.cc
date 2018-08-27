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

#include "DegraderSD.hh"
#include "DegraderHit.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

DegraderSD::DegraderSD(G4String name):G4VSensitiveDetector(name){
  collectionName.insert("degraderHitCollection");  
  }

DegraderSD::~DegraderSD()
{}

void DegraderSD::Initialize(G4HCofThisEvent* HCE){
  static int HCID = -1;
  DegraderHitCollection = new DegraderHitsCollection(SensitiveDetectorName,collectionName[0]);
  HCID = GetCollectionID(0);
  HCE->AddHitsCollection(HCID,DegraderHitCollection); 
  //  G4cout << "init DegraderSD " << G4endl;
}


G4bool DegraderSD::ProcessHits(G4Step*aStep,G4TouchableHistory*){
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4int tkID = aStep->GetTrack()->GetTrackID();
  const G4ParticleDefinition* particle = aStep->GetTrack()->GetParticleDefinition();
  G4int pdg = particle->GetPDGEncoding();
  G4double kinE = aStep->GetTrack()->GetKineticEnergy();
  G4double eLoss = aStep->GetTotalEnergyDeposit();
  G4ThreeVector SPosition = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector EPosition = aStep->GetPostStepPoint()->GetPosition();
  G4ThreeVector MomDirStart = aStep->GetPreStepPoint()->GetMomentumDirection();
  G4ThreeVector MomDirEnd = aStep->GetPostStepPoint()->GetMomentumDirection();
  G4double stepLength = aStep->GetStepLength();
  G4double dedx= 0;
  if(particle->GetPDGCharge()!= 0.) {
    if(stepLength==0)
      dedx = 0;
    else
      dedx = eLoss/stepLength;
  }
  DegraderHit* aHit = new DegraderHit(kinE,MomDirStart,MomDirEnd,eLoss,SPosition,EPosition,stepLength,dedx,tkID,pdg);
  DegraderHitCollection->insert(aHit);
  //  G4cout << "Degrader insert aHit tkID " << tkID << " kinE " << kinE << G4endl;
  return true;
}

void DegraderSD::EndOfEvent(G4HCofThisEvent*HCE){
  static G4int HCID = -1;
  HCID = GetCollectionID(0);   
  HCE->AddHitsCollection( HCID, DegraderHitCollection );
  //  G4cout << "fin even DegraderSD HCID " << HCID << G4endl;
}

void DegraderSD::clear(){
} 

void DegraderSD::DrawAll(){
} 

void DegraderSD::PrintAll(){
} 
