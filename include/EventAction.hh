#ifndef EventAction_h
#define EventAction_h 1


#include "G4VUserEventAction.hh"
#include "G4String.hh"
#include "globals.hh"

class HistoManager;
class G4Event;

class EventAction : public G4VUserEventAction
{
    public:
        EventAction(HistoManager* histo);
        virtual ~EventAction();
        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);
        void AddEnergyDeposit(G4double edep);
    private:
        HistoManager* fHistoManager;
        G4String fDecayChain;
        G4double fEdep;
};

#endif