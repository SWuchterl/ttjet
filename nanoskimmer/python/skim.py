#!/usr/bin/env python

import argparse
import os
import subprocess
import sys
import time

# import htcondor
import ROOT
import yaml
from dbs.apis.dbsClient import DbsApi

# sys.path.append("/usr/lib64/python2.6/site-packages/")
sys.path.append(
    "/afs/desy.de/user/s/sewuchte/.local/lib/python2.7/site-packages")

ROOT.PyConfig.IgnoreCommandLineOptions = True


def parser():
    parser = argparse.ArgumentParser(
        description="Script to skim NANOAOD root files", formatter_class=argparse.RawTextHelpFormatter)

    parser.add_argument("--filename", action="store",
                        help="Name of the input NANOAOD root file")
    parser.add_argument("--version", action="store",
                        help="Version Number")
    # parser.add_argument("--channel", nargs="+", choices=["ele+4j", "mu+4j"], default=[
    #                     "ele+4j", "mu+4j"], help="Final state which is of interest")

    parser.add_argument("--bkg-txt", action="store",
                        help="Txt file with data set names of bkg samples")
    parser.add_argument("--data-txt", action="store",
                        help="Txt file with data set names of data samples")
    parser.add_argument("--sig-txt", action="store",
                        help="Txt file with data set names of signal samples")

    parser.add_argument("--batch", action="store_true", default=False,
                        help="State if you want local or HTcondor jobs")
    parser.add_argument("--out-dir", type=str, default="{}/src".format(
        os.environ["CMSSW_BASE"]), help="Name of output directory")
    parser.add_argument("--out-name", type=str,
                        default="outputSkim.root", help="Output name of skimmed file")

    return parser.parse_args()


def getFilenames(txtFile):
    # dasgoclient python API
    dbs = DbsApi(
        'https://cmsweb.cern.ch/dbs/prod/global/DBSReader')
    global_director = "root://cmsxrootd.fnal.gov/"

    # Read out input files containing data set names
    with open(txtFile) as f:
        datasets = [dataset for dataset in f.read(
        ).splitlines() if dataset != ""]

    # Fill file names in using dasgoclient API
    filelist = {}

    for setname in datasets:
        if "mc" in setname:
            filelist[setname.split("/")[1]] = [global_director + filename['logical_file_name']
                                               for filename in dbs.listFiles(dataset=setname, detail=1)]

        elif "user" in setname:
            filelist[setname.split(
                "/")[5]] = [global_director + setname]

        else:
            filelist[setname.split("/")[1] + "-" + setname.split("/")[2]] = [global_director +
                                                                             filename['logical_file_name'] for filename in dbs.listFiles(dataset=setname, detail=1)]

    # print filelist

    return filelist


args = parser()
if args.batch:
    import htcondor

    def condorSubmit(skimdir, dirname, filename, index):
        # Condor class
        job = htcondor.Submit()
        schedd = htcondor.Schedd()

        skimFilename = dirname + "_{}.root".format(index)

        # Condor configuration
        job["executable"] = "{}/src/ttjet/nanoskimmer/batch/produceSkim.sh".format(
            os.environ["CMSSW_BASE"])
        # job["arguments"] = " ".join(
        #     [filename, skimFilename] + list(channels))

        job["getenv"] = "True"

        job["arguments"] = " ".join(
            [filename, skimFilename])
        job["universe"] = "vanilla"

        job["should_transfer_files"] = "YES"
        # job["transfer_input_files"] = ",".join(
        #     [os.environ["CMSSW_BASE"] + "/src/ttjet", os.environ["CMSSW_BASE"] + "/src/x509"])
        # job["transfer_input_files"] = ",".join(
        #     [os.environ["CMSSW_BASE"] + "/src/x509"])
        job["transfer_input_files"] = ",".join(
            [os.environ["CMSSW_BASE"] + "/src/ttjet", os.environ["CMSSW_BASE"] + "/src/x509"])
        # job["transfer_input_files"] = ",".join([
        #     os.environ["X509_USER_PROXY"]])

        job["log"] = "{}/{}/log/job_$(Cluster).log".format(
            skimdir, dirname)
        job["output"] = "{}/{}/log/job_$(Cluster).out".format(
            skimdir, dirname)
        job["error"] = "{}/{}/log/job_$(Cluster).err".format(
            skimdir, dirname)

        # print skimdir, dirname, filename, index

        job["when_to_transfer_output"] = "ON_EXIT"
        job["transfer_output_remaps"] = '"' + '{outFile} = {skimDir}/{dirName}/{outFile}'.format(
            outFile=skimFilename, skimDir=skimdir, dirName=dirname) + '"'

       # Agressively submit your jobs

        def submit(schedd, job):
            with schedd.transaction() as txn:
                job.queue(txn)
                print "Submit job for file {}".format(
                    filename)

        while(True):
            try:
                submit(schedd, job)
                break

            except:
                pass


# def skimmer(filename, channels, outputName):
def skimmer(filename, outputName):
    # xSecFile = yaml.load(file(
    #     "{}/src/ChargedHiggs/nano_skimming/data/xsec.yaml".format(os.environ["CMSSW_BASE"]), "r"))

    xSec = 1.
    print "skimmer", filename, outputName

    # for key in xSecFile.keys():
    #     if key in outputName:
    #         xSec = xSecFile[key]["xsec"]

    # isData = "Single" in outputName
    outName = filename.split(
        "/")[-1].split(".")[0] + "_output." + filename.split("/")[-1].split(".")[1]
    print "skimmer",  outName
    Skimmer = ROOT.Skimmer(
        ROOT.std.string(filename), ROOT.std.string(filename), outputName, 2016)
    Skimmer.Analyze()

    # Skimmer.WriteOutput(ROOT.std.string(outName))
    Skimmer.WriteOutput(ROOT.std.string(outputName))


def main():
    args = parser()
    if args.batch:
        # skimdir = "/nfs/dust/cms/user/{}/skims/nanoSkim_{}".format(
        #     os.environ["USER"], "_".join([str(time.localtime()[i]) for i in range(6)]))
        skimdir = "/nfs/dust/cms/user/{}/skims/nanoSkim_{}".format(
            os.environ["USER"], "_".join([args.version]))

        # Create dirs and copy proxy file to initialdir
        os.system("mkdir -p {}".format(skimdir))
        os.system("chmod 755 {}".format(
            os.environ["X509_USER_PROXY"]))
        os.system("cp -u {} {}/src/".format(
            os.environ["X509_USER_PROXY"], os.environ["CMSSW_BASE"]))

        for txtFile in [txtFile for txtFile in [args.bkg_txt, args.sig_txt, args.data_txt] if txtFile != None]:
            filelist = getFilenames(txtFile)

            # Submit
            for dirname, filenames in filelist.iteritems():
                os.system(
                    "mkdir -p {}/{}/log".format(skimdir, dirname))
                # print "main", dirname, filenames
                for index, filename in enumerate(filenames):
                    # print "main", skimdir, dirname, filename, index
                    condorSubmit(
                        skimdir, dirname, filename, index)

    else:
        # skimmer(args.filename, channels, args.out_name)
        skimmer(args.filename, args.out_name)


if __name__ == "__main__":
    main()
