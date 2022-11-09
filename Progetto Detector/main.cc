#include <vector>
#include <G4RunManagerFactory.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4String.hh>
#include <G4UImanager.hh>
#include "ActionInitialization.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include <G4EmLivermorePhysics.hh>
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4ScoringManager.hh"
#include <Analysis.hh>

using namespace std;


int main(int argc, char** argv)
{
  G4cout << "Application starting..." << G4endl;

  vector<G4String> macros;
  G4bool interactive = false;

  // Parse command line arguments
  if  (argc == 1)
    {
      interactive = true;
    }
  else
    {
      for (int i = 1; i < argc; i++)
        {
	  G4String arg = argv[i];
	  if (arg == "-i" || arg == "--interactive")
            {
	      interactive = true;
	      continue;
            }
	  else
            {
	      macros.push_back(arg);
            }
        }
    }


  auto* runManager  = 
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);
  runManager->SetVerboseLevel(1);

  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  runManager->SetUserInitialization(new PhysicsList());

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new ActionInitialization());

  G4UIExecutive* ui = nullptr;
  if (interactive)
    {
      G4cout << "Creating interactive UI session ...";
      ui = new G4UIExecutive(argc, argv);
    }
  G4UImanager* UImanager = G4UImanager::GetUIpointer();


    G4ScoringManager::GetScoringManager();

  for (auto macro : macros)
    {
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command + macro);
    }

  if (interactive)
    {
      if (ui->IsGUI())
	{
	  UImanager->ApplyCommand("/control/execute macros/ui.mac");
	}
      else
	{
	  UImanager->ApplyCommand("/run/initialize");
	}
      ui->SessionStart();
      delete ui;
    }

  delete runManager;
    

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->CloseFile();

  G4cout << "Application successfully ended.\nBye :-)" << G4endl;

  return 0;
}
