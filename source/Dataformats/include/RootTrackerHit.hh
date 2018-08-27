#ifndef RootTrackerHit_h
#define RootTrackerHit_h 1
////////////////////////////////////////////////////////////////////////////////
//
#include <vector>

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

////////////////////////////////////////////////////////////////////////////////
//
class RootTrackerHit : public TObject
{
public:
  RootTrackerHit ();
  RootTrackerHit (TVector3 aEntry,TVector3 aExit,float aKE,float aToF,float aEloss,
		  int aPDG ,unsigned int aID,unsigned int atkID,float aTheta,float aPhi,TVector3 aMomDir);
  
  ~RootTrackerHit ();
  RootTrackerHit (const RootTrackerHit&);
  
  inline TVector3 GetEntryPoint(){return theEntryPoint;}
  inline TVector3 GetExitPoint(){return theExitPoint;}
  inline float GetKinEnergy(){return theKinEnergy;}
  inline float GetToF(){return theTimeOfFlight;}
  inline float GetELoss(){return theEnergyLoss;}
  inline int GetParticleType(){return theParticeType;}
  inline unsigned int GetDetectorId(){return theDetectorId;}
  inline unsigned int GetTrackId(){return theTrackIdInHit;}
  inline float GetThetaAtEntry(){return theThetaAtEntry;}
  inline float GetPhiAtEntry(){return thePhiAtEntry;}
  inline TVector3 GetMomDir(){return theMomDir;}

  ClassDef(RootTrackerHit,1);
  
private:
  TVector3 theEntryPoint;
  TVector3 theExitPoint;
  float theKinEnergy;
  float theTimeOfFlight;
  float theEnergyLoss;
  int    theParticeType;
  unsigned int theDetectorId;
  unsigned int theTrackIdInHit;
  float theThetaAtEntry;
  float thePhiAtEntry;
  TVector3 theMomDir;
};

#endif
