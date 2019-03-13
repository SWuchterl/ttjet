#ifndef PILEUPWEIGHTER_H
#define PILEUPWEIGHTER_H

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
// #include <ttjet/nanoskimmer/interface/skimmer.h>
#include <ttjet/nanoskimmer/interface/myReader.h>
#include <ttjet/nanoskimmer/interface/event.h>


class PileupWeighter {
protected:
        TH1* dataHist= 0;
        TH1* dataHistNorm=0;
        TH1* mcHist=0;
        TH1* mcHistNorm=0;
        TH1* weights=0;

public:
        PileupWeighter();
        PileupWeighter(TTreeReader &reader,const int &year);
        MyReader *skimmer;
        float GetWeight(const float & nPU, const bool &isData);
};












#endif
