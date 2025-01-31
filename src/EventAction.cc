#include "EventAction.hh"
#include "HistoManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"


#include <iostream>

EventAction::EventAction(HistoManager* histo):G4UserEventAction(), fHistoManager(histo), fEdep(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fDecayChain = G4String("");
    fEdep = 0.;
}
void EventAction::AddSecondary(G4double secE)
{
    fSecEnergies.push_back(secE);
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4cout<<"Debugging here[Event]: "<<event<<G4endl;
    G4cout<<"Issue at fEdep [fEdep]: "<<fEdep<<G4endl;
    if (fEdep > 0.)
    {
        G4cout<<"Debug: EventAction line 30:   "<<fEdep<<G4endl;
        fHistoManager->FillH1(0,fEdep,1);
    }
    G4int eventID = event->GetEventID();
    G4int printProgress = G4RunManager::GetRunManager()->GetPrintProgress();

    if (eventID%printProgress == 0)
    {
        G4cout << ">>> Event :  " << eventID << "  processed" << G4endl;
    }
    // G4TrajectoryContainer* trajectory= event->GetTrajectoryContainer();
    // if (trajectory)
    // {
    //     for(size_t i=0;i<trajectory->size();i++)
    //     {
    //         G4Trajectory* trj = static_cast<G4Trajectory*>((*trajectory)[i]);
    //         trj->DrawTrajectory();
    //     }
    // }
}

void EventAction::AddEnergyDeposit(G4double edep)
{
    fEdep += edep;
}
