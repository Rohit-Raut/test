#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RadioactiveDecay.hh"
#include "Randomize.hh"



G4ParticleDefinition* PrimaryGeneratorAction::GetBi207()
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
    // particleSource = new G4GeneralParticleSource();
   // G4double randomEnergy = G4UniformRand()*(5000.-0.)+0;
   // particleSource->SetNumberOfParticles(10);
    // auto energyDist = particleSource->GetCurrentSource()->GetEneDist();
    // energyDist->SetEnergyDisType("Gauss");
    // energyDist->SetMonoEnergy(randomEnergy*keV);
    particleSource->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");
    //Later on change this to 37000
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // static bool firstCall = true;
    // if (firstCall)
    // {
    //     G4ParticleDefinition* bi207 = GetBi207();
    //     G4cout << "DEBUG: Setting primary to Bi207 at rest" << G4endl;
    //     particleSource->SetParticleDefinition(bi207);
    //     firstCall = false;
    // }
    // G4double randomEnergy = G4UniformRand()*5000.*keV;
    G4ParticleDefinition* bi207element = GetBi207();
    if (!bi207element) {
        G4cerr << "Error: GetBi207() returned nullptr" << G4endl;
        return;
    }
    G4PrimaryVertex* vertex = new G4PrimaryVertex(G4ThreeVector(0, 0, 0), 0);
    G4PrimaryParticle* particle = new G4PrimaryParticle(bi207element);
    vertex->SetPrimary(particle);
    anEvent->AddPrimaryVertex(vertex);
    // auto eneDist = particleSource->GetCurrentSource()->GetEneDist();
    // eneDist->SetEnergyDisType("Gauss"); 
    // eneDist->SetMonoEnergy(random*keV); 
    //G4cout << "DEBUG: Setting energy to " << randomEnergy / keV << " keV" << G4endl;
    // gamma_energy = particleSource->GetParticleEnergy();
    G4cout << "generate Bi-207 at rest "<< G4endl;
    Bi207Decay(anEvent);
}


void PrimaryGeneratorAction::Bi207Decay(G4Event* anEvent)
{   
    struct Bi207decayproduct{
        G4ParticleDefinition* particle;
        G4double energy;
        G4double probability;
    };
    std::vector<Bi207decayproduct> decaySpectrum = {
       // { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  569.7 * keV, 0.9976 }, // 569.7 keV gamma (~99.76%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  1063.7 * keV, 0.7458 }, // 1063.7 keV gamma (~74.58%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  1770.2 * keV, 0.0687 }, // 1770.2 keV gamma (~6.87%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  328.1 * keV, 0.000044 }, // 328.1 keV gamma (~0.0044%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  897.8 * keV, 0.001284 }, // 897.8 keV gamma (~0.1284%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  1442.2 * keV, 0.001315 }, // 1442.2 keV gamma (~0.1315%)
        { G4ParticleTable::GetParticleTable()->FindParticle("gamma"),  511.0 * keV, 0.00024 }, // 511 keV gamma (~0.024%) from positron annihilation

        // Internal conversion electrons
        { G4ParticleTable::GetParticleTable()->FindParticle("e-"),  975.0 * keV, 0.0711 }, // Internal conversion electron (~7.11%)
        { G4ParticleTable::GetParticleTable()->FindParticle("e-"),  1047.8 * keV, 0.0184 }, // Internal conversion electron (~1.84%)
        { G4ParticleTable::GetParticleTable()->FindParticle("e-"),  1062.8 * keV, 0.01193 }, // Internal conversion electron (~1.193%)
        { G4ParticleTable::GetParticleTable()->FindParticle("e-"),  481.7 * keV, 0.01548 }, // Internal conversion electron (~1.548%)

        // Beta-plus decay (rare)
        { G4ParticleTable::GetParticleTable()->FindParticle("e+"),  805.8 * keV, 0.00012 } // Beta+ emission (~0.012%)
    };
    G4double randSample = G4UniformRand();
    G4double cumulativeProb = 0.0;
    for (const auto& decayProduct : decaySpectrum)
    {
        cumulativeProb += decayProduct.probability;
        if (randSample <= cumulativeProb)
        {
            G4ThreeVector direction = RandomDirection();
            G4PrimaryVertex* vertex = new G4PrimaryVertex(G4ThreeVector(0, 0, 0), 0);
            G4PrimaryParticle* particle = new G4PrimaryParticle(decayProduct.particle, decayProduct.energy * direction.x(), decayProduct.energy * direction.y(), decayProduct.energy * direction.z());
            vertex->SetPrimary(particle);
            anEvent->AddPrimaryVertex(vertex);
            G4cout<<"Generated "<<decayProduct.particle->GetParticleName()<<" at "<<decayProduct.energy/keV<<"keV"<<G4endl;
            break;
        }
    }


}

G4ThreeVector PrimaryGeneratorAction::RandomDirection()
{
    G4double theta = std::acos(1-2*G4UniformRand());
    G4double phi = 2* CLHEP::pi*G4UniformRand();  
    G4double x = std::sin(theta)*std::cos(phi);
    G4double y = std::sin(theta)*std::sin(phi);
    G4double z = std::cos(theta);
    return G4ThreeVector(x, y, z);
}

 
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleSource;
}
