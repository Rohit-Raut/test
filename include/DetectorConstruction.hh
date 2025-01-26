#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4FieldManager;
class G4ChordFinder;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();
        virtual G4VPhysicalVolume* Construct() override;
        virtual void ConstructSDandField() override;
    private:
        G4double fInnerRadius;
        G4double fOuterRadius;
        G4double fDriftLength;
        G4LogicalVolume* fLogicActive;
        G4LogicalVolume* fLogicInnerDisk;
        G4LogicalVolume* fLogicOuterDisk;
        G4FieldManager* fFieldMgr;
        G4ChordFinder* fChordFinder;
};
#endif