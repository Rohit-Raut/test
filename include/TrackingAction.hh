// MyTrackingAction.hh
#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
class RunAction;

class TrackingAction : public G4UserTrackingAction
{
public:
  TrackingAction(RunAction* runAction_);
  virtual ~TrackingAction();
  virtual void PreUserTrackingAction(const G4Track* track) override;
  virtual void PostUserTrackingAction(const G4Track* track) override;
private:
  RunAction* runAction;
};


#endif
