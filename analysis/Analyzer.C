#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <iostream>
#include <TRandom.h>
#include <TMath.h>
#include <iostream>
 
void Analyzer::InitHisto_e_acc(float energie){

  TString cfichhist = Form("HistElectron_acct6_%3.1f_MeV.root",energie);
  fichhist = new TFile(cfichhist,"recreate");

  Double_t theERange = energie;
  printf("energie %3.1f \n",energie);
  char chistg[10];
  char chista[10];
  char chistasv[10];
  char chistasvl[10];

  int nebin = 16;
  Double_t ebin[16] = { 2, 3, 5, 10, 15, 25, 35, 45, 55, 75, 100, 125, 150, 200, 6.7, 8.4};
  Double_t epsilon = 0.001;

  for (int i=0; i<nebin; i++) {
    if(TMath::AreEqualRel(theERange,ebin[i],epsilon)) {
      sprintf(chistg,"h%d",1000+i);
      sprintf(chista,"h%d",1100+i);
      sprintf(chistasv,"h%d",1200+i);
      sprintf(chistasvl,"h%d",1300+i);
    }
  }
  /*
  if(theERange == 2.0){
    sprintf(chistg,"h1000");
    sprintf(chista,"h1100");
    sprintf(chistasv,"h1200");
  }else if(theERange == 3){
    sprintf(chistg,"h1001");
    sprintf(chista,"h1101");
    sprintf(chistasv,"h1201");
  }else if(theERange == 5){
    sprintf(chistg,"h1002");
    sprintf(chista,"h1102");
    sprintf(chistasv,"h1202");
  }else if(theERange == 10){
    sprintf(chistg,"h1003");
    sprintf(chista,"h1103");
    sprintf(chistasv,"h1203");
  }else if(theERange == 15){
    sprintf(chistg,"h1004");
    sprintf(chista,"h1104");
    sprintf(chistasv,"h1204");
  }else if(theERange == 25){
    sprintf(chistg,"h1005");
    sprintf(chista,"h1105");
    sprintf(chistasv,"h1205");
  }else if(theERange == 35){
    sprintf(chistg,"h1006");
    sprintf(chista,"h1106");
    sprintf(chistasv,"h1206");
  }else if(theERange == 45){
    sprintf(chistg,"h1007");
    sprintf(chista,"h1107");
    sprintf(chistasv,"h1207");
  }else if(theERange == 55){
    sprintf(chistg,"h1008");
    sprintf(chista,"h1108");
    sprintf(chistasv,"h1208");
  }else if(theERange == 75){
    sprintf(chistg,"h1009");
    sprintf(chista,"h1109");
    sprintf(chistasv,"h1209");
  }else if(theERange == 100){
    sprintf(chistg,"h1010");
    sprintf(chista,"h1110");
    sprintf(chistasv,"h1210");
  }else if(theERange == 125){
    sprintf(chistg,"h1011");
    sprintf(chista,"h1111");
    sprintf(chistasv,"h1211");
  }else if(theERange == 150){
    sprintf(chistg,"h1012");
    sprintf(chista,"h1112");
    sprintf(chistasv,"h1212");
  }else if(theERange == 200){
    sprintf(chistg,"h1013");
    sprintf(chista,"h1113");
    sprintf(chistasv,"h1213");
  }else if(AreEqualAbs(theERange,6.7,0.1)){
    sprintf(chistg,"h1014");
    sprintf(chista,"h1114");
    sprintf(chistasv,"h1214");
    } */
  float rmax = (Xgen/2)*(Xgen/2) + (Ygen/2)*(Ygen/2);
  rmax = TMath::Sqrt(rmax);
  printf("chistg %s\n",chistg);
  printf("chista %s\n",chista);
  printf("chistasv %s\n",chistasv);
  printf("chistasvl %s\n",chistasvl);
  rtheta_gen = new TH2D(chistg,"rtheta gen",50,0,rmax,50,0,90);
  rtheta_acc = new TH2D(chista,"rtheta acc",50,0,rmax,50,0,90);
  rtheta_acc_sv = new TH2D(chistasv,"rtheta acc sans veto",50,0,rmax,50,0,90);
  rtheta_acc_svl = new TH2D(chistasvl,"rtheta acc sans veto lat",50,0,rmax,50,0,90);

}
 
void Analyzer::InitHisto_p_acc(float energie){

  TString cfichhist = Form("HistProton_acct6_%3.1f_MeV.root",energie);
  fichhist = new TFile(cfichhist,"recreate");

  float theERange = energie;
  printf("energie %3.1f \n",energie);
  char chistg[10];
  char chista[10];
  char chistasv[10];
  char chistasvl[10];
  if(theERange == 30){
    sprintf(chistg,"h1000");
    sprintf(chista,"h1100");
    sprintf(chistasv,"h1200");
    sprintf(chistasvl,"h1300");
  }else if(theERange == 35){
    sprintf(chistg,"h1001");
    sprintf(chista,"h1101");
    sprintf(chistasv,"h1201");
    sprintf(chistasvl,"h1301");
  }else if(theERange == 55){
    sprintf(chistg,"h1002");
    sprintf(chista,"h1102");
    sprintf(chistasv,"h1202");
    sprintf(chistasvl,"h1302");
  }else if(theERange == 75){
    sprintf(chistg,"h1003");
    sprintf(chista,"h1103");
    sprintf(chistasv,"h1203");
    sprintf(chistasvl,"h1303");
  }else if(theERange == 100){
    sprintf(chistg,"h1004");
    sprintf(chista,"h1104");
    sprintf(chistasv,"h1204");
    sprintf(chistasvl,"h1304");
  }else if(theERange == 125){
    sprintf(chistg,"h1005");
    sprintf(chista,"h1105");
    sprintf(chistasv,"h1205");
    sprintf(chistasvl,"h1305");
  }else if(theERange == 150){
    sprintf(chistg,"h1006");
    sprintf(chista,"h1106");
    sprintf(chistasv,"h1206");
    sprintf(chistasvl,"h1306");
  }else if(theERange == 200){
    sprintf(chistg,"h1007");
    sprintf(chista,"h1107");
    sprintf(chistasv,"h1207");
    sprintf(chistasvl,"h1307");
  }else if(theERange == 225){
    sprintf(chistg,"h1008");
    sprintf(chista,"h1108");
    sprintf(chistasv,"h1208");
    sprintf(chistasvl,"h1308");
  }else if(theERange == 250){
    sprintf(chistg,"h1009");
    sprintf(chista,"h1109");
    sprintf(chistasv,"h1209");
    sprintf(chistasvl,"h1309");
  }else if(theERange == 300){
    sprintf(chistg,"h1010");
    sprintf(chista,"h1110");
    sprintf(chistasv,"h1210");
    sprintf(chistasvl,"h1310");
  }else if(theERange == 45){
    sprintf(chistg,"h1011");
    sprintf(chista,"h1111");
    sprintf(chistasv,"h1211");
    sprintf(chistasvl,"h1311");
  }else if(theERange == 65){
    sprintf(chistg,"h1012");
    sprintf(chista,"h1112");
    sprintf(chistasv,"h1212");
    sprintf(chistasvl,"h1312");
  }else if(theERange == 450){
    sprintf(chistg,"h1013");
    sprintf(chista,"h1113");
    sprintf(chistasv,"h1213");
    sprintf(chistasvl,"h1313");
  }else if(theERange == 500){
    sprintf(chistg,"h1014");
    sprintf(chista,"h1114");
    sprintf(chistasv,"h1214");
    sprintf(chistasvl,"h1314");
  }
  float rmax = (Xgen/2)*(Xgen/2) + (Ygen/2)*(Ygen/2);
  rmax = TMath::Sqrt(rmax);
  printf("chistg %s\n",chistg);
  printf("chista %s\n",chista);
  printf("chistasv %s\n",chistasv);
  printf("chistasvl %s\n",chistasvl);
  rtheta_gen = new TH2D(chistg,"rtheta gen",50,0,rmax,50,0,90);
  rtheta_acc = new TH2D(chista,"rtheta acc",50,0,rmax,50,0,90);
  rtheta_acc_sv = new TH2D(chistasv,"rtheta acc sans veto",50,0,rmax,50,0,90);
  rtheta_acc_svl = new TH2D(chistasvl,"rtheta acc sans veto lat",50,0,rmax,50,0,90);

}

void Analyzer::CloseHisto_acc() {

  fichhist->ls();
  fichhist->cd();
   //  hf->Write();
  int nx = rtheta_gen->GetNbinsX();
  int ny = rtheta_gen->GetNbinsY();
  float ngen = rtheta_gen->GetEntries();
  printf("ngen %f\n",ngen);
  int bin;
 
  float val_acc;
  for (int ix=1; ix<=nx; ix++)
    for (int iy=1; iy<=ny; iy++) {
      bin = rtheta_gen->GetBin(ix,iy);
      val_acc = rtheta_acc->GetBinContent(bin);
      val_acc*=(Xgen*Ygen*sigma/ngen);
      //      printf("bin %d, val_acc %f\n",bin,val_acc);
      rtheta_acc->SetBinContent(bin,val_acc);
      val_acc = rtheta_acc_sv->GetBinContent(bin);
      val_acc*=(Xgen*Ygen*sigma/ngen);
      //      printf("bin %d, val_acc_sv %f\n",bin,val_acc);
      rtheta_acc_sv->SetBinContent(bin,val_acc);
      val_acc = rtheta_acc_svl->GetBinContent(bin);
      val_acc*=(Xgen*Ygen*sigma/ngen);
      //      printf("bin %d, val_acc_sv %f\n",bin,val_acc);
      rtheta_acc_svl->SetBinContent(bin,val_acc);
    };

  rtheta_gen->Write();
  rtheta_acc->Write();
  rtheta_acc_sv->Write();
  rtheta_acc_svl->Write();
        
  return;

}

void Analyzer::InitHisto(){
  layerDepthElectron = new TProfile("layerDepthElectron","Calo Layer Depth",250,0,250,0,24);  
  layerDepthProton = new TProfile("layerDepthProton","Calo Layer Depth",250,0,250,0,24);  
  
  energyAVGRangeElectron = new TProfile("energyAVGRangeElectron","Energy ratio between LYSO and SCINT(AVG)",300,0,300,0,15);
  energySUMRangeElectron = new TProfile("energySUMRangeElectron","Energy ratio between LYSO and SCINT(SUM)",300,0,300,0,15);

  energyAVGRangeProton = new TProfile("energyAVGRangeProton","Energy ratio between LYSO and SCINT(AVG)",300,0,300,0,15);
  energySUMRangeProton = new TProfile("energySUMRangeProton","Energy ratio between LYSO and SCINT(SUM)",300,0,300,0,15);

  Ecinetique_gen = new TH1F("hecgen","Distribution Ek generated",1000,0,200);
  Ecinetique_gen->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Ecinetique_gen->GetXaxis()->CenterTitle(true);
  Ecinetique_gen->GetXaxis()->SetTitleSize(0.06);
  Ecinetique_gen->GetXaxis()->SetTitleOffset(1.10);
  Ecinetique_gen->GetXaxis()->SetLabelOffset(0.001);
  Ecinetique_gen->GetXaxis()->SetLabelSize(0.055);
  Ecinetique_gen->GetYaxis()->SetTitle("Entries");  
  Ecinetique_gen->GetYaxis()->CenterTitle(true);
  Ecinetique_gen->GetYaxis()->SetTitleSize(0.06);
  Ecinetique_gen->GetYaxis()->SetTitleOffset(1.10);
  Ecinetique_gen->GetYaxis()->SetLabelSize(0.055);
  Ecinetique_gen->SetLineColor(kBlue);
  Ecinetique_gen->GetXaxis()->SetRangeUser(0.5,200.);

  Vertex_xy_gen = new TH2D("hvxgen","Distribution XY generated",250,-40,40,300,-50,50);
  Vertex_xy_gen->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_gen->GetXaxis()->CenterTitle(true);
  Vertex_xy_gen->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_gen->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_gen->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_gen->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_gen->GetYaxis()->CenterTitle(true);
  Vertex_xy_gen->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_gen->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_gen->SetLineColor(kBlue);

  Vertex_xy_gen_ce = new TH2D("hvxgence","Distribution XY generated ce",250,-40,40,300,-50,50);
  Vertex_xy_gen_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_gen_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_gen_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_gen_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_gen_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_gen_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_gen_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_gen_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_gen_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_gen_ce->SetLineColor(kBlue);
 
  Ecinetique_acc_trk = new TH1F("hecacctrk","Distribution Ek accepteed trk",1000,0,200);
  Ecinetique_acc_trk->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Ecinetique_acc_trk->GetXaxis()->CenterTitle(true);
  Ecinetique_acc_trk->GetXaxis()->SetTitleSize(0.06);
  Ecinetique_acc_trk->GetXaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_trk->GetXaxis()->SetLabelSize(0.05);
  Ecinetique_acc_trk->GetXaxis()->SetLabelOffset(0.001);
  Ecinetique_acc_trk->GetYaxis()->SetTitle("Entries");  
  Ecinetique_acc_trk->GetYaxis()->CenterTitle(true);
  Ecinetique_acc_trk->GetYaxis()->SetTitleSize(0.06);
  Ecinetique_acc_trk->GetYaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_trk->GetYaxis()->SetLabelSize(0.055);
  Ecinetique_acc_trk->SetLineColor(kBlue);
  Ecinetique_acc_trk->GetXaxis()->SetRangeUser(0.5,200.);

  Vertex_xy_acc_trk = new TH2D("hvxacc_trk","Distribution XY trk acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_trk->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_trk->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_trk->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_trk->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_trk->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_trk->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk->SetLineColor(kBlue);

  Vertex_xy_acc_trk_ce = new TH2D("hvxacc_trkce","Distribution XY trk acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_trk_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_trk_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk_ce->SetLineColor(kBlue);

  Ecinetique_acc_sci = new TH1F("hecaccaco","Distribution Ek accepteed sci",1000,0,200);
  Ecinetique_acc_sci->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Ecinetique_acc_sci->GetXaxis()->CenterTitle(true);
  Ecinetique_acc_sci->GetXaxis()->SetTitleSize(0.06);
  Ecinetique_acc_sci->GetXaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_sci->GetXaxis()->SetLabelSize(0.055);
  Ecinetique_acc_sci->GetXaxis()->SetLabelOffset(0.001);
  Ecinetique_acc_sci->GetYaxis()->SetTitle("Entries");  
  Ecinetique_acc_sci->GetYaxis()->CenterTitle(true);
  Ecinetique_acc_sci->GetYaxis()->SetTitleSize(0.06);
  Ecinetique_acc_sci->GetYaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_sci->GetYaxis()->SetLabelSize(0.055);
  Ecinetique_acc_sci->SetLineColor(kBlue);
  Ecinetique_acc_sci->GetXaxis()->SetRangeUser(0.5,200.);

  Vertex_xy_acc_sci = new TH2D("hvxacc_sci","Distribution XY sci acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_sci->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_sci->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_sci->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_sci->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_sci->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_sci->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci->SetLineColor(kBlue);

  Vertex_xy_acc_sci_ce = new TH2D("hvxacc_sci_ce","Distribution XY sci acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_sci_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_sci_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci_ce->SetLineColor(kBlue);

  Ecinetique_acc_veto = new TH1F("hecaccvetp","Distribution Ek accepteed veto",1000,0,200);
  Ecinetique_acc_veto->GetXaxis()->SetTitle("Kinetic Energy (MeV)");
  Ecinetique_acc_veto->GetXaxis()->CenterTitle(true);
  Ecinetique_acc_veto->GetXaxis()->SetTitleSize(0.06);
  Ecinetique_acc_veto->GetXaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_veto->GetXaxis()->SetLabelSize(0.055);
  Ecinetique_acc_veto->GetXaxis()->SetLabelOffset(0.001);
  Ecinetique_acc_veto->GetYaxis()->SetTitle("Entries");  
  Ecinetique_acc_veto->GetYaxis()->CenterTitle(true);
  Ecinetique_acc_veto->GetYaxis()->SetTitleSize(0.06);
  Ecinetique_acc_veto->GetYaxis()->SetTitleOffset(1.10);
  Ecinetique_acc_veto->GetYaxis()->SetLabelSize(0.055);
  Ecinetique_acc_veto->SetLineColor(kBlue);
  Ecinetique_acc_veto->GetXaxis()->SetRangeUser(0.5,200.);

  Vertex_xy_acc_veto = new TH2D("hvxacc_veto","Distribution XY veto acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_veto->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_veto->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_veto->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_veto->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_veto->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_veto->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto->SetLineColor(kBlue);

  Vertex_xy_acc_veto_ce = new TH2D("hvxacc_veto_ce","Distribution XY sci acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_veto_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_veto_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto_ce->SetLineColor(kBlue);

}

void Analyzer::InitHisto_P(){

  Pcinetique_gen = new TH1F("hecgen","Distribution Ek generated",5000,5,500);
  Pcinetique_gen->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Pcinetique_gen->GetXaxis()->CenterTitle(true);
  Pcinetique_gen->GetXaxis()->SetTitleSize(0.06);
  Pcinetique_gen->GetXaxis()->SetTitleOffset(1.10);
  Pcinetique_gen->GetXaxis()->SetLabelOffset(0.001);
  Pcinetique_gen->GetXaxis()->SetLabelSize(0.055);
  Pcinetique_gen->GetYaxis()->SetTitle("Entries");  
  Pcinetique_gen->GetYaxis()->CenterTitle(true);
  Pcinetique_gen->GetYaxis()->SetTitleSize(0.06);
  Pcinetique_gen->GetYaxis()->SetTitleOffset(1.10);
  Pcinetique_gen->GetYaxis()->SetLabelSize(0.055);
  Pcinetique_gen->SetLineColor(kRed);
  //  Pcinetique_gen->GetXaxis()->SetRangeUser(0.5,500.);

  Vertex_xy_gen = new TH2D("hvxgen","Distribution XY generated",250,-40,40,300,-50,50);
  Vertex_xy_gen->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_gen->GetXaxis()->CenterTitle(true);
  Vertex_xy_gen->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_gen->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_gen->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_gen->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_gen->GetYaxis()->CenterTitle(true);
  Vertex_xy_gen->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_gen->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_gen->SetLineColor(kBlue);

  Vertex_xy_gen_ce = new TH2D("hvxgence","Distribution XY generated ce",250,-40,40,300,-50,50);
  Vertex_xy_gen_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_gen_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_gen_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_gen_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_gen_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_gen_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_gen_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_gen_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_gen_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_gen_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_gen_ce->SetLineColor(kBlue);
 
  Pcinetique_acc_trk = new TH1F("hecacctrk","Distribution Ek accepteed trk",5000,5,500);
  Pcinetique_acc_trk->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Pcinetique_acc_trk->GetXaxis()->CenterTitle(true);
  Pcinetique_acc_trk->GetXaxis()->SetTitleSize(0.06);
  Pcinetique_acc_trk->GetXaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_trk->GetXaxis()->SetLabelSize(0.05);
  Pcinetique_acc_trk->GetXaxis()->SetLabelOffset(0.001);
  Pcinetique_acc_trk->GetYaxis()->SetTitle("Entries");  
  Pcinetique_acc_trk->GetYaxis()->CenterTitle(true);
  Pcinetique_acc_trk->GetYaxis()->SetTitleSize(0.06);
  Pcinetique_acc_trk->GetYaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_trk->GetYaxis()->SetLabelSize(0.055);
  Pcinetique_acc_trk->SetLineColor(kRed);
  //  Pcinetique_acc_trk->GetXaxis()->SetRangeUser(0.5,500.);

  Vertex_xy_acc_trk = new TH2D("hvxacc_trk","Distribution XY trk acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_trk->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_trk->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_trk->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_trk->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_trk->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_trk->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk->SetLineColor(kBlue);

  Vertex_xy_acc_trk_ce = new TH2D("hvxacc_trkce","Distribution XY trk acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_trk_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_trk_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_trk_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_trk_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_trk_ce->SetLineColor(kBlue);

  Pcinetique_acc_sci = new TH1F("hecaccaco","Distribution Ek accepteed sci",5000,5,500);
  Pcinetique_acc_sci->GetXaxis()->SetTitle("Kineteic Energy (MeV)");
  Pcinetique_acc_sci->GetXaxis()->CenterTitle(true);
  Pcinetique_acc_sci->GetXaxis()->SetTitleSize(0.06);
  Pcinetique_acc_sci->GetXaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_sci->GetXaxis()->SetLabelSize(0.055);
  Pcinetique_acc_sci->GetXaxis()->SetLabelOffset(0.001);
  Pcinetique_acc_sci->GetYaxis()->SetTitle("Entries");  
  Pcinetique_acc_sci->GetYaxis()->CenterTitle(true);
  Pcinetique_acc_sci->GetYaxis()->SetTitleSize(0.06);
  Pcinetique_acc_sci->GetYaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_sci->GetYaxis()->SetLabelSize(0.055);
  Pcinetique_acc_sci->SetLineColor(kRed);
  //  Pcinetique_acc_sci->GetXaxis()->SetRangeUser(0.5,500.);

  Vertex_xy_acc_sci = new TH2D("hvxacc_sci","Distribution XY sci acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_sci->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_sci->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_sci->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_sci->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_sci->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_sci->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci->SetLineColor(kBlue);

  Vertex_xy_acc_sci_ce = new TH2D("hvxacc_sci_ce","Distribution XY sci acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_sci_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_sci_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_sci_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_sci_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_sci_ce->SetLineColor(kBlue);

  Pcinetique_acc_veto = new TH1F("hecaccvetp","Distribution Ek accepteed veto",5000,5,500);
  Pcinetique_acc_veto->GetXaxis()->SetTitle("Kinetic Energy (MeV)");
  Pcinetique_acc_veto->GetXaxis()->CenterTitle(true);
  Pcinetique_acc_veto->GetXaxis()->SetTitleSize(0.06);
  Pcinetique_acc_veto->GetXaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_veto->GetXaxis()->SetLabelSize(0.055);
  Pcinetique_acc_veto->GetXaxis()->SetLabelOffset(0.001);
  Pcinetique_acc_veto->GetYaxis()->SetTitle("Entries");  
  Pcinetique_acc_veto->GetYaxis()->CenterTitle(true);
  Pcinetique_acc_veto->GetYaxis()->SetTitleSize(0.06);
  Pcinetique_acc_veto->GetYaxis()->SetTitleOffset(1.10);
  Pcinetique_acc_veto->GetYaxis()->SetLabelSize(0.055);
  Pcinetique_acc_veto->SetLineColor(kRed);
  //  Pcinetique_acc_veto->GetXaxis()->SetRangeUser(0.5,500.);

  Vertex_xy_acc_veto = new TH2D("hvxacc_veto","Distribution XY veto acc",250,-40,40,300,-50,50);
  Vertex_xy_acc_veto->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_veto->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_veto->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_veto->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_veto->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_veto->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto->SetLineColor(kBlue);

  Vertex_xy_acc_veto_ce = new TH2D("hvxacc_veto_ce","Distribution XY sci acc ce",250,-40,40,300,-50,50);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitle("Vertex X Position (cm)");
  Vertex_xy_acc_veto_ce->GetXaxis()->CenterTitle(true);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetLabelOffset(0.001);
  Vertex_xy_acc_veto_ce->GetXaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitle("Verteix Y Position (cm)");  
  Vertex_xy_acc_veto_ce->GetYaxis()->CenterTitle(true);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitleSize(0.06);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetTitleOffset(1.10);
  Vertex_xy_acc_veto_ce->GetYaxis()->SetLabelSize(0.055);
  Vertex_xy_acc_veto_ce->SetLineColor(kBlue);

}

void Analyzer::CloseHisto(){
  
  TCanvas* c1f = new TCanvas("c1f","",200,10,700,500);
  gStyle->SetOptStat(0);
  layerDepthElectron->SetMarkerColor(kBlue);
  layerDepthElectron->SetMarkerStyle(22);
  layerDepthElectron->SetMarkerSize(2);
  layerDepthElectron->GetXaxis()->SetTitle("Energy [MeV]");
  layerDepthElectron->GetXaxis()->CenterTitle(true);
  layerDepthElectron->GetXaxis()->SetTitleSize(0.05);
  layerDepthElectron->GetXaxis()->SetTitleOffset(0.90);
  layerDepthElectron->GetXaxis()->SetLabelSize(0.05);
  layerDepthElectron->GetYaxis()->SetTitle("<#> Layer");  
  layerDepthElectron->GetYaxis()->CenterTitle(true);
  layerDepthElectron->GetYaxis()->SetTitleSize(0.05);
  layerDepthElectron->GetYaxis()->SetTitleOffset(0.90);
  layerDepthElectron->GetYaxis()->SetLabelSize(0.05);

  layerDepthProton->SetMarkerColor(kRed);
  layerDepthProton->SetMarkerStyle(23);
  layerDepthProton->SetMarkerSize(2);
  layerDepthProton->GetXaxis()->SetTitle("Energy [MeV]");
  layerDepthProton->GetXaxis()->CenterTitle(true);
  layerDepthProton->GetXaxis()->SetTitleSize(0.06);
  layerDepthProton->GetXaxis()->SetTitleOffset(1.10);
  layerDepthProton->GetXaxis()->SetLabelSize(0.055);
  layerDepthProton->GetYaxis()->SetTitle("<#> Layer");  
  layerDepthProton->GetYaxis()->CenterTitle(true);
  layerDepthProton->GetYaxis()->SetTitleSize(0.06);
  layerDepthProton->GetYaxis()->SetTitleOffset(1.10);
  layerDepthProton->GetYaxis()->SetLabelSize(0.05);

  if(layerDepthElectron->GetBinContent(layerDepthElectron->GetMaximumBin())>layerDepthProton->GetBinContent(layerDepthProton->GetMaximumBin())){
    layerDepthElectron->Draw();
    layerDepthProton->Draw("same");
  }else{
    layerDepthProton->Draw();
    layerDepthElectron->Draw("same");
  }

  //  c1f->SaveAs("LayerDepth.eps");

  TCanvas* c2f = new TCanvas("c2f","",200,10,700,500);
  gStyle->SetOptStat(0);  
  
  energyAVGRangeElectron->SetMarkerColor(kBlue);
  energyAVGRangeElectron->SetMarkerStyle(22);
  energyAVGRangeElectron->SetMarkerSize(1);
  energyAVGRangeElectron->SetTitle("");
  energyAVGRangeElectron->GetXaxis()->SetTitle("Energy [MeV]");
  energyAVGRangeElectron->GetYaxis()->SetTitle("E_{Rec LYSO}/<E_{Rec SCINT}>"); 
  energyAVGRangeElectron->SetLineColor(kBlue);
  
  energyAVGRangeElectron->Draw("BOX");

  //  c2f->SaveAs("Figure/TestE_AVG.eps");

  TCanvas* c3f = new TCanvas("c3f","",200,10,700,500);
  gStyle->SetOptStat(0);
  energySUMRangeElectron->SetMarkerColor(kBlue);
  energySUMRangeElectron->SetMarkerStyle(22);
  energyAVGRangeElectron->SetMarkerSize(1);
  energySUMRangeElectron->SetTitle("");
  energySUMRangeElectron->GetXaxis()->SetTitle("Energy [MeV]");
  energySUMRangeElectron->GetYaxis()->SetTitle("E_{Rec LYSO}/#Sigma E_{Rec SCINT}"); 
  energySUMRangeElectron->SetLineColor(kBlue);
  
  energySUMRangeElectron->Draw("BOX");

  //  c3f->SaveAs("Figure/TestE_SUM.eps");
  
  TCanvas* c4f = new TCanvas("c4f","",200,10,700,500);
  gStyle->SetOptStat(0);
  energyAVGRangeProton->SetMarkerColor(kRed);
  energyAVGRangeProton->SetMarkerStyle(22);
  energyAVGRangeProton->SetMarkerSize(1);
  energyAVGRangeProton->SetTitle("");
  energyAVGRangeProton->GetXaxis()->SetTitle("Energy [MeV]");
  energyAVGRangeProton->GetYaxis()->SetTitle("E_{Rec LYSO}/<E_{Rec SCINT}>"); 
  energyAVGRangeProton->SetLineColor(kRed);
  
  energyAVGRangeProton->Draw("BOX");

  //  c4f->SaveAs("Figure/TestP_AVG.eps");

  TCanvas* c5f = new TCanvas("c5f","",200,10,700,500);
  gStyle->SetOptStat(0);
  energySUMRangeProton->SetMarkerColor(kRed);
  energySUMRangeProton->SetMarkerStyle(22);
  energySUMRangeProton->SetMarkerSize(1);
  energySUMRangeProton->SetTitle("");
  energySUMRangeProton->GetXaxis()->SetTitle("Energy [MeV]");
  energySUMRangeProton->GetYaxis()->SetTitle("E_{Rec LYSO}/#Sigma E_{Rec SCINT}"); 
  energySUMRangeProton->SetLineColor(kRed);
  
  energySUMRangeProton->Draw("BOX");

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadColor(10);
  gStyle->SetPalette(1,0);
  gStyle->SetFrameFillColor(kWhite);

  char cpad[80];
  TPad* ptpad;
  
  TCanvas* c1 = new TCanvas("c1","ec gen electron",0,0,500,500);
  c1->SetFillColor(0);
  c1->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c1_%d",i+1);
    ptpad = (TPad*) c1->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(1);
    ptpad->SetLogx(1);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c1->cd(i+1);
    switch(i) {
    case 0: Ecinetique_gen->Draw(); break;
    case 1: Ecinetique_acc_trk->Draw(); break;
    case 2: Ecinetique_acc_sci->Draw(); break;
    case 3: Ecinetique_acc_veto->Draw(); break;
    default: break;
    }
  }
  
  TCanvas* c2 = new TCanvas("c2","vxy gen electron",0,0,500,500);
  c2->SetFillColor(0);
  c2->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c2_%d",i+1);
    ptpad = (TPad*) c2->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(0);
    ptpad->SetLogx(0);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c2->cd(i+1);
    switch(i) {
    case 0: Vertex_xy_gen->Draw("colz"); break;
    case 1: Vertex_xy_acc_trk->Draw("colz"); break;
    case 2: Vertex_xy_acc_sci->Draw("colz"); break;
    case 3: Vertex_xy_acc_veto->Draw("colz"); break;
    default: break;
    }
  }
  
  TCanvas* c3 = new TCanvas("c3","vxy gen electron",0,0,500,500);
  c3->SetFillColor(0);
  c3->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c3_%d",i+1);
    ptpad = (TPad*) c3->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(0);
    ptpad->SetLogx(0);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c3->cd(i+1);
    switch(i) {
    case 0: Vertex_xy_gen_ce->Draw("colz"); break;
    case 1: Vertex_xy_acc_trk_ce->Draw("colz"); break;
    case 2: Vertex_xy_acc_sci_ce->Draw("colz"); break;
    case 3: Vertex_xy_acc_veto_ce->Draw("colz"); break;
    default: break;
    }
  }

  
}

void Analyzer::CloseHisto_P(){
  

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadColor(10);
  gStyle->SetPalette(1,0);
  gStyle->SetFrameFillColor(kWhite);

  char cpad[80];
  TPad* ptpad;
  
  TCanvas* c1 = new TCanvas("c1","ec gen electron",0,0,500,500);
  c1->SetFillColor(0);
  c1->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c1_%d",i+1);
    ptpad = (TPad*) c1->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(1);
    ptpad->SetLogx(1);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c1->cd(i+1);
    switch(i) {
    case 0: Pcinetique_gen->Draw(); break;
    case 1: Pcinetique_acc_trk->Draw(); break;
    case 2: Pcinetique_acc_sci->Draw(); break;
    case 3: Pcinetique_acc_veto->Draw(); break;
    default: break;
    }
  }
  
  TCanvas* c2 = new TCanvas("c2","vxy gen electron",0,0,500,500);
  c2->SetFillColor(0);
  c2->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c2_%d",i+1);
    ptpad = (TPad*) c2->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(0);
    ptpad->SetLogx(0);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c2->cd(i+1);
    switch(i) {
    case 0: Vertex_xy_gen->Draw("colz"); break;
    case 1: Vertex_xy_acc_trk->Draw("colz"); break;
    case 2: Vertex_xy_acc_sci->Draw("colz"); break;
    case 3: Vertex_xy_acc_veto->Draw("colz"); break;
    default: break;
    }
  }
  
  TCanvas* c3 = new TCanvas("c3","vxy gen electron ce",0,0,500,500);
  c3->SetFillColor(0);
  c3->Divide(2,2,0.001,0.001);
  for (int i=0; i<4; i++) {
    sprintf(cpad,"c3_%d",i+1);
    ptpad = (TPad*) c3->FindObject(cpad);
    ptpad->SetFillColor(10);
    ptpad->SetLogy(0);
    ptpad->SetLogx(0);
    ptpad->SetLeftMargin(0.15);
    ptpad->SetBottomMargin(0.15);
    ptpad->SetRightMargin(0.125);
    ptpad->SetTopMargin(0.125);
    c3->cd(i+1);
    switch(i) {
    case 0: Vertex_xy_gen_ce->Draw("colz"); break;
    case 1: Vertex_xy_acc_trk_ce->Draw("colz"); break;
    case 2: Vertex_xy_acc_sci_ce->Draw("colz"); break;
    case 3: Vertex_xy_acc_veto_ce->Draw("colz"); break;
    default: break;
    }
  }

  
}

void Analyzer::Loop()
{

  //  double Energy = E;
  int bufsize = 80000000;
    
  printf("get entries\n");
  Long64_t nentries = fTreeChain->GetEntriesFast();
  printf("get entries\n");
  Long64_t nbytes = 0, nb = 0;
  Double_t maxLayer = 0;

  //  printf("nentries %d\n",nentries);
  //  for (Long64_t jentry=0; jentry<50000;jentry++) {
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
 
    bool s1Hit=false;
    bool s2Hit=false;
    bool noVetoHit=false;
    bool hitOnTkLayer1=false;
    bool hitOnTkLayer2=false;
    bool goodHit=false;
    maxLayer=0;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fTreeChain->GetEntry(jentry);   nbytes += nb;
    std::vector<RootTrack> myTracks = Event->GetTracks();
    std::vector<RootCaloHit> myCaloHit = Event->GetCaloHit();
    std::vector<RootCaloHit> myVetoHit = Event->GetVetoHit();
    std::vector<RootTrackerHit> myTrackerHit = Event->GetTrackerHit();

    TVector3 electronDir = myTracks[0].GetDirection();
    TVector3 position = myTracks[0].GetPosition();
    float theta = electronDir.Theta()*180/TMath::Pi();
    if(theta>90)
      theta=180-theta;
    float ce = myTracks[0].GetKinEnergy();
    Ecinetique_gen->Fill(ce);
    Vertex_xy_gen->Fill(position.X()/10,position.Y()/10);
    if (ce <=2) Vertex_xy_gen_ce->Fill(position.X()/10,position.Y()/10);
	if(myTrackerHit.size()>0){
	  //          printf("trk no hits %d\n",myTrackerHit.size());
	  for(size_t th=0;th<myTrackerHit.size();th++){
	    int detId = myTrackerHit[th].GetDetectorId();
            int tkid = myTrackerHit[th].GetTrackId();
	    //            printf("tk hit %d det id %d\n",th,detId); 
	    if(detId>2200 && tkid==1) {
	      hitOnTkLayer1=true;
	      //              printf("hit layer 1\n",th);
            }
	    else if(detId>2100 && tkid==1) {
	      hitOnTkLayer2=true;
	      //              printf("hit layer 2\n",th);
            }
	  }
	  if(hitOnTkLayer2&&hitOnTkLayer1) {
	           Ecinetique_acc_trk->Fill(ce);
                   Vertex_xy_acc_trk->Fill(position.X()/10,position.Y()/10);
            if (ce <=2) Vertex_xy_acc_trk_ce->Fill(position.X()/10,position.Y()/10);
	    //		   printf("no tracker hits 2\n",ce);
	  //          printf("\n");
          }
	}
    hitOnTkLayer1=false;
    hitOnTkLayer2=false;
    if(myCaloHit.size()>0){
      if (ce > 10) {
	//         printf("pdg %d x %f y %f z %f\n",myTracks[0].GetPDG(),position.X(),position.Y(),position.Z());
	//         printf("ientry %d energie %10.3e\n",ientry,ce);
      }
      //    printf("Calo hit size %d\n",myCaloHit.size());
      for(size_t sh=0;sh<myCaloHit.size();sh++){
	int scintLayer = myCaloHit[sh].GetVolume();
	//        printf("scintlayer %d\n",scintLayer);
	std::vector<int> plist = myCaloHit[sh].GetParticleList();       
	//f or(size_t p=0;p<plist.size();p++)
	//	  printf("pid %d PDG %d\n",plist[p],myTracks[plist[p]].GetPDG());
	//	if(scintLayer.Contains("S1"))
	//    if (myCaloHit.size()>=2 && ce <= 15)
	  	  //	printf("scintLayer %d\n",scintLayer);
	if (scintLayer >= 1300 && plist[0]==1) s1Hit=true;
        if (scintLayer == 1216 && plist[0]==1) s2Hit=true;
      }
      //      printf("\n");
      if(s1Hit&&s2Hit){
        Ecinetique_acc_sci->Fill(ce);
        Vertex_xy_acc_sci->Fill(position.X()/10,position.Y()/10);
        if (ce <=2) Vertex_xy_acc_sci_ce->Fill(position.X()/10,position.Y()/10);
	if(myVetoHit.size()==0){
	  noVetoHit=true;
          Ecinetique_acc_veto->Fill(ce);
          Vertex_xy_acc_veto->Fill(position.X()/10,position.Y()/10);
          if (ce <=2) Vertex_xy_acc_veto_ce->Fill(position.X()/10,position.Y()/10);
	}
	if(myTrackerHit.size()>0&&noVetoHit){
	  for(size_t th=0;th<myTrackerHit.size();th++){
	    int detId = myTrackerHit[th].GetDetectorId();
            int tkid = myTrackerHit[th].GetTrackId();
	    if(detId>2200 && tkid==1) {
	      hitOnTkLayer1=true;
	      //              printf("hit layer 1\n",th);
            }
	    else if(detId>2100 && tkid==1) {
	      hitOnTkLayer2=true;
	      //              printf("hit layer 2\n",th);
            }
	  }
	  if(hitOnTkLayer2&&hitOnTkLayer1)
	    goodHit=true;
	}
      }
    }
    
    /*    if(checkPos&&goodHit){
      for(size_t j=0;j<myTracks.size();j++){
	if(myTracks[j].GetTrackID()==1){
	  Double_t Xpos =std::fabs(myTracks[j].GetPosition().X());
	  Double_t Ypos =std::fabs(myTracks[j].GetPosition().Y());
	  if(Xpos>Xlimit&&Ypos>Ylimit)
	    goodHit=false;
	}
      }
    } 
    if(checkTheta&&goodHit){
      Double_t myThetaWithSmearing = ComputeAngleWithSmearing(myTrackerHit,0.05)*180/TMath::Pi();
      if(myThetaWithSmearing>Thetalimit)
	goodHit=false;
	} */

    /*    if(goodHit){
      Double_t myTheta = ComputeAngle(myTrackerHit)*180/TMath::Pi();
      Double_t myThetaWithSmearing = ComputeAngleWithSmearing(myTrackerHit,0.05)*180/TMath::Pi();
      
      Double_t trackTheta=0;
      for(size_t j=0;j<myTracks.size();j++){
	if(myTracks[j].GetTrackID()==1)
	  trackTheta=myTracks[j].GetDirection().Theta()*180/TMath::Pi();
      }
      if(trackTheta>90)
	trackTheta=180-trackTheta;
      
      float totalEdep   = 0;
      float totalEnoS1  = 0;
      float scintS1Edep = 0;
      float scintS2Edep = 0;
      float scintEdep   = 0;
      float caloEdep    = 0;
      float siliconEdep = 0;
      for(size_t i=0;i<myTrackerHit.size();i++){
	siliconEdep+=myTrackerHit[i].GetELoss();
	totalEdep+=myTrackerHit[i].GetELoss();
	totalEnoS1+=myTrackerHit[i].GetELoss();
	int detId = myTrackerHit[i].GetDetectorId();
	/*	if(detId>200)
	  layerDepElectron->Fill(1,myTrackerHit[i].GetELoss());
	if(detId<200)
	layerDepElectron->Fill(2,myTrackerHit[i].GetELoss());  */
    //      }
      //      siliconEdepHisto->Fill(siliconEdep);
  /*      for(size_t i=0;i<myCaloHit.size();i++){
	scintEdep+=myCaloHit[i].GetTotalEdep();
	totalEdep+=myCaloHit[i].GetTotalEdep();
	TString volume = myCaloHit[i].GetVolume();
	if(volume.Contains("S1")){
	  scintS1Edep+=myCaloHit[i].GetTotalEdep();
	  //	  layerDepElectron->Fill(3,myCaloHit[i].GetTotalEdep());
	}
	else if(volume.Contains("S2")){
	  scintS2Edep+=myCaloHit[i].GetTotalEdep();
	  totalEnoS1+=myCaloHit[i].GetTotalEdep();
	  //	  layerDepElectron->Fill(4,myCaloHit[i].GetTotalEdep());
	}
      }
      //      scintS1EdepHisto->Fill(scintS1Edep);
      //      scintS2EdepHisto->Fill(scintS2Edep);
      //      scintEdepHisto->Fill(scintEdep);
      if(myCaloHit.size()){
	float E_Rec_Scint=0;
	float E_Rec_LYSO=0;
	int hittedBricks=0;
	float eDep = 0;
	float bricksEDep[9];
	for(int i =0;i<9;i++)
	  bricksEDep[i] = 0;
	for(size_t i=0;i<myCaloHit.size();i++){
	  eDep = myCaloHit[i].GetTotalEdep();;
	  caloEdep+=eDep;
	  totalEdep+=eDep;
	  totalEnoS1+=eDep;
	  TString layer = myCaloHit[i].GetVolume();
	  int layernumb;
	  if(numbLayerCrystal==-1&&layer.Contains("ActiveBlockCrystal")){
	    layernumb = numbLayerScint+1;
	    hittedBricks++;
	    layer.Remove(0,18);
	    bricksEDep[layer.Atoi()]+=eDep;
	  }else if(layer.Contains("ActiveLayerCrystal")){
	    layer.Remove(0,18);
	    layernumb = numbLayerScint+numbLayerCrystal-layer.Atoi();
	  }else if(layer.Contains("ActiveLayerScint")){
	    layer.Remove(0,16);
	    layernumb = numbLayerScint-layer.Atoi();
	  }else{ 
	    layer.Remove(0,11);
	    layernumb = numbCaloLayer-layer.Atoi();
	  }
	  if(maxLayer<layernumb)
	    maxLayer=layernumb;
	  //	  layerDepElectron->Fill(layernumb+4,eDep);
	  if(layernumb== numbLayerScint+1)
	    E_Rec_LYSO+=eDep;
	  else
	    E_Rec_Scint+=eDep;
	}
	float lysoDep=0;
	for(int i = 0;i<9;i++){
	  if(bricksEDep[i]!=0){
	    lysoDep+=bricksEDep[i];
	    //	    singlebrickDep->Fill(bricksEDep[i]);	
	  }
	  //	  if(lysoDep!=0&&i==8)
	  //  allbricksDep->Fill(lysoDep);
	}
	//	bricksHitted->Fill(hittedBricks);
	//      	caloEdepHisto->Fill(caloEdep);
	//	layerDepthElectron->Fill(theERange,maxLayer);
	//	energyAVGRangeElectron->Fill(theERange,E_Rec_LYSO/(E_Rec_Scint/numbLayerScint));
	//	energySUMRangeElectron->Fill(theERange,E_Rec_LYSO/E_Rec_Scint);
      }

      //      totalEdepHistoNoS1NoCut->Fill(totalEnoS1);
      //      totalEdepHistoNoCut->Fill(totalEdep);
      
      /*      if(totalEnoS1>2.5)
	totalEdepHistoNoS1->Fill(totalEnoS1);
      if(totalEnoS1>1.5)
	totalEdepHistoNoS1Cut2->Fill(totalEnoS1);
      if(totalEdep>=2.5){
	totalEdepHisto->Fill(totalEdep);
	energyVSangle->Fill(myThetaWithSmearing,totalEdep/theERange);
	} 
    } */
    
  }
}


void Analyzer::Loop_acc()
{

  //  double Energy = E;
  int bufsize = 80000000;
    
  printf("get entries\n");
  Long64_t nentries = fTreeChain->GetEntriesFast();
  printf("get entries %d\n",nentries);
  Long64_t nbytes = 0, nb = 0;
  Double_t maxLayer = 0;

  //  for (Long64_t jentry=0; jentry<10000;jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
 
    bool s1Hit=false;
    bool s1Hit_centre=false;
    bool s2Hit=false;
    bool s3Hit=false;
    bool s4Hit=false;
    bool s17Hit=false;
    bool LYSOHit=false;
    bool noVetoHit=false;
    bool noVeto_lateral=true;
    bool noVeto_bottom=true;
    bool hitOnTkLayer1=false;
    bool hitOnTkLayer2=false;
    bool Trig=false;
    bool Trig_sv=false;
    maxLayer=0;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fTreeChain->GetEntry(jentry);   nbytes += nb;
    std::vector<RootTrack> myTracks = Event->GetTracks();
    std::vector<RootCaloHit> myCaloHit = Event->GetCaloHit();
    std::vector<RootCaloHit> myVetoHit = Event->GetVetoHit();
    std::vector<RootTrackerHit> myTrackerHit = Event->GetTrackerHit();

    TVector3 electronDir = myTracks[0].GetDirection();
    TVector3 position = myTracks[0].GetPosition();
    float theta = electronDir.Theta()*180/TMath::Pi();
    float rgen = position.X()*position.X() + position.Y()*position.Y();
    if (rgen > 0) rgen=TMath::Sqrt(rgen);
    rgen/=10;
    //    printf("rgen %f\n",rgen);
    if(theta>90)
      theta=180-theta;
    rtheta_gen->Fill(rgen,theta);

    if(myCaloHit.size()>0){
      for(size_t sh=0;sh<myCaloHit.size();sh++){
	int scintLayer = myCaloHit[sh].GetVolume();
	//        printf("scintlayer %d\n",scintLayer);
	std::vector<int> plist = myCaloHit[sh].GetParticleList();       
	//f or(size_t p=0;p<plist.size();p++)
	//	  printf("pid %d PDG %d\n",plist[p],myTracks[plist[p]].GetPDG());
	//	if(scintLayer.Contains("S1"))
	//    if (myCaloHit.size()>=2 && ce <= 15)
	  	  //	printf("scintLayer %d\n",scintLayer);
        if (plist[0]==1) {
	if (scintLayer >= 1300) s1Hit=true;
        if (scintLayer == 1313 || scintLayer == 1321) s1Hit_centre=true;
        if (scintLayer == 1216) s2Hit=true;
        if (scintLayer == 1215) s3Hit=true;
        if (scintLayer == 1214) s4Hit=true;
        if (scintLayer == 1201) s17Hit=true;
        if (scintLayer >= 1111 && scintLayer <= 1133) LYSOHit=true;
        }
      }
      //      printf("\n");
      // t3
      //            if(s1Hit && (s2Hit || s3Hit) && s17Hit) {
      // t4
      //      if(s1Hit && (s2Hit || s3Hit)) {
      // t5
      //        if(s1Hit_centre && s2Hit) {
      // t6
      if(s1Hit && (s2Hit || s3Hit) && LYSOHit) {
	if(myVetoHit.size()==0) noVetoHit=true;
        if(myVetoHit.size()>0) {
	  for(size_t vh=0;vh<myVetoHit.size();vh++){
	    int scintLayer = myVetoHit[vh].GetVolume();
            if (scintLayer >= 1411 && scintLayer <= 1422) noVeto_lateral=false;
            if (scintLayer == 1430) noVeto_bottom=false;
          }
        }
	if(myTrackerHit.size()>0){
	  for(size_t th=0;th<myTrackerHit.size();th++){
	    int detId = myTrackerHit[th].GetDetectorId();
            int tkid = myTrackerHit[th].GetTrackId();
	    if(detId>2200 && tkid==1) {
	      hitOnTkLayer1=true;
	      //              printf("hit layer 1\n",th);
            }
	    else if(detId>2100 && tkid==1) {
	      hitOnTkLayer2=true;
	      //              printf("hit layer 2\n",th);
            }
	  }
	  if(hitOnTkLayer2&&hitOnTkLayer1) {
	    if (noVetoHit) Trig_sv=true;
            else Trig=true;
          }
	}
      }
    }
    if (Trig) rtheta_acc->Fill(rgen,theta);       
    if (Trig_sv) rtheta_acc_sv->Fill(rgen,theta);
    if (Trig && noVeto_lateral && !(noVeto_bottom)) rtheta_acc_svl->Fill(rgen,theta);
  }
}

void Analyzer::Loop_P()
{

  //  double Energy = E;
  int bufsize = 80000000;
    
  printf("get entries\n");
  Long64_t nentries = fTreeChain->GetEntriesFast();
  printf("get entries\n");
  Long64_t nbytes = 0, nb = 0;
  Double_t maxLayer = 0;

  //  printf("nentries %d\n",nentries);
  //  for (Long64_t jentry=0; jentry<50000;jentry++) {
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
 
    bool s1Hit=false;
    bool s2Hit=false;
    bool noVetoHit=false;
    bool hitOnTkLayer1=false;
    bool hitOnTkLayer2=false;
    bool goodHit=false;
    maxLayer=0;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fTreeChain->GetEntry(jentry);   nbytes += nb;
    std::vector<RootTrack> myTracks = Event->GetTracks();
    std::vector<RootCaloHit> myCaloHit = Event->GetCaloHit();
    std::vector<RootCaloHit> myVetoHit = Event->GetVetoHit();
    std::vector<RootTrackerHit> myTrackerHit = Event->GetTrackerHit();

    TVector3 electronDir = myTracks[0].GetDirection();
    TVector3 position = myTracks[0].GetPosition();
    float theta = electronDir.Theta()*180/TMath::Pi();
    if(theta>90)
      theta=180-theta;
    float ce = myTracks[0].GetKinEnergy();
    Pcinetique_gen->Fill(ce);
    Vertex_xy_gen->Fill(position.X()/10,position.Y()/10);
    if (ce <=40) Vertex_xy_gen_ce->Fill(position.X()/10,position.Y()/10);
	if(myTrackerHit.size()>0){
	  //          printf("trk no hits %d\n",myTrackerHit.size());
	  for(size_t th=0;th<myTrackerHit.size();th++){
	    int detId = myTrackerHit[th].GetDetectorId();
            int tkid = myTrackerHit[th].GetTrackId();
	    //            printf("tk hit %d det id %d\n",th,detId); 
	    if(detId>2200 && tkid==1) {
	      hitOnTkLayer1=true;
	      //              printf("hit layer 1\n",th);
            }
	    else if(detId>2100 && tkid==1) {
	      hitOnTkLayer2=true;
	      //              printf("hit layer 2\n",th);
            }
	  }
	  if(hitOnTkLayer2&&hitOnTkLayer1) {
	           Pcinetique_acc_trk->Fill(ce);
                   Vertex_xy_acc_trk->Fill(position.X()/10,position.Y()/10);
            if (ce <=40) Vertex_xy_acc_trk_ce->Fill(position.X()/10,position.Y()/10);
	    //		   printf("no tracker hits 2\n",ce);
	  //          printf("\n");
          }
	}
    hitOnTkLayer1=false;
    hitOnTkLayer2=false;
    if(myCaloHit.size()>0){
      if (ce > 10) {
	//         printf("pdg %d x %f y %f z %f\n",myTracks[0].GetPDG(),position.X(),position.Y(),position.Z());
	//         printf("ientry %d energie %10.3e\n",ientry,ce);
      }
      //    printf("Calo hit size %d\n",myCaloHit.size());
      for(size_t sh=0;sh<myCaloHit.size();sh++){
	int scintLayer = myCaloHit[sh].GetVolume();
	//        printf("scintlayer %d\n",scintLayer);
	std::vector<int> plist = myCaloHit[sh].GetParticleList();       
	//f or(size_t p=0;p<plist.size();p++)
	//	  printf("pid %d PDG %d\n",plist[p],myTracks[plist[p]].GetPDG());
	//	if(scintLayer.Contains("S1"))
	//    if (myCaloHit.size()>=2 && ce <= 15)
	  	  //	printf("scintLayer %d\n",scintLayer);
	if (scintLayer >= 1300 && plist[0]==1) s1Hit=true;
        if (scintLayer == 1216 && plist[0]==1) s2Hit=true;
      }
      //      printf("\n");
      if(s1Hit&&s2Hit){
        Pcinetique_acc_sci->Fill(ce);
        Vertex_xy_acc_sci->Fill(position.X()/10,position.Y()/10);
        if (ce <=40) Vertex_xy_acc_sci_ce->Fill(position.X()/10,position.Y()/10);
	if(myVetoHit.size()==0){
	  noVetoHit=true;
          Pcinetique_acc_veto->Fill(ce);
          Vertex_xy_acc_veto->Fill(position.X()/10,position.Y()/10);
          if (ce <=40) Vertex_xy_acc_veto_ce->Fill(position.X()/10,position.Y()/10);
	}
	if(myTrackerHit.size()>0&&noVetoHit){
	  for(size_t th=0;th<myTrackerHit.size();th++){
	    int detId = myTrackerHit[th].GetDetectorId();
            int tkid = myTrackerHit[th].GetTrackId();
	    if(detId>2200 && tkid==1) {
	      hitOnTkLayer1=true;
	      //              printf("hit layer 1\n",th);
            }
	    else if(detId>2100 && tkid==1) {
	      hitOnTkLayer2=true;
	      //              printf("hit layer 2\n",th);
            }
	  }
	  if(hitOnTkLayer2&&hitOnTkLayer1)
	    goodHit=true;
	}
      }
    }
    
    /*    if(checkPos&&goodHit){
      for(size_t j=0;j<myTracks.size();j++){
	if(myTracks[j].GetTrackID()==1){
	  Double_t Xpos =std::fabs(myTracks[j].GetPosition().X());
	  Double_t Ypos =std::fabs(myTracks[j].GetPosition().Y());
	  if(Xpos>Xlimit&&Ypos>Ylimit)
	    goodHit=false;
	}
      }
    } 
    if(checkTheta&&goodHit){
      Double_t myThetaWithSmearing = ComputeAngleWithSmearing(myTrackerHit,0.05)*180/TMath::Pi();
      if(myThetaWithSmearing>Thetalimit)
	goodHit=false;
	} */

    /*    if(goodHit){
      Double_t myTheta = ComputeAngle(myTrackerHit)*180/TMath::Pi();
      Double_t myThetaWithSmearing = ComputeAngleWithSmearing(myTrackerHit,0.05)*180/TMath::Pi();
      
      Double_t trackTheta=0;
      for(size_t j=0;j<myTracks.size();j++){
	if(myTracks[j].GetTrackID()==1)
	  trackTheta=myTracks[j].GetDirection().Theta()*180/TMath::Pi();
      }
      if(trackTheta>90)
	trackTheta=180-trackTheta;
      
      float totalEdep   = 0;
      float totalEnoS1  = 0;
      float scintS1Edep = 0;
      float scintS2Edep = 0;
      float scintEdep   = 0;
      float caloEdep    = 0;
      float siliconEdep = 0;
      for(size_t i=0;i<myTrackerHit.size();i++){
	siliconEdep+=myTrackerHit[i].GetELoss();
	totalEdep+=myTrackerHit[i].GetELoss();
	totalEnoS1+=myTrackerHit[i].GetELoss();
	int detId = myTrackerHit[i].GetDetectorId();
	/*	if(detId>200)
	  layerDepElectron->Fill(1,myTrackerHit[i].GetELoss());
	if(detId<200)
	layerDepElectron->Fill(2,myTrackerHit[i].GetELoss());  */
    //      }
      //      siliconEdepHisto->Fill(siliconEdep);
  /*      for(size_t i=0;i<myCaloHit.size();i++){
	scintEdep+=myCaloHit[i].GetTotalEdep();
	totalEdep+=myCaloHit[i].GetTotalEdep();
	TString volume = myCaloHit[i].GetVolume();
	if(volume.Contains("S1")){
	  scintS1Edep+=myCaloHit[i].GetTotalEdep();
	  //	  layerDepElectron->Fill(3,myCaloHit[i].GetTotalEdep());
	}
	else if(volume.Contains("S2")){
	  scintS2Edep+=myCaloHit[i].GetTotalEdep();
	  totalEnoS1+=myCaloHit[i].GetTotalEdep();
	  //	  layerDepElectron->Fill(4,myCaloHit[i].GetTotalEdep());
	}
      }
      //      scintS1EdepHisto->Fill(scintS1Edep);
      //      scintS2EdepHisto->Fill(scintS2Edep);
      //      scintEdepHisto->Fill(scintEdep);
      if(myCaloHit.size()){
	float E_Rec_Scint=0;
	float E_Rec_LYSO=0;
	int hittedBricks=0;
	float eDep = 0;
	float bricksEDep[9];
	for(int i =0;i<9;i++)
	  bricksEDep[i] = 0;
	for(size_t i=0;i<myCaloHit.size();i++){
	  eDep = myCaloHit[i].GetTotalEdep();;
	  caloEdep+=eDep;
	  totalEdep+=eDep;
	  totalEnoS1+=eDep;
	  TString layer = myCaloHit[i].GetVolume();
	  int layernumb;
	  if(numbLayerCrystal==-1&&layer.Contains("ActiveBlockCrystal")){
	    layernumb = numbLayerScint+1;
	    hittedBricks++;
	    layer.Remove(0,18);
	    bricksEDep[layer.Atoi()]+=eDep;
	  }else if(layer.Contains("ActiveLayerCrystal")){
	    layer.Remove(0,18);
	    layernumb = numbLayerScint+numbLayerCrystal-layer.Atoi();
	  }else if(layer.Contains("ActiveLayerScint")){
	    layer.Remove(0,16);
	    layernumb = numbLayerScint-layer.Atoi();
	  }else{ 
	    layer.Remove(0,11);
	    layernumb = numbCaloLayer-layer.Atoi();
	  }
	  if(maxLayer<layernumb)
	    maxLayer=layernumb;
	  //	  layerDepElectron->Fill(layernumb+4,eDep);
	  if(layernumb== numbLayerScint+1)
	    E_Rec_LYSO+=eDep;
	  else
	    E_Rec_Scint+=eDep;
	}
	float lysoDep=0;
	for(int i = 0;i<9;i++){
	  if(bricksEDep[i]!=0){
	    lysoDep+=bricksEDep[i];
	    //	    singlebrickDep->Fill(bricksEDep[i]);	
	  }
	  //	  if(lysoDep!=0&&i==8)
	  //  allbricksDep->Fill(lysoDep);
	}
	//	bricksHitted->Fill(hittedBricks);
	//      	caloEdepHisto->Fill(caloEdep);
	//	layerDepthElectron->Fill(theERange,maxLayer);
	//	energyAVGRangeElectron->Fill(theERange,E_Rec_LYSO/(E_Rec_Scint/numbLayerScint));
	//	energySUMRangeElectron->Fill(theERange,E_Rec_LYSO/E_Rec_Scint);
      }

      //      totalEdepHistoNoS1NoCut->Fill(totalEnoS1);
      //      totalEdepHistoNoCut->Fill(totalEdep);
      
      /*      if(totalEnoS1>2.5)
	totalEdepHistoNoS1->Fill(totalEnoS1);
      if(totalEnoS1>1.5)
	totalEdepHistoNoS1Cut2->Fill(totalEnoS1);
      if(totalEdep>=2.5){
	totalEdepHisto->Fill(totalEdep);
	energyVSangle->Fill(myThetaWithSmearing,totalEdep/theERange);
	} 
    } */
    
  }
}

void Analyzer::SetAcceptanceWindows(Double_t X,Double_t Y){
  checkPos=true;
  Xlimit=X/2.;
  Ylimit=Y/2.;
}

void Analyzer::SetThetaAcceptance(Double_t aTheta){
  checkTheta=true;
  Thetalimit=aTheta;
}

Double_t Analyzer::ComputeAngle(std::vector<RootTrackerHit>& myTrackerHit){

  std::vector<RootTrackerHit> layer2Hit;
  std::vector<RootTrackerHit> layer1Hit;
  
  for(size_t th=0;th<myTrackerHit.size();th++){
    int detId = myTrackerHit[th].GetDetectorId();
    if(detId>200)
      layer2Hit.push_back(myTrackerHit[th]);
    if(detId<200)
      layer1Hit.push_back(myTrackerHit[th]);
  }
  
  TVector3 posL2;
  TVector3 posL1;

  if(layer2Hit.size()==1){
    posL2 = (layer2Hit[0].GetEntryPoint()+layer2Hit[0].GetExitPoint())*0.5;
  }else{
    for(size_t j= 0;j<layer2Hit.size();j++){
      if(layer2Hit[j].GetTrackId()==1)
	posL2 = (layer2Hit[j].GetEntryPoint()+layer2Hit[j].GetExitPoint())*0.5;
    }
  }
  if(layer1Hit.size()==1){
    posL1 = (layer1Hit[0].GetEntryPoint()+layer1Hit[0].GetExitPoint())*0.5;
  }else{
    for(size_t j= 0;j<layer2Hit.size();j++){
      if(layer1Hit[j].GetTrackId()==1)
	posL1 = (layer1Hit[j].GetEntryPoint()+layer1Hit[j].GetExitPoint())*0.5;
    }
  }

  TVector3 segment = posL2-posL1;

  return segment.Theta();
}

Double_t Analyzer::ComputeAngleWithSmearing(std::vector<RootTrackerHit>& myTrackerHit,Double_t delta){

  std::vector<RootTrackerHit> layer2Hit;
  std::vector<RootTrackerHit> layer1Hit;
  
  for(size_t th=0;th<myTrackerHit.size();th++){
    int detId = myTrackerHit[th].GetDetectorId();
    if(detId>200)
      layer2Hit.push_back(myTrackerHit[th]);
    if(detId<200)
      layer1Hit.push_back(myTrackerHit[th]);
  }
  
  TVector3 posL2;
  TVector3 posL1;

  if(layer2Hit.size()==1){
    posL2 = (layer2Hit[0].GetEntryPoint()+layer2Hit[0].GetExitPoint())*0.5;
  }else{
    for(size_t j= 0;j<layer2Hit.size();j++){
      if(layer2Hit[j].GetTrackId()==1)
	posL2 = (layer2Hit[j].GetEntryPoint()+layer2Hit[j].GetExitPoint())*0.5;
    }
  }
  if(layer1Hit.size()==1){
    posL1 = (layer1Hit[0].GetEntryPoint()+layer1Hit[0].GetExitPoint())*0.5;
  }else{    
    for(size_t j= 0;j<layer2Hit.size();j++){
      if(layer1Hit[j].GetTrackId()==1)
	posL1 = (layer1Hit[j].GetEntryPoint()+layer1Hit[j].GetExitPoint())*0.5;
    }
  }

  TRandom myRand;

  Double_t xL1 = posL1.X()+myRand.Uniform(-delta,delta);
  Double_t yL1 = posL1.Y()+myRand.Uniform(-delta,delta);

  posL1.SetX(xL1);
  posL1.SetY(yL1);

  Double_t xL2 = posL2.X()+myRand.Uniform(-delta,delta);
  Double_t yL2 = posL2.Y()+myRand.Uniform(-delta,delta);

  posL2.SetX(xL2);
  posL2.SetY(yL2);

  TVector3 segment = posL2-posL1;

  return segment.Theta();
}
