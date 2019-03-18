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
#include <TRandom.h>
#include <TMath.h>

#include <ttjet/nanoskimmer/interface/event.h>
#include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>
#include <ttjet/nanoskimmer/interface/particles.h>

// #include <ttjet/nanoskimmer/interface/skimmer.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/RoccoR.h>

using namespace std;

Event::Event(){
};
// Event::Event(MyReader &skim_,TriggerFilter &trigF_,MetFilter &metF_,RoccoR &rocco_,PileupWeighter &PUWeighter_, bool &Data){
Event::Event(bool &Data){
        // skim=skim_;
        // trigF=trigF_;
        // metF=metF_;
        // rocco=rocco_;
        // PUWeighter=PUWeighter_;
        isData=Data;
};


// void Event::SetAdresses(MyReader &skim, TTree* tree){
void Event::SetAdresses(MyReader &skim, vector<TTree*> trees){
        for(TTree* tree: trees) {
                tree->Branch("electrons", &electrons);
                tree->Branch("muons", &muons);
                tree->Branch("jets", &jets);
                tree->Branch("met", &met);
                tree->Branch("genWeight", &mc_weight);
                tree->Branch("puWeight", &pu_weight);
                tree->Branch("trigSingleEle", &trigSingleEle);
                tree->Branch("trigSingleMu", &trigSingleMu);
                tree->Branch("trigDoubleEle", &trigDoubleEle);
                tree->Branch("trigDoubleMu", &trigDoubleMu);
                tree->Branch("trigMuEle", &trigMuEle);

                tree->Branch("runNr", &runNr);
                tree->Branch("lumiNr", &lumiNr);
                tree->Branch("eventNr", &eventNr);

                tree->Branch("ht", &ht);
        }

};

void Event::Clear(){
        electrons.clear();
        muons.clear();
        jets.clear();

        pu_weight=1.;
        mc_weight=1.;

        ht=0.;

        trigSingleEle=false;
        trigSingleMu=false;
        trigDoubleEle=false;
        trigDoubleMu=false;
        trigMuEle=false;
};

// Event::Event(){
//   ree->Branch("electron", &validElectrons);
// };
void Event::SetMuons(MyReader &skim,RoccoR &rocco,TRandom &gRandom, Weighter &IDWeighter, Weighter &IDWeighterStat, Weighter &IDWeighterSyst, Weighter &ISOWeighter, Weighter &ISOWeighterStat, Weighter &ISOWeighterSyst){


        for(unsigned int i=0; i<*(skim.nMuons); i++) {
                Muon muon;

                //calculate rochester muon Pt corrections
                double SF=1.;
                if(isData) {
                        SF=rocco.kScaleDT(skim.muonCharge.At(i), skim.muonPt.At(i), skim.muonEta.At(i), skim.muonPhi.At(i), 0, 0);
                }else{
                        if(abs(skim.genPartId.At(skim.muonGenParticleIndex.At(i)))==13) {
                                SF=rocco.kSpreadMC(skim.muonCharge.At(i), (skim.muonPt).At(i), (skim.muonEta).At(i), (skim.muonPhi).At(i),skim.genPartPt.At(skim.muonGenParticleIndex.At(i)), 0, 0);
                        }else{
                                // to be corrected
                                SF=rocco.kSmearMC(skim.muonCharge.At(i), (skim.muonPt).At(i), (skim.muonEta).At(i), (skim.muonPhi).At(i), skim.muonNLayers.At(i), gRandom.Rndm(), 0, 0);
                        }
                }

                //use them here
                muon.L.SetPtEtaPhiM((skim.muonPt).At(i)*SF,(skim.muonEta).At(i),(skim.muonPhi).At(i),(skim.muonMass).At(i));
                //or not?
                // muon.L.SetPtEtaPhiM((skim.muonPt).At(i),(skim.muonEta).At(i),(skim.muonPhi).At(i),(skim.muonMass).At(i));
                muon.charge=skim.muonCharge.At(i);
                // muon.isLoose=false;
                // muon.isMedium=(skim.muonMediumId.At(i));
                muon.isTight=(skim.muonTightId.At(i));
                // muon.isMediumSF=1.;
                muon.isTightSF=isData ? 1. : IDWeighter.getWeight(skim.muonEta.At(i),skim.muonPt.At(i));
                // muon.isIsoLoose=(skim.muonIso.At(i)<0.25);
                muon.isIsoTight=(skim.muonIso.At(i)<0.15);
                // muon.isIsoLooseSF=1.;
                muon.isIsoTightSF=isData ? 1. : ISOWeighter.getWeight(skim.muonEta.At(i),skim.muonPt.At(i));
                muons.push_back(muon);

        }
};
void Event::SetElectrons(MyReader &skim,Weighter &recoWeighter,Weighter &recoWeighter20, Weighter &idWeighter){
        for(unsigned int i=0; i<*(skim.nElectrons); i++) {
                Electron electron;
                electron.L.SetPtEtaPhiM(skim.electronPt.At(i),skim.electronEta.At(i),skim.electronPhi.At(i),skim.electronMass.At(i));
                electron.charge=skim.electronCharge.At(i);
                // electron.isLoose=(skim.electronCutBasedId.At(i)>1);
                // electron.isMedium=(skim.electronCutBasedId.At(i)>2);
                electron.isTight=(skim.electronCutBasedId.At(i)>3);
                // electron.looseSF=1; //todo
                // electron.mediumSF=1;
                if(skim.electronPt.At(i)>20.) {
                        electron.tightSF=isData ? 1. : idWeighter.getWeight(skim.electronEta.At(i),skim.electronPt.At(i))*recoWeighter20.getWeight(skim.electronEta.At(i),skim.electronPt.At(i));
                }else{
                        electron.tightSF=isData ? 1. : idWeighter.getWeight(skim.electronEta.At(i),skim.electronPt.At(i))*recoWeighter.getWeight(skim.electronEta.At(i),skim.electronPt.At(i));
                }
                electron.isIsoTight=(skim.electronIso.At(i)<0.15);//???????????????
                electron.relIso=skim.electronIso.At(i);
                // electron.isLooseMVA=skim.electronMVALoose.At(i);
                // electron.isMediumMVA=skim.electronMVAMedium.At(i);
                // electron.isTightMVA=skim.electronMVATight.At(i);
                // electron.looseMVASF=1;
                // electron.mediumMVASF=1;
                // electron.tightMVASF=1;
                // electron.isLooseMVAIso=skim.electronMVALooseIso.At(i);
                // electron.isMediumMVAIso=skim.electronMVAMediumIso.At(i);
                // electron.isTightMVAIso=skim.electronMVATightIso.At(i);
                // electron.looseMVASFIso=1;
                // electron.mediumMVASFIso=1;
                // electron.tightMVASFIso=1;
                electron.passConversionVeto=skim.electronConvVeto.At(i);
                electrons.push_back(electron);
        }
};
//
void Event::SetJets(MyReader &skim){
        for(unsigned int i=0; i<*(skim.nJets); i++) {
                Jet jet;
                jet.L.SetPtEtaPhiM(skim.jetPt.At(i),skim.jetEta.At(i),skim.jetPhi.At(i),skim.jetMass.At(i));

                jet.hasElectronMatch=false;
                jet.hasMuonMatch=false;
                // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
                jet.isBLooseDeepCSV=(skim.jetBTagDiscriminator_DeepCSV.At(i)>.2217);
                jet.isBMediumDeepCSV=(skim.jetBTagDiscriminator_DeepCSV.At(i)>.6321);
                jet.isBTightDeepCSV=(skim.jetBTagDiscriminator_DeepCSV.At(i)>.6321);
                jet.bLooseSFDeepCSV=1;
                jet.bMediumSFDeepCSV=1;
                jet.bTightSFDeepCSV=1;

                jet.isBLooseDeepJet=(skim.jetBTagDiscriminator_DeepFlavour.At(i)>.0614);
                jet.isBMediumDeepJet=(skim.jetBTagDiscriminator_DeepFlavour.At(i)>.3093);
                jet.isBTightDeepJet=(skim.jetBTagDiscriminator_DeepFlavour.At(i)>.7221);
                jet.bLooseSFDeepJet=1;
                jet.bMediumSFDeepJet=1;
                jet.bTightSFDeepJet=1;
                jets.push_back(jet);
        }
};
//
void Event::SetValues(MyReader &skim, TTree* tree, TriggerFilter &trigF,const int &year, PileupWeighter &PUWeighter){

        met.L.SetPtEtaPhiM(*(skim.metPt),0.,*(skim.metPhi),0.);
        // particle met_JECu;

        if (!isData) {
                pu_weight=PUWeighter.GetWeight(*(skim.nPUTrueInt),isData); //todo

                mc_weight=*(skim.genWeight);
        }
        //
        ht=10.;
        //
        runNr=*(skim.runNr);
        lumiNr=*(skim.lumiNr);
        eventNr=*(skim.eventNr);


        trigSingleEle=trigF.getDecision(skim,year,E);
        trigSingleMu=trigF.getDecision(skim,year,M);
        trigDoubleEle=trigF.getDecision(skim,year,EE);
        trigDoubleMu=trigF.getDecision(skim,year,MM);
        trigMuEle=trigF.getDecision(skim,year,EM);
};


bool Event::SingleEleDecision(){
        return trigSingleEle;
};
bool Event::SingleMuDecision(){
        return trigSingleMu;

};
bool Event::DoubleEleDecision(){
        return trigDoubleEle;

};
bool Event::DoubleMuDecision(){
        return trigDoubleMu;

};
bool Event::EleMuDecision(){
        return trigMuEle;

};
