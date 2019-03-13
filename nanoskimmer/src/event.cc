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
#include <ttjet/nanoskimmer/interface/RoccoR.h>

using namespace std;

Event::Event(){
};
Event::Event(Skimmer *skim){
        skimmer=skim;
};
// Event::Event(){
//   ree->Branch("electron", &validElectrons);
// };
void Event::SetMuons(){

        //scale factors for momentum of each muon:
        // double dtSF = rc.kScaleDT(Q, pt, eta, phi, s=0, m=0); //data
        // double mcSF = rc.kSpreadMC(Q, pt, eta, phi, genPt, s=0, m=0); //(recommended), MC scale and resolution correction when matched gen muon is available
        // double mcSF = rc.kSmearMC(Q, pt, eta, phi, nl, u, s=0, m=0); //MC scale and extra smearing when matched gen muon is not available
        // todo: get genMatched muon


        for(unsigned int i=0; i<*(skimmer->nMuons); i++) {
                Muon muon;

                //calculate rochester muon Pt corrections
                double SF=1.;
                if(skimmer->isData) {
                        SF=skimmer->rochesterCorrection->kScaleDT(skimmer->muonCharge.At(i), skimmer->muonPt.At(i), skimmer->muonEta.At(i), skimmer->muonPhi.At(i), 0, 0);
                }else{
                        if(abs(skimmer->genPartId.At(skimmer->muonGenParticleIndex.At(i)))==13) {
                                SF=skimmer->rochesterCorrection->kSpreadMC(skimmer->muonCharge.At(i), (skimmer->muonPt).At(i), (skimmer->muonEta).At(i), (skimmer->muonPhi).At(i),skimmer->genPartPt.At(skimmer->muonGenParticleIndex.At(i)), 0, 0);
                        }else{
                                SF=skimmer->rochesterCorrection->kSmearMC(skimmer->muonCharge.At(i), (skimmer->muonPt).At(i), (skimmer->muonEta).At(i), (skimmer->muonPhi).At(i), 3, 0.5, 0, 0);
                        }
                }

                //use them here
                muon.L.SetPtEtaPhiM((skimmer->muonPt).At(i)*SF,(skimmer->muonEta).At(i),(skimmer->muonPhi).At(i),(skimmer->muonMass).At(i));
                //or not?
                // muon.L.SetPtEtaPhiM((skimmer->muonPt).At(i),(skimmer->muonEta).At(i),(skimmer->muonPhi).At(i),(skimmer->muonMass).At(i));
                muon.charge=skimmer->muonCharge.At(i);
                muon.isLoose=false;
                muon.isMedium=(skimmer->muonMediumId.At(i));
                muon.isTight=(skimmer->muonTightId.At(i));
                muon.isIsoLoose=(skimmer->muonIso.At(i)<0.25);
                muon.isIsoTight=(skimmer->muonIso.At(i)<0.15);
                muons.push_back(muon);

        }
};
void Event::SetElectrons(){
        for(unsigned int i=0; i<*(skimmer->nElectrons); i++) {
                Electron electron;
                electron.L.SetPtEtaPhiM(skimmer->electronPt.At(i),skimmer->electronEta.At(i),skimmer->electronPhi.At(i),skimmer->electronMass.At(i));
                electron.charge=skimmer->electronCharge.At(i);
                electron.isLoose=(skimmer->electronCutBasedId.At(i)>1);
                electron.isMedium=(skimmer->electronCutBasedId.At(i)>2);
                electron.isTight=(skimmer->electronCutBasedId.At(i)>3);
                electron.looseSF=1; //todo
                electron.mediumSF=1;
                electron.tightSF=1;
                electron.isLooseMVA=skimmer->electronMVALoose.At(i);
                electron.isMediumMVA=skimmer->electronMVAMedium.At(i);
                electron.isTightMVA=skimmer->electronMVATight.At(i);
                electron.looseMVASF=1;
                electron.mediumMVASF=1;
                electron.tightMVASF=1;
                electron.isLooseMVAIso=skimmer->electronMVALooseIso.At(i);
                electron.isMediumMVAIso=skimmer->electronMVAMediumIso.At(i);
                electron.isTightMVAIso=skimmer->electronMVATightIso.At(i);
                electron.looseMVASFIso=1;
                electron.mediumMVASFIso=1;
                electron.tightMVASFIso=1;
                electron.passConversionVeto=skimmer->electronConvVeto.At(i);
                electrons.push_back(electron);
        }
};
//
void Event::SetJets(){
        for(unsigned int i=0; i<*(skimmer->nJets); i++) {
                Jet jet;
                jet.L.SetPtEtaPhiM(skimmer->jetPt.At(i),skimmer->jetEta.At(i),skimmer->jetPhi.At(i),skimmer->jetMass.At(i));

                jet.hasElectronMatch=false;
                jet.hasMuonMatch=false;
                // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
                jet.isBLooseDeepCSV=(skimmer->jetBTagDiscriminator_DeepCSV.At(i)>.2217);
                jet.isBMediumDeepCSV=(skimmer->jetBTagDiscriminator_DeepCSV.At(i)>.6321);
                jet.isBTightDeepCSV=(skimmer->jetBTagDiscriminator_DeepCSV.At(i)>.6321);
                jet.bLooseSFDeepCSV=1;
                jet.bMediumSFDeepCSV=1;
                jet.bTightSFDeepCSV=1;

                jet.isBLooseDeepJet=(skimmer->jetBTagDiscriminator_DeepFlavour.At(i)>.0614);
                jet.isBMediumDeepJet=(skimmer->jetBTagDiscriminator_DeepFlavour.At(i)>.3093);
                jet.isBTightDeepJet=(skimmer->jetBTagDiscriminator_DeepFlavour.At(i)>.7221);
                jet.bLooseSFDeepJet=1;
                jet.bMediumSFDeepJet=1;
                jet.bTightSFDeepJet=1;
                jets.push_back(jet);
        }
};
//
void Event::SetValues(){
        met.L.SetPtEtaPhiM(*(skimmer->metPt),0.,*(skimmer->metPhi),0.);
        // particle met_JECu;


        pu_weight=1.; //todo
        mc_weight=*(skimmer->genWeight);
        //
        ht=10.;
        //
        TriggerFilter TrigFilter(skimmer,2016);
        MetFilter MetFilter(skimmer,2016);


        trigSingleEle=TrigFilter.getDecision(E);
        trigSingleMu=TrigFilter.getDecision(M);
        trigDoubleEle=TrigFilter.getDecision(EE);
        trigDoubleMu=TrigFilter.getDecision(MM);
        trigMuEle=TrigFilter.getDecision(EM);
};
