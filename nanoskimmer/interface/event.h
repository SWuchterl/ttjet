#ifndef EVENT_H
#define EVENT_H

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

#include <ttjet/nanoskimmer/interface/particles.h>
#include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>
// #include <ttjet/nanoskimmer/interface/skimmer.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/weighter.h>
#include <ttjet/nanoskimmer/interface/pileupWeighter.h>

#include <ttjet/nanoskimmer/interface/RoccoR.h>


class Event {
private:
std::vector<Electron> electrons;
std::vector<Muon> muons;
std::vector<Jet> jets;
Particle met;
Particle met_JECu;
Particle met_JECd;
Particle met_JESu;
Particle met_JESd;
Particle met_Raw;

float pu_weight;
float mc_weight;

float ht;



bool trigSingleEle;
bool trigSingleMu;
bool trigDoubleEle;
bool trigDoubleMu;
bool trigMuEle;

public:
Event();
Event(MyReader &skim_,TriggerFilter &trigF_,MetFilter &metF_,RoccoR &rocco_, bool &Data);
// MyReader skim;
TriggerFilter trigF;
MetFilter metF;
RoccoR rocco;

void SetElectrons(MyReader &skim_);
void SetMuons(MyReader &skim_);
void SetJets(MyReader &skim_);
void SetValues(MyReader &skim_);
bool isData;

// attributes

};
#endif
