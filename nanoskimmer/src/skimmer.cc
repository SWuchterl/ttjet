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
#include <ttjet/nanoskimmer/interface/filters.h>
#include <ttjet/nanoskimmer/interface/particles.h>

#include <ttjet/nanoskimmer/interface/skimmer.h>

using namespace std;



// Skimmer::Skimmer(){
// };


// TFile* file = TFile::Open(inFile.c_str(), "READ");
// Skimmer::Skimmer(TFile* file, string Name){

Skimmer::Skimmer(const string &inputFileName, const string &Name) :
        inputFile(new TFile(inputFileName.c_str())),
        reader("Events",inputFile),
        nMuons(reader, "nMuon"),
        muonPt(reader, "Muon_pt"), //{
        muonEta(reader,"Muon_eta"),
        muonPhi(reader,"Muon_phi"),
        muonMass(reader,"Muon_mass"),
        muonMediumId(reader,"Muon_mediumId"),
        muonIso(reader,"Muon_pfRelIso04_all"),
        muonSIP3D(reader,"Muon_sip3d"),
        muonMVAId(reader,"Muon_mvaId"),
        muonTightId(reader,"Muon_tightId"),
        muonDz(reader,"Muon_dz"),
        muonDxy(reader,"Muon_dxy"),
        muonGenPartFlav(reader,"Muon_genPartFlav"),
        muonGenParticleIndex(reader,"Muon_genPartIdx"),
        muonCharge(reader,"Muon_charge"),

        nElectrons(reader,"nElectron"),
        electronPt(reader,"Electron_pt"),
        electronEta(reader,"Electron_eta"),
        electronPhi(reader,"Electron_phi"),
        electronMass(reader,"Electron_mass"),
        electronCutBasedId(reader,"Electron_cutBased"),
        electronDz(reader,"Electron_dz"),
        electronDxy(reader,"Electron_dxy"),
        electronSIP3D(reader,"Electron_sip3d"),
        electronGenPartFlav(reader,"Electron_genPartFlav"),
        electronGenParticleIndex(reader,"Electron_genPartIdx"),
        electronMVALoose(reader,"Electron_mvaFall17V2noIso_WPL"),
        electronMVAMedium(reader,"Electron_mvaFall17V2noIso_WP90"),
        electronMVATight(reader,"Electron_mvaFall17V2noIso_WP80"),
        electronMVALooseIso(reader,"Electron_mvaFall17V2Iso_WPL"),
        electronMVAMediumIso(reader,"Electron_mvaFall17V2Iso_WP90"),
        electronMVATightIso(reader,"Electron_mvaFall17V2Iso_WP80"),
        electronCharge(reader,"Electron_charge"),
        electronConvVeto(reader,"Electron_convVeto"),


        nJets(reader,"nJet"),
        jetPt(reader,"Jet_pt"),
        jetEta(reader,"Jet_eta"),
        jetPhi(reader,"Jet_phi"),
        jetMass(reader,"Jet_mass"),
        genJetIndex(reader,"Jet_genJetIdx"),
        jetFlavour(reader,"Jet_phi"),
        jetBTagDiscriminator_DeepCSV(reader,"Jet_btagDeepB"),
        jetBTagDiscriminator_DeepFlavour(reader,"Jet_btagDeepFlavB"),
        jetRawFactor(reader,"Jet_rawFactor"),

        metPt(reader,"MET_pt"),
        metPhi(reader,"MET_phi"),
        metPt_Puppi(reader,"PuppiMET_pt"),
        metPhi_Puppi(reader,"PuppiMET_phi"),
        metPt_Raw(reader,"RawMET_pt"),
        metPhi_Raw(reader,"RawMET_phi"),

        nPVertex(reader,"PV_npvs"),
        nGoodPVertex(reader,"PV_npvsGood"),
        nPU(reader,"Pileup_nPU"),
        nPUTrueInt(reader,"Pileup_nTrueInt"),

        genWeight(reader,"genWeight"),


        metFilter_primaryVertex(reader,"Flag_goodVertices"),
        metFilter_beamHalo(reader,"Flag_globalSuperTightHalo2016Filter"),
        metFilter_HBHENoise(reader,"Flag_HBHENoiseFilter"),
        metFilter_HBHENoiseIso(reader,"Flag_HBHENoiseIsoFilter"),
        metFilter_ECALTP(reader,"Flag_EcalDeadCellTriggerPrimitiveFilter"),
        metFilter_BadPFMuon(reader,"Flag_BadPFMuonFilter"),
        metFilter_BadChargedHadron(reader,"Flag_BadChargedCandidateFilter"),
        metFilter_eeBadSCNoise(reader,"Flag_eeBadScFilter"),


        nGenJet(reader,"nGenJet"),
        nGenJetEta(reader,"GenJet_eta"),
        genJetPhi(reader,"GenJet_phi"),
        genJetPt(reader,"GenJet_pt"),
        genJetMass(reader,"GenJet_mass"),
        genJetPartonFlavour(reader,"GenJet_partonFlavour"),
        genJetHadronFlavour(reader,"GenJet_hadronFlavour"),

        genMetPhi(reader,"GenMET_phi"),
        genMetPt(reader,"GenMET_pt"),

        nGenPart(reader,"nGenPart"),
        genPartEta(reader,"GenPart_eta"),
        genPartPhi(reader,"GenPart_phi"),
        genPartPt(reader,"GenPart_pt"),
        genPartMotherIndex(reader,"GenPart_genPartIdxMother"),
        genPartId(reader,"GenPart_pdgId"),
        genPartStatus(reader,"GenPart_pdgId"),
        genPartStatusFlags(reader,"GenPart_pdgId"),



// 2016
        HLT_SingleEle(reader,"HLT_Ele25_WPTight_Gsf"),
        HLT_SingleMu(reader,"HLT_IsoMu20"),
        HLT_SingleMuIso(reader,"HLT_IsoTkMu20"),
        HLT_DoubleMu(reader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"),
        HLT_DoubleMuDZ(reader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"),
        HLT_DoubleMuTK(reader,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"),
        HLT_DoubleMuTkDZ(reader,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"),
        HLT_DoubleEle(reader,"HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"),
        HLT_MuEleHigh(reader,"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"),
        HLT_MuEleLow(reader,"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL")
{
        // 2017
        //  HLT_(reader,"HLT_");

        start = std::chrono::steady_clock::now();
        std::cout << "Input file for analysis: " + inputFileName << std::endl;

        dataSetName=Name;

        rochesterCorrection = new RoccoR("ttjet/nanoskimmer/data/rochester/RoccoR2016.txt");


        if((Name.find("Double")!=string::npos)||(Name.find("Single")!=string::npos)) {
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

        while(reader.Next()) {
                Event event(this);
                event.SetMuons();
                event.SetElectrons();
                event.SetJets();
                event.SetValues();
                continue;
        }
        return true;
};


void Skimmer::CreateOutputTree(const std::string &outFile){

        inputFile->Close();

        tree = new TTree();
        outFileName=outFile;
        tree->SetName("Events");
};
void Skimmer::WriteOutput(const std::string &outFile){

        TFile* file = TFile::Open(outFileName.c_str(), "RECREATE");

        tree->Write();


        file->Write();
        file->Close();

        end = std::chrono::steady_clock::now();
        std::cout << "Finished event loop (in seconds): " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;

        std::cout << "Output file created: " + outFileName << std::endl;
}
