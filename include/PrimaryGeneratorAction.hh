#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        PrimaryGeneratorAction();
        virtual ~PrimaryGeneratorAction();
        virtual void GeneratePrimaries(G4Event* anEvent);
    private:
        G4GeneralParticleSource* particleSource;
        G4ParticleDefinition* GetBi207();
        //void Bi207Decay(G4Event* anEvent);
        G4ThreeVector RandomDirection();
	    G4double gamma_energy;
};
#endif
