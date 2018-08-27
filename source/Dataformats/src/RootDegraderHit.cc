////////////////////////////////////////////////////////////////////////////////
//
#include "RootDegraderHit.hh"

ClassImp(RootDegraderHit)

////////////////////////////////////////////////////////////////////////////////
//
RootDegraderHit::RootDegraderHit ():theMomDirStart(0,0,0),theMomDirEnd(0,0,0),theStartPosition(0,0,0),theEndPosition(0,0,0)
{
  theKinEnergy = 0;
  theELoss = 0;
  theStepLength = 0;
  thedEdx= 0;
  theParticleType = -999;
  theTrackIdInHit = 0;
}
////////////////////////////////////////////////////////////////////////////////
//
RootDegraderHit::RootDegraderHit(float aKinEnergy,TVector3 aMomDirStart,TVector3 aMomDirEnd,float aELoss,
				 TVector3 aBPosition,TVector3 aEPosition,float aStepLength,float adEdx,
                                 unsigned int aTrackIdInHit, int aParticleType)  
{ 
  theKinEnergy   = aKinEnergy;	  
  theMomDirStart = aMomDirStart;
  theMomDirEnd = aMomDirEnd;
  theELoss       = aELoss;
  theStartPosition    = aBPosition;	 
  theEndPosition    = aEPosition;	 
  theStepLength  = aStepLength;
  thedEdx        = adEdx;	 
  theParticleType = aParticleType;
  theTrackIdInHit = aTrackIdInHit; 
}
////////////////////////////////////////////////////////////////////////////////
//
RootDegraderHit::~RootDegraderHit ()
{}
////////////////////////////////////////////////////////////////////////////////
//
RootDegraderHit::RootDegraderHit (const RootDegraderHit& right) : TObject()
{
  theKinEnergy      = right.theKinEnergy;
  theMomDirStart = right.theMomDirStart;	 
  theMomDirEnd = right.theMomDirEnd;	 
  theELoss          = right.theELoss;
  theStartPosition  = right.theStartPosition;	 
  theEndPosition    = right.theEndPosition;	 
  theStepLength     = right.theStepLength;
  thedEdx           = right.thedEdx;
  theParticleType   = right.theParticleType;
  theTrackIdInHit   = right.theTrackIdInHit;	 
}
////////////////////////////////////////////////////////////////////////////////
//
