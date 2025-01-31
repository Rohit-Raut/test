#include "SteppingAction.hh"


#include "EventAction.hh"
#include "HistoManager.hh"
#include "G4IonTable.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(EventAction* eventAction): G4UserSteppingAction(), fEvents(eventAction)
{}
SteppingAction::~SteppingAction()
{}  

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit() / CLHEP::keV;
    G4cout << "Energy Deposit: " << edep << G4endl;
    if (edep > 0.)
    {
        G4cout << "Energy Deposit: " << edep << G4endl;
        fEvents->AddEnergyDeposit(edep);
    }  
    // auto secondaries = step->GetSecondaryInCurrentStep();
    // if (!secondaries)
    // {
    //     return;
    // }
    // for(const auto* secTrack: *secondaries)
    // {
    //     auto proc = secTrack->GetCreatorProcess();
    //     if(proc && proc->GetProcessName() == "RadioactiveDecay")
    //     {
    //         G4double secE = secTrack->GetKineticEnergy() / CLHEP::keV;
    //         G4cout<<"Secondary Energy: "<<secE<<G4endl;
    //         fEvents->AddSecondary(secE);
    //     }
    // }

}

