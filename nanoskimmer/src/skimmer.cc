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








Skimmer::Skimmer(const string &inputFileName_, const string &dataSetName_,const string &outName)
{

        outFileName=outName;
        start = std::chrono::steady_clock::now();
        std::cout << "Input file for analysis: " + inputFileName_ << std::endl;

        dataSetName=dataSetName_;
        inputFileName=inputFileName_;


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

        TTree* tree = new TTree();
        tree->SetName("Events");
        trees.push_back(tree);

        MyReader myReader(reader);
        const int year=2016;
        MetFilter METFilter;
        TriggerFilter TrigFilter;
        RoccoR rochesterCorrection("ttjet/nanoskimmer/data/rochester/RoccoR2016.txt");
        PileupWeighter PUWeighter(reader,year);

        Weighter MuonSFWeighterBCDEF_tightID("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt");
        MuonSFWeighterBCDEF_tightID.fillOverflow2d();
        Weighter MuonSFWeighterBCDEF_tightIDSys("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt_syst");
        MuonSFWeighterBCDEF_tightIDSys.fillOverflow2d();
        Weighter MuonSFWeighterBCDEF_tightIDStat("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt_stat");
        MuonSFWeighterBCDEF_tightIDStat.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightID("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt");
        MuonSFWeighterGH_tightID.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightIDSys("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt_syst");
        MuonSFWeighterGH_tightIDSys.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightIDStat("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ID.root","NUM_TightID_DEN_genTracks_eta_pt_stat");
        MuonSFWeighterGH_tightIDStat.fillOverflow2d();

        Weighter MuonSFWeighterBCDEF_tightIso("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
        MuonSFWeighterBCDEF_tightIso.fillOverflow2d();
        Weighter MuonSFWeighterBCDEF_tightIsoSys("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst");
        MuonSFWeighterBCDEF_tightIsoSys.fillOverflow2d();
        Weighter MuonSFWeighterBCDEF_tightIsoStat("ttjet/nanoskimmer/data/scaleFactors/muon/RunBCDEF_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat");
        MuonSFWeighterBCDEF_tightIsoStat.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightIso("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
        MuonSFWeighterGH_tightIso.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightIsoSys("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst");
        MuonSFWeighterGH_tightIsoSys.fillOverflow2d();
        Weighter MuonSFWeighterGH_tightIsoStat("ttjet/nanoskimmer/data/scaleFactors/muon/RunGH_SF_ISO.root","NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat");
        MuonSFWeighterGH_tightIsoStat.fillOverflow2d();
        //pt vs eta
        Weighter ElectronSFWeighter_ID("ttjet/nanoskimmer/data/scaleFactors/electron/2016LegacyReReco_ElectronTight_Fall17V2.root","EGamma_SF2D");
        ElectronSFWeighter_ID.fillOverflow2d();
        Weighter ElectronSFWeighter_Reco("ttjet/nanoskimmer/data/scaleFactors/electron/EGM2D_BtoH_low_RecoSF_Legacy2016.root","EGamma_SF2D");
        ElectronSFWeighter_Reco.fillOverflow2d();
        Weighter ElectronSFWeighter_Reco20("ttjet/nanoskimmer/data/scaleFactors/electron/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root","EGamma_SF2D");
        ElectronSFWeighter_Reco20.fillOverflow2d();

        Event event(isData);

        event.SetAdresses(myReader,trees[0]);


        while(reader.Next()) {

                if(METFilter.getDecision(myReader,year)) {
                        event.Clear();
                        event.SetMuons(myReader,rochesterCorrection);
                        event.SetElectrons(myReader,ElectronSFWeighter_Reco,ElectronSFWeighter_Reco20,ElectronSFWeighter_ID);
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
        file->Close();
        return true;



};



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
