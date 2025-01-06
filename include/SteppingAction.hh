#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;

class SteppingAction: public G4UserSteppingAction
{
public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Track* track) override;

private:
    EventAction* fEventAction;
};

#endif