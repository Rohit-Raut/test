#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"



G4ParticleDefinition* GetBi207()
{
    G4int Z = 83, A = 207;
    G4double excitation = 0.0*keV;
    auto ion =  G4IonTable::GetIonTable()->GetIon(Z, A, excitation);
    if (!ion)
    {
        G4Exception("GetBi207", "Bi207Initialization", FatalException,"Unable to create Bi-207 ion. Ensure GenericIon is initialized.");
    }
    return ion;

}
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    particleSource = new G4GeneralParticleSource();
    particleSource->SetNumberOfParticles(10);
    particleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(0.0*MeV);
    particleSource->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");
    //Later on change this to 37000
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    static bool firstCall = true;
    if (firstCall)
    {
        G4ParticleDefinition* bi207 = GetBi207();
        particleSource->SetParticleDefinition(bi207);
        firstCall = false;
    }
    particleSource->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleSource;
}