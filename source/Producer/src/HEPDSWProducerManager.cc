//
//  wjb modifed for optical photon simulation
//

#include "HEPDSWProducerManager.hh"
#include "HEPDSWProducerMessenger.hh"

//Analyser
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4PrimaryParticle.hh"

#include "G4Step.hh"
#include "G4Timer.hh"
#include "Randomize.hh"

#include "RootCaloHit.hh"
#include "CalorimeterSD.hh"
#include "VetoSD.hh"
#include "PmtSD.hh"
#include <map>
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VTrajectory.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4TrajectoryContainer.hh"
#include <iterator>
#include "G4SIunits.hh"

HEPDSWProducerManager* HEPDSWProducerManager::instance = 0;

////////////////////////////////////////////////////////////////////////////////
//
HEPDSWProducerManager::HEPDSWProducerManager():theEvent(0),theRootFile(0),theEventTree(0),thePathDir(0)
{
  theMessenger = new HEPDSWProducerMessenger(this);
  caloHitCollID=-1;
  pmtHitsCollID=-1;
  vetoHitCollID=-1;
  trackerHitCollID=-1;
  degraderHitCollID=-1;
  trackCollID=-1;
  vertexCollID=-1;
  theAutoSaveLimit = 1000;
  eventID=0;
  verboseLevel = 0;
  saveTracker=true;
  saveMCTruth=true;
  saveCalo=true;
  saveDegrader=true;
  theEvent = new RootEvent();
}
////////////////////////////////////////////////////////////////////////////////
//
HEPDSWProducerManager::~HEPDSWProducerManager()
{
  delete theMessenger;
  delete theEventTree;
  delete theEvent;
  delete theRootFile;
}
////////////////////////////////////////////////////////////////////////////////
//

void HEPDSWProducerManager::SetRootFile(G4String aFileName,G4String aDirName)
{
  theRootFile = new TFile(aFileName,"RECREATE","Storing of HEPD info");

  G4String aNameDir = aDirName;
  thePathDir = theRootFile->mkdir(aNameDir);

  thePathDir->cd();

  theEventTree = new TTree("EventTree","The Tree with the variable used to performe the calculation of energy deposition on the HEPD detector");
  theEventTree->Branch("Event","RootEvent",&theEvent);
  theEventTree->SetAutoSave(theAutoSaveLimit);
}


HEPDSWProducerManager* HEPDSWProducerManager::GetInstance()
{
  if (instance == 0) instance = new HEPDSWProducerManager;
  return instance;
}
////////////////////////////////////////////////////////////////////////////////
//
void HEPDSWProducerManager::BeginOfEventAction(const G4Event*)
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(caloHitCollID<0||vetoHitCollID<0||trackerHitCollID<0||trackCollID<0){
    if(saveCalo){
      caloHitCollID = SDman->GetCollectionID("caloCollection");
      vetoHitCollID = SDman->GetCollectionID("vetoCollection");
      pmtHitsCollID = SDman->GetCollectionID("pmtCollection");
    }
    if(saveTracker)
      trackerHitCollID = SDman->GetCollectionID("trackerHitCollection");
    if(saveDegrader)
      degraderHitCollID = SDman->GetCollectionID("degraderHitCollection");
    if(saveMCTruth){
      trackCollID = SDman->GetCollectionID("trackCollection");
      vertexCollID = SDman->GetCollectionID("vertexCollection");
    }
  }
}



void HEPDSWProducerManager::StoreRootFile()
{
  theRootFile->Write(0,TObject::kOverwrite);
  theRootFile->Close();
}
void HEPDSWProducerManager::BeginOfRunAction(const G4Run*)
{
  eventID=0;
}
///////////////////////////////////////////////////////////////////////////////
//
void HEPDSWProducerManager::EndOfEventAction(const G4Event* evt)
{
  if(verboseLevel>0)
    G4cout << "entering in EndOfEventAction..." << G4endl;

  eventID = evt->GetEventID();


  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();

  if(verboseLevel>0) {
  G4cout << " prod fin eventID " << eventID << " HCE " << HCE << G4endl;
  G4cout << " degraderHitCollID " << degraderHitCollID << G4endl;  
  G4cout << " trackerHitCollID " << trackerHitCollID << G4endl;  
  G4cout << " pmtHitsCollID " << pmtHitsCollID << G4endl;
  G4cout << " caloHitCollID " << caloHitCollID << G4endl;  
  G4cout << " vetoHitCollID " << vetoHitCollID << G4endl;  
  G4cout << " trackCollID " << trackCollID << G4endl;  
  G4cout << " vertexCollID " << vertexCollID << G4endl;  
  }

  PmtHitsCollection * pmtHC  = 0;
  CaloHitsCollection * caloHC  = 0;
  CaloHitsCollection * vetoHC  = 0;
  TrackerHitsCollection * trackerHC   = 0;
  DegraderHitsCollection * degraderHC   = 0;
  TracksCollection * trackHC   = 0;
  VertexsCollection * vertexHC   = 0;

  if(theCaloHitContainer.size())
    theCaloHitContainer.clear();
  if(thePmtHitsContainer.size())
    thePmtHitsContainer.clear();
  if(theVetoHitContainer.size())
    theVetoHitContainer.clear();
  if(theTrackerHitContainer.size())
    theTrackerHitContainer.clear();
  if(theDegraderHitContainer.size())
    theDegraderHitContainer.clear();
  if(theTrackContainer.size())
    theTrackContainer.clear();
  if(theVertexContainer.size())
    theVertexContainer.clear();

  if(HCE){
    if(verboseLevel>0)
      std::cout<<"Evento # "<<eventID<<std::endl;
    if(!(degraderHitCollID<0)){
      degraderHC = (DegraderHitsCollection*)(HCE->GetHC(degraderHitCollID));
      for(int i=0;i<degraderHC->entries();i++){
         TVector3 SPosHit((*degraderHC)[i]->GetStartPosition().getX(),(*degraderHC)[i]->GetStartPosition().getY(),(*degraderHC)[i]->GetStartPosition().getZ());
         TVector3 EPosHit((*degraderHC)[i]->GetEndPosition().getX(),(*degraderHC)[i]->GetEndPosition().getY(),(*degraderHC)[i]->GetEndPosition().getZ());
         TVector3 MomDirStartHit((*degraderHC)[i]->GetMomDirStart().getX(),(*degraderHC)[i]->GetMomDirStart().getY(),(*degraderHC)[i]->GetMomDirStart().getZ());
         TVector3 MomDirEndHit((*degraderHC)[i]->GetMomDirEnd().getX(),(*degraderHC)[i]->GetMomDirEnd().getY(),(*degraderHC)[i]->GetMomDirEnd().getZ());
         theDegraderHitContainer.push_back(RootDegraderHit((*degraderHC)[i]->GetKineticEnergy(),MomDirStartHit,MomDirEndHit,(*degraderHC)[i]->GetELoss(),SPosHit,EPosHit,(*degraderHC)[i]->GetStepLength(),(*degraderHC)[i]->GetdEdx(),(*degraderHC)[i]->GetTrackId(),(*degraderHC)[i]->GetParticleType()));
	 if(verboseLevel>0) std::cout<<"DegraderHit  # "<<i<<" ; Edep = "<<(*degraderHC)[i]->GetELoss()<<" MeV"<<std::endl;
      }
    }
    if(!(trackerHitCollID<0)){
      trackerHC = (TrackerHitsCollection*)(HCE->GetHC(trackerHitCollID));
      for(int i=0;i<trackerHC->entries();i++){
	TVector3 Entry((*trackerHC)[i]->GetEntryPoint().getX(),(*trackerHC)[i]->GetEntryPoint().getY(),(*trackerHC)[i]->GetEntryPoint().getZ());
	TVector3 Exit((*trackerHC)[i]->GetExitPoint().getX(),(*trackerHC)[i]->GetExitPoint().getY(),(*trackerHC)[i]->GetExitPoint().getZ());
	TVector3 MomDir((*trackerHC)[i]->GetMomentumDirection().getX(),(*trackerHC)[i]->GetMomentumDirection().getY(),(*trackerHC)[i]->GetMomentumDirection().getZ());            
	theTrackerHitContainer.push_back(RootTrackerHit(Entry,Exit,(*trackerHC)[i]->GetKinEnergy(),(*trackerHC)[i]->GetToF(),(*trackerHC)[i]->GetELoss(),(*trackerHC)[i]->GetParticleType(),(*trackerHC)[i]->GetDetectorId(),(*trackerHC)[i]->GetTrackId(),(*trackerHC)[i]->GetThetaAtEntry(),(*trackerHC)[i]->GetPhiAtEntry(),MomDir));
	//if(verboseLevel>0)
	//std::cout<<"TrackerHit  # "<<i<<" ; Edep = "<<(*trackerHC)[i]->GetELoss()<<" MeV"<<std::endl;
      }
    }

    if(!(caloHitCollID<0)){
      caloHC = (CaloHitsCollection*)(HCE->GetHC(caloHitCollID));
      //G4cout << " caloHC entries " << caloHC->entries() << G4endl;
      std::map<int,TVector3> aStepPosMap;
      for(int i=0;i<caloHC->entries();i++){
        aStepPosMap.clear();
        TVector3 Entry((*caloHC)[i]->GetEntryPoint().getX(),(*caloHC)[i]->GetEntryPoint().getY(),(*caloHC)[i]->GetEntryPoint().getZ());
	TVector3 Exit((*caloHC)[i]->GetExitPoint().getX(),(*caloHC)[i]->GetExitPoint().getY(),(*caloHC)[i]->GetExitPoint().getZ());
	aStepPosMap.empty();
        unsigned int mapsize = 0;
        bool arret = false;
	for(std::map<int,G4ThreeVector>::iterator j=(*caloHC)[i]->GetStepPosMap().begin();j!=(*caloHC)[i]->GetStepPosMap().end();j++){
          mapsize++;
          if ((*caloHC)[i]->GetStepPosMap().size()<mapsize) break;
          int itkid = j->first;
          G4ThreeVector g4tv = j->second;
          TVector3 tv(g4tv.getX(),g4tv.getY(),g4tv.getZ());
	  aStepPosMap[itkid]=tv;  
	}
        if (arret) break;
	theCaloHitContainer.push_back( RootCaloHit((*caloHC)[i]->GetVolume(),Entry,Exit,(*caloHC)[i]->GetKinEnergy(),(*caloHC)[i]->GetTotalEdep()/CLHEP::MeV,(*caloHC)[i]->GetEdepMap(),aStepPosMap,(*caloHC)[i]->GetNPhot((*caloHC)[i]->GetVolume())) ); // OP
	  if(verboseLevel>0) std::cout <<"CaloHit  # "<<i<<" ; Volume = "<<(*caloHC)[i]->GetVolume()<<" ; Edep = "<<(*caloHC)[i]->GetTotalEdep()/CLHEP::MeV<<" MeV"<< std::endl;
      }
    }

    if(!(vetoHitCollID<0)){
      vetoHC = (CaloHitsCollection*)(HCE->GetHC(vetoHitCollID));
      //G4cout << " vetoHC entries " << vetoHC->entries() << G4endl; 
      std::map<int,TVector3> aStepPosMap;
      for(int i=0;i<vetoHC->entries();i++){
        aStepPosMap.clear();
        TVector3 Entry((*vetoHC)[i]->GetEntryPoint().getX(),(*vetoHC)[i]->GetEntryPoint().getY(),(*vetoHC)[i]->GetEntryPoint().getZ());	
        TVector3 Exit((*vetoHC)[i]->GetExitPoint().getX(),(*vetoHC)[i]->GetExitPoint().getY(),(*vetoHC)[i]->GetExitPoint().getZ());
        unsigned int mapsize = 0;
	//bool arret = false;
	  for(std::map<int,G4ThreeVector>::iterator j=(*vetoHC)[i]->GetStepPosMap().begin();j!=(*vetoHC)[i]->GetStepPosMap().end();j++){
            mapsize++;
            if ((*vetoHC)[i]->GetStepPosMap().size()<mapsize) break;
            int itkid = j->first;
            G4ThreeVector g4tv = j->second;
            TVector3 tv(g4tv.getX(),g4tv.getY(),g4tv.getZ());
	    aStepPosMap[itkid]=tv;  
	  }
	  theVetoHitContainer.push_back(RootCaloHit((*vetoHC)[i]->GetVolume(),Entry,Exit,(*vetoHC)[i]->GetKinEnergy(),(*vetoHC)[i]->GetTotalEdep()/CLHEP::MeV,(*vetoHC)[i]->GetEdepMap(),aStepPosMap,(*vetoHC)[i]->GetNPhot((*vetoHC)[i]->GetVolume())) ); // OP
	  if(verboseLevel>0) std::cout<<"VetoHit  # "<<i<<" ; Volume = "<<(*vetoHC)[i]->GetVolume()<<" ; Edep = "<<(*vetoHC)[i]->GetTotalEdep()/CLHEP::MeV<<" MeV"<<std::endl;
      }
    }

    if(!(trackCollID<0)){
      trackHC = (TracksCollection*)(HCE->GetHC(trackCollID));
      for(int i=0;i<trackHC->entries();i++){
        TVector3 Pos((*trackHC)[i]->GetPosition().getX(),(*trackHC)[i]->GetPosition().getY(),(*trackHC)[i]->GetPosition().getZ());
	TVector3 Dir((*trackHC)[i]->GetMomentumDirection().getX(),(*trackHC)[i]->GetMomentumDirection().getY(),(*trackHC)[i]->GetMomentumDirection().getZ());
	theTrackContainer.push_back(RootTrack((*trackHC)[i]->GetTrackId(),(*trackHC)[i]->GetPDGCode(),(*trackHC)[i]->GetName(),Pos,Dir,(*trackHC)[i]->GetKinEnergy(),(*trackHC)[i]->GetMotherTrackId(),(*trackHC)[i]->GetVertexVolumeName(),(*trackHC)[i]->GetCreatorProcessName()));
      }
    }
    
    if(!(vertexCollID<0)){
      vertexHC = (VertexsCollection*)(HCE->GetHC(vertexCollID));
      if(vertexHC->entries()){
	for(int i=0;i<vertexHC->entries();i++){
	  TString volumeName((std::string)(*vertexHC)[i]->GetVolumeName());
	  TVector3 Pos((*vertexHC)[i]->GetPosition().getX(),(*vertexHC)[i]->GetPosition().getY(),(*vertexHC)[i]->GetPosition().getZ());
	  theVertexContainer.push_back(RootVertex((*vertexHC)[i]->IsQuasielastic(),(*vertexHC)[i]->IsInelastic(),volumeName,Pos));
	}
      } else theVertexContainer.push_back(RootVertex(false,false,"NA",TVector3(0,0,0)));
    }

    if(!(pmtHitsCollID<0)){
      pmtHC = (PmtHitsCollection*)(HCE->GetHC(pmtHitsCollID));
      for(int i=0;i<pmtHC->entries();i++){
        int TotalNPhot[53];
	char PmtName[53][6];
	//	G4cout << " entree " << i << " NPmt " << (*pmtHC)[i]->GetNPmt() << G4endl;
        for (int j=0; j<53; j++) {
	  TotalNPhot[j] = (*pmtHC)[i]->GetNPhot(j);
	  //	  G4cout << " pmt " << j << " TotalNPhot " << TotalNPhot[j] << G4endl;
          switch (j) {
          case 0: sprintf(PmtName[j],"%s","T1w"); break;
          case 1: sprintf(PmtName[j],"%s","T1e"); break;
          case 2: sprintf(PmtName[j],"%s","T2w"); break;
          case 3: sprintf(PmtName[j],"%s","T2e"); break;
          case 4: sprintf(PmtName[j],"%s","T3w"); break;
          case 5: sprintf(PmtName[j],"%s","T3e"); break;
          case 6: sprintf(PmtName[j],"%s","T4w"); break;
          case 7: sprintf(PmtName[j],"%s","T4e"); break;
          case 8: sprintf(PmtName[j],"%s","T5w"); break;
          case 9: sprintf(PmtName[j],"%s","T5e"); break;
          case 10: sprintf(PmtName[j],"%s","T6w"); break;
          case 11: sprintf(PmtName[j],"%s","T6e"); break;
          case 12: sprintf(PmtName[j],"%s","P1nw"); break;
          case 13: sprintf(PmtName[j],"%s","P1se"); break;
          case 14: sprintf(PmtName[j],"%s","P2sw"); break;
          case 15: sprintf(PmtName[j],"%s","P2ne"); break;
          case 16: sprintf(PmtName[j],"%s","P3nw"); break;
          case 17: sprintf(PmtName[j],"%s","P3se"); break;
          case 18: sprintf(PmtName[j],"%s","P4sw"); break;
          case 19: sprintf(PmtName[j],"%s","P4ne"); break;
          case 20: sprintf(PmtName[j],"%s","P5nw"); break;
          case 21: sprintf(PmtName[j],"%s","P5se"); break;
          case 22: sprintf(PmtName[j],"%s","P6sw"); break;
          case 23: sprintf(PmtName[j],"%s","P6ne"); break;
          case 24: sprintf(PmtName[j],"%s","P7nw"); break;
          case 25: sprintf(PmtName[j],"%s","P7se"); break;
          case 26: sprintf(PmtName[j],"%s","P8sw"); break;
          case 27: sprintf(PmtName[j],"%s","P8ne"); break;
          case 28: sprintf(PmtName[j],"%s","P9nw"); break;
          case 29: sprintf(PmtName[j],"%s","P9se"); break;
          case 30: sprintf(PmtName[j],"%s","P10sw"); break;
          case 31: sprintf(PmtName[j],"%s","P10ne"); break;
          case 32: sprintf(PmtName[j],"%s","P11nw"); break;
          case 33: sprintf(PmtName[j],"%s","P11se"); break;
          case 34: sprintf(PmtName[j],"%s","P12sw"); break;
          case 35: sprintf(PmtName[j],"%s","P12ne"); break;
          case 36: sprintf(PmtName[j],"%s","P13nw"); break;
          case 37: sprintf(PmtName[j],"%s","P13se"); break;
          case 38: sprintf(PmtName[j],"%s","P14sw"); break;
          case 39: sprintf(PmtName[j],"%s","P14ne"); break;
          case 40: sprintf(PmtName[j],"%s","P15nw"); break;
          case 41: sprintf(PmtName[j],"%s","P15se"); break;
          case 42: sprintf(PmtName[j],"%s","P16sw"); break;
          case 43: sprintf(PmtName[j],"%s","P16ne"); break;
          case 44: sprintf(PmtName[j],"%s","L1ne"); break;
          case 45: sprintf(PmtName[j],"%s","L4n"); break;
          case 46: sprintf(PmtName[j],"%s","L7nw"); break;
          case 47: sprintf(PmtName[j],"%s","L2e"); break;
          case 48: sprintf(PmtName[j],"%s","L5c"); break;
          case 49: sprintf(PmtName[j],"%s","L8w"); break;
          case 50: sprintf(PmtName[j],"%s","L3se"); break;
          case 51: sprintf(PmtName[j],"%s","L6s"); break;
          case 52: sprintf(PmtName[j],"%s","L9sw"); break;
          default: break;
          }
        }	
	thePmtHitsContainer.push_back(RootPmtHits(TotalNPhot,&PmtName[0],
						  (*pmtHC)[i]->GetNPmt()));
      }
    }

    

    if(verboseLevel>0)
      std::cout<<"=============================================================================================="<<std::endl;
  }


  if(verboseLevel>0)
    G4cout << "theEvent: " << theEvent << G4endl;
  theEvent->SetEventID(eventID);
  if(verboseLevel>0)
    G4cout << "saveCalo: " << saveCalo <<  "\tsaveTracker: " << saveTracker << "\tsaveDegrader: " << saveDegrader <<"\tsaveMCTruth: " << saveMCTruth << G4endl;
  if(saveCalo){
    theEvent->SetCaloHit(theCaloHitContainer);
    theEvent->SetVetoHit(theVetoHitContainer);
    theEvent->SetPmtHits(thePmtHitsContainer);
  }
  if(saveTracker)
    theEvent->SetTrackerHit(theTrackerHitContainer);
  if(saveDegrader)
    theEvent->SetDegraderHit(theDegraderHitContainer);
  if(saveMCTruth){
    theEvent->SetTracks(theTrackContainer);
    theEvent->SetVertex(theVertexContainer);
  }
  //if(verboseLevel>0)
  //G4cout << "theEventTree: 0x" << theEventTree << G4endl;
  theEventTree->Fill();
  if(verboseLevel>0)
    G4cout << "leaving in EndOfEventAction..." << G4endl;

}

