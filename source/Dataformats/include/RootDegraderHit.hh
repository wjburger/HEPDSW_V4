#ifndef RootDegraderHit_h
#define RootDegraderHit_h 1
////////////////////////////////////////////////////////////////////////////////
//
#include <vector>

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

////////////////////////////////////////////////////////////////////////////////
//
class RootDegraderHit : public TObject
{
public:
  RootDegraderHit ();
  RootDegraderHit (float aKinEnergy, TVector3 aMomDirStart, TVector3 aMomDirEnd, float aeLoss, TVector3 aBPosition,TVector3 aEPosition,float aStepLength,float adEdx, unsigned int atkID, int aPDG);
  
  ~RootDegraderHit ();
  RootDegraderHit (const RootDegraderHit&);
  
  inline float GetKinEnergy(){return theKinEnergy;}
  inline TVector3 GetMomDirStart(){return theMomDirStart;}
  inline TVector3 GetMomDirEnd(){return theMomDirEnd;}
  inline float GetELoss(){return theELoss;}
  inline TVector3 GetStartPosition(){return theStartPosition;}
  inline TVector3 GetEndPosition(){return theEndPosition;}
  inline float GetSetpLength(){return theStepLength;}
  inline float GetdEdx(){return thedEdx;}
  inline unsigned int GetTrackId(){return theTrackIdInHit;}
  inline int GetParticleType(){return theParticleType;}

  ClassDef(RootDegraderHit,2);
  
private:
  float theKinEnergy;
  TVector3 theMomDirStart;
  TVector3 theMomDirEnd;
  float theELoss;
  TVector3 theStartPosition;
  TVector3 theEndPosition;
  float theStepLength;
  float thedEdx;
  int theParticleType;
  unsigned int theTrackIdInHit;
};

#endif
