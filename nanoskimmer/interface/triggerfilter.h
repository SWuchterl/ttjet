#ifndef TRIGGERFILTER_H
#define TRIGGERFILTER_H

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
#include <TMath.h>

// #include <ttjet/nanoskimmer/interface/particles.h>
// #include <ttjet/nanoskimmer/interface/event.h>
// #include <ttjet/nanoskimmer/interface/skimmer.h>
// #include <ttjet/nanoskimmer/interface/myReader.h>
// #include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>

class TriggerFilter: public Filter{
// class TriggerFilter {
private:
        bool decisionE=false;
        bool decisionM=false;
        bool decisionEE=false;
        bool decisionMM=false;
        bool decisionEM=false;
public:
        TriggerFilter();
        TriggerFilter(MyReader &skim,const int &year);
        bool getDecision(const TriggerCombination &combination);
};

#endif
