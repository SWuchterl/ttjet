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
#include <ttjet/nanoskimmer/interface/filters.h>
#include <ttjet/nanoskimmer/interface/skimmer.h>

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
Event(Skimmer *skim);
// SetElectrons(TTreeReaderValue<int> &nEle, TTreeReaderArray &Pt,TTreeReaderArray &Phi,TTreeReaderArray &Eta,TTreeReaderArray &Mass);
Skimmer *skimmer;

void SetElectrons();
void SetMuons();
void SetJets();
void SetValues();

// attributes

};
#endif
