import pyxrootd
import uproot

print "Importing uproot and pyroott worked fine"

path = "/store/mc/RunIISummer16NanoAODv4/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/NANOAODSIM/PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/30000/3C337E12-9298-6D4C-961D-06F7CAD68921.root"
path_prefix = "root://cmsxrootd.fnal.gov/"
print "Loading root file via xrootd"
file = uproot.open(path_prefix + path)
print "Loaded succesfully"
print "Printing keys"
print file.keys()
tree = file["Events"]
ept = tree["Electron_pt"]
print "Loaded tree. Printing Electron pt"
print ept
print tree.array("Electron_pt")