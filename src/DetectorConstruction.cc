#include "DetectorConstruction.hh"

#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Material.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <G4Isotope.hh>
#include <G4Element.hh>
#include <G4Material.hh>

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
    fInnerRadius(1.50 * cm),
    fOuterRadius(3.0 * cm),
    fDriftLength(18.0 * cm)
{
}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* matLar = nist->FindOrBuildMaterial("G4_lAr");
    G4Material* matAnode= nist->FindOrBuildMaterial("G4_Al");

    //THis is specifically just for Bismtuh source
    G4int ncomponents, natoms;
    G4double abundance;
    G4Isotope* Bi207 = new G4Isotope("Bi207", 83, 207, 206.9786 * g/mole);
    G4Element* Bi = new G4Element("Bismuth", "Bi", 1);
    Bi->AddIsotope(Bi207, 100.*perCent);

    G4Material* matBi207 = new G4Material("Bismuth", 9.806 * g/cm3, 1);
    matBi207->AddElement(Bi, 1);

    //the dimensions of the volume should be cylindrical
    G4double worldRadius = 4.0 * cm;
    G4double worldLength = 20.0 * cm;
    G4Tubs* solidWorld = new G4Tubs("World", 0., worldRadius, 0.5* worldLength, 0., 360. * deg);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, matLar, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);
     //this is for LAr
    G4Tubs* solidActive = new G4Tubs("ActiveLar",0.0, fOuterRadius, 0.5 * fDriftLength, 0. , 360. * deg);
    G4LogicalVolume* logicActive = new G4LogicalVolume(solidActive, matLar, "ActiveLar");
    new G4PVPlacement(nullptr, G4ThreeVector(), logicActive, "ActiveLar", logicWorld, false, 0);


    //Here lets create a anode region
    G4double anodeThickness = 0.1 * mm;
    G4double zPosAnode = 0.5 * fDriftLength + 0.5 * anodeThickness;

    //InnerDisk anode
    G4Tubs* solidInnerDisk = new G4Tubs("InnerDisk", 0., fInnerRadius, 0.5 * anodeThickness, 0., 360. * deg);
    G4LogicalVolume* logicInnerDisk = new G4LogicalVolume(solidInnerDisk, matAnode, "InnerDisk");
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., zPosAnode), logicInnerDisk, "InnerDisk", logicWorld, false, 0);

    //OuterDisk anode
    G4Tubs* solidOuterDisk = new G4Tubs("OuterDisk", fInnerRadius, fOuterRadius, 0.5 * anodeThickness, 0., 360. * deg);
    G4LogicalVolume* logicOuterDisk = new G4LogicalVolume(solidOuterDisk, matAnode, "OuterDisk");
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., zPosAnode), logicOuterDisk, "OuterDisk", logicWorld, false, 0);


    //cathode place to encapsulate the Bismuth with solid titanium
    G4Material* matTi = nist->FindOrBuildMaterial("G4_Ti");
    G4double cathodeRadius = 3.0 * cm;
    G4double cathodeThickness = 0.1 * mm;
    G4Tubs* solidCathode = new G4Tubs("Cathode", 0., cathodeRadius, 0.5 * cathodeThickness, 0., 360. * deg);
    G4LogicalVolume* logicCathode = new G4LogicalVolume(solidCathode, matAnode, "Cathode");
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., -0.5 * fDriftLength - 0.5 * cathodeThickness), logicCathode, "Cathode", logicWorld, false, 0, true);

    //source parameters
    G4double biDiameter = 5.0 * mm;
    G4double biRadius = biDiameter * 0.5;
    G4double biThickness = 0.05 * mm;
    G4ThreeVector biPosition(0.0,0.0,0.0);
    
    //Bismuth encapsulated in Titanium foil
    G4Tubs* solidTiFoil = new G4Tubs("TiFoil", 0., biRadius+biThickness, 0.5 * biThickness, 0., 360. * deg);
    G4LogicalVolume* logicTiFoil = new G4LogicalVolume(solidTiFoil, matTi, "TiFoil");
    new G4PVPlacement(nullptr, biPosition, logicTiFoil, "TiFoil", logicCathode, false, 0, true);

    //Bismuth source
    G4Tubs* solidBi207 = new G4Tubs("Bi207Source", 0., biRadius, 0.5 * biThickness, 0., 360. * deg);
    G4LogicalVolume* logicBi207 = new G4LogicalVolume(solidBi207, matBi207, "Bi207Source");
    G4PVPlacement* physBi207 = new G4PVPlacement(nullptr, biPosition, logicBi207, "Bi207Source", logicTiFoil, false, 0, true);



    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
    G4VisAttributes* visAttrActive = new G4VisAttributes(G4Colour(0.0, 0.8,1.0, 0.3));
    logicActive->SetVisAttributes(visAttrActive);

    G4VisAttributes* innerDiskVis = new G4VisAttributes(G4Colour(0.0, 0.0,1.0, 0.6));
    logicInnerDisk->SetVisAttributes(innerDiskVis);

    G4VisAttributes* outerDiskVis = new G4VisAttributes(G4Colour(1.0, 0.5,0.0, 0.6));
    logicOuterDisk->SetVisAttributes(outerDiskVis);

    G4VisAttributes* visAttrCathode = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8)); 
    logicTiFoil->SetVisAttributes(visAttrCathode);

    G4VisAttributes* visAttrBi207 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); 
    logicBi207->SetVisAttributes(visAttrBi207);

    return physWorld;

}
