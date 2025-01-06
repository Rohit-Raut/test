#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager(): fFilename("decay_chain")
{
    Book();
}
HistoManager::~HistoManager()
{
    delete G4GenericAnalysisManager::Instance();
}


void HistoManager::Book()
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetFileName(fFilename);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetActivation(true);

    const G4int KMaxHisto = 10;
    const G4String id[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    const G4String title[] = {
        "dummy",  // 0
        "energy spectrum (%): e+ e-",  // 1
        "energy spectrum (%): nu_e anti_nu_e",  // 2
        "energy spectrum (%): gamma",  // 3
        "energy spectrum (%): alpha",  // 4
        "energy spectrum (%): ions",  // 5
        "total kinetic energy per single decay (Q)",  // 6
        "momentum balance",  // 7
        "total time of life of decay chain",  // 8
        "total visible energy in decay chain"  // 9
    };

    G4int nbins = 100;
    G4double vmin = 0.;
    G4double vmax = 2000.;
    for (G4int k = 1; k < KMaxHisto; k++)
    {
        G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
        analysisManager->SetH1Activation(ih, true);
    }
}

void HistoManager::OpenFile(const G4String& filename)
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->OpenFile(filename);
}


void HistoManager::Save()
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}


void HistoManager::FillH1(G4int ih, G4double xvalue, G4double weight)
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->FillH1(ih, xvalue, weight);
}