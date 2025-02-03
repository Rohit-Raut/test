#include "TrackingAction.hh"
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"   
#include "G4RadioactiveDecay.hh"
#include "G4HadronicProcessType.hh"
#include "G4HadronicProcess.hh"
#include "G4AnalysisManager.hh"

TrackingAction::TrackingAction(RunAction* runAction_) :G4UserTrackingAction(), runAction(runAction_)
{}
TrackingAction::~TrackingAction()
{}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if(track->GetTrackID()==1) return;
    G4cout<<"Debugging to line 23 Tracking Action" << G4endl;
    const G4VProcess* creatorProcess = track->GetCreatorProcess();
    if (!creatorProcess) {
        G4cout << "DEBUG: Track ID has no creator process." << G4endl;
        return;
    }
    G4int creator = creatorProcess->GetProcessSubType();
    const G4ParticleDefinition* particle = track->GetDefinition();
    G4String name = particle->GetParticleName();
    G4int pid = particle->GetPDGEncoding();
    G4int z = particle->GetAtomicNumber();
    G4int a = particle->GetAtomicMass();
    G4double charge = particle->GetPDGCharge();
    G4double energy = track->GetKineticEnergy();
    G4double time = track->GetGlobalTime();
    G4double weight = track->GetWeight();

    runAction ->GetHistoManager()->FillDecayParticlesNtuple(pid, energy);
    // if (creator==fRadioactiveDecay){
    //     G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //     G4int id= 0;
    //     analysisManager->FillNtupleDColumn(id,0, double(pid));
    //    // analysisManager->FillNtupleDColumn(id,1, double(z));
    //    // analysisManager->FillNtupleDColumn(id,2, double(a));
    //     analysisManager->FillNtupleDColumn(id,1, energy);
    //     //analysisManager->FillNtupleDColumn(id,4, time/s);
    //     //analysisManager->FillNtupleDColumn(id,5, weight);
    //     if (charge < 10.) {
    //         analysisManager->FillH1(0,energy,1);
    //     }

    //G4bool unstableIon = ((charge>2.)&&!(particle->GetPDGStable()));
    //if ((unstableIon)){
    //    G4int id = 1;
    //    analysisManager->FillNtupleDColumn(id, 0, double(pid));
    //    analysisManager->FillNtupleDColumn(id, 1, time / s);
    //    analysisManager->FillNtupleDColumn(id, 2, weight);
    //    analysisManager->AddNtupleRow(id);

    //}
    
    G4bool unstableIon = ((charge>1.)&&!(particle->GetPDGStable()));
    if (unstableIon)
    {
        runAction->GetHistoManager()->FillEnergyDepositionsNtuple(pid, energy);
    }
}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{}
