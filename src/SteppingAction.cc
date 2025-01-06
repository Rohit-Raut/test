#include "SteppingAction.hh"

#include "EventAction.hh"
#include "HistoManager.hh"
#include "G4IonTable.hh"
#include "G4RunManager.hh"
#include"G4Track.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(EventAction* eventAction): G4UserSteppingAction(), fEvents(eventAction)
{}
SteppingAction::~SteppingAction()
{}  

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep > 0.)
    {
        fEvents->AddEnergyDeposit(edep);
    }
}