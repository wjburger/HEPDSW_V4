#ifndef RootPmtHits_h
#define RootPmtHits_h 1
////////////////////////////////////////////////////////////////////////////////
//
#include <vector>
#include <map>

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

////////////////////////////////////////////////////////////////////////////////
//
class RootPmtHits : public TObject
{
public:
  RootPmtHits ();
  RootPmtHits (int aTotalPhot[], char NamePmt[][6], unsigned int aNPmt);
  
  ~RootPmtHits ();
  RootPmtHits (const RootPmtHits&);
  
  inline int GetNPmt(){return theNPmt;}
  inline int GetNPhot(int npmt){
    int val = theTotalPhot[npmt];
    return val;}
  inline TString GetNamePmt(int npmt) {
    TString pmtname(thePmtName[npmt]);
    printf("%s\n",pmtname.Data());
    return pmtname;}

  ClassDef(RootPmtHits,2);
  
private:
  unsigned int theNPmt;
  int theTotalPhot[53];
  char thePmtName[53][6];
};

#endif
