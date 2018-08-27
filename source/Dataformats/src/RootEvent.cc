////////////////////////////////////////////////////////////////////////////////
//

#include "RootEvent.hh"

ClassImp(RootEvent)

////////////////////////////////////////////////////////////////////////////////
//
RootEvent::RootEvent ():eventID(0)
{
  theCaloHitCollection.clear();
  thePmtHitsCollection.clear();
  theVetoHitCollection.clear();
  theTrackerHitCollection.clear();
  theDegraderHitCollection.clear();
}
////////////////////////////////////////////////////////////////////////////////
//
RootEvent::RootEvent (int aEventID,
		      std::vector<RootTrack> aTracks,
		      std::vector<RootVertex> aVertex,
		      std::vector<RootCaloHit> aCaloHit,
		      std::vector<RootCaloHit> aVetoHit,
		      std::vector<RootPmtHits> aPmtHits,
		      std::vector<RootTrackerHit> aTrackerHit,
		      std::vector<RootDegraderHit> aDegraderHit)
{ 
  eventID                 = aEventID;
  theTrackCollection      = aTracks;
  theVertexCollection     = aVertex;
  theCaloHitCollection    = aCaloHit;
  theVetoHitCollection    = aVetoHit;
  thePmtHitsCollection    = aPmtHits;
  theTrackerHitCollection = aTrackerHit;
  theDegraderHitCollection = aDegraderHit;
}
////////////////////////////////////////////////////////////////////////////////
//
RootEvent::~RootEvent ()
{}
////////////////////////////////////////////////////////////////////////////////
//
RootEvent::RootEvent (const RootEvent& right): TObject()
{
  eventID                 = right.eventID;
  theTrackCollection      = right.theTrackCollection;
  theVertexCollection     = right.theVertexCollection;
  theCaloHitCollection    = right.theCaloHitCollection;
  theVetoHitCollection    = right.theVetoHitCollection;
  thePmtHitsCollection    = right.thePmtHitsCollection;
  theTrackerHitCollection = right.theTrackerHitCollection;
  theDegraderHitCollection = right.theDegraderHitCollection;
  
}
////////////////////////////////////////////////////////////////////////////////
//
