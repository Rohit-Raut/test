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
    // G4double edep = step->GetTotalEnergyDeposit() / CLHEP::keV;
    // if (edep > 0.)
    // {
    //     fEvents->AddEnergyDeposit(edep);
    // }  
    auto secondaries = step->GetSecondaryInCurrentStep();
    if (!secondaries)
    {
        return;
    }
    for(const auto* secTrack: *secondaries)
    {
        auto proc = secTrack->GetCreatorProcess();
        if(proc && proc->GetProcessName() == "RadioactiveDecay")
        {
            G4double secE = secTrack->GetKineticEnergy() / CLHEP::keV;
            fEvents->AddSecondary(secE);
        }
    }

}

