//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 25 10:41:51 2013 by ROOT version 5.34/09
// from TTree EventTree/The Tree with the variable used to performe the calculation of energy deposition on the HEPD detector
// found on file: Electron5MeV_4M.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TString.h>
#include <TMath.h>
#include <vector>
#include <iostream>
#include <fstream>

// Header file for the classes stored in the TTree if any.
#include "/data8/wduser/wjb/aiglon/geant4/HEPDSW/source/Dataformats/include/RootEvent.hh"
#include "/data8/wduser/wjb/aiglon/geant4/HEPDSW/source/Dataformats/include/RootTrack.hh"
#include "/data8/wduser/wjb/aiglon/geant4/HEPDSW/source/Dataformats/include/RootVertex.hh"
#include "/data8/wduser/wjb/aiglon/geant4/HEPDSW/source/Dataformats/include/RootCaloHit.hh"
#include "/data8/wduser/wjb/aiglon/geant4/HEPDSW/source/Dataformats/include/RootTrackerHit.hh"

//#include "/home/wjb_local/aiglon/geant4/HEPDSW/source/Dataformats/include/RootEvent.hh"
//#include "/home/wjb_local/aiglon/geant4/HEPDSW/source/Dataformats/include/RootTrack.hh"
//#include "/home/wjb_local/aiglon/geant4/HEPDSW/source/Dataformats/include/RootVertex.hh"
//#include "/home/wjb_local/aiglon/geant4/HEPDSW/source/Dataformats/include/RootCaloHit.hh"
//#include "/home/wjb_local/aiglon/geant4/HEPDSW/source/Dataformats/include/RootTrackerHit.hh"

#include <TObject.h>
#include <TVector3.h>


class Analyzer {
public :
   TTree          *fTree;        //!pointer to the analyzed TTree
   TChain         *fTreeChain;   //!pointer to the analyzed TChain
   Int_t           fCurrent;     //!current Tree number in a TChain
   // Declaration of leaf types
   RootEvent   *Event;
   double VETOEdep;
   double TOTALEdep;

   // List of branches
   TBranch        *b_Event;   //!
   
   float theERange;
   Bool_t checkPos;
   Bool_t checkTheta;
   Double_t Xlimit,Ylimit,Thetalimit;

   Int_t numbCaloLayer,numbLayerScint,numbLayerCrystal;

   TFile* fichhist;

   float Xgen; // cm
   float Ygen; // cm
   float sigma; // angle solide

   // hist acc
   TH2D* rtheta_gen;
   TH2D* rtheta_acc;
   TH2D* rtheta_acc_sv; //sans veto
   TH2D* rtheta_acc_svl; //sans veto lateral

   // histograms
   TProfile*          layerDepthElectron;
   TProfile*          layerDepthProton;
   TProfile*          energyAVGRangeElectron;
   TProfile*          energySUMRangeElectron;
   TProfile*          energyAVGRangeProton;
   TProfile*          energySUMRangeProton;
   TH1F*              Ecinetique_gen;
   TH1F*              Ecinetique_acc_trk;
   TH1F*              Ecinetique_acc_sci;
   TH1F*              Ecinetique_acc_veto;
   TH2D*              Vertex_xy_gen;
   TH2D*              Vertex_xy_acc_trk;
   TH2D*              Vertex_xy_acc_sci;
   TH2D*              Vertex_xy_acc_veto;
   TH2D*              Vertex_xy_gen_ce;
   TH2D*              Vertex_xy_acc_trk_ce;
   TH2D*              Vertex_xy_acc_sci_ce;
   TH2D*              Vertex_xy_acc_veto_ce;
   TH1F*              Pcinetique_gen;
   TH1F*              Pcinetique_acc_trk;
   TH1F*              Pcinetique_acc_sci;
   TH1F*              Pcinetique_acc_veto;

   Analyzer();
   virtual ~Analyzer();
   virtual void     SetFile(TString fileName);
   virtual void     SetFileChain(TString fileName);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     InitChain();
   virtual void     Loop_acc();
   virtual void     Loop();
   virtual void     Loop_P();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     InitHisto_e_acc(float energie);
   virtual void     InitHisto_p_acc(float energie);
   virtual void     CloseHisto_acc();
   virtual void     InitHisto();
   virtual void     CloseHisto();
   virtual void     InitHisto_P();
   virtual void     CloseHisto_P();
   virtual void     SetThetaAcceptance(Double_t theta); //in degree
   virtual void     SetAcceptanceWindows(Double_t X, Double_t Y); //in millimiters
   virtual Double_t ComputeAngle(std::vector<RootTrackerHit>& myTkHit);
   virtual Double_t ComputeAngleWithSmearing(std::vector<RootTrackerHit>& myTkHit,Double_t delta);
};

#endif
 
#ifdef Analyzer_cxx
Analyzer::Analyzer() : fTree(0)
{
   Xgen = 2*27.5; // cm
   Ygen = 2*37.5; // cm
   sigma = TMath::Pi(); // angle solide
}

Analyzer::~Analyzer()
{
   if (!fTree) return;
   delete fTree->GetCurrentFile();
}

void Analyzer::SetFile(TString fileName)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName);
  if (!f || !f->IsOpen()) {
    f = new TFile(fileName);
  }
  fileName.Append(":/HEPD");
  TDirectory * dir = (TDirectory*)f->Get(fileName);
  dir->GetObject("EventTree",fTree);
  Init(fTree);  
  
}

void Analyzer::SetFileChain(TString fileName)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  //fileName.Append(":/HEPD");
  TString HEPDPath = "/HEPD/EventTree";
  fTreeChain = new TChain(HEPDPath);

  std::ifstream File_Input(fileName);
  if (!File_Input){
    std::cout<<"List of ROOT file NOT found"<<std::endl;
    return;
  }
  while(!File_Input.eof()){
    TString singlefile = "noName";
    File_Input>> singlefile;
    if(singlefile!="noName"&&singlefile!=""){
    fTreeChain->Add(singlefile);
    printf("ajoute %s\n",singlefile.Data());
    }
  }
  File_Input.close();
  InitChain();  
}


Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fTree) return 0;
   return fTree->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
//   printf("load tree\n");
   if (!fTreeChain) return -5;
   Long64_t centry = fTreeChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fTreeChain->GetTreeNumber() != fCurrent) {
      fCurrent = fTreeChain->GetTreeNumber();
      Notify();
   }
   //   printf("load tree\n",fTree);
   return centry;
}

void Analyzer::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  Event = 0;
  if (!tree) return;
  fTree = tree;
  fCurrent = -1;
  
  fTree->SetBranchAddress("Event", &Event, &b_Event);
  Notify();
}

void Analyzer::InitChain()
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  Event = 0;
  fCurrent = -1;
  printf("fTreeChain %d\n",fTreeChain);
  
  fTreeChain->SetBranchAddress("Event", &Event, &b_Event);
  printf("fTreeChain %d\n",fTreeChain);
  Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fTree) return;
   fTree->Show(entry);
}
#endif // #ifdef Analyzer_cxx
