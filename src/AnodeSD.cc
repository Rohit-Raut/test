#include "AnodeSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
// #include "G4VProgress.hh"

AnodeSD::AnodeSD(const G4String& name): G4VSensitiveDetector(name)
{}

AnodeSD::~AnodeSD()
{}

G4bool AnodeSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    const G4Track* track = aStep->GetTrack();
    G4String ParticleName = track->GetDefinition()->GetParticleName();
    G4double kineticEnergy = track->GetKineticEnergy();

    G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
    G4cout<<"Anode Plane Particle Detection"<<ParticleName<<"Energy Deposition"<<G4BestUnit(kineticEnergy, "Energy")<<"Position"<<G4BestUnit(position, "Length")<<G4endl;
    return true;
}