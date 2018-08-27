////////////////////////////////////////////////////////////////////////////////
//
#include "Track.hh"

G4Allocator<Track> TrackAllocator;
////////////////////////////////////////////////////////////////////////////////
//
Track::Track ():theTrackId(0),thePDG(0),
		thePosition(0),theMomentumDirection(0),theKinEnergy(0),
		theMotherTrackId(0)
{theName="";
theVertexVolumeName="";
theCreatorProcessName="";}
////////////////////////////////////////////////////////////////////////////////
//
Track::Track (G4int aTrackId, G4int aPDG, G4String aName,
		      G4ThreeVector aPosition, G4ThreeVector aMomentumDirection, G4double aKinEnergy,
	      G4int aMotherTrackId, G4String aVertexVolumeName, G4String aCreatorProcessName)
{ 
  theTrackId             = aTrackId;	 
  thePDG                 = aPDG;
  theName                = aName;
  thePosition            = aPosition;	 
  theMomentumDirection   = aMomentumDirection;
  theKinEnergy           = aKinEnergy;
  theMotherTrackId       = aMotherTrackId;
  theVertexVolumeName    = aVertexVolumeName;
  theCreatorProcessName  = aCreatorProcessName;
}
////////////////////////////////////////////////////////////////////////////////
//
Track::~Track ()
{}
////////////////////////////////////////////////////////////////////////////////
//
Track::Track (const Track& right) : G4VHit()
{
  theTrackId              = right.theTrackId;
  thePDG                  = right.thePDG;
  theName                 = right.theName;
  thePosition             = right.thePosition;	 
  theMomentumDirection    = right.theMomentumDirection;
  theKinEnergy            = right.theKinEnergy;
  theMotherTrackId        = right.theMotherTrackId;
  theVertexVolumeName     = right.theVertexVolumeName;
  theCreatorProcessName   =  right.theCreatorProcessName;
}
////////////////////////////////////////////////////////////////////////////////
//
const Track& Track::operator= (const Track& right)
{ 
  theTrackId              = right.theTrackId;
  thePDG                  = right.thePDG;
  theName                 = right.theName;
  thePosition             = right.thePosition;	 
  theMomentumDirection    = right.theMomentumDirection;
  theKinEnergy            = right.theKinEnergy;
  theMotherTrackId        = right.theMotherTrackId;
  theVertexVolumeName     = right.theVertexVolumeName;
  theCreatorProcessName   =  right.theCreatorProcessName;
  return *this;
}
////////////////////////////////////////////////////////////////////////////////
//
int Track::operator== (const Track& ) const
{
  return 0;
}

