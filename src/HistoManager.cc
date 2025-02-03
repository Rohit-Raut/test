#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

HistoManager::HistoManager()
 : fFilename("decay_chain.root"),
   // Initialize IDs to -1 or some invalid sentinel
   fNtupleID_DecayParticles(-1),
   fNtupleID_EnergyDepositions(-1)
{
    // Don't open or book anything here.
}

HistoManager::~HistoManager()
{
    // Also do NOT close the file here:
    // Let RunAction do it exactly once per run.
}

void HistoManager::OpenFile(const G4String& filename)
{
    G4cout << "Opening ROOT file: " << filename << G4endl;
    auto analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetActivation(true);

    // Set the filename and open
    analysisManager->SetFileName(filename);
    G4int status = analysisManager->OpenFile(filename);
    if ( status != 0 ) {
        G4cerr << "[ERROR] Could not open ROOT file: " << filename << G4endl;
    } else {
        G4cout << "ROOT File opened successfully: " << filename << G4endl;
    }
}

void HistoManager::Book()
{
    auto analysisManager = G4GenericAnalysisManager::Instance();

    // Create 1D histogram (ID=0 by default)
    G4int nbins = 40;
    G4double vmin = 0.;
    G4double vmax = 1500.;
    analysisManager->CreateH1("H1", "Energy deposit (keV)", nbins, vmin, vmax);

    // Now create two ntuples:
    // 1) "DecayParticles" with 3 columns: PID, Energy, Weight
    fNtupleID_DecayParticles = analysisManager->CreateNtuple("DecayParticles", "Emitted Particles");
    analysisManager->CreateNtupleDColumn("PID");
    analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->CreateNtupleDColumn("Weight"); // optional
    analysisManager->FinishNtuple();

    // 2) "EnergyDepositions" with 2 columns: PID, Energy
    fNtupleID_EnergyDepositions = analysisManager->CreateNtuple("EnergyDepositions", "Energy depositions");
    analysisManager->CreateNtupleDColumn("PID");
    analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->FinishNtuple();

    G4cout << "Book() completed: histograms and ntuples created.\n"
           << "  DecayParticles NtupleID=" << fNtupleID_DecayParticles
           << "  EnergyDepositions NtupleID=" << fNtupleID_EnergyDepositions
           << G4endl;
}

void HistoManager::Save()
{
    auto analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4cout << "ROOT file written and closed.\n";
}

void HistoManager::FillH1(G4int ih, G4double xvalue, G4double weight)
{
    auto analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->FillH1(ih, xvalue, weight);
}

// Fill the "DecayParticles" ntuple. We have 3 columns:
//  (0) PID, (1) Energy, (2) Weight
void HistoManager::FillDecayParticlesNtuple(G4double pid, G4double energy)
{
    auto analysisManager = G4GenericAnalysisManager::Instance();

    // Fill 3 columns (we'll just store weight=1 here, or whatever you like)
    // Make sure fNtupleID_DecayParticles is valid
    analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 0, pid);
    analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 1, energy);
    analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 2, 1.0); // Weight

    // Add the row
    analysisManager->AddNtupleRow(fNtupleID_DecayParticles);
}

// Fill the "EnergyDepositions" ntuple. We have 2 columns:
//  (0) PID, (1) Energy
void HistoManager::FillEnergyDepositionsNtuple(G4double pid, G4double energy)
{
    auto analysisManager = G4GenericAnalysisManager::Instance();

    // Make sure fNtupleID_EnergyDepositions is valid
    analysisManager->FillNtupleDColumn(fNtupleID_EnergyDepositions, 0, pid);
    analysisManager->FillNtupleDColumn(fNtupleID_EnergyDepositions, 1, energy);

    // Add the row
    analysisManager->AddNtupleRow(fNtupleID_EnergyDepositions);
}

