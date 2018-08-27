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
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"

#include "HEPDSWDetectorConstruction.hh"
#include "HEPDSWPhysicsList.hh"
#include "HEPDSWPrimaryGeneratorAction.hh"
#include "HEPDSWRunAction.hh"
#include "HEPDSWEventAction.hh"
#include "HEPDSWTrackingAction.hh"
#include "HEPDSWSteppingAction.hh"
#include "HEPDSWProducerManager.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  G4RunManager * runManager = new G4RunManager;

  // set mandatory initialization classes
  HEPDSWDetectorConstruction* detector = new HEPDSWDetectorConstruction();
  runManager->SetUserInitialization(detector);

  runManager->SetUserInitialization(new HEPDSWPhysicsList());

  // primary generator
  HEPDSWPrimaryGeneratorAction* primary = new HEPDSWPrimaryGeneratorAction(detector);
  runManager->SetUserAction(primary);

  // set user action classes
  HEPDSWRunAction*      runAct = new HEPDSWRunAction();
  HEPDSWEventAction*    evtAct = new HEPDSWEventAction();
  HEPDSWTrackingAction* trkAct = new HEPDSWTrackingAction();
  HEPDSWSteppingAction* stpAct = new HEPDSWSteppingAction(primary);

  runManager->SetUserAction(runAct);
  runManager->SetUserAction(evtAct);
  runManager->SetUserAction(trkAct);
  runManager->SetUserAction(stpAct);

  HEPDSWProducerManager* theProducerManager = HEPDSWProducerManager::GetInstance();
  //HEPDSWProducerManager::GetInstance();

  // get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();

  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }

  else           //define visualization and UI terminal for interactive mode
    {
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif

#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute setup/gui.mac");
#endif
      ui->SessionStart();
      delete ui;
#endif

#ifdef G4VIS_USE
     delete visManager;
#endif
    }

  // job termination
  //
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

