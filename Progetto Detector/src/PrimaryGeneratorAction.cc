#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>

#include <G4GeneralParticleSource.hh>

#include <G4ParticleTable.hh>
#include <G4IonTable.hh>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{

    fGPS = new G4GeneralParticleSource();

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{

    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

    fGPS->GeneratePrimaryVertex(anEvent);
}
