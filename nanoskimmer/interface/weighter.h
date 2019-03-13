#ifndef WEIGHTER_H
#define WEIGHTER_H

#include <iostream>
#include <vector>
#include <string>

#include <thread>
#include <mutex>
#include <chrono>
#include <pthread.h>

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>

using namespace std;


class Weighter {
public:
        Weighter();
        Weighter(const string& filename, const string& histname);

        // deleting the histogram pointer leads to segmentation violations
        // ~Weighter() {
        // }

        float getWeight(float value);

        float getError(float value);

        float getWeight(float x, float y);
        float getError(float x, float y);

        void fillOverflow2d();

private:
        TH1* h = 0;
};
#endif
