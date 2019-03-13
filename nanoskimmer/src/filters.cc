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

Filter::Filter(){
};

Filter::Filter(Skimmer *skim){
        skimmer=skim;
};

MetFilter::MetFilter(Skimmer *skim,const int &year){
        skimmer=skim;
        if(year==2016) {
                decision=(*(skimmer->metFilter_ECALTP) && *(skimmer->metFilter_beamHalo) && *(skimmer->metFilter_HBHENoise) && *(skimmer->metFilter_HBHENoiseIso) && *(skimmer->metFilter_eeBadSCNoise) && *(skimmer->metFilter_primaryVertex) && *(skimmer->metFilter_BadChargedHadron));
        }else{
                decision=false;
        }
};

bool MetFilter::getDecision(){
        return decision;
};


TriggerFilter::TriggerFilter(Skimmer *skim,const int &year){
        skimmer=skim;
        if(year==2016) {
                decisionE=(*(skimmer->HLT_SingleEle));
                decisionM=(*(skimmer->HLT_SingleMu) || *(skimmer->HLT_SingleMuIso));
                decisionEE=(*(skimmer->HLT_DoubleEle));
                decisionMM=(*(skimmer->HLT_DoubleMu)||*(skimmer->HLT_DoubleMuDZ)||*(skimmer->HLT_DoubleMuTK)||*(skimmer->HLT_DoubleMuTkDZ));
                decisionEM=(*(skimmer->HLT_MuEleLow)||*(skimmer->HLT_MuEleHigh));
        }else{
                decisionE=false;
                decisionM=false;
                decisionEE=false;
                decisionMM=false;
                decisionEM=false;
        }
};

bool TriggerFilter::getDecision(const TriggerCombination &combination){
        if (combination==E) {
                return decisionE;
        }
        if (combination==M) {
                return decisionM;
        }
        if (combination==EE) {
                return decisionEE;
        }
        if (combination==MM) {
                return decisionMM;
        }
        if (combination==EM) {
                return decisionEM;
        }
        if (combination==ME) {
                return decisionEM;
        }
        return false;

};
