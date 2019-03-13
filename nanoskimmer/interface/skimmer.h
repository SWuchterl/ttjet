#ifndef SKIMMER_H
#define SKIMMER_H

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
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/filter.h>
#include <ttjet/nanoskimmer/interface/triggerfilter.h>
#include <ttjet/nanoskimmer/interface/metfilter.h>
#include <ttjet/nanoskimmer/interface/particles.h>
#include <ttjet/nanoskimmer/interface/weighter.h>
#include <ttjet/nanoskimmer/interface/RoccoR.h>


using namespace std;


class Skimmer {
public:
bool isData;
string inputFileName;
string dataSetName;
string outFileName;
//Measure execution time
std::chrono::steady_clock::time_point start;
std::chrono::steady_clock::time_point end;
// MyReader &myReader;



public:
// Skimmer();
// TFile* file = TFile::Open(inFile.c_str(), "READ");
// Skimmer(TFile* file, string Name);
// Skimmer(const string &inputFileName, const string &Name);
Skimmer(const string &inputFileName_, const string &dataSetName_,const string &outName);

bool Analyze();

// RoccoR rochesterCorrection("ttjet/nanoskimmer/data/rochester/RoccoR2016.txt");
// RoccoR *rochesterCorrection;
// TriggerFilter *TrigFilter;
// MetFilter *METFilter;

// TTree *tree;
std::vector<TTree*> trees;

void ProgressBar(const int &progress);
// TTree CreateOutputTree(const std::string &outFile);
void WriteOutput(const std::string &outFile);

};
#endif
