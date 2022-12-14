#include "PhysicsList.hh"
#include <G4EmStandardPhysics.hh>
#include <G4DecayPhysics.hh> 
#include <G4ProductionCutsTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4EmLivermorePhysics.hh>
#include <G4EmPenelopePhysics.hh>
#include <G4EmLowEPPhysics.hh>


PhysicsList::PhysicsList()
{
  RegisterPhysics(new G4EmStandardPhysics());
    // RegisterPhysics(new G4EmLivermorePhysics());
    // RegisterPhysics(new G4EmPenelopePhysics());
  //RegisterPhysics(new G4EmLowEPPhysics());
  
}


void PhysicsList::SetCuts()
{

  G4VUserPhysicsList::SetCuts();
  
  DumpCutValuesTable();
}
