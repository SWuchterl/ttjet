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
#include <ttjet/nanoskimmer/interface/pileupWeighter.h>


PileupWeighter::PileupWeighter(){
};

PileupWeighter::PileupWeighter(TTreeReader &reader,const int &year){
        // skimmer=skim;
        Double_t norm = 1;
        TH1F* mcHist = new TH1F("mcHist", "mcHist", 100, 0, 100);
        reader.GetTree()->Draw("Pileup_nTrueInt>>mcHist");
        Double_t scaleMC = norm/(mcHist->Integral());
        mcHistNorm=(TH1*) mcHist->Clone();
        mcHistNorm->Scale(scaleMC);


        if(year==2016) {
                TFile f(("ttjet/pileup/dataPU2016.root"));
                dataHist = (TH1*) f.Get(("pileup"));
                if (dataHist) {
                        dataHist->SetDirectory(0);
                } else {
                        cerr << "Error in <PileupWeighter::PileupWeighter>:  Could not find histogram "
                             << "pileup" << " in file " << "ttjet/pileup/dataPU2016.root" << endl;
                }
                f.Close();
                Double_t scale = norm/(dataHist->Integral());
                dataHistNorm=(TH1*) dataHist->Clone();
                dataHistNorm->Scale(scale);
                weights = new TH1F("weights", "weights", 100, 0, 100);
                weights->Divide(dataHistNorm, mcHistNorm);

        }else{
                if(year==2017) {
                        TFile f(("ttjet/pileup/dataPU2017.root"));
                        dataHist = (TH1*) f.Get(("pileup"));
                        if (dataHist) {
                                dataHist->SetDirectory(0);
                        } else {
                                cerr << "Error in <PileupWeighter::PileupWeighter>:  Could not find histogram "
                                     << "pileup" << " in file " << "ttjet/pileup/dataPU2016.root" << endl;
                        }
                        f.Close();
                        Double_t scale = norm/(dataHist->Integral());
                        dataHistNorm=(TH1*) dataHist->Clone();
                        dataHistNorm->Scale(scale);
                        weights = new TH1F("weights", "weights", 100, 0, 100);
                        weights->Divide(dataHistNorm, mcHistNorm);
                }else{
                        cerr << "Error in <PileupWeighter::PileupWeighter>:  No valid year specified" << endl;
                }
        }



};

float PileupWeighter::GetWeight(const float & nPU, const bool &isData){
        float weight=1.;
        if(isData) {
                return 1.;
        }else{
                return 1;
        }
        return weight;
};
