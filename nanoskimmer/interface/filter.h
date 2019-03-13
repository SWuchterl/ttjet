#ifndef FILTER_H
#define FILTER_H

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
#include <ttjet/nanoskimmer/interface/myReader.h>

enum TriggerCombination {E,M,EE,MM,EM,ME};

class Filter{
public:
Filter();
// Filter(MyReader &skim);
bool decision;
// MyReader skimmer;
};


#endif /* FILTER_H */
