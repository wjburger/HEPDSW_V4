#include "Analyzer.h"

void analg4() {
  Analyzer* anal = new Analyzer(); 
  //  anal->SetFile("/home/wjb_local/aiglon/geant4/root/ElectronPowerlaw_Job_9_Seeds_12494_19927.root");
  printf("set file chain\n");
  anal->SetFileChain("fichiers_Ppowerlaw.txt");
  printf("set file chain retour\n");
  printf("init hist\n");
  anal->InitHisto_P();
  printf("init hist retour\n");
  printf("loop\n");
  anal->Loop_P();
  printf("loop retour\n");
  printf("close hist\n");
  anal->CloseHisto_P();
  printf("close hist retour\n");
}

void analg4_acc_e() {
  float energie = 10;
  Analyzer* anal = new Analyzer(); 
  //  anal->SetFile("/home/wjb_local/aiglon/geant4/root/ElectronPowerlaw_Job_9_Seeds_12494_19927.root");
  printf("set file chain\n");
  anal->SetFileChain("fichiers_e_10MeV_ss.txt");
  printf("set file chain retour\n");
  printf("init hist e acc\n");
  anal->InitHisto_e_acc(energie);
  printf("init hist_e_acc retour\n");
  printf("loop\n");
  anal->Loop_acc();
  printf("loop acc retour\n");
  printf("close hist\n");
  anal->CloseHisto_acc();
  printf("close hist retour\n");
}


void analg4_acc_p() {
  float energie = 30;
  Analyzer* anal = new Analyzer(); 
  printf("set file chain\n");
  anal->SetFileChain("fichiers_p_30MeV_ams-farm.txt");
  printf("set file chain retour\n");
  printf("init hist e acc\n");
  anal->InitHisto_p_acc(energie);
  printf("init hist_p_acc retour\n");
  printf("loop\n");
  anal->Loop_acc();
  printf("loop acc retour\n");
  printf("close hist\n");
  anal->CloseHisto_acc();
  printf("close hist retour\n");
}

void tviewer() {
  //  TBrowser *tb = new TBrowser();
  gSystem->Load("libTreeViewer.so");
  new TTreeViewer();
  return;

}
void tbrowser() {
  TBrowser *tb = new TBrowser();
  //  gSystem->Load("libTreeViewer.so");
  //  new TTreeViewer();
  return;
}
