import ROOT

# Setup a canvas for plotting. The arguments are a name, an optional title, and the width and height in pixels.
# canvas = ROOT.TCanvas('canvas', '', 500, 500)

# all int lumis 2016 per run range in fb-1:
B = 5.750490644
C = 2.572903489
D = 4.242291557
E = 4.025228137
F = 3.104509132
G = 7.575824256
H = 8.650628380
BtoF = B + C + D + E + F
GtoH = G + H


def combine2DHistos(hist1, hist2, weight1, weight2):
    outHisto = hist1.Clone()
    for binX in range(0, hist1.GetNbinsX() + 1):
        for binY in range(0, hist1.GetNbinsY() + 1):
            v1 = hist1.GetBinContent(binX, binY)
            v2 = hist2.GetBinContent(binX, binY)
            v1err = hist1.GetBinError(binX, binY)
            v2err = hist2.GetBinError(binX, binY)
            # v1errUp=hist1.GetBinErrorUp(binX,binY)
            # v1errDn=hist1.GetBinErrorUp(binX,binY)
            # v2errUp=hist2.GetBinErrorUp(binX,binY)
            # v2errDn=hist2.GetBinErrorUp(binX,binY)
            outV = weight1 * v1 + weight2 * \
                v2 / (weight1 + weight2)
            term1 = weight1 / (weight1 + weight2) * v1err
            term2 = weight2 / (weight1 + weight2) * v2err
            outErr = ROOT.TMath.Sqrt(
                (term1 * term1) + (term2 + term2))
            outHisto.SetBinContent(binX, binY, outV)
            outHisto.SetBinError(binX, binY, outErr)
    return outHisto.Clone()


dict = {}
dict["RunBCDEF_SF_ID"] = {}
dict["RunGH_SF_ID"] = {}
dict["RunBCDEF_SF_ISO"] = {}
dict["RunGH_SF_ISO"] = {}
dict["RunBCDEFGH_SF_ID"] = {}
dict["RunBCDEFGH_SF_ISO"] = {}
path = "ttjet/nanoskimmer/data/scaleFactors/muon/"
f = ROOT.TFile.Open(path + 'RunBCDEF_SF_ID.root', 'read')
dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt').Clone()
dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt').Clone()
dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat').Clone()
dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst').Clone()
dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt').Clone()
dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt').Clone()
dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt_syst').Clone()

for h in dict["RunBCDEF_SF_ID"]:
    # print h
    dict["RunBCDEF_SF_ID"][h].SetDirectory(0)

f.Close()
f = ROOT.TFile.Open(path + 'RunGH_SF_ID.root', 'read')
dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt').Clone()
dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_LooseID_DEN_genTracks_eta_pt_syst').Clone()
dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt').Clone()
dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat').Clone()
dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"] = f.Get(
    'NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst').Clone()
dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt').Clone()
dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_TightID_DEN_genTracks_eta_pt_syst').Clone()
dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt').Clone()
dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt_stat').Clone()
dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"] = f.Get(
    'NUM_MediumID_DEN_genTracks_eta_pt_syst').Clone()
for h in dict["RunGH_SF_ID"]:
    dict["RunGH_SF_ID"][h].SetDirectory(0)
f.Close()
f = ROOT.TFile.Open(path + 'RunBCDEF_SF_ISO.root', 'read')
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt_syst').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat').Clone()
dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst').Clone()
for h in dict["RunBCDEF_SF_ISO"]:
    dict["RunBCDEF_SF_ISO"][h].SetDirectory(0)
f.Close()
f = ROOT.TFile.Open(path + 'RunGH_SF_ISO.root', 'read')
dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"] = f.Get(
    'NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"] = f.Get(
    'NUM_TightRelIso_DEN_MediumID_eta_pt_syst').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = f.Get(
    'NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_MediumID_eta_pt_syst').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_LooseID_eta_pt_syst').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat').Clone()
dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = f.Get(
    'NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst').Clone()
for h in dict["RunGH_SF_ISO"]:
    dict["RunGH_SF_ISO"][h].SetDirectory(0)
f.Close()


outFile = ROOT.TFile.Open(
    path + "RunBCDEFGH_SF_ID.root", "RECREATE")
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"], dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"], dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"], dict["RunGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_LooseID_DEN_genTracks_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"], dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"], dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_stat"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"], dict["RunGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_HighPtID_DEN_genTracks_eta_pair_newTuneP_probe_pt_syst"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"], dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"], dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"], dict["RunGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_TightID_DEN_genTracks_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"], dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"], dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"], dict["RunGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ID"]["NUM_MediumID_DEN_genTracks_eta_pt_syst"].Write()
outFile.Close()

outFile = ROOT.TFile.Open(
    path + "RunBCDEFGH_SF_ISO.root", "RECREATE")
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"], dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"], dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"], dict["RunGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelTkIso_DEN_HighPtIDandIPCut_eta_pair_newTuneP_probe_pt_syst"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_MediumID_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"], dict["RunGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_MediumID_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_LooseID_eta_pt_syst"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_stat"].Write()
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"] = combine2DHistos(
    dict["RunBCDEF_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"], dict["RunGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"], BtoF, GtoH)
dict["RunBCDEFGH_SF_ISO"]["NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt_syst"].Write()
outFile.Close()
