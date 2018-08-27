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

#include "CaloHit.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

G4Allocator<CaloHit> CaloHitAllocator;

CaloHit::CaloHit()
//{VolumeID="";}
{DetID=-1000;}

// CaloHit::CaloHit(G4String volume)
//   : VolumeID(volume)
// {;}
CaloHit::CaloHit(G4int det,G4ThreeVector aEntry, G4ThreeVector aExit, G4double aKE)
  : DetID(det)
{theEntryPoint = aEntry;
  theExitPoint = aExit;
  theKinEnergy = aKE;}


CaloHit::~CaloHit()
{;}

CaloHit::CaloHit(const CaloHit &right)
  : G4VHit()
{
  //  VolumeID = right.VolumeID;
  DetID = right.DetID;
  theEntryPoint = right.theEntryPoint;
  theExitPoint = right.theExitPoint;
  theKinEnergy = right.theKinEnergy;
  edep = right.edep;
  totalEdep = right.totalEdep;
  for (int i=0; i<53; i++) totalPhot[i] = right.totalPhot[i];  //OP
}

const CaloHit& CaloHit::operator=(const CaloHit &right)
{
  //  VolumeID = right.VolumeID;
  DetID = right.DetID;
  theEntryPoint = right.theEntryPoint;
  theExitPoint = right.theExitPoint;
  theKinEnergy = right.theKinEnergy;
  edep = right.edep;
  totalEdep = right.totalEdep;
  for (int i=0; i<53; i++) totalPhot[i] = right.totalPhot[i];  //OP
  return *this;
}

void CaloHit::SetEdep(G4double aEdep,G4int aTkID){
  totalEdep=0;
  totalEdep=aEdep;
  if(edep.find(aTkID)!=edep.end())
    edep[aTkID]+=aEdep;
  else
    edep[aTkID]=aEdep;
}

void CaloHit::SetStepPos(G4ThreeVector StepPos,G4int aTkID){
  //  G4cout << "SetStepPos aTkID " << aTkID << " x " << StepPos.getX() << " y " << StepPos.getY() << " z " << StepPos.getZ() << G4endl;
  steppos[aTkID]=StepPos;
}

void CaloHit::AddEdep(G4double aEdep,G4int aTkID){
  totalEdep+=aEdep;
  //      G4cout << " Energy added to TkID " 
  //	     << aTkID <<" total energy deposit = "<<totalEdep << G4endl; 
  if(edep.find(aTkID)!=edep.end())
    edep[aTkID]+=aEdep;
  else
    edep[aTkID]=aEdep;
}

void CaloHit::AddPhot(G4int detID){  //OP
  totalPhot[detID]+=1;
  G4cout << " AddPhot detID " << detID << " total " << totalPhot[detID] << G4endl;
}

G4int CaloHit::operator==(const CaloHit &right) const
{
  //  return (VolumeID==right.VolumeID);
  return (DetID==right.DetID);
}


void CaloHit::Draw()
{;}


void CaloHit::Print()
{;}


