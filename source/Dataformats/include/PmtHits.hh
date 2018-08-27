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
//   wjb added for optical photon simulation

#ifndef PmtHits_h
#define PmtHits_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include <vector>
#include <iostream>
#include <cstring>
#include "G4ios.hh"

class PmtHits : public G4VHit
{
public:

  PmtHits();
  PmtHits(G4int aTotalPhot[], size_t aNPmt);
  //  CaloHit(G4String volume);
  //  PmtHits(G4int DetID);
  ~PmtHits();
  PmtHits(const PmtHits &right);
  const PmtHits& operator=(const PmtHits &right);
  G4int operator==(const PmtHits &) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  void Draw();
  void Print();

private:
  size_t theNPmt;
  G4int theTotalPhot[53]; 

public:
  inline G4int GetNPmt(){return theNPmt;}
  inline G4int* GetTotalPhotpt(){return theTotalPhot;}
  inline G4int GetNPhot(G4int npmt) {
    //    G4cout << "npmt " << npmt << G4endl;
    G4int val = theTotalPhot[npmt];
    //    G4cout << "val " << val << G4endl;
    return val;}  //OP
  
};

typedef G4THitsCollection<PmtHits> PmtHitsCollection;

extern G4Allocator<PmtHits> PmtHitsAllocator;

inline void* PmtHits::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PmtHitsAllocator.MallocSingle();
  return aHit;
}

inline void PmtHits::operator delete(void *aHit)
{
  PmtHitsAllocator.FreeSingle((PmtHits*) aHit);
}

#endif


