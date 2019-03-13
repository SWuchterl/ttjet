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
#include <ttjet/nanoskimmer/interface/triggerfilter.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>
#include <ttjet/nanoskimmer/interface/particles.h>

// #include <ttjet/nanoskimmer/interface/skimmer.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/RoccoR.h>

using namespace std;

Event::Event(){
};
Event::Event(MyReader &skim_,TriggerFilter &trigF_,MetFilter &metF_,RoccoR &rocco_, bool &Data){
        // skim=skim_;
        trigF=trigF_;
        metF=metF_;
        rocco=rocco_;
        isData=Data;
};
// Event::Event(){
//   ree->Branch("electron", &validElectrons);
// };
void Event::SetMuons(MyReader &skim){


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
                                SF=rocco.kSmearMC(skim.muonCharge.At(i), (skim.muonPt).At(i), (skim.muonEta).At(i), (skim.muonPhi).At(i), 3, 0.5, 0, 0);
                        }
                }

                //use them here
                muon.L.SetPtEtaPhiM((skim.muonPt).At(i)*SF,(skim.muonEta).At(i),(skim.muonPhi).At(i),(skim.muonMass).At(i));
                //or not?
                // muon.L.SetPtEtaPhiM((skim.muonPt).At(i),(skim.muonEta).At(i),(skim.muonPhi).At(i),(skim.muonMass).At(i));
                muon.charge=skim.muonCharge.At(i);
                muon.isLoose=false;
                muon.isMedium=(skim.muonMediumId.At(i));
                muon.isTight=(skim.muonTightId.At(i));
                muon.isIsoLoose=(skim.muonIso.At(i)<0.25);
                muon.isIsoTight=(skim.muonIso.At(i)<0.15);
                muons.push_back(muon);

        }
};
void Event::SetElectrons(MyReader &skim){
        for(unsigned int i=0; i<*(skim.nElectrons); i++) {
                Electron electron;
                electron.L.SetPtEtaPhiM(skim.electronPt.At(i),skim.electronEta.At(i),skim.electronPhi.At(i),skim.electronMass.At(i));
                electron.charge=skim.electronCharge.At(i);
                electron.isLoose=(skim.electronCutBasedId.At(i)>1);
                electron.isMedium=(skim.electronCutBasedId.At(i)>2);
                electron.isTight=(skim.electronCutBasedId.At(i)>3);
                electron.looseSF=1; //todo
                electron.mediumSF=1;
                electron.tightSF=1;
                electron.isLooseMVA=skim.electronMVALoose.At(i);
                electron.isMediumMVA=skim.electronMVAMedium.At(i);
                electron.isTightMVA=skim.electronMVATight.At(i);
                electron.looseMVASF=1;
                electron.mediumMVASF=1;
                electron.tightMVASF=1;
                electron.isLooseMVAIso=skim.electronMVALooseIso.At(i);
                electron.isMediumMVAIso=skim.electronMVAMediumIso.At(i);
                electron.isTightMVAIso=skim.electronMVATightIso.At(i);
                electron.looseMVASFIso=1;
                electron.mediumMVASFIso=1;
                electron.tightMVASFIso=1;
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
void Event::SetValues(MyReader &skim){
        met.L.SetPtEtaPhiM(*(skim.metPt),0.,*(skim.metPhi),0.);
        // particle met_JECu;


        pu_weight=1.; //todo
        mc_weight=*(skim.genWeight);
        //
        ht=10.;
        //



        trigSingleEle=trigF.getDecision(E);
        trigSingleMu=trigF.getDecision(M);
        trigDoubleEle=trigF.getDecision(EE);
        trigDoubleMu=trigF.getDecision(MM);
        trigMuEle=trigF.getDecision(EM);
};
