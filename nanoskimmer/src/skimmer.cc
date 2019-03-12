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

Skimmer::Skimmer(const string &inputFileName, const string &Name) : inputFile(new TFile(inputFileName.c_str())),reader("Events",inputFile),nMuons(reader, "nMuon"),
        muonPt(reader, "Muon_pt") {
        // TFile* file = TFile::Open(inputFileName.c_str(), "READ");
        // TTree* eventTree=(TTree*)file->Get("Events");
        // eventTree=(TTree*)file->Get("Events");
        // reader(eventTree);
        // reader.SetTree(eventTree);
        // nMuons(reader,"nMuons");
        // muonPt(reader,"Muon_pt");
        // TTreeReaderArray<float> muonEta(reader,"Muon_eta");
        // TTreeReaderArray<float> muonPhi(reader,"Muon_phi");
        // TTreeReaderArray<float> muonMass(reader,"Muon_mass");
        // TTreeReaderArray<bool> muonMediumId(reader,"Muon_mediumId");
        // TTreeReaderArray<char> muonPFIsoId(reader,"Muon_pfIsoId");
        // TTreeReaderArray<float> muonSIP3D(reader,"Muon_pfIsoId");
        // TTreeReaderArray<char> muonMVAId(reader,"Muon_pfIsoId");
        // TTreeReaderArray<bool> muonTightId(reader,"Muon_pfIsoId");
        // TTreeReaderArray<float> muonDz(reader,"Muon_pfIsoId");
        // TTreeReaderArray<float> muonDxy(reader,"Muon_pfIsoId");
        // TTreeReaderArray<char> muonGenPartFlav(reader,"Muon_pfIsoId");
        // TTreeReaderArray<int> muonCharge(reader,"Muon_charge");
        //
        // TTreeReaderValue<uint> nElectrons(reader,"nElectrons");
        // TTreeReaderArray<float> electronPt(reader,"Electron_pt");
        // TTreeReaderArray<float> electronEta(reader,"Electron_eta");
        // TTreeReaderArray<float> electronPhi(reader,"Electron_phi");
        // TTreeReaderArray<float> electronCutBasedId(reader,"Electron_cutBased");
        // TTreeReaderArray<float> electronDz(reader,"Electron_dz");
        // TTreeReaderArray<float> electronDxy(reader,"Electron_dxy");
        // TTreeReaderArray<float> electronSIP3D(reader,"Electron_sip3d");
        // TTreeReaderArray<char> electronGenPartFlav(reader,"Electron_genPartFlav");
        // TTreeReaderArray<bool> electronMVALoose(reader,"Electron_mvaFall17V2noIso_WPL");
        // TTreeReaderArray<bool> electronMVAMedium(reader,"Electron_mvaFall17V2noIso_WP90");
        // TTreeReaderArray<bool> electronMVATight(reader,"Electron_mvaFall17V2noIso_WP80");
        // TTreeReaderArray<bool> electronMVALooseIso(reader,"Electron_mvaFall17V2Iso_WPL");
        // TTreeReaderArray<bool> electronMVAMediumIso(reader,"Electron_mvaFall17V2Iso_WP90");
        // TTreeReaderArray<bool> electronMVATightIso(reader,"Electron_mvaFall17V2Iso_WP80");
        // TTreeReaderArray<bool> electronCharge(reader,"Electron_charge");
        //
        //
        // TTreeReaderValue<uint> nJets(reader,"nJets");
        // TTreeReaderArray<float> jetPt(reader,"Jet_pt");
        // TTreeReaderArray<float> jetEta(reader,"Jet_eta");
        // TTreeReaderArray<float> jetPhi(reader,"Jet_phi");
        // TTreeReaderArray<int> genJetIndex(reader,"Jet_genJetIdx");
        // TTreeReaderArray<float> jetFlavour(reader,"Jet_phi");
        // TTreeReaderArray<float> jetBTagDiscriminator_DeepCSV(reader,"Jet_btagDeepB");
        // TTreeReaderArray<float> jetBTagDiscriminator_DeepFlavour(reader,"Jet_btagDeepFlavB");
        // TTreeReaderArray<float> jetRawFactor(reader,"Jet_rawFactor");
        //
        // TTreeReaderValue<float> metPt(reader,"MET_Pt");
        // TTreeReaderValue<float> metPhi(reader,"MET_Phi");
        // TTreeReaderValue<float> metPt_Puppi(reader,"PuppiMET_Pt");
        // TTreeReaderValue<float> metPhi_Puppi(reader,"PuppiMET_Phi");
        // TTreeReaderValue<float> metPt_Raw(reader,"RawMET_Pt");
        // TTreeReaderValue<float> metPhi_Raw(reader,"RawMET_Phi");
        //
        // TTreeReaderValue<int> nPVertex(reader,"PV_npvs");
        // TTreeReaderValue<int> nGoodPVertex(reader,"PV_npvsGood");
        // TTreeReaderValue<int> nPU(reader,"Pileup_nPU");
        // TTreeReaderValue<float> nPUTrueInt(reader,"Pileup_nTrueInt");
        //
        // TTreeReaderValue<float> genWeight(reader,"genWeight");
        //
        //
        // TTreeReaderValue<bool> metFilter_primaryVertex(reader,"Flag_goodVertices");
        // TTreeReaderValue<bool> metFilter_beamHalo(reader,"Flag_globalSuperTightHalo2016Filter");
        // TTreeReaderValue<bool> metFilter_HBHENoise(reader,"Flag_HBHENoiseFilter");
        // TTreeReaderValue<bool> metFilter_HBHENoiseIso(reader,"Flag_HBHENoiseIsoFilter");
        // TTreeReaderValue<bool> metFilter_ECALTP(reader,"Flag_EcalDeadCellTriggerPrimitiveFilter");
        // TTreeReaderValue<bool> metFilter_BadPFMuon(reader,"Flag_BadPFMuonFilter");
        // TTreeReaderValue<bool> metFilter_BadChargedHadron(reader,"Flag_BadChargedCandidateFilter");
        // TTreeReaderValue<bool> metFilter_eeBadSCNoise(reader,"Flag_eeBadScFilter");
        //
        //
        // TTreeReaderValue<uint> nGenJet(reader,"nGenJet");
        // TTreeReaderArray<float> nGenJetEta(reader,"GenJet_eta");
        // TTreeReaderValue<float> genJetPhi(reader,"GenJet_phi");
        // TTreeReaderValue<float> genJetPt(reader,"GenJet_pt");
        // TTreeReaderValue<float> genJetMass(reader,"GenJet_mass");
        // TTreeReaderValue<int> genJetPartonFlavour(reader,"GenJet_partonFlavour");
        // TTreeReaderValue<uchar> genJetHadronFlavour(reader,"GenJet_hadronFlavour");
        //
        // TTreeReaderValue<float> genMetPhi(reader,"GenMET_phi");
        // TTreeReaderValue<float> genMetPt(reader,"GenMET_pt");
        //
        // TTreeReaderValue<uint> nGenPart(reader,"nGenPart");
        // TTreeReaderArray<float> genPartEta(reader,"GenPart_eta");
        // TTreeReaderArray<float> genPartPhi(reader,"GenPart_phi");
        // TTreeReaderArray<float> genPartPt(reader,"GenPart_pt");
        // TTreeReaderArray<int> genPartMotherIndex(reader,"GenPart_genPartIdxMother");
        // TTreeReaderArray<int> genPartId(reader,"GenPart_pdgId");
        // TTreeReaderArray<int> genPartStatus(reader,"GenPart_pdgId");
        // TTreeReaderArray<int> genPartStatusFlags(reader,"GenPart_pdgId");
        //
        //
        //
        // // 2016
        // TTreeReaderValue<bool> HLT_SingleEle(reader,"HLT_Ele25_WPTight_Gsf");
        // TTreeReaderValue<bool> HLT_SingleMu(reader," HLT_IsoMu20");
        // TTreeReaderValue<bool> HLT_SingleMuIso(reader," HLT_IsoTkMu20");
        // TTreeReaderValue<bool> HLT_DoubleMu(reader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
        // TTreeReaderValue<bool> HLT_DoubleMuDZ(reader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ");
        // TTreeReaderValue<bool> HLT_DoubleMuTK(reader,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL");
        // TTreeReaderValue<bool> HLT_DoubleMuTkDZ(reader,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ");
        // TTreeReaderValue<bool> HLT_DoubleEle(reader,"HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        // TTreeReaderValue<bool> HLT_MuEleHigh(reader,"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
        // TTreeReaderValue<bool> HLT_MuEleLow(reader,"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL");
        // 2017
        // TTreeReaderValue<bool> HLT_(reader,"HLT_");

        dataSetName=Name;

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

                // cout<< *nMuons<<endl;
                continue;
        }
        return true;
};


void Skimmer::CreateOutputTree(const std::string &outFile){

        myFile->Close();

        tree = new TTree();
        outFileName=outFile;
        cout<<outFileName<<endl;
        tree->SetName("Events");
};
void Skimmer::WriteOutput(const std::string &outFile){
        cout<<outFileName<<endl;

        TFile* file = TFile::Open(outFileName.c_str(), "RECREATE");

        tree->Write();


        file->Write();
        file->Close();

        end = std::chrono::steady_clock::now();
        std::cout << "Finished event loop (in seconds): " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;

        std::cout << "Output file created: " + outFileName << std::endl;
}
