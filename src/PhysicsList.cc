#include "PhysicsList.hh"
#include "G4EmBuilder.hh"
#include "G4EmStandardPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4NuclearLevelData.hh"
#include "G4ParticleTypes.hh"
#include "G4PhysicsListHelper.hh"
#include "G4Radioactivation.hh"
#include "G4SystemOfUnits.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4NuclideTable.hh"
#include "G4RadioactiveDecay.hh"
#include "G4IonPhysics.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"




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
    // G4EmBuilder::ConstructMinimalEmSet();
    G4GenericIon::GenericIonDefinition();
    G4BaryonConstructor baryon;
    baryon.ConstructParticle();

    G4BosonConstructor boson;
    boson.ConstructParticle();

    G4MesonConstructor meson;
    meson.ConstructParticle();

    G4LeptonConstructor lepton;
    lepton.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();

    //for em
    auto emPhysics = new G4EmStandardPhysics();
    emPhysics->ConstructProcess();

    //Ion physics
    G4IonPhysics* ionPhysics = new G4IonPhysics();
    ionPhysics->ConstructProcess();


    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    radioactiveDecay->SetARM(false);
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
    auto gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    ph->RegisterProcess(new G4PhotoElectricEffect(), gamma);
    ph->RegisterProcess(new G4ComptonScattering(), gamma);
    ph->RegisterProcess(new G4GammaConversion(), gamma);
}