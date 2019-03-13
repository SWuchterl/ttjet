#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <cmath>

#include <thread>
#include <mutex>
#include <chrono>
#include <pthread.h>

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TMath.h>

#include <ttjet/nanoskimmer/interface/event.h>
#include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>
#include <ttjet/nanoskimmer/interface/particles.h>
#include <ttjet/nanoskimmer/interface/weighter.h>
#include <ttjet/nanoskimmer/interface/pileupWeighter.h>

#include <ttjet/nanoskimmer/interface/skimmer.h>

using namespace std;



// Skimmer::Skimmer(){
// };


// TFile* file = TFile::Open(inFile.c_str(), "READ");
// Skimmer::Skimmer(TFile* file, string Name){

Skimmer::Skimmer(const string &inputFileName_, const string &dataSetName_,const string &outName)
{
        // theReader=MyReader(inputFileName,Name);
        // myReader = MyReader(inputFileName,Name);
        // myReader = theReader;
        // 2017
        //  HLT_(reader,"HLT_");
        outFileName=outName;
        start = std::chrono::steady_clock::now();
        std::cout << "Input file for analysis: " + inputFileName_ << std::endl;

        dataSetName=dataSetName_;
        inputFileName=inputFileName_;

        // TrigFilter = new TriggerFilter(myReader,2016);
        // METFilter = new MetFilter(myReader,2016);

        if((dataSetName_.find("Double")!=string::npos)||(dataSetName_.find("Single")!=string::npos)) {
                isData=true;
        }else{
                isData=false;
        }
};

void Skimmer::ProgressBar(const int &progress){
        std::string progressBar = "[";

        for(int i = 0; i < progress; i++) {
                if(i%2 == 0) progressBar += "#";
        }

        for(int i = 0; i < 100 - progress; i++) {
                if(i%2 == 0) progressBar += " ";
        }

        progressBar = progressBar + "] " + std::to_string(progress) + "% of Events processed";
        std::cout << "\r" << progressBar << std::flush;

        if(progress == 100) std::cout << std::endl;

}

bool Skimmer::Analyze(){

// ProgressBar(0.);
        int processed = 0;

        TFile* file = TFile::Open(inputFileName.c_str(), "READ");
        TTree* eventTree = (TTree*)file->Get("Events");
        TTreeReader reader(eventTree);

        // TTree* tree = new TTree();
        TTree* tree = new TTree();
        tree->SetName("Events");
        trees.push_back(tree);

        MyReader myReader(reader);
        const int year=2016;
        // TTree outputTree=CreateOutputTree(outFileName);
        MetFilter METFilter;
        TriggerFilter TrigFilter;
        RoccoR rochesterCorrection("ttjet/nanoskimmer/data/rochester/RoccoR2016.txt");
        PileupWeighter PUWeighter(reader,year);
        Event event(isData);

        event.SetAdresses(myReader,trees[0]);


        while(reader.Next()) {

                if(METFilter.getDecision(myReader,year)) {
                        // Event event(myReader,TrigFilter,METFilter,rochesterCorrection,PUWeighter,isData);
                        event.Clear();
                        event.SetMuons(myReader,rochesterCorrection);
                        event.SetElectrons(myReader);
                        event.SetJets(myReader);
                        event.SetValues(myReader,trees[0],TrigFilter,year,PUWeighter);

                        trees[0]->Fill();
                }
                processed++;
                if(processed % 1000 == 0) {
                        int progress = 100*(float)processed/eventTree->GetEntries();
                        ProgressBar(progress);
                }
                continue;
        }
        // ProgressBar(100);
        // file->Close();
        return true;
        // file->Close();
        // inputFileName.->Close();


};


// &TTree Skimmer::CreateOutputTree(const std::string &outFile){
//
//
//
//         TTree* tree = new TTree();
//         // outFileName=outFile;
//         tree->SetName("Events");
//         return tree;
// };
void Skimmer::WriteOutput(const std::string &outFile){

        TFile* file = TFile::Open(outFileName.c_str(), "RECREATE");

        for(TTree* tree: trees) {
                tree->Write();
        }


        file->Write();
        file->Close();

        end = std::chrono::steady_clock::now();
        std::cout << "Finished event loop (in seconds): " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;

        std::cout << "Output file created: " + outFileName << std::endl;
}
