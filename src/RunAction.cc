#include "RunAction.hh"
#include "HistoManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4GenericAnalysisManager.hh"
RunAction::RunAction(HistoManager* histo)
    : G4UserRunAction(), fHistoManager(histo)
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    auto analysisManager = G4GenericAnalysisManager::Instance();
    G4cout << "DEBUG: BeginOfRunAction for run " << G4endl;
    analysisManager->OpenFile(fHistoManager->GetFilename());
    fHistoManager->Book();
    G4cout << "DEBUG: Opened decay_chain.root" << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
    G4cout << "DEBUG: EndOfRunAction for run " << G4endl;
    fHistoManager->Save();
    G4cout << "DEBUG: Wrote & closed decay_chain.root" << G4endl;
}
