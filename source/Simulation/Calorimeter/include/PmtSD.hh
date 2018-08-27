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
//    add PmtSD for optical photon simulation

#ifndef PmtSD_h
#define PmtSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PmtHits.hh"
#include "PmtSDMessenger.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class PmtSD : public G4VSensitiveDetector
{
  
public:
  PmtSD(G4String name);
  ~PmtSD();
  
  void Initialize(G4HCofThisEvent*HCE);
  G4int GetDetID(G4Step*aStep);
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
  void PmtAnalysis(G4String detname, G4double energy);
  void EndOfEvent(G4HCofThisEvent*HCE);
  void clear();
  void DrawAll();
  void PrintAll();
  inline PmtHitsCollection* GetPmtHitsCollection(){return PmtCollection;}

private:
  const G4int nPmt = 53;
  PmtSDMessenger* fMessenger;
  PmtHitsCollection* PmtCollection;
  G4int verboseLevel;
  G4int totalPhotEvent[53];
};




#endif

