#ifndef HistoManager_h
#define HistoManager_h 1

#include "Globals.hh"
#include "G4String.hh"


class G4AnalysisManager;

class HistoManager
{
    public:
        HistoManager();
        virtual ~HistoManager();
        void OpenFile(const G4String& filename);
        void Save();
        void FillH1(G4int ih, G4double xvalue, G4double weight = 1.);
    private:
        void Book();
        G4String fFilename;
};
#endif
