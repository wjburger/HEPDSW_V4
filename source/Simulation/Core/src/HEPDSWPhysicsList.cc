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
//
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HEPDSWPhysicsList.hh"
#include "HEPDSWPhysicsListMessenger.hh"

#include "PhysListEmStandard.hh"
#include "PhysListEmStandardSS.hh"
#include "PhysListEmStandardSSM.hh"
#include "PhysListEmStandardGS.hh"
#include "PhysListEmStandardWVI.hh"

#include "G4StepLimiterPhysics.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4Decay.hh"
#include "StepMax.hh"

// Optical Process headers
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh" 

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Hadrons
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

// hadron physics

#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsShielding.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4HadronInelasticQBBC.hh"

#include "G4IonElasticPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4IonQMDPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPhysicsList::HEPDSWPhysicsList() : G4VModularPhysicsList()
{
  fMessenger = new HEPDSWPhysicsListMessenger(this); 
   
  // EM physics
  fEmName = G4String("local");
  fEmHEPDSWPhysicsList = new PhysListEmStandard(fEmName);
      
  // Step limitation seen as a process
  stepMaxProcess = new StepMax();


  defaultCutValue = 1.*mm;

  fCutForGamma     = defaultCutValue;
  fCutForElectron  = defaultCutValue;
  fCutForPositron  = defaultCutValue;
  fUseOpticalProcesses = true;

  helIsRegistered  = false;
  hinIsRegistered  = false;
  bicIsRegistered  = false;
  biciIsRegistered = false;
  shieldIsRegistered = false;
  qmdiIsRegistered = false;
  inclxxIsRegistered = false;
  inclxxiIsRegistered = false;
  locIonIonInelasticIsRegistered = false;
  radioactiveDecayIsRegistered = false;

  SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HEPDSWPhysicsList::~HEPDSWPhysicsList()
{
  delete fEmHEPDSWPhysicsList;
  delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::ConstructParticle()
{
  // optical photon definition
  G4OpticalPhoton::OpticalPhotonDefinition();

  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  
  // gamma
  G4Gamma::GammaDefinition();
  
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();  

  // mesons
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();

  // barions
  G4BaryonConstructor bConstructor;
  bConstructor.ConstructParticle();

  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::ConstructProcess()
{
  AddTransportation();
  fEmHEPDSWPhysicsList->ConstructProcess();
  AddDecay();
  for(size_t i=0; i<hadronPhys.size(); i++) {
    hadronPhys[i]->ConstructProcess();
  }
  G4cout << "---------> CHECKPOINT: fUseOpticalProcesses: "  << fUseOpticalProcesses << std::endl;
  if (fUseOpticalProcesses)
    AddOpticalProcesses();
  AddStepMax();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::AddOpticalProcesses()
{
  G4Cerenkov* theCerenkovProcess = new G4Cerenkov("Cerenkov");
  theCerenkovProcess->SetTrackSecondariesFirst(true);
  G4int MaxNumPhotons = 300;
  theCerenkovProcess->SetMaxNumPhotonsPerStep(MaxNumPhotons);
  theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  
  G4Scintillation* theScintProcess = new G4Scintillation("Scintillation");
  theScintProcess->SetTrackSecondariesFirst(true);
  theScintProcess->SetScintillationYieldFactor(1.);

  G4EmSaturation* emSaturation =  G4LossTableManager::Instance()->EmSaturation();
  theScintProcess->AddSaturation(emSaturation);
  
  G4OpBoundaryProcess* theOpBoundaryProcess = new G4OpBoundaryProcess("Boundary");
  G4OpAbsorption* theAbsProcess = new G4OpAbsorption("Absorption");
  G4OpRayleigh* theRayleighScattProcess = new G4OpRayleigh("RayleighScattering");
  G4OpMieHG* theMieHGScattProcess = new G4OpMieHG("MieHGScattering");

  theParticleIterator->reset();
  while( (*theParticleIterator)() )
  {  
     G4ParticleDefinition* particle = theParticleIterator->value();
     G4ProcessManager* pmanager = particle->GetProcessManager();
     G4String particleName = particle->GetParticleName();

     if (theCerenkovProcess->IsApplicable(*particle)) 
     {
        pmanager->AddProcess(theCerenkovProcess);
	pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
     }
     if (theScintProcess->IsApplicable(*particle)) 
     {
	pmanager->AddProcess(theScintProcess);
	pmanager->SetProcessOrderingToLast(theScintProcess, idxAtRest);
	pmanager->SetProcessOrderingToLast(theScintProcess, idxPostStep);
     }
     if (particleName == "opticalphoton") 
     {
	G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
	pmanager->AddDiscreteProcess(theAbsProcess);
	pmanager->AddDiscreteProcess(theRayleighScattProcess);
	pmanager->AddDiscreteProcess(theMieHGScattProcess);
	pmanager->AddDiscreteProcess(theOpBoundaryProcess);

     }
  }

}

void HEPDSWPhysicsList::AddDecay()
{
  // Add Decay Process

  G4Decay* fDecayProcess = new G4Decay();

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (fDecayProcess->IsApplicable(*particle) && !particle->IsShortLived()) { 

      pmanager ->AddProcess(fDecayProcess);

      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);

    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::AddStepMax()
{
  theParticleIterator->reset();
  while ((*theParticleIterator)()){
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();

      if (stepMaxProcess->IsApplicable(*particle) && !particle->IsShortLived())
        {
          pmanager ->AddDiscreteProcess(stepMaxProcess);
        }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>-1) {
    G4cout << "HEPDSWPhysicsList::AddHEPDSWPhysicsList: <" << name << ">" << G4endl;
  }

  if (name == fEmName) return;

  if (name == "local") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new PhysListEmStandard(name);

  } else if (name == "emstandard_opt0") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmStandardPhysics();

  } else if (name == "emstandard_opt1") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt2") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmStandardPhysics_option2();
    
  } else if (name == "emstandard_opt3") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmStandardPhysics_option3();
    
  } else if (name == "emstandard_opt4") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmStandardPhysics_option4();
        
  } else if (name == "standardSS") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new PhysListEmStandardSS(name);

  } else if (name == "standardSSM") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new PhysListEmStandardSSM(name);

  } else if (name == "standardWVI") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new PhysListEmStandardWVI(name);

  } else if (name == "standardGS") {

    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new PhysListEmStandardGS(name);

  } else if (name == "empenelope"){
    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmPenelopePhysics();

  } else if (name == "emlivermore"){
    fEmName = name;
    delete fEmHEPDSWPhysicsList;
    fEmHEPDSWPhysicsList = new G4EmLivermorePhysics();
    
  } else if (name == "elastic" && !helIsRegistered) {
    G4cout << "THE FOLLOWING HADRONIC ELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronElasticPhysics()" << G4endl;
    hadronPhys.push_back( new G4HadronElasticPhysics());
    helIsRegistered = true;

  } else if (name == "DElastic" && !helIsRegistered) {
    hadronPhys.push_back( new G4HadronDElasticPhysics());
    helIsRegistered = true;

  } else if (name == "HPElastic" && !helIsRegistered) {
    hadronPhys.push_back( new G4HadronElasticPhysicsHP());
    helIsRegistered = true;

  } else if (name == "QGSP_BIC" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_BIC());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_BIC()" << G4endl;

  } else if (name == "QGSP_BIC_HP" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_BIC_HP());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_BIC_HP()" << G4endl;

  } else if (name == "QGSP_BIC_AllHP" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_BIC_AllHP());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_BIC_AllHP()" << G4endl;

  } else if (name == "QGSP_BERT" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_BERT());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_BERT()" << G4endl;

  } else if (name == "QGSP_BERT_HP" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_BERT_HP());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_BERT_HP()" << G4endl;

  } else if (name == "QGSP_FTFP_BERT" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsQGSP_FTFP_BERT());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsQGSP_FTFP_BERT()" << G4endl;

  } else if (name == "binary_ion" && !biciIsRegistered) {
    hadronPhys.push_back(new G4IonBinaryCascadePhysics());
    biciIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4IonBinaryCascadePhysics()" << G4endl;

  } else if (name == "qmd_ion" && !qmdiIsRegistered) {
    hadronPhys.push_back(new G4IonQMDPhysics());
    qmdiIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4IonQMDPhysics()" << G4endl;

  } else if (name == "inclxx_ion" && !inclxxiIsRegistered) {
    hadronPhys.push_back(new G4IonINCLXXPhysics());
    inclxxiIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4IonINCLXXPhysics()" << G4endl;

  } else if (name == "FTFP_BERT" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsFTFP_BERT());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsFTFP_BERT()" << G4endl;

  } else if (name == "FTFP_BERT_HP" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsFTFP_BERT_HP());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsFTFP_BERT_HP()" << G4endl;

  } else if (name == "IonElastic" && !ionElasticIsRegistered) {
    hadronPhys.push_back(new G4IonElasticPhysics());
    ionElasticIsRegistered = true;
    G4cout << "THE FOLLOWING ION ELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4IonElastic()" << G4endl;

  } else if (name == "FTFP_BERT_TRV" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsFTFP_BERT_TRV());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsFTFP_BERT_TRV()" << G4endl;

  } else if (name == "QBBC" && !hinIsRegistered) {
    hadronPhys.push_back(new G4HadronInelasticQBBC());
    hinIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronInelasticQBBC()" << G4endl;

  } else if (name == "INCLXX" && !inclxxIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsINCLXX());
    inclxxIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsINCLXX()" << G4endl;

  } else if (name == "Shielding" && !shieldIsRegistered) {
    hadronPhys.push_back(new G4HadronPhysicsShielding());
    shieldIsRegistered = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronPhysicsShielding()" << G4endl;
                        
  } else {

    G4cout << "HEPDSWPhysicsList::AddHEPDSWPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::SetCuts()
{
  if (verboseLevel >0) {
    G4cout << "HEPDSWPhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(fCutForGamma, "gamma");
  SetCutValue(fCutForElectron, "e-");
  SetCutValue(fCutForPositron, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::SetCutForGamma(G4double cut)
{
  fCutForGamma = cut;
  SetParticleCuts(fCutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::SetCutForElectron(G4double cut)
{
  fCutForElectron = cut;
  SetParticleCuts(fCutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HEPDSWPhysicsList::SetCutForPositron(G4double cut)
{
  fCutForPositron = cut;
  SetParticleCuts(fCutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
