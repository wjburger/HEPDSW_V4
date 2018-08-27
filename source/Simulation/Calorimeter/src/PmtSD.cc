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
// * institutes,nor the agencies providing financial support for this *33
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
//   wjb add PmtSD for optical photon simulation

#include "PmtSD.hh"
#include "PmtHits.hh"
#include "G4SDManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4OpticalPhoton.hh" //OP

PmtSD::PmtSD(G4String name):G4VSensitiveDetector(name){
  collectionName.insert("pmtCollection");
  fMessenger = new PmtSDMessenger(this);
  
}

PmtSD::~PmtSD()
{}

void PmtSD::Initialize(G4HCofThisEvent*){
  PmtCollection = new PmtHitsCollection(SensitiveDetectorName,collectionName[0]); 
  
  verboseLevel = 0;
  for (int i=0; i<nPmt; i++) totalPhotEvent[i]=0;
  G4cout << " init PmtSD " << G4endl;
}


G4int PmtSD::GetDetID(G4Step*aStep){

  G4TouchableHistory* touchable
       = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  G4int depth = touchable->GetHistoryDepth();
      //     G4cout << "depth " << depth << G4endl;
  char  detname[20];
  G4int detID = -1000;
  detname[0] = '\0';
  if (depth > 0) {
    G4int id_pmt = 0;
    G4int id_tscin = 0;
    G4int id_cal_layer = 0;
    G4int ncopy = 0;
    for (int d=0; d<depth; d++) {
       G4VPhysicalVolume* dpvolume =  touchable->GetVolume(d);
	   //	   G4cout << " depth " << d << " copy number " << touchable->GetCopyNumber(d) << " vname " << dpvolume->GetName() << G4endl;
    }
    for (int d=0; d<1; d++) {
      G4VPhysicalVolume* dpvolume =  touchable->GetVolume(d);
	 //	 G4cout << " depth " << d << " copy number " << touchable->GetCopyNumber(d) << " vname " << dpvolume->GetName() << G4endl;
      if (d == 0) {
	G4String vname = dpvolume->GetName(); 
	   //	   G4cout << "vname " << vname << G4endl;
 	if (strstr(vname,"TSP") != 0) {
	  if (strcmp(vname,"TSPmt1") == 0) id_pmt = 1;
	  if (strcmp(vname,"TSPmt2") == 0) id_pmt = 2;
	  vname = touchable->GetVolume(1)->GetName();
	  if (strcmp(vname,"S1ScintillatorM") == 0)
	    id_tscin = touchable->GetCopyNumber(1) + 1;
	  if (strcmp(vname,"S1ScintillatorP") == 0)
	    id_tscin = touchable->GetCopyNumber(1) + 4;
	  sprintf(detname,"T%dPmt%d",id_tscin,id_pmt);
	     //	     G4cout << " T1 PLANE " << detname << G4endl;
        }
        if (strstr(vname,"P1P") != 0) {
	  if (strcmp(vname,"P1Pmt1") == 0) id_pmt = 1;
	  if (strcmp(vname,"P1Pmt2") == 0) id_pmt = 2;
	  ncopy = touchable->GetCopyNumber(2);
	  id_cal_layer = 2*ncopy - 1;
	     //	     G4cout << "ici" << " id_cal_layer " << id_cal_layer << " id_pmt " << id_pmt << " ncopy " << ncopy << G4endl;
	  sprintf(detname,"P%dPmt%d",id_cal_layer,id_pmt);
	     //	     printf("%s/n",detname);
	     //	     G4cout << " CAL PLANE ODD " << detname << G4endl;
	}
	   //	   else G4cout << " vname " << vname << G4endl;
 	if (strstr(vname,"P2P") != 0) {
	     //	     G4cout << "ok" << G4endl;
	  if (strcmp(vname,"P2Pmt1") == 0) id_pmt = 1;
	  if (strcmp(vname,"P2Pmt2") == 0) id_pmt = 2;
	  vname = touchable->GetVolume(1)->GetName();
	  if (strcmp(vname,"ActiveLastLayerScint") == 0) {
	    id_cal_layer = 16;
	  } else { 
	    ncopy = touchable->GetCopyNumber(2);
	    id_cal_layer = 2*ncopy;
	  }  
	  sprintf(detname,"P%dPmt%d",id_cal_layer,id_pmt);
	     //	     G4cout << " CAL PLANE EVEN " << detname << G4endl;
	}
	if (strstr(vname,"LPmt") != 0) {
	  ncopy = touchable->GetCopyNumber(2) + touchable->GetCopyNumber(3)*3;
	  sprintf(detname,"L%dPmt",ncopy+1);
	  G4cout << "ici detname " << detname << G4endl;
	}  
	   //	   else G4cout << " vname " << vname << G4endl;
	   //	   else G4cout << " vname " << vname << G4endl;
      }
      //      if (d == 0) anActiveLayerName = dpvolume->GetName();
    }
  }
  return detID;
}

G4bool PmtSD::ProcessHits(G4Step*aStep,G4TouchableHistory*){
//OP - begin

//   G4cout << "---> PmtSD process hits" << G4endl;

  G4Track* aTrack = aStep->GetTrack();
  G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
  G4VPhysicalVolume* theTrackPV = aTrack->GetVolume();
  
  G4ParticleDefinition* particleType = aTrack->GetDefinition();
  //  G4cout << " particle name " << particleType->GetParticleName() << " opt photon " << G4OpticalPhoton::OpticalPhotonDefinition()->GetParticleName() << G4endl;
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    G4double energy = aTrack->GetKineticEnergy();
    //    printf(" energie %5.4e \n", energy);
    //    G4cout << "photon energy " << energy << G4endl;
    //    G4cout << " pre material " << thePrePV->GetLogicalVolume()->GetMaterial()->GetName() << G4endl;
    //    G4cout << " post material " << thePostPV->GetLogicalVolume()->GetMaterial()->GetName() << G4endl;
    //    G4cout << " track volume " << theTrackPV->GetName() << G4endl;
    if(thePrePV->GetLogicalVolume()->GetMaterial()->GetName()=="AluminiumOpt") {
      //      G4cout << "debut aluminium process steps" << G4endl;
      G4TouchableHistory* touchable
       = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
      G4int depth = touchable->GetHistoryDepth();
      //     G4cout << "depth " << depth << G4endl;
      char  detname[20];
      detname[0] = '\0';
      if (depth > 0) {
	G4int id_pmt = 0;
	G4int id_tscin = 0;
	G4int id_cal_layer = 0;
	G4int ncopy = 0;
	for (int d=0; d<depth; d++) {
	   G4VPhysicalVolume* dpvolume =  touchable->GetVolume(d);
	   //	   G4cout << " depth " << d << " copy number " << touchable->GetCopyNumber(d) << " vname " << dpvolume->GetName() << G4endl;
	}
        for (int d=0; d<1; d++) {
         G4VPhysicalVolume* dpvolume =  touchable->GetVolume(d);
	 //	 G4cout << " depth " << d << " copy number " << touchable->GetCopyNumber(d) << " vname " << dpvolume->GetName() << G4endl;
	 if (d == 0) {
	   G4String vname = dpvolume->GetName(); 
	   // 	   G4cout << "d == 0 vname " << vname << G4endl;
 	   if (strstr(vname,"TSP") != 0) {
	     if (strcmp(vname,"TSPmt1") == 0) id_pmt = 1;
	     if (strcmp(vname,"TSPmt2") == 0) id_pmt = 2;
	     vname = touchable->GetVolume(1)->GetName();
	     if (strcmp(vname,"S1ScintillatorM") == 0)
	       id_tscin = touchable->GetCopyNumber(1) + 1;
	     if (strcmp(vname,"S1ScintillatorP") == 0)
	       id_tscin = touchable->GetCopyNumber(1) + 4;
	     sprintf(detname,"T%dPmt%d",id_tscin,id_pmt);
	     //	     G4cout << " T1 PLANE " << detname << G4endl;
             energy *= 1.0e6;
	   }
	   //	   else G4cout << " vname " << vname << G4endl;
 	   if (strstr(vname,"P1P") != 0) {
	     if (strcmp(vname,"P1Pmt1") == 0) id_pmt = 1;
	     if (strcmp(vname,"P1Pmt2") == 0) id_pmt = 2;
	     ncopy = touchable->GetCopyNumber(2);
	     id_cal_layer = 2*ncopy - 1;
	     //	     G4cout << "ici" << " id_cal_layer " << id_cal_layer << " id_pmt " << id_pmt << " ncopy " << ncopy << G4endl;
	     sprintf(detname,"P%dPmt%d",id_cal_layer,id_pmt);
	     //	     printf("%s/n",detname);
	     //	     G4cout << " CAL PLANE ODD " << detname << G4endl;
             energy *= 1.0e6;
	   }
	   //	   else G4cout << " vname " << vname << G4endl;
 	   if (strstr(vname,"P2P") != 0) {
	     //	     G4cout << "ok" << G4endl;
	     if (strcmp(vname,"P2Pmt1") == 0) id_pmt = 1;
	     if (strcmp(vname,"P2Pmt2") == 0) id_pmt = 2;
	     vname = touchable->GetVolume(1)->GetName();
	     if (strcmp(vname,"ActiveLastLayerScint") == 0) {
	       id_cal_layer = 16;
	     } else { 
	       ncopy = touchable->GetCopyNumber(2);
	       id_cal_layer = 2*ncopy;
	     }  
	     sprintf(detname,"P%dPmt%d",id_cal_layer,id_pmt);
	     //	     G4cout << " CAL PLANE EVEN " << detname << G4endl;
             energy *= 1.0e6;
	   }
	   if (strstr(vname,"LPmt") != 0) {
	     ncopy = touchable->GetCopyNumber(2) + touchable->GetCopyNumber(3)*3;
	     sprintf(detname,"L%dPmt",ncopy+1);
	     //	     G4cout << "ici detname " << detname << G4endl;
	   }  
	   //	   else G4cout << " vname " << vname << G4endl;
	 }
      //      if (d == 0) anActiveLayerName = dpvolume->GetName();
        }
      }
      G4String pmtname(detname);
      //      G4cout << " detname " << detname << " pmtname " << pmtname << G4endl;
      PmtAnalysis(pmtname, energy);
      //      PMTAnalysis(pmtname, energy, number, ph_energy, pmt_qe);
      aTrack->SetTrackStatus(fStopAndKill);
      //      G4cout << "---> fin PmtSD process hits" << G4endl;
    }
  }
  return true;
}

void PmtSD::PmtAnalysis(G4String detname, G4double energy){
//----------Quantum efficiency of PMT R9880-210
  //NUMBERS from R9880-210 datasheet
  const G4int number = 121;
  G4double ph_energy[number] = {1.692, 1.695, 1.698, 1.701, 1.704,
		           1.710, 1.716, 1.725, 1.728, 1.732,
		           1.741, 1.744, 1.751, 1.757, 1.764,
		           1.767, 1.777, 1.780, 1.784, 1.790,
			   1.801, 1.807, 1.811, 1.821, 1.825,
			   1.828, 1.835, 1.839, 1.846, 1.850,
			   1.860, 1.883, 1.890, 1.901, 1.909,
			   1.921, 1.928, 1.936, 1.948, 1.956,
			   1.976, 1.993, 2.006, 2.018, 2.036,
			   2.053, 2.076, 2.094, 2.113, 2.127,
			   2.146, 2.180, 2.211, 2.232, 2.258,
			   2.280, 2.302, 2.324, 2.342, 2.359,
			   2.365, 2.383, 2.389, 2.401, 2.431,
			   2.450, 2.476, 2.508, 2.542, 2.562,
			   2.583, 2.612, 2.648, 2.678, 2.708,
			   2.740, 2.796, 2.846, 2.890, 2.943,
			   2.999, 3.067, 3.138, 3.223, 3.290,
			   3.383, 3.470, 3.547, 3.628, 3.743,
			   3.818, 3.912, 3.994, 4.045, 4.115,
			   4.188, 4.263, 4.321, 4.361, 4.442,
			   4.527, 4.571, 4.637, 4.683, 4.730,
			   4.801, 4.826, 4.900, 4.951, 4.977,
			   5.030, 5.057, 5.111, 5.139, 5.195,
			   5.223, 5.252, 5.281, 5.311, 5.371,
			   5.402};

  G4double pmt_qe[number] ={0.00, 0.00, 0.00, 0.00, 0.00,
		        0.00, 0.00, 0.00, 0.00, 0.00,
	       	        0.00, 0.00, 0.00, 0.00, 0.00,
	       	        0.01, 0.01, 0.01, 0.01, 0.01,
       		        0.01, 0.01, 0.01, 0.01, 0.01,
		        0.01, 0.02, 0.02, 0.02, 0.02,
	       	        0.02, 0.02, 0.02, 0.03, 0.03,
		        0.03, 0.04, 0.04, 0.04, 0.04,
	       	        0.05, 0.05, 0.05, 0.06, 0.06,
      		        0.07, 0.07, 0.08, 0.08, 0.09,
		        0.09, 0.10, 0.10, 0.11, 0.12,
		        0.13, 0.13, 0.15, 0.16, 0.17,
		        0.18, 0.19, 0.21, 0.22, 0.24,
		        0.25, 0.26, 0.27, 0.28, 0.29,
		        0.29, 0.30, 0.32, 0.33, 0.34,
		        0.36, 0.37, 0.37, 0.38, 0.39,
       		        0.40, 0.40, 0.41, 0.41, 0.41,
		        0.42, 0.42, 0.42, 0.42, 0.41,
		        0.40, 0.39, 0.37, 0.35, 0.34,
		        0.32, 0.30, 0.29, 0.27, 0.26,
		        0.24, 0.22, 0.21, 0.20, 0.18,
		        0.17, 0.16, 0.14, 0.13, 0.12,
		        0.11, 0.10, 0.09, 0.08, 0.07,
		        0.06, 0.06, 0.05, 0.05, 0.04,
		        0.03};


  G4int detectorID = 0;
  G4int detID = 0;
  char PmtName[10];

  //  G4cout << "PMTAnalysis detname " << detname << " energy " << energy << G4endl;
  //  if (strcmp(detname,"P11Pmt1") == 0) {
  //    G4cout << " ok " << G4endl;
  //    detectorID = 12061; detID = 32;
  //  }
  //  G4cout << " detname " << detname << G4endl;
  for (int i=0; i<number; i++){
    G4double prob = rand() % 101;  //random number between 0 and 100
    prob = prob/100.;
    if(energy > ph_energy[i] && energy < ph_energy[i+1]){
    if(prob < pmt_qe[i]+(pmt_qe[i+1]-pmt_qe[i])/(ph_energy[i+1]-ph_energy[i])*(energy-ph_energy[i])) {
      //        G4cout << " photon detecte " << G4endl;
        if(detname=="T1Pmt1") { detectorID = 13111; detID = 0; sprintf(PmtName,"%s","T1w");}
	if(detname=="T1Pmt2") { detectorID = 13112; detID = 1; sprintf(PmtName,"%s","T1e");}
	if(detname=="T2Pmt1") { detectorID = 13121; detID = 2; sprintf(PmtName,"%s","T2w");}
	if(detname=="T2Pmt2") { detectorID = 13122; detID = 3; sprintf(PmtName,"%s","T2e");}
	if(detname=="T3Pmt1") { detectorID = 13131; detID = 4; sprintf(PmtName,"%s","T3w");}
	if(detname=="T3Pmt2") { detectorID = 13132; detID = 5; sprintf(PmtName,"%s","T3e");}
	if(detname=="T4Pmt1") { detectorID = 13211; detID = 6; sprintf(PmtName,"%s","T4w");}
	if(detname=="T4Pmt2") { detectorID = 13212; detID = 7; sprintf(PmtName,"%s","T4e");}
	if(detname=="T5Pmt1") { detectorID = 13221; detID = 8; sprintf(PmtName,"%s","T5w");}
	if(detname=="T5Pmt2") { detectorID = 13222; detID = 9; sprintf(PmtName,"%s","T5e");}
	if(detname=="T6Pmt1") { detectorID = 13231; detID = 10; sprintf(PmtName,"%s","T6w");}
	if(detname=="T6Pmt2") { detectorID = 13232; detID = 11; sprintf(PmtName,"%s","T6e");}

	if(detname=="P1Pmt1") { detectorID = 12161; detID = 12; sprintf(PmtName,"%s","P1nw");}
	if(detname=="P1Pmt2") { detectorID = 12162; detID = 13; sprintf(PmtName,"%s","P1se");}
	if(detname=="P2Pmt1") { detectorID = 12151; detID = 14; sprintf(PmtName,"%s","P2sw");}
	if(detname=="P2Pmt2") { detectorID = 12152; detID = 15; sprintf(PmtName,"%s","P2ne");}
	if(detname=="P3Pmt1") { detectorID = 12141; detID = 16; sprintf(PmtName,"%s","P3nw");}
	if(detname=="P3Pmt2") { detectorID = 12142; detID = 17; sprintf(PmtName,"%s","P3se");}
	if(detname=="P4Pmt1") { detectorID = 12131; detID = 18; sprintf(PmtName,"%s","P4sw");}
	if(detname=="P4Pmt2") { detectorID = 12132; detID = 19; sprintf(PmtName,"%s","P4ne");}
	if(detname=="P5Pmt1") { detectorID = 12121; detID = 20; sprintf(PmtName,"%s","P5nw");}
	if(detname=="P5Pmt2") { detectorID = 12122; detID = 21; sprintf(PmtName,"%s","P5se");}
	if(detname=="P6Pmt1") { detectorID = 12111; detID = 22; sprintf(PmtName,"%s","P6sw");}
	if(detname=="P6Pmt2") { detectorID = 12112; detID = 23; sprintf(PmtName,"%s","P6ne");}
	if(detname=="P7Pmt1") { detectorID = 12101; detID = 24; sprintf(PmtName,"%s","P7nw");}
	if(detname=="P7Pmt2") { detectorID = 12102; detID = 25; sprintf(PmtName,"%s","P7se");}
	if(detname=="P8Pmt1") { detectorID = 12091; detID = 26; sprintf(PmtName,"%s","P8sw");}
	if(detname=="P8Pmt2") { detectorID = 12092; detID = 27; sprintf(PmtName,"%s","P8ne");}
	if(detname=="P9Pmt1") { detectorID = 12081; detID = 28; sprintf(PmtName,"%s","P9nw");}
	if(detname=="P9Pmt2") { detectorID = 12082; detID = 29; sprintf(PmtName,"%s","P9se");}
	if(detname=="P10Pmt1") { detectorID = 12071; detID = 30; sprintf(PmtName,"%s","P10sw");}
	if(detname=="P10Pmt2") { detectorID = 12072; detID = 31; sprintf(PmtName,"%s","P10ne");}
        if (strcmp(detname,"P11Pmt1") == 0) { detectorID = 12061; detID = 32; sprintf(PmtName,"%s","P11nw");}
	//	if(detname=="P11Pmt1") { detectorID = 12061; detID = 32;}
	if(detname=="P11Pmt2") { detectorID = 12062; detID = 33; sprintf(PmtName,"%s","P11se");}
	if(detname=="P12Pmt1") { detectorID = 12051; detID = 34; sprintf(PmtName,"%s","P12sw");}
	if(detname=="P12Pmt2") { detectorID = 12052; detID = 35; sprintf(PmtName,"%s","P12ne");}
	if(detname=="P13Pmt1") { detectorID = 12041; detID = 36; sprintf(PmtName,"%s","P13nw");}
	if(detname=="P13Pmt2") { detectorID = 12042; detID = 37; sprintf(PmtName,"%s","P13se");}
	if(detname=="P14Pmt1") { detectorID = 12031; detID = 38; sprintf(PmtName,"%s","P14sw");}
	if(detname=="P14Pmt2") { detectorID = 12032; detID = 39; sprintf(PmtName,"%s","P14ne");}
	if(detname=="P15Pmt1") { detectorID = 12021; detID = 40; sprintf(PmtName,"%s","P15nw");}
	if(detname=="P15Pmt2") { detectorID = 12022; detID = 41; sprintf(PmtName,"%s","P15se");}
	if(detname=="P16Pmt1") { detectorID = 12011; detID = 42; sprintf(PmtName,"%s","P16sw");}
	if(detname=="P16Pmt2") { detectorID = 12012; detID = 43; sprintf(PmtName,"%s","P16ne");}

	if(detname=="L1Pmt") { detectorID = 11111; detID = 44; sprintf(PmtName,"%s","L1ne");}
	if(detname=="L2Pmt") { detectorID = 11211; detID = 45; sprintf(PmtName,"%s","L4n");}
	if(detname=="L3Pmt") { detectorID = 11311; detID = 46; sprintf(PmtName,"%s","L7nw");}
	if(detname=="L4Pmt") { detectorID = 11121; detID = 47; sprintf(PmtName,"%s","L2e");}
	if(detname=="L5Pmt") { detectorID = 11221; detID = 48; sprintf(PmtName,"%s","L5c");}
	if(detname=="L6Pmt") { detectorID = 11321; detID = 49; sprintf(PmtName,"%s","L8w");}
	if(detname=="L7Pmt") { detectorID = 11131; detID = 50; sprintf(PmtName,"%s","L3se");}
	if(detname=="L8Pmt") { detectorID = 11231; detID = 51; sprintf(PmtName,"%s","L6s");}
	if(detname=="L9Pmt") { detectorID = 11331; detID = 52; sprintf(PmtName,"%s","L9sw");}

	//	G4cout << "detectID " << detectorID << " detID " << detID << " detname " << detname << " PmtName " << PmtName << G4endl;
	totalPhotEvent[detID] += 1;
	//	G4cout << " detID " << detID << " totalPhotEvent " << totalPhotEvent[detID] << G4endl;
	//	G4cout << " ok " << G4endl;
    }
    }
  }
  
}

void PmtSD::EndOfEvent(G4HCofThisEvent*HCE){
  //  G4cout << " PmtSD eofe " << G4endl;
  //  for (int i=0; i<nPmt; i++) {
  //	G4cout << " pmt  " << i << " totalPhotEvent " << totalPhotEvent[i] << G4endl;
  //  }
  size_t tnPmt = ((size_t) nPmt);
  G4int aTotalPhot[tnPmt];
  for (int i=0; i<nPmt; i++) aTotalPhot[i] = totalPhotEvent[i];
  PmtHits* store_pmtHits = new PmtHits(aTotalPhot,tnPmt);
  PmtSD* sd = dynamic_cast<PmtSD*>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("/hepd/pmt"));
  sd->GetPmtHitsCollection()->insert(store_pmtHits);
  G4int* TotalPhot_ptr = store_pmtHits->GetTotalPhotpt();
  //  G4cout << " TotalPhot_ptr " << TotalPhot_ptr << G4endl;
  //  for (int i=0; i<nPmt; i++) {
  //    G4cout << " pmt " << i << " totalPhotEven hits " << store_pmtHits->GetNPhot(i) << G4endl;
  //  }  
  static G4int HCID = -1;
  if(HCID<0)
    HCID = GetCollectionID(0);
  //  G4cout << "HCID " << HCID << G4endl;
  HCE->AddHitsCollection( HCID, PmtCollection );
  //  G4cout << " fin PmtSD eofe " << G4endl;
}

void PmtSD::clear(){
} 

void PmtSD::DrawAll(){
} 

void PmtSD::PrintAll(){
} 
