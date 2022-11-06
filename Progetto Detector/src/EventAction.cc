#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>
#include "Analysis.hh"
#include "EnergyTimeHit.hh"

using namespace std;

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    if(!hcofEvent) return;

    if (fAbsorberId < 0)
    {
        fAbsorberId = sdm->GetCollectionID("absorber/energy");
        G4cout << "EventAction: absorber energy scorer ID: " << fAbsorberId << G4endl;
    }

    G4int histogramId = 1;
    G4double eTot = 0.;

    if (fAbsorberId >= 0)
    {

        G4THitsMap<G4double>* hitMapA = dynamic_cast<G4THitsMap<G4double>*>(hcofEvent->GetHC(fAbsorberId)) ;
        
      if (hitMapA)
      {
          for (auto pair : *(hitMapA->GetMap()))
          {
              G4double energy = *(pair.second);
              eTot += energy;
          }
      }
    }
    if (eTot>0) analysis->FillH1(histogramId, eTot / keV);
    
}
