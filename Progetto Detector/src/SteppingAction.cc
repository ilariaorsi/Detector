#include "SteppingAction.hh"
#include "RunAction.hh"

#include <G4Step.hh>
#include <G4Electron.hh>

SteppingAction::SteppingAction(RunAction* runAction)
    : fRunAction(runAction)
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{

    G4VPhysicalVolume* volume=aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
   // G4VPhysicalVolume* volume=aStep->GetPreStepPoint()->GetPhysicalVolume();
    
    if(volume != NULL) {
        if ( (volume != nullptr) && (volume->GetName() != "absorber") ) {

          if(aStep->GetTrack()->GetParticleDefinition() == G4Electron::Definition()){
              fRunAction->AddTrackLength(aStep->GetTrack()->GetStepLength());
          }
        }
    }
}


