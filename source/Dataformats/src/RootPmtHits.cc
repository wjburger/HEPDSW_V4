////////////////////////////////////////////////////////////////////////////////
//
#include "RootPmtHits.hh"

ClassImp(RootPmtHits)

////////////////////////////////////////////////////////////////////////////////
//
RootPmtHits::RootPmtHits ()
{
  theNPmt = 53;
  for (int i=0; i<theNPmt; i++) {
    theTotalPhot[i]=0;
    switch (i) {
    case 0: sprintf(thePmtName[i],"%s","T1w"); break;
    case 1: sprintf(thePmtName[i],"%s","T1e"); break;
    case 2: sprintf(thePmtName[i],"%s","T2w"); break;
    case 3: sprintf(thePmtName[i],"%s","T2e"); break;
    case 4: sprintf(thePmtName[i],"%s","T3w"); break;
    case 5: sprintf(thePmtName[i],"%s","T3e"); break;
    case 6: sprintf(thePmtName[i],"%s","T4w"); break;
    case 7: sprintf(thePmtName[i],"%s","T4e"); break;
    case 8: sprintf(thePmtName[i],"%s","T5w"); break;
    case 9: sprintf(thePmtName[i],"%s","T5e"); break;
    case 10: sprintf(thePmtName[i],"%s","T6w"); break;
    case 11: sprintf(thePmtName[i],"%s","T6e"); break;
    case 12: sprintf(thePmtName[i],"%s","P1nw"); break;
    case 13: sprintf(thePmtName[i],"%s","P1se"); break;
    case 14: sprintf(thePmtName[i],"%s","P2sw"); break;
    case 15: sprintf(thePmtName[i],"%s","P2ne"); break;
    case 16: sprintf(thePmtName[i],"%s","P3nw"); break;
    case 17: sprintf(thePmtName[i],"%s","P3se"); break;
    case 18: sprintf(thePmtName[i],"%s","P4sw"); break;
    case 19: sprintf(thePmtName[i],"%s","P4ne"); break;
    case 20: sprintf(thePmtName[i],"%s","P5nw"); break;
    case 21: sprintf(thePmtName[i],"%s","P5se"); break;
    case 22: sprintf(thePmtName[i],"%s","P6sw"); break;
    case 23: sprintf(thePmtName[i],"%s","P6ne"); break;
    case 24: sprintf(thePmtName[i],"%s","P7nw"); break;
    case 25: sprintf(thePmtName[i],"%s","P7se"); break;
    case 26: sprintf(thePmtName[i],"%s","P8sw"); break;
    case 27: sprintf(thePmtName[i],"%s","P8ne"); break;
    case 28: sprintf(thePmtName[i],"%s","P9nw"); break;
    case 29: sprintf(thePmtName[i],"%s","P9se"); break;
    case 30: sprintf(thePmtName[i],"%s","P10sw"); break;
    case 31: sprintf(thePmtName[i],"%s","P10ne"); break;
    case 32: sprintf(thePmtName[i],"%s","P11nw"); break;
    case 33: sprintf(thePmtName[i],"%s","P11se"); break;
    case 34: sprintf(thePmtName[i],"%s","P12sw"); break;
    case 35: sprintf(thePmtName[i],"%s","P12ne"); break;
    case 36: sprintf(thePmtName[i],"%s","P13nw"); break;
    case 37: sprintf(thePmtName[i],"%s","P13se"); break;
    case 38: sprintf(thePmtName[i],"%s","P14sw"); break;
    case 39: sprintf(thePmtName[i],"%s","P14ne"); break;
    case 40: sprintf(thePmtName[i],"%s","P15nw"); break;
    case 41: sprintf(thePmtName[i],"%s","P15se"); break;
    case 42: sprintf(thePmtName[i],"%s","P16sw"); break;
    case 43: sprintf(thePmtName[i],"%s","P16ne"); break;
    case 44: sprintf(thePmtName[i],"%s","L1ne"); break;
    case 45: sprintf(thePmtName[i],"%s","L4n"); break;
    case 46: sprintf(thePmtName[i],"%s","L7nw"); break;
    case 47: sprintf(thePmtName[i],"%s","L2e"); break;
    case 48: sprintf(thePmtName[i],"%s","L5c"); break;
    case 49: sprintf(thePmtName[i],"%s","L8w"); break;
    case 50: sprintf(thePmtName[i],"%s","L3se"); break;
    case 51: sprintf(thePmtName[i],"%s","L6s"); break;
    case 52: sprintf(thePmtName[i],"%s","L9sw"); break;
    default: break;
    }
    printf(" i %d %s\n",i,thePmtName[i]);
    TString pmtname(thePmtName[i]);
    printf(" pmtname %s\n",pmtname.Data());
  }  
}
////////////////////////////////////////////////////////////////////////////////
//
RootPmtHits::RootPmtHits(int aTotalPhot[], char PmtName[][6], unsigned int aNPmt)  
{ 
  theNPmt   = aNPmt;
  for (int i=0; i<theNPmt; i++) {
    theTotalPhot[i] = aTotalPhot[i];
    sprintf(thePmtName[i],"%s",PmtName[i]);
  }  
}
////////////////////////////////////////////////////////////////////////////////
//
RootPmtHits::~RootPmtHits ()
{}
////////////////////////////////////////////////////////////////////////////////
//
RootPmtHits::RootPmtHits (const RootPmtHits& right) : TObject()
{
  theNPmt = right.theNPmt;
  for (int i=0; i<((int) theNPmt); i++) theTotalPhot[i] = right.theTotalPhot[i];  
  for (int i=0; i<((int) theNPmt); i++) sprintf(thePmtName[i],"%s",right.thePmtName[i]);  
}
////////////////////////////////////////////////////////////////////////////////
//
