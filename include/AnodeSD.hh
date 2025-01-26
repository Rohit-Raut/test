#ifndef AnodeSD_h
#define AnodeSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

class AnodeSD : public G4VSensitiveDetector
{
public:
  AnodeSD(const G4String& name);
  virtual ~AnodeSD();

  // Called when a step is inside the volume with this SD attached
  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* hist) override;
};

#endif
