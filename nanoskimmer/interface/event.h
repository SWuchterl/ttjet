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

uint runNr;
uint lumiNr;
unsigned long long eventNr;



bool trigSingleEle;
bool trigSingleMu;
bool trigDoubleEle;
bool trigDoubleMu;
bool trigMuEle;

public:
Event();
// Event(MyReader &skim_,TriggerFilter &trigF_,MetFilter &metF_,RoccoR &rocco_,PileupWeighter &PUWeighter_, bool &Data);
Event(bool &Data);
// MyReader skim;
// TriggerFilter trigF;
// MetFilter metF;
// RoccoR rocco;
// PileupWeighter PUWeighter;

void Clear();
// void SetAdresses(MyReader &skim, TTree* tree);
void SetAdresses(MyReader &skim, vector<TTree*> trees);
void SetElectrons(MyReader &skim,Weighter &recoWeighter,Weighter &recoWeighter20, Weighter &idWeighter);
void SetMuons(MyReader &skim,RoccoR &rocco);
void SetJets(MyReader &skim);
void SetValues(MyReader &skim, TTree* tree, TriggerFilter &trigF,const int &year, PileupWeighter &PUWeighter);
bool isData;

bool SingleEleDecision();
bool SingleMuDecision();
bool DoubleEleDecision();
bool DoubleMuDecision();
bool EleMuDecision();


// attributes

};
#endif
