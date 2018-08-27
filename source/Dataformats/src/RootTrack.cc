////////////////////////////////////////////////////////////////////////////////
//
#include "RootTrack.hh"

ClassImp(RootTrack)

////////////////////////////////////////////////////////////////////////////////
//
RootTrack::RootTrack():theTrackId(0),thePDG(0),thePosition(0,0,0),theDirection(0,0,0),theKinEnergy(0),theParentTrackId(0)
{
  theName="";
  theVertexVolumeName="";
  theCreatorProcessName="";
}
////////////////////////////////////////////////////////////////////////////////
//
RootTrack::RootTrack (int aTkId,int aPDG,TString aName,TVector3 aPos,TVector3 aDir,float aKinE,int aPTkId,TString aVertexVolumeName,TString aCreatorProcessName)
{
  theTrackId = aTkId;	 	 
  thePDG = aPDG;
  theName = aName;
  thePosition = aPos;	 
  theDirection = aDir;	 
  theKinEnergy = aKinE;		 
  theParentTrackId = aPTkId;
  theVertexVolumeName = aVertexVolumeName;
  theCreatorProcessName = aCreatorProcessName;
}
////////////////////////////////////////////////////////////////////////////////
//
RootTrack::~RootTrack ()
{}
////////////////////////////////////////////////////////////////////////////////
//
RootTrack::RootTrack (const RootTrack& right) : TObject()
{
  theTrackId = right.theTrackId;
  thePDG = right.thePDG;
  theName = right.theName;
  thePosition = right.thePosition;	 
  theDirection = right.theDirection;	 
  theKinEnergy = right.theKinEnergy;		 
  theParentTrackId = right.theParentTrackId;
  theVertexVolumeName = right.theVertexVolumeName;
  theCreatorProcessName = right.theCreatorProcessName;
}
////////////////////////////////////////////////////////////////////////////////
//
