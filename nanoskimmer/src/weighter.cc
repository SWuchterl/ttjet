

#include <ttjet/nanoskimmer/interface/weighter.h>



Weighter::Weighter() {
};
Weighter::Weighter(const string& filename, const string& histname) {
        TFile f(filename.c_str());
        h = (TH1*) f.Get(histname.c_str());
        if (h) {
                h->SetDirectory(0);
        } else {
                cerr << "Error in <Weighter::Weighter>:  Could not find histogram "
                     << histname << " in file " << filename << endl;
        }
        f.Close();
};

// deleting the histogram pointer leads to segmentation violations
// ~Weighter() {
// }

float Weighter::getWeight(float value) {
        return h ? h->GetBinContent( h->FindFixBin(value) ) : 1.;
};

float Weighter::getError(float value) {
        return h ? h->GetBinError( h->FindFixBin(value) ) : 1.;
};

float Weighter::getWeight(float x, float y) {
        return h ? h->GetBinContent( h->FindFixBin(x,y) ) : 1.;
};
float Weighter::getError(float x, float y) {
        return h ? h->GetBinError( h->FindFixBin(x,y) ) : 1.;
};

void Weighter::fillOverflow2d() {
        int nX = h->GetNbinsX();
        int nY = h->GetNbinsY();
        for (int x=0; x<nX+2; x++) {
                if (!h->GetBinContent(x, 0)) h->SetBinContent(x, 0, h->GetBinContent(x, 1));
                if (!h->GetBinContent(x, nY+1)) h->SetBinContent(x, nY+1, h->GetBinContent(x, nY));
        }
        for (int y=0; y<nY+2; y++) {
                if (!h->GetBinContent(0, y)) h->SetBinContent(0, y, h->GetBinContent(1, y));
                if (!h->GetBinContent(nX+1, y)) h->SetBinContent(nX+1, y, h->GetBinContent(nX, y));
        }
};
