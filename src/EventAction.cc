#include "EventAction.hh"
#include "HistoManager.hh"
#include "Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"


#include <iostream>

EventAction::EventAction(HistoManager* histo):G4VUserEventAction(), fHistoManager(histo), fEdep(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fDecayChain = G4String("");
    fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    if (fEdep > 0.)
    {
        fHistoManager->FillH1(0,fEdep);
    }
    G4int eventID = event->GetEventID();
    G4int printProgress = G4RunManager::GetRunManager()->GetPrintProgress();

    if (eventID%printProgress == 0)
    {
        G4cout << ">>> Event " << eventID << " processed" << G4endl;
    }
    G4TrajectoryContainer* trajectory= event->GetTrajectoryContainer();
    if (trajectory)
    {
        for(size_t i=0;i<trajectory->size();i++)
        {
            G4Trajectory* trj = static_cast<G4Trajectory*>((*trajectory)[i]);
            trj->DrawTrajectory();
        }
    }
}

void EventAction::AddEnergyDeposit(G4double edep)
{
    fEdep += edep;
}