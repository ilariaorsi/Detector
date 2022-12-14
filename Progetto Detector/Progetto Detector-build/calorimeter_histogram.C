// This ROOT script displays histogram as saved in 4c in ROOT format.
// How to run it: `root calorimeter_histogram.C`
// Before running, check that you have an existing task4.root file and 
// that the histogram is called "eDep".

#include <iostream>

void calorimeter_histogram()
{
    const char* path = "/Users/admin/geant4-v11.0.1/Progetto Detector-build/progetto.root";
    const char* histogramName = "eDep";
    TFile* f = TFile::Open(path);
    if (!f)
    {
        std::cout << "File " << path << " does not exist." << std::endl;
        return;
    }
    else
    {
        auto h = (TH1F*)f->Get(histogramName);
        if (!h)
        {
            std::cout << "Error: The files does not contain histogram " << histogramName << std::endl;
        }
        else
        {
            new TCanvas();
            h->Draw();
        }
    }
}
