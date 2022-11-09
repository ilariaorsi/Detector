#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"


void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());

    RunAction* theRunAction = new RunAction();
    SetUserAction(theRunAction);
    SetUserAction(new StackingAction(theRunAction));
    SetUserAction(new SteppingAction(theRunAction));
    EventAction* theEvent = new EventAction;
       SetUserAction(theEvent);
}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}
