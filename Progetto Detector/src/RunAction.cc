#include "RunAction.hh"
#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4AccumulableManager.hh>
#include <G4SystemOfUnits.hh>
#include <Analysis.hh>
#include <iostream>
using namespace std;


RunAction::RunAction() :
  G4UserRunAction(),
  fNGammas("NGammas", 0),
  fNElectrons("NElectrons", 0),
  fAverageGammaEnergy("AvgGammaEnergy",0.),
  fAverageElectronEnergy("AvgElectronEnergy",0.),
  fTotalTrackLength("TotalTrackLength",0.)
{
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fNGammas);
  accumulableManager->RegisterAccumulable(fNElectrons);
  accumulableManager->RegisterAccumulable(fAverageGammaEnergy);
  accumulableManager->RegisterAccumulable(fAverageElectronEnergy);
  accumulableManager->RegisterAccumulable(fTotalTrackLength);

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstNtupleId(1);
  analysisManager->SetFirstHistoId(1);

	//CREAZIONE ISTOGRAMMI 
    analysisManager->CreateH1("eDep" , "depositedEnergy" , 200 , 0., 700.);
    
   // analysisManager->CreateH1("eSec_gamma", "secondaryphotonsEnergy", 200, 0., 700.);
    
   // analysisManager->CreateH1("eSec_e-", "secondaryelectronsEnergy", 200, 0., 700.);

   analysisManager->OpenFile("progetto");
}


void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();

  if (nofEvents == 0) return;

  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  if (IsMaster())
  {
    G4cout
     << "\n--------------------End of Global Run-----------------------"
     << " \n The run was " << nofEvents << " events " << G4endl;
    if (fNGammas.GetValue())
      G4cout << " * Produced " << fNGammas.GetValue()/((G4double)nofEvents) <<
	" secondary gammas/event. Average energy: "
	     << fAverageGammaEnergy.GetValue()/keV/fNGammas.GetValue() << " keV" << G4endl;
    else
      G4cout << " * No secondary gammas produced" << G4endl;
    if (fNElectrons.GetValue())
      G4cout << " * Produced " << fNElectrons.GetValue()/((G4double)nofEvents)  <<
	" secondary electrons/event. Average energy: "
	     << fAverageElectronEnergy.GetValue()/keV/fNElectrons.GetValue() << " keV" << G4endl;
    else
      G4cout << " * No secondary electrons produced" << G4endl;

  }
}


RunAction::~RunAction()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}

void RunAction::AddSecondary(const G4ParticleDefinition* particle,
			     G4double energy)
{
  if (particle == G4Gamma::Definition())
    {
     // G4AnalysisManager* analysis2 = G4AnalysisManager::Instance();
      fNGammas += 1;
      fAverageGammaEnergy += energy;
    //  analysis2->FillH1(2,energy/keV); -> ISTOGRAMMA FOTONI SECONDARI
    }
  else if (particle == G4Electron::Definition())
    {
    //  G4AnalysisManager* analysis3 = G4AnalysisManager::Instance();
      fNElectrons += 1;
      fAverageElectronEnergy += energy;
     // analysis3->FillH1(3,energy/keV); -> ISTOGRAMMA ELETTRONI SECONDARI
    }
  return;
}

void RunAction::AddTrackLength(G4double trackLength)
{
    fTotalTrackLength += trackLength;
    return;
}


