#ifndef Track_h
#define Track_h 1
////////////////////////////////////////////////////////////////////////////////
//
#include "globals.hh"
#include <vector>

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

#include "G4HCofThisEvent.hh"

////////////////////////////////////////////////////////////////////////////////
//
class Track : public G4VHit
{
public:
  Track ();
  Track (G4int aTrackId, G4int aPDG, G4String aName,
	 G4ThreeVector aPosition, G4ThreeVector aMomentumDirection, G4double theKinEnergy,
	 G4int aMotherTrackId,G4String aVertexVolumeName,G4String aCreatorProcessName);
  
  ~Track ();
  Track (const Track&);
  const Track& operator= (const Track&);
  int operator== (const Track&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  inline G4int          GetTrackId(){return theTrackId;}
  inline G4int          GetPDGCode(){return thePDG;}
  inline G4String       GetName(){return theName;}
  inline G4ThreeVector  GetPosition(){return thePosition;}
  inline G4double       GetKinEnergy(){return theKinEnergy;}
  inline G4ThreeVector  GetMomentumDirection(){return theMomentumDirection;}
  inline G4int          GetMotherTrackId(){return theMotherTrackId;}
  inline G4String       GetVertexVolumeName(){return theVertexVolumeName;} 
  inline G4String       GetCreatorProcessName(){return theCreatorProcessName;} 
  inline void           AddPhot(G4int detID){
  totalPhot[detID]+=1;
  G4cout << " AddPhot detID " << detID << " total " << totalPhot[detID] << G4endl;} //OP 
  
  void Draw () {};
  void Print () {};
  void clear () {};
  void DrawAll () {};
  void PrintAll () {};

private:
  G4int          theTrackId;	 
  G4int          thePDG;              //Using this code we can in ROOT to the built in table and create a 
                                      //TParticlePDG that contain particleMass particleCharge
  G4String       theName;
  G4ThreeVector  thePosition;	 
  G4ThreeVector  theMomentumDirection;	 
  G4double       theKinEnergy;	 
  G4int          theMotherTrackId;
  G4String       theVertexVolumeName;
  G4String       theCreatorProcessName;
  G4int          totalPhot[53];  //OP
};

typedef G4THitsCollection<Track> TracksCollection;

extern G4Allocator<Track> TrackAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* Track::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackAllocator.MallocSingle();
  //  G4cout << " Track aHit " << aHit << G4endl;
////  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
////  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
////  TracksCollection* trackHC = (TracksCollection*)(HCE->GetHC(0));
  //  G4cout << " trackHC " << trackHC << G4endl;
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void Track::operator delete(void *aHit)
{
  TrackAllocator.FreeSingle((Track*) aHit);
}


////////////////////////////////////////////////////////////////////////////////
#endif
