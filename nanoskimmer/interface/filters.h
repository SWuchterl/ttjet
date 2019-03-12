#ifndef FILTERS_H
#define FILTERS_H

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

#include <ttjet/nanoskimmer/interface/particles.h>
#include <ttjet/nanoskimmer/interface/event.h>
#include <ttjet/nanoskimmer/interface/skimmer.h>

enum TriggerCombination {E,M,EE,MM,EM,ME};

class Filter {
protected:
bool decision;
Skimmer *skimmer;
public:
Filter();
Filter(Skimmer *skim);
};

class MetFilter : public Filter {
public:
MetFilter(const int &year);
bool getDecision();
};


class TriggerFilter : public Filter {
private:
bool decisionE=false;
bool decisionM=false;
bool decisionEE=false;
bool decisionMM=false;
bool decisionEM=false;
public:
TriggerFilter(const int &year);
bool getDecision(const TriggerCombination &combination);
};
#endif /* FILTERS_H */
