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
// #include <ttjet/nanoskimmer/interface/particles.h>
// #include <ttjet/nanoskimmer/interface/skimmer.h>
// #include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>

using namespace std;

MetFilter::MetFilter(){
        Filter();
};

// MetFilter::MetFilter(MyReader &skim,const int &year){
//         Filter();
//         // skimmer=skim;
//         if(year==2016) {
//                 decision=(*(skim.metFilter_ECALTP) &&
//                 *(skim.metFilter_beamHalo) &&
//                 *(skim.metFilter_HBHENoise)
//                 && *(skim.metFilter_HBHENoiseIso)
//                 && *(skim.metFilter_eeBadSCNoise)
//                 && *(skim.metFilter_primaryVertex)
//                 && *(skim.metFilter_BadChargedHadron));
//         }else{
//                 decision=false;
//         }
// };

bool MetFilter::getDecision(MyReader &skim,const int &year){
        if(year==2016) {
                decision=(*(skim.metFilter_ECALTP) &&
                          *(skim.metFilter_beamHalo) &&
                          *(skim.metFilter_HBHENoise)
                          && *(skim.metFilter_HBHENoiseIso)
                          && *(skim.metFilter_eeBadSCNoise)
                          && *(skim.metFilter_primaryVertex)
                          && *(skim.metFilter_BadChargedHadron));
        }else{
                decision=false;
        }
        return decision;
};
