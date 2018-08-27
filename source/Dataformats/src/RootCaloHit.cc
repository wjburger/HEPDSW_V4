////////////////////////////////////////////////////////////////////////////////
//
#include "RootCaloHit.hh"
#include <iostream>
ClassImp(RootCaloHit)

////////////////////////////////////////////////////////////////////////////////
//
RootCaloHit::RootCaloHit():theEntryPoint(0,0,0),theExitPoint(0,0,0),theTotalEdep(0),theParticleList(0)
{
  //  theVolume="";
  theDet=-1000;
  theKinEnergy = 0;
}
////////////////////////////////////////////////////////////////////////////////
//
//RootCaloHit::RootCaloHit(TString aVolume,double aTotalEdep,std::map<int,double> aEdep) 
RootCaloHit::RootCaloHit(int aDetID, TVector3 aEntry, TVector3 aExit, float aKE, double aTotalEdep,std::map<int,double> aEdep, std::map<int,TVector3> aStepPos, int aTotalNphot)  //OP
//RootCaloHit::RootCaloHit(int aDetID,TVector3 aEntry,TVector3 aExit,float aKE,double aTotalEdep,std::map<int,double> aEdep,std::map<int,double> bEdep) 
{ 
  //  theVolume     = aVolume;
  theDet     = aDetID;
  theEntryPoint = aEntry;
  theExitPoint = aExit;
  theKinEnergy = aKE;
  theTotalEdep  = aTotalEdep;	  
  theEdep       = aEdep;
  theStepPos    = aStepPos;
  for(std::map<int,double>::iterator i = theEdep.begin();i!=theEdep.end();i++){
    theParticleList.push_back(i->first);
  }
  theTotalNphot = aTotalNphot;  //OP
}
////////////////////////////////////////////////////////////////////////////////
//
RootCaloHit::~RootCaloHit()
{;}
////////////////////////////////////////////////////////////////////////////////
//
RootCaloHit::RootCaloHit(const RootCaloHit& right) : TObject()
{
  //  theVolume       = right.theVolume;
  theDet       = right.theDet;
  theEntryPoint = right.theEntryPoint;
  theExitPoint = right.theExitPoint;
  theKinEnergy = right.theKinEnergy;
  theTotalEdep    = right.theTotalEdep;	 
  theEdep         = right.theEdep;
  theStepPos      = right.theStepPos;
  theParticleList = right.theParticleList;
  theTotalNphot = right.theTotalNphot; //OP
}
////////////////////////////////////////////////////////////////////////////////
//
double RootCaloHit::GetEdep(int aTkID)
{
  if(theEdep.find(aTkID)==theEdep.end()){
    std::cout<<"You are asking the wrong track ID = "<<aTkID<<" try with one of these ";
      for(unsigned int i=0;i<theParticleList.size();i++)
	std::cout<<theParticleList[i]<<"; ";
    std::cout<<" "<<std::endl;
    return 0;
  }else{
    return theEdep[aTkID];
  }
}

TVector3 RootCaloHit::GetStepPos(int aTkID)
{
  if(theStepPos.find(aTkID)==theStepPos.end()){
    std::cout<<"You are asking the wrong track ID = "<<aTkID<<" try with one of these ";
      for(unsigned int i=0;i<theParticleList.size();i++)
	std::cout<<theParticleList[i]<<"; ";
    std::cout<<" "<<std::endl;
  }else{
    return theStepPos[aTkID];
  }
}
