// HistoManager.hh
#ifndef HISTOMANAGER_HH
#define HISTOMANAGER_HH

#include "G4String.hh"
#include "globals.hh"

class HistoManager {
public:
    HistoManager();
    ~HistoManager();

    void OpenFile(const G4String& filename);
    void Book();
    void Save();
    G4String GetFilename()const{return fFilename;}
    void FillH1(G4int ih, G4double xvalue, G4double weight = 1.0);
    void FillDecayParticlesNtuple(G4double pid, G4double energy);
    void FillEnergyDepositionsNtuple(G4double pid, G4double energy);

private:
    G4String fFilename;
    G4int fNtupleID_DecayParticles;
    G4int fNtupleID_EnergyDepositions;
};

#endif // HISTOMANAGER_HH
