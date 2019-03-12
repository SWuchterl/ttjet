#include <ttjet/nanoskimmer/interface/event.h>
#include <ttjet/nanoskimmer/interface/filters.h>
#include <ttjet/nanoskimmer/interface/particles.h>
#include <ttjet/nanoskimmer/interface/skimmer.h>

namespace {
        namespace {
                Jet jet;
                Electron electron;
                Muon muon;
                GenParticle genPart;
                Lepton lepton;
                Met met;

                std::vector<Jet> jets;
                std::vector<Electron> electrons;
                std::vector<Muon> muons;
                std::vector<GenParticle> genParts;
                std::vector<Lepton> leptons;
                std::vector<Met> mets;

                // Skimmer skimmer("d","d");
                // Skimmer skimmer("d","d");
                Event event;
                Filter filter;
        }
}
