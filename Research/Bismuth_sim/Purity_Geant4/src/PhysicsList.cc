#include "PhysicsList.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}
PhysicsList::~PhysicsList(){}

void PhysicsList::ConstructParticle()
{
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    //radioactiveDecay->ConstructProcess();

    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while((*particleIterator)())
    {
        G4ParticleDefinition* particle = particleIterator->value();
        if (particle->GetPDGCharge()!=0.0 || particle->GetParticleName() =="gamma")
        {
            G4ProcessManager* pmanager = particle->GetProcessManager();
            if (radioactiveDecay->IsApplicable(*particle))
            {
                pmanager->AddProcess(radioactiveDecay);
            }
        }
    }
}