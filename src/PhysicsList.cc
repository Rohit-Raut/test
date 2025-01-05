#include "PhysicsList.hh"
#include "G4EmBuilder.hh"
#include "G4LossTableManager.hh"
#include "G4NuclearLevelData.hh"
#include "G4ParticleTypes.hh"
#include "G4PhysicsListHelper.hh"
#include "G4Radioactivation.hh"
#include "G4SystemOfUnits.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4NuclideTable.hh"



PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
    const G4double meanlife = 1 * nanosecond;
    G4NuclideTable::GetInstance()->SetMeanLifeThreshold(meanlife);
    G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);
    SetDefaultCutValue(1.0 * mm);

}
PhysicsList::~PhysicsList(){}

void PhysicsList::ConstructParticle()
{
    G4EmBuilder::ConstructMinimalEmSet();
    G4GenericIon::GenericIonDefinition();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    G4Radioactivation* radioactiveDecay = new G4Radioactivation();
    radioactiveDecay->SetARM(false);
    //radioactiveDecay->ConstructProcess();

    G4LossTableManager* lossManager = G4LossTableManager::Instance();
    G4VAtomDeexcitation* de = lossManager->AtomDeexcitation();
    if (!de)
    {
        de = new G4UAtomicDeexcitation();
        lossManager->SetAtomDeexcitation(de);
    }
    de->InitialiseAtomicDeexcitation();
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
}