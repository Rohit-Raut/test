#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"   
#include "G4RadioactiveDecay.hh"
#include "G4HadronicProcessType.hh"


TrackingAction::TrackingAction() :G4UserTrackingAction()
{}
TrackingAction::~TrackingAction()
{}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if(track->GetParentID()==0) return;
    G4int creator = track->GetCreatorProcess()->GetProcessSubType();
    //if(!creator) return;
    if (creator==fRadioactiveDecay){
        G4double e = track->GetKineticEnergy();
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1,e);
    }
}