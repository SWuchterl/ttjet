#ifndef MYREADER_H
#define MYREADER_H
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
// #include <ttjet/nanoskimmer/interface/triggerfilter.h>
// #include <ttjet/nanoskimmer/interface/metfilter.h>
// #include <ttjet/nanoskimmer/interface/particles.h>
// #include <ttjet/nanoskimmer/interface/weighter.h>
// #include <ttjet/nanoskimmer/interface/RoccoR.h>

using namespace std;


class MyReader {
public:
// TTree *eventTree;
// TFile *inputFile;
// TTreeReader reader;

TTreeReaderValue<uint> nMuons;
TTreeReaderArray<float> muonPt;
TTreeReaderArray<float> muonEta;
TTreeReaderArray<float> muonPhi;
TTreeReaderArray<float> muonMass;
TTreeReaderArray<bool> muonMediumId;
TTreeReaderArray<float> muonIso;
TTreeReaderArray<float> muonSIP3D;
TTreeReaderArray<unsigned char> muonMVAId;
TTreeReaderArray<bool> muonTightId;
TTreeReaderArray<float> muonDz;
TTreeReaderArray<float> muonDxy;
TTreeReaderArray<unsigned char> muonGenPartFlav;
TTreeReaderArray<int> muonGenParticleIndex;
TTreeReaderArray<int> muonCharge;

TTreeReaderValue<uint> nElectrons;
TTreeReaderArray<float> electronPt;
TTreeReaderArray<float> electronEta;
TTreeReaderArray<float> electronPhi;
TTreeReaderArray<float> electronMass;
TTreeReaderArray<int> electronCutBasedId;
TTreeReaderArray<float> electronDz;
TTreeReaderArray<float> electronDxy;
TTreeReaderArray<float> electronSIP3D;
TTreeReaderArray<unsigned char> electronGenPartFlav;
TTreeReaderArray<int> electronGenParticleIndex;
TTreeReaderArray<bool> electronMVALoose;
TTreeReaderArray<bool> electronMVAMedium;
TTreeReaderArray<bool> electronMVATight;
TTreeReaderArray<bool> electronMVALooseIso;
TTreeReaderArray<bool> electronMVAMediumIso;
TTreeReaderArray<bool> electronMVATightIso;
TTreeReaderArray<int> electronCharge;
TTreeReaderArray<bool> electronConvVeto;
TTreeReaderArray<float> electronIso;


TTreeReaderValue<uint> nJets;
TTreeReaderArray<float> jetPt;
TTreeReaderArray<float> jetEta;
TTreeReaderArray<float> jetPhi;
TTreeReaderArray<float> jetMass;
TTreeReaderArray<int> genJetIndex;
TTreeReaderArray<float> jetFlavour;
TTreeReaderArray<float> jetBTagDiscriminator_DeepCSV;
TTreeReaderArray<float> jetBTagDiscriminator_DeepFlavour;
TTreeReaderArray<float> jetRawFactor;

TTreeReaderValue<float> metPt;
TTreeReaderValue<float> metPhi;
TTreeReaderValue<float> metPt_Puppi;
TTreeReaderValue<float> metPhi_Puppi;
TTreeReaderValue<float> metPt_Raw;
TTreeReaderValue<float> metPhi_Raw;

TTreeReaderValue<int> nPVertex;
TTreeReaderValue<int> nGoodPVertex;
TTreeReaderValue<int> nPU;
TTreeReaderValue<float> nPUTrueInt;

TTreeReaderValue<float> genWeight;


TTreeReaderValue<bool> metFilter_primaryVertex;
TTreeReaderValue<bool> metFilter_beamHalo;
TTreeReaderValue<bool> metFilter_HBHENoise;
TTreeReaderValue<bool> metFilter_HBHENoiseIso;
TTreeReaderValue<bool> metFilter_ECALTP;
TTreeReaderValue<bool> metFilter_BadPFMuon;
TTreeReaderValue<bool> metFilter_BadChargedHadron;
TTreeReaderValue<bool> metFilter_eeBadSCNoise;


TTreeReaderValue<uint> nGenJet;
TTreeReaderArray<float> nGenJetEta;
TTreeReaderValue<float> genJetPhi;
TTreeReaderValue<float> genJetPt;
TTreeReaderValue<float> genJetMass;
TTreeReaderValue<int> genJetPartonFlavour;
TTreeReaderValue<unsigned char> genJetHadronFlavour;

TTreeReaderValue<float> genMetPhi;
TTreeReaderValue<float> genMetPt;

TTreeReaderValue<uint> nGenPart;
TTreeReaderArray<float> genPartEta;
TTreeReaderArray<float> genPartPhi;
TTreeReaderArray<float> genPartPt;
TTreeReaderArray<int> genPartMotherIndex;
TTreeReaderArray<int> genPartId;
TTreeReaderArray<int> genPartStatus;
TTreeReaderArray<int> genPartStatusFlags;

TTreeReaderValue<uint> runNr;
TTreeReaderValue<uint> lumiNr;
TTreeReaderValue<unsigned long long> eventNr;



// 2016
TTreeReaderValue<bool> HLT_SingleEle;
TTreeReaderValue<bool> HLT_SingleMu;
TTreeReaderValue<bool> HLT_SingleMuIso;
TTreeReaderValue<bool> HLT_DoubleMu;
TTreeReaderValue<bool> HLT_DoubleMuDZ;
TTreeReaderValue<bool> HLT_DoubleMuTK;
TTreeReaderValue<bool> HLT_DoubleMuTkDZ;
TTreeReaderValue<bool> HLT_DoubleEle;
TTreeReaderValue<bool> HLT_MuEleHigh;
TTreeReaderValue<bool> HLT_MuEleLow;
// 2017
// TTreeReaderValue<bool> HLT_(reader,"HLT_");



public:

// MyReader(const string &inputFileName, const string &Name);
MyReader(TTreeReader &reader_);


};


#endif
