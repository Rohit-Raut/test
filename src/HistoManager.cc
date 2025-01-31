#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"


HistoManager::HistoManager() : fFilename("decay_chain.root")
{
    // OpenFile(fFilename);
    Book();
}

HistoManager::~HistoManager()
{
    Save();
}

void HistoManager::OpenFile(const G4String& fFilename)
{
    G4cout<<"Opening ROOT file"<<G4endl;
	auto analysisManager  = G4GenericAnalysisManager::Instance();
	//analysisManager ->SetDefaultFileType("root");
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetActivation(true);

	analysisManager->SetFileName(fFilename);
	G4int status = analysisManager->OpenFile(fFilename);
	if(status !=0)
	{
		G4cerr<<"Error root file: Traced error to histomanager"<< G4endl;
	}
	else{
		G4cout<<"ROOT File opened"<< G4endl;
	}
}

void HistoManager::Book()
{
    auto analysisManager= G4GenericAnalysisManager::Instance();
    G4int nbins = 40;
    G4double vmin = 0.;
    G4double vmax = 1500.;

    // Creating histograms
    analysisManager->CreateH1("H1", "Energy deposit (MeV) in the target", nbins, vmin, vmax);
    //analysisManager->CreateH1("H2", "Energy deposit (MeV) in the detector", nbins, vmin, vmax);
    //analysisManager->CreateH1("H3", "Total energy (MeV) in target and detector", nbins, vmin, vmax);
    //analysisManager->CreateH1("H4", "Coincidence spectrum (MeV)", nbins, vmin, vmax);

    // // Additional histograms
    //analysisManager->CreateH1("H5", "Decay emission spectrum (0 - 5 MeV)", nbins, 0., 5.);
    // analysisManager->CreateH1("H6", "Decay emission spectrum (0 - 5 MeV)", nbins, 0., 5.);
    // analysisManager->CreateH1("H7", "Decay emission spectrum (0 - 5 MeV)", nbins, 0., 5.);

    // Creating ntuples
    analysisManager->CreateNtuple("DecayParticles", "Emitted Particles");
    analysisManager->CreateNtupleDColumn("PID");      // Particle ID
    analysisManager->CreateNtupleDColumn("Energy");   // Energy
    //analysisManager->CreateNtupleDColumn("Time");     // Time
    analysisManager->CreateNtupleDColumn("Weight");   // Weight
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("EnergyDepositions", "Energy depositions");
    analysisManager->CreateNtupleDColumn("PID");      // Particle ID
    analysisManager->CreateNtupleDColumn("Energy");   // Energy
    //analysisManager->CreateNtupleDColumn("Time");     // Time
    //analysisManager->CreateNtupleDColumn("Weight");   // Weight
    analysisManager->FinishNtuple();
}

void HistoManager::FillH1(G4int ih, G4double xvalue, G4double weight)
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->FillH1(ih, xvalue, weight);
}

void HistoManager::FillEnergyDepositionsNtuple(G4double pid, G4double energy)
{
	auto analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager ->FillNtupleDColumn(fNtupleID_EnergyDepositions, 0, pid);
    analysisManager ->FillNtupleDColumn(fNtupleID_EnergyDepositions, 1, energy);
    //analysisManager-> FillNtupleDColumn(fNtupleID_EnergyDepositions, 1, time);
    //analysisManager-> FillNtupleDColumn(fNtupleID_EnergyDepositions, 2, weight);
    analysisManager->AddNtupleRow(fNtupleID_EnergyDepositions);
}

void HistoManager::FillDecayParticlesNtuple(G4double pid, G4double energy)
{
	auto analysisManager = G4GenericAnalysisManager::Instance();
	analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 0, pid);
    analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 1, energy);
    //analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 2, time);
    //analysisManager->FillNtupleDColumn(fNtupleID_DecayParticles, 3, weight);
    analysisManager->AddNtupleRow(fNtupleID_DecayParticles);
}

void HistoManager::Save()
{
    G4GenericAnalysisManager* analysisManager = G4GenericAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4cout<<"ROOT FIle Written and Saved"<<G4endl;
}