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

#ifndef DegraderHit_h
#define DegraderHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DegraderHit : public G4VHit
{
public:

  DegraderHit();
  DegraderHit(G4double aKinEnergy, G4ThreeVector aMomDirStart, G4ThreeVector aMomDirEnd,
	 G4double aeLoss, G4ThreeVector aSPosition,G4ThreeVector aEPosition,
	      G4double aStepLength,G4double adEdx,unsigned int aTrackId, G4int aParticleType);
  ~DegraderHit();
  DegraderHit(const DegraderHit &right);
  const DegraderHit& operator=(const DegraderHit &right);
  G4int operator==(const DegraderHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  void Draw();
  void Print();

  inline G4double       GetKineticEnergy(){return theKinEnergy;}
  inline G4ThreeVector  GetMomDirStart(){return theMomDirStart;}
  inline G4ThreeVector  GetMomDirEnd(){return theMomDirEnd;}
  inline G4double       GetELoss(){return theELoss;}
  inline G4double       GetdEdx(){return thedEdx;}
  inline G4ThreeVector  GetStartPosition(){return theStartPosition;}
  inline G4ThreeVector  GetEndPosition(){return theEndPosition;}
  inline G4double       GetStepLength(){return theStepLength;}
  inline G4int          GetParticleType(){return theParticleType;}
  inline unsigned int   GetTrackId(){return theTrackId;}
  
private:
                                      //TParticlePDG that contain particleMass particleCharge 	 
  G4double       theKinEnergy;	
  G4ThreeVector  theMomDirStart; 
  G4ThreeVector  theMomDirEnd; 
  G4double       theELoss;	 
  G4ThreeVector  theStartPosition;	 
  G4ThreeVector  theEndPosition;	 
  G4double       theStepLength;
  G4double       thedEdx;	 
  unsigned int   theTrackId;
  G4int          theParticleType;	 

};

typedef G4THitsCollection<DegraderHit> DegraderHitsCollection;

extern G4Allocator<DegraderHit> DegraderHitAllocator;

inline void* DegraderHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) DegraderHitAllocator.MallocSingle();
  return aHit;
}

inline void DegraderHit::operator delete(void *aHit)
{
  DegraderHitAllocator.FreeSingle((DegraderHit*) aHit);
}

#endif


