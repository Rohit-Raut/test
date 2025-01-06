#include "RunAction.hh"
#include "HistoManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

RunAction::RunAction(HistoManager* histo)
    : G4UserRunAction(), fHistoManager(histo)
{
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    fHistoManager->OpenFile("decay_chain");
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
    fHistoManager->Save();
}
