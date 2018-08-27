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
//  wjb added for optical photon simulation

#include "PmtHits.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

G4Allocator<PmtHits> PmtHitsAllocator;

PmtHits::PmtHits(){
  theNPmt = 53;
  for (int i=0; i<53; i++) theTotalPhot[i] = 0;
}

PmtHits::~PmtHits()
{;}

//PmtHits::PmtHits(std::vector<G4int> aTotalPhot, size_t aNPmt) {
PmtHits::PmtHits(int aTotalPhot[], size_t aNPmt) {
  theNPmt = aNPmt;
  for (int i=0; i<((int)theNPmt); i++) {
    theTotalPhot[i] = aTotalPhot[i];
  }  
}

PmtHits::PmtHits(const PmtHits &right)
  : G4VHit()
{
  theNPmt = right.theNPmt;
  for (int i=0; i<((int) theNPmt); i++) theTotalPhot[i] = right.theTotalPhot[i];  //OP
}

const PmtHits& PmtHits::operator=(const PmtHits &right)
{
  theNPmt = right.theNPmt;
  for (int i=0; i<((int) theNPmt); i++) theTotalPhot[i] = right.theTotalPhot[i];  //OP
  return *this;
}

// void PmtHits::AddPhot(G4int detID){  //OP
//  totalPhot[detID]+=1;
//  G4cout << " AddPhot detID " << detID << " total " << totalPhot[detID] << G4endl;
//}

G4int PmtHits::operator==(const PmtHits &) const
{
  return 0;
}


void PmtHits::Draw()
{;}


void PmtHits::Print()
{;}


