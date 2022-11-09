#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>

class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

    G4VPhysicalVolume* Construct() override;

private:
 
    void ConstructDemo(G4LogicalVolume* worldLog);
    void ConstructSDandField() override;
};

#endif
