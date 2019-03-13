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
MyReader::MyReader(TTreeReader &reader_) :
        // inputFile(new TFile(inputFileName.c_str())),
        // reader("Events",inputFile),
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
        muonGenPartFlav(reader_,"Muon_genPartFlav"),
        muonGenParticleIndex(reader_,"Muon_genPartIdx"),
        muonCharge(reader_,"Muon_charge"),

        nElectrons(reader_,"nElectron"),
        electronPt(reader_,"Electron_pt"),
        electronEta(reader_,"Electron_eta"),
        electronPhi(reader_,"Electron_phi"),
        electronMass(reader_,"Electron_mass"),
        electronCutBasedId(reader_,"Electron_cutBased"),
        electronDz(reader_,"Electron_dz"),
        electronDxy(reader_,"Electron_dxy"),
        electronSIP3D(reader_,"Electron_sip3d"),
        electronGenPartFlav(reader_,"Electron_genPartFlav"),
        electronGenParticleIndex(reader_,"Electron_genPartIdx"),
        electronMVALoose(reader_,"Electron_mvaFall17V2noIso_WPL"),
        electronMVAMedium(reader_,"Electron_mvaFall17V2noIso_WP90"),
        electronMVATight(reader_,"Electron_mvaFall17V2noIso_WP80"),
        electronMVALooseIso(reader_,"Electron_mvaFall17V2Iso_WPL"),
        electronMVAMediumIso(reader_,"Electron_mvaFall17V2Iso_WP90"),
        electronMVATightIso(reader_,"Electron_mvaFall17V2Iso_WP80"),
        electronCharge(reader_,"Electron_charge"),
        electronConvVeto(reader_,"Electron_convVeto"),


        nJets(reader_,"nJet"),
        jetPt(reader_,"Jet_pt"),
        jetEta(reader_,"Jet_eta"),
        jetPhi(reader_,"Jet_phi"),
        jetMass(reader_,"Jet_mass"),
        genJetIndex(reader_,"Jet_genJetIdx"),
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
        nPU(reader_,"Pileup_nPU"),
        nPUTrueInt(reader_,"Pileup_nTrueInt"),

        genWeight(reader_,"genWeight"),


        metFilter_primaryVertex(reader_,"Flag_goodVertices"),
        metFilter_beamHalo(reader_,"Flag_globalSuperTightHalo2016Filter"),
        metFilter_HBHENoise(reader_,"Flag_HBHENoiseFilter"),
        metFilter_HBHENoiseIso(reader_,"Flag_HBHENoiseIsoFilter"),
        metFilter_ECALTP(reader_,"Flag_EcalDeadCellTriggerPrimitiveFilter"),
        metFilter_BadPFMuon(reader_,"Flag_BadPFMuonFilter"),
        metFilter_BadChargedHadron(reader_,"Flag_BadChargedCandidateFilter"),
        metFilter_eeBadSCNoise(reader_,"Flag_eeBadScFilter"),


        nGenJet(reader_,"nGenJet"),
        nGenJetEta(reader_,"GenJet_eta"),
        genJetPhi(reader_,"GenJet_phi"),
        genJetPt(reader_,"GenJet_pt"),
        genJetMass(reader_,"GenJet_mass"),
        genJetPartonFlavour(reader_,"GenJet_partonFlavour"),
        genJetHadronFlavour(reader_,"GenJet_hadronFlavour"),

        genMetPhi(reader_,"GenMET_phi"),
        genMetPt(reader_,"GenMET_pt"),

        nGenPart(reader_,"nGenPart"),
        genPartEta(reader_,"GenPart_eta"),
        genPartPhi(reader_,"GenPart_phi"),
        genPartPt(reader_,"GenPart_pt"),
        genPartMotherIndex(reader_,"GenPart_genPartIdxMother"),
        genPartId(reader_,"GenPart_pdgId"),
        genPartStatus(reader_,"GenPart_pdgId"),
        genPartStatusFlags(reader_,"GenPart_pdgId"),



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
