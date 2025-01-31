#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class HistoManager;  // Forward declaration

class RunAction : public G4UserRunAction
{
public:
    RunAction(HistoManager* histo);
    virtual ~RunAction();
    
    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;
    HistoManager* GetHistoManager() const{ return fHistoManager; }
private:
    HistoManager* fHistoManager;
};

#endif
