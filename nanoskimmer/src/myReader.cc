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

// #include <ttjet/nanoskimmer/interface/event.h>
// #include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
// #include <ttjet/nanoskimmer/interface/triggerfilter.h>
// #include <ttjet/nanoskimmer/interface/metfilter.h>
// #include <ttjet/nanoskimmer/interface/particles.h>

// #include <ttjet/nanoskimmer/interface/skimmer.h>

using namespace std;



// Skimmer::Skimmer(){
// };


// TFile* file = TFile::Open(inFile.c_str(), "READ");
// Skimmer::Skimmer(TFile* file, string Name){

// MyReader::MyReader(const string &inputFileName, const string &Name) :
MyReader::MyReader(TTreeReader &reader_,bool &isData_) :
        // inputFile(new TFile(inputFileName.c_str())),
        // reader("Events",inputFile),
        isData{isData_},
        nMuons(reader_, "nMuon"),
        muonPt(reader_, "Muon_pt"), //{
        muonEta(reader_,"Muon_eta"),
        muonPhi(reader_,"Muon_phi"),
        muonMass(reader_,"Muon_mass"),
        muonMediumId(reader_,"Muon_mediumId"),
        muonIso(reader_,"Muon_pfRelIso04_all"),
        muonSIP3D(reader_,"Muon_sip3d"),
        muonMVAId(reader_,"Muon_mvaId"),
        muonTightId(reader_,"Muon_tightId"),
        muonDz(reader_,"Muon_dz"),
        muonDxy(reader_,"Muon_dxy"),
        muonGenPartFlav(reader_,isData_ ? "Muon_mvaId" : "Muon_genPartFlav"),
        muonGenParticleIndex(reader_,isData_ ? "Muon_charge" : "Muon_genPartIdx"),
        muonCharge(reader_,"Muon_charge"),
        muonNLayers(reader_,"Muon_nTrackerLayers"),

        nElectrons(reader_,"nElectron"),
        electronPt(reader_,"Electron_pt"),
        electronEta(reader_,"Electron_eta"),
        electronPhi(reader_,"Electron_phi"),
        electronMass(reader_,"Electron_mass"),
        electronCutBasedId(reader_,"Electron_cutBased"),
        electronDz(reader_,"Electron_dz"),
        electronDxy(reader_,"Electron_dxy"),
        electronSIP3D(reader_,"Electron_sip3d"),
        electronGenPartFlav(reader_,isData_ ? "Muon_mvaId" : "Electron_genPartFlav"),
        electronGenParticleIndex(reader_,isData_ ? "Electron_charge" : "Electron_genPartIdx"),
        electronMVALoose(reader_,"Electron_mvaFall17V2noIso_WPL"),
        electronMVAMedium(reader_,"Electron_mvaFall17V2noIso_WP90"),
        electronMVATight(reader_,"Electron_mvaFall17V2noIso_WP80"),
        electronMVALooseIso(reader_,"Electron_mvaFall17V2Iso_WPL"),
        electronMVAMediumIso(reader_,"Electron_mvaFall17V2Iso_WP90"),
        electronMVATightIso(reader_,"Electron_mvaFall17V2Iso_WP80"),
        electronCharge(reader_,"Electron_charge"),
        electronConvVeto(reader_,"Electron_convVeto"),
        electronIso(reader_,"Electron_pfRelIso03_all"),


        nJets(reader_,"nJet"),
        jetPt(reader_,"Jet_pt"),
        jetEta(reader_,"Jet_eta"),
        jetPhi(reader_,"Jet_phi"),
        jetMass(reader_,"Jet_mass"),
        genJetIndex(reader_,isData_ ? "Electron_charge" : "Jet_genJetIdx"),
        jetFlavour(reader_,"Jet_phi"),
        jetBTagDiscriminator_DeepCSV(reader_,"Jet_btagDeepB"),
        jetBTagDiscriminator_DeepFlavour(reader_,"Jet_btagDeepFlavB"),
        jetRawFactor(reader_,"Jet_rawFactor"),

        metPt(reader_,"MET_pt"),
        metPhi(reader_,"MET_phi"),
        metPt_Puppi(reader_,"PuppiMET_pt"),
        metPhi_Puppi(reader_,"PuppiMET_phi"),
        metPt_Raw(reader_,"RawMET_pt"),
        metPhi_Raw(reader_,"RawMET_phi"),

        nPVertex(reader_,"PV_npvs"),
        nGoodPVertex(reader_,"PV_npvsGood"),
        nPU(reader_,isData_ ? "PV_npvs" : "Pileup_nPU"),
        nPUTrueInt(reader_,isData_ ? "MET_pt" : "Pileup_nTrueInt"),

        genWeight(reader_,isData_ ? "MET_pt" : "genWeight"),


        metFilter_primaryVertex(reader_,"Flag_goodVertices"),
        metFilter_beamHalo(reader_,"Flag_globalSuperTightHalo2016Filter"),
        metFilter_HBHENoise(reader_,"Flag_HBHENoiseFilter"),
        metFilter_HBHENoiseIso(reader_,"Flag_HBHENoiseIsoFilter"),
        metFilter_ECALTP(reader_,"Flag_EcalDeadCellTriggerPrimitiveFilter"),
        metFilter_BadPFMuon(reader_,"Flag_BadPFMuonFilter"),
        metFilter_BadChargedHadron(reader_,"Flag_BadChargedCandidateFilter"),
        metFilter_eeBadSCNoise(reader_,"Flag_eeBadScFilter"),


        nGenJet(reader_,isData_ ? "nMuon" : "nGenJet"),
        nGenJetEta(reader_,isData_ ? "Muon_eta" : "GenJet_eta"),
        genJetPhi(reader_,isData_ ? "Muon_phi" : "GenJet_phi"),
        genJetPt(reader_,isData_ ? "Muon_pt" : "GenJet_pt"),
        genJetMass(reader_,isData_ ? "Muon_mass" : "GenJet_mass"),
        genJetPartonFlavour(reader_,isData_ ? "Muon_charge" : "GenJet_partonFlavour"),
        genJetHadronFlavour(reader_,isData_ ? "Muon_mvaId" : "GenJet_hadronFlavour"),

        genMetPhi(reader_,isData_ ? "MET_phi" : "GenMET_phi"),
        genMetPt(reader_,isData_ ? "MET_pt" : "GenMET_pt"),

        nGenPart(reader_,isData_ ? "nMuon" : "nGenPart"),
        genPartEta(reader_,isData_ ? "Muon_eta" : "GenPart_eta"),
        genPartPhi(reader_,isData_ ? "Muon_phi" : "GenPart_phi"),
        genPartPt(reader_,isData_ ? "Muon_pt" : "GenPart_pt"),
        genPartMotherIndex(reader_,isData_ ? "PV_npvs" : "GenPart_genPartIdxMother"),
        genPartId(reader_,isData_ ? "PV_npvs" : "GenPart_pdgId"),
        genPartStatus(reader_,isData_ ? "PV_npvs" : "GenPart_pdgId"),
        genPartStatusFlags(reader_,isData_ ? "PV_npvs" : "GenPart_pdgId"),

        runNr(reader_,"run"),
        lumiNr(reader_,"luminosityBlock"),
        eventNr(reader_,"event"),



// 2016
        HLT_SingleEle(reader_,"HLT_Ele25_WPTight_Gsf"),
        HLT_SingleMu(reader_,"HLT_IsoMu20"),
        HLT_SingleMuIso(reader_,"HLT_IsoTkMu20"),
        HLT_DoubleMu(reader_,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"),
        HLT_DoubleMuDZ(reader_,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"),
        HLT_DoubleMuTK(reader_,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"),
        HLT_DoubleMuTkDZ(reader_,"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"),
        HLT_DoubleEle(reader_,"HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"),
        HLT_MuEleHigh(reader_,"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"),
        HLT_MuEleLow(reader_,"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL")
{
// cout<<"Reader constructor"<<endl;
// // cout<<reader_.GetCurrentEntry()<<endl;
// // cout<<reader_.GetEntries(true)<<endl;
// // cout<<reader.GetTree()->GetName()<<endl;
// cout<<"End Reader constructor"<<endl;

};
