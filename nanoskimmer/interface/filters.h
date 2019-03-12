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

class Filter {
public:
Filter();
};

class MetFilter : public Filter {

bool getDecision(Event &event){
        return false;
}
};


class TriggerFilter : public Filter {
bool getDecision(Event &event){
        return false;
}
};
#endif /* FILTERS_H */
