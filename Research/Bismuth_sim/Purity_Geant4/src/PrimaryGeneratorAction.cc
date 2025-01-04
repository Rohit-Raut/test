#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"



G4ParticleDefinition* GetBi207()
{
    G4int Z = 83, A = 207;
    G4double excitation = 0.0*keV;
    return G4IonTable::GetIonTable()->GetIon(Z, A, excitation);
}
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    particleSource = new G4GeneralParticleSource();
    G4ParticleDefinition* bi207 = GetBi207();
    particleSource->SetParticleDefinition(bi207);
    //particleSource->GetCurrentSource()->GetAngDist()->SetIso();
    //particleSource->GetCurrentSource()->GetEneDistribution()->SetMonoEnergy(0.0*keV);
    //particleSource->SetParticleMomentumDirection(G4ThreeVector(0., 0., 0.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleSource;
}
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    particleSource->GeneratePrimaryVertex(anEvent);
}