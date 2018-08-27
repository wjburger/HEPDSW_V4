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

#include "DegraderHit.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include <iostream>

G4Allocator<DegraderHit> DegraderHitAllocator;

DegraderHit::DegraderHit():theKinEnergy(0),theMomDirStart(0),theMomDirEnd(0),theELoss(0),theStartPosition(0),theEndPosition(0),theStepLength(0),
thedEdx(0),theTrackId(0),theParticleType(0){}

DegraderHit::DegraderHit(G4double aKinEnergy,G4ThreeVector aMomDirStart,G4ThreeVector aMomDirEnd,G4double aELoss,
			 G4ThreeVector aSPosition,G4ThreeVector aEPosition,G4double aStepLength,G4double adEdx,unsigned int aTrackId,
	       G4int aParticleType)
{
  theKinEnergy   = aKinEnergy;	  
  theMomDirStart = aMomDirStart;
  theMomDirEnd = aMomDirEnd;
  theELoss       = aELoss;
  theStartPosition    = aSPosition;	 
  theEndPosition    = aEPosition;	 
  theStepLength  = aStepLength;
  thedEdx        = adEdx;
  theParticleType = aParticleType;	  
  theTrackId     = (unsigned int) aTrackId;	 
}

DegraderHit::~DegraderHit()
{;}


DegraderHit::DegraderHit(const DegraderHit &right)
  : G4VHit()
{
  theKinEnergy      = right.theKinEnergy;	 
  theMomDirStart = right.theMomDirStart;
  theMomDirEnd = right.theMomDirEnd;
  theELoss          = right.theELoss;
  theStartPosition       = right.theStartPosition;	 
  theEndPosition       = right.theEndPosition;	 
  theStepLength     = right.theStepLength;
  thedEdx           = right.thedEdx;	 
  theParticleType   = right.theParticleType;	 
  theTrackId        = right.theTrackId;	 
}

const DegraderHit& DegraderHit::operator=(const DegraderHit &right)
{
  theKinEnergy      = right.theKinEnergy;	 
  theMomDirStart = right.theMomDirStart;
  theMomDirEnd = right.theMomDirEnd;
  theELoss          = right.theELoss;
  theStartPosition       = right.theStartPosition;	 
  theEndPosition       = right.theEndPosition;	 
  theStepLength     = right.theStepLength;
  thedEdx           = right.thedEdx;	 
  theParticleType   = right.theParticleType;	 
  theTrackId        = right.theTrackId;	 
  return *this;
}

G4int DegraderHit::operator==(const DegraderHit &) const
{
  return 0;
}


void DegraderHit::Draw()
{;}


void DegraderHit::Print()
{
  std::cout<<"::DegraderHit::"<<std::endl;
  std::cout<<"  KinEnergy = "<<theKinEnergy<<"; "<<std::endl;
  std::cout<<"  E Loss = "<<theELoss<<"; "<<std::endl;
  std::cout<<"  Step Length = "<<theStepLength<<"; "<<std::endl;
  std::cout<<"  dE/dx= "<<thedEdx<<"; "<<std::endl;
  std::cout<<"  TrackID = "<<theTrackId<<"; "<<std::endl;
}


