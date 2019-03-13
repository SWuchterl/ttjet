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
#include <ttjet/nanoskimmer/interface/particles.h>
// #include <ttjet/nanoskimmer/interface/skimmer.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>

using namespace std;

TriggerFilter::TriggerFilter(){
        Filter();
};
// TriggerFilter::TriggerFilter(MyReader &skim,const int &year){
//         Filter();
//         // skimmer=skim;
//         if(year==2016) {
//                 decisionE=(*(skim.HLT_SingleEle));
//                 decisionM=(*(skim.HLT_SingleMu) || *(skim.HLT_SingleMuIso));
//                 decisionEE=(*(skim.HLT_DoubleEle));
//                 decisionMM=(*(skim.HLT_DoubleMu)||*(skim.HLT_DoubleMuDZ)||*(skim.HLT_DoubleMuTK)||*(skim.HLT_DoubleMuTkDZ));
//                 decisionEM=(*(skim.HLT_MuEleLow)||*(skim.HLT_MuEleHigh));
//         }else{
//                 decisionE=false;
//                 decisionM=false;
//                 decisionEE=false;
//                 decisionMM=false;
//                 decisionEM=false;
//         }
// };

bool TriggerFilter::getDecision(MyReader &skim,const int &year,const TriggerCombination &combination){

        if(year==2016) {
                decisionE=(*(skim.HLT_SingleEle));
                decisionM=(*(skim.HLT_SingleMu) || *(skim.HLT_SingleMuIso));
                decisionEE=(*(skim.HLT_DoubleEle));
                decisionMM=(*(skim.HLT_DoubleMu)||*(skim.HLT_DoubleMuDZ)||*(skim.HLT_DoubleMuTK)||*(skim.HLT_DoubleMuTkDZ));
                decisionEM=(*(skim.HLT_MuEleLow)||*(skim.HLT_MuEleHigh));
        }else{
                decisionE=false;
                decisionM=false;
                decisionEE=false;
                decisionMM=false;
                decisionEM=false;
        }


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
