#include "DetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Box.hh>
#include <G4Orb.hh>
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>

#include <sstream>

using namespace std;

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    //CREATION OF CUBIC WORLD OF 5m SIZE
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeX = 5 * m;
    G4double worldSizeY = 5 * m;
    G4double worldSizeZ = 5 * m;


    // 1) Solid
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // 2) Logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, nist->FindOrBuildMaterial("G4_AIR"), "world");
    G4VisAttributes* visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);
    worldLog->SetVisAttributes(visAttr);

    // 3) Physical volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    //CREATION OF THE DETECTOR
    G4double thickness = 10 * cm;
    G4double width = 5 * cm;
    G4double height = 5 * cm;

    G4Material *polystyrene=nist->FindOrBuildMaterial("G4_POLYSTYRENE");
    
    G4VSolid* absorberBox = new G4Box("absorber", thickness, width, height);

    G4LogicalVolume* absorberLog = new G4LogicalVolume(absorberBox, polystyrene, "absorber");

    G4ThreeVector absorberPosition = {0.,0.,0.};
    new G4PVPlacement (0, absorberPosition, absorberLog, "absorber", worldLog, false, 0, 0);
    
    
    // The Construct() method has to return the final (physical) world volume:
    return worldPhys;
}

void DetectorConstruction::ConstructDemo(G4LogicalVolume* worldLog)
{
  vector<string> labelData = {
        "                                                                                            ",
        "  #######  ####     #####   #     #   #######    ###       ####    #####      #     #####   ",
        "     #     #   #    #       ##    #      #      #   #         #    #   #     ##    #    #   ",
        "     #     #   #    #       # #   #      #      #   #         #    #   #    # #    #   #    ",
        "     #     ####     ###     #  #  #      #      #   #        #     #   #      #     ####    ",
        "     #     #  #     #       #   # #      #      #   #       #      #   #      #     ####    ",
        "     #     #   #    #       #    ##      #      #   #      #       #   #      #    #    #   ",
        "     #     #   #    #####   #     #      #       ###       ####    #####      #    ## # #   ",
        "                                                                                            "
    };
 }
 
void DetectorConstruction::ConstructSDandField()
{
 
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    sdManager->SetVerboseLevel(2);
    
    G4MultiFunctionalDetector* absorberDetector = new G4MultiFunctionalDetector("absorber");

    G4VPrimitiveScorer* absorberScorer = new G4PSEnergyDeposit("energy");
    absorberDetector ->RegisterPrimitive(absorberScorer);

    SetSensitiveDetector("absorber", absorberDetector);
    sdManager->AddNewDetector(absorberDetector);
    
    
}
