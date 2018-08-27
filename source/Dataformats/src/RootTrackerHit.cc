////////////////////////////////////////////////////////////////////////////////
//
#include "RootTrackerHit.hh"

ClassImp(RootTrackerHit)

////////////////////////////////////////////////////////////////////////////////
//
RootTrackerHit::RootTrackerHit ():theEntryPoint(0,0,0),theExitPoint(0,0,0),theMomDir(0,0,0)
{
  theKinEnergy = 0;
  theTimeOfFlight = 0;
  theEnergyLoss = 0;
  theParticeType = 0;
  theDetectorId= 0;
  theTrackIdInHit= 0;
  theThetaAtEntry = 0;
  thePhiAtEntry = 0;
}
////////////////////////////////////////////////////////////////////////////////
//
RootTrackerHit::RootTrackerHit(TVector3 aEntry,TVector3 aExit,float aKE,float aToF,float aEloss,
			       int aPDG ,unsigned int aID,unsigned int aTkID,float aTheta,float aPhi,TVector3 aMomDir)
  
{ 
  theEntryPoint = aEntry;
  theExitPoint = aExit;
  theKinEnergy = aKE;
  theTimeOfFlight = aToF;
  theEnergyLoss = aEloss;
  theParticeType = aPDG;
  theDetectorId = aID;
  theTrackIdInHit = aTkID;
  theThetaAtEntry = aTheta;
  thePhiAtEntry = aPhi;
  theMomDir = aMomDir;
}
////////////////////////////////////////////////////////////////////////////////
//
RootTrackerHit::~RootTrackerHit ()
{}
////////////////////////////////////////////////////////////////////////////////
//
RootTrackerHit::RootTrackerHit (const RootTrackerHit& right) : TObject()
{
  theEntryPoint = right.theEntryPoint;
  theExitPoint = right.theExitPoint;
  theKinEnergy = right.theKinEnergy;
  theTimeOfFlight = right.theTimeOfFlight;
  theEnergyLoss = right.theEnergyLoss;
  theParticeType = right.theParticeType;
  theDetectorId = right.theDetectorId;
  theTrackIdInHit = right.theTrackIdInHit;
  theThetaAtEntry = right.theThetaAtEntry;
  thePhiAtEntry = right.thePhiAtEntry;
  theMomDir = right.theMomDir;
}
////////////////////////////////////////////////////////////////////////////////
//
