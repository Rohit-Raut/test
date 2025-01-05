#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
{
    Book();
}

void HistoManager::Book()
{
    G4String fFilename = "decay_chain";
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
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
        analysisManager->SetH1Activation(ih, false);
    }
}
