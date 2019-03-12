
#ifndef PARTICLES_H
#define PARTICLES_H

#include <TLorentzVector.h>
// #include <TVector3.h>

struct Particle
{
        TLorentzVector L;
};

struct GenParticle : public Particle
{
        Int_t pdgId;
        Int_t statusId;
        Int_t motherId;
        Bool_t isPrompt;
        Bool_t fromHardProcess;
        Bool_t isHardProcess;
        Bool_t isPromptFinalState;
        // std::vector<GenParticle> daughters;

};

struct Lepton : public Particle
{
        Char_t charge;
        Float_t isolation;
        // float passImpactParameter;
};

struct Muon : public Lepton
{
        Bool_t isLoose;
        Bool_t isMedium;
        Bool_t isTight;

        Bool_t isIsoLoose;
        Bool_t isIsoTight;

        // Float_t
};
struct Electron : public Lepton
{
        Bool_t isLoose;
        Bool_t isMedium;
        Bool_t isTight;
        Float_t looseSF;
        Float_t mediumSF;
        Float_t tightSF;

        Bool_t isLooseMVA;
        Bool_t isMediumMVA;
        Bool_t isTightMVA;
        Float_t looseMVASF;
        Float_t mediumMVASF;
        Float_t tightMVASF;

        Bool_t isLooseMVAIso;
        Bool_t isMediumMVAIso;
        Bool_t isTightMVAIso;
        Float_t looseMVASFIso;
        Float_t mediumMVASFIso;
        Float_t tightMVASFIso;

        Bool_t passConversionVeto;
};

struct Jet : public Particle
{
        Bool_t isLoose;
        Bool_t isMedium;
        Bool_t isTight;
        Bool_t hasElectronMatch;
        Bool_t hasMuonMatch;

        Bool_t isBLooseDeepCSV;
        Bool_t isBMediumDeepCSV;
        Bool_t isBTightDeepCSV;
        Float_t bLooseSFDeepCSV;
        Float_t bMediumSFDeepCSV;
        Float_t bTightSFDeepCSV;

        Bool_t isBLooseDeepJet;
        Bool_t isBMediumDeepJet;
        Bool_t isBTightDeepJet;
        Float_t bLooseSFDeepJet;
        Float_t bMediumSFDeepJet;
        Float_t bTightSFDeepJet;
};

struct Met : public Particle
{
        Float_t unc;
};

#endif /* PARTICLES_H */
