#!/usr/bin/env python

import subprocess
import time


def getInfos():
    out = subprocess.check_output(["condor_q", "-long"])
    for jobStrings in out.split("\n\n"):
        for line in jobStrings.split("\n"):
            if line:
                break
                print[line.split(" = ")]

                # if " = " in line:
                #     print line.replace("\"", "").split(
                #         " = ")
    return [dict([line.replace("\"", "").split(" = ") for line in jobStrings.split("\n") if (" = " in line)and len((line.replace("\"", "").split(" = "))) == 2]) for jobStrings in out.split("\n\n") if jobStrings]


def getSummary():
    out = subprocess.check_output(["condor_q"])
    return out.split("\n")[-2]


def getNameFromFile(fname):
    return fname.replace(".sh", "").split("/")[-1]


nrRun = 0
nrIdle = 0
nrSupended = 0

jobs = getInfos()
jobs = sorted(
    jobs, key=lambda l: l["JobStatus"] + l["Args"])
for job in jobs:
    name = getNameFromFile(job["Cmd"])
    args = getNameFromFile(job["Args"])
    jStatus = job["JobStatus"]
    if jStatus == "1":
        # print name, "IDLE"
        print name, args.split(" ")[
            1], "\033[96m IDLE\033[00m"
        nrIdle += 1
    elif jStatus == "2":
        # print name, "\033[92m RUNNING\033[00m", job["ClusterId"], " @ ", job["RemoteHost"].replace(
        #     ".physik.rwth-aachen.de", "").replace("slot", "")
        # print name, "\033[92m RUNNING\033[00m", job["ClusterId"], " @ ", job["RemoteHost"]
        # print name, args.split(" ")[
        #     1], "\033[92m RUNNING\033[00m", job["ClusterId"], " @ ", job["RemoteHost"]
        print name, args.split(" ")[
            1], "\033[92m RUNNING\033[00m", job["ClusterId"], " @ "
        nrRun += 1
    elif jStatus == "7":
        nrSupended += 1
        susTime = (time.time()
                   - int(job["LastSuspensionTime"])) / 60.
        # print name, "\033[93m SUSPENDED\033[00m since {:.2f} min".format(
        #     susTime), job["ClusterId"], "@", job["RemoteHost"].replace(".physik.rwth-aachen.de", "").replace("slot", "")
        print name, "\033[93m SUSPENDED\033[00m since {:.2f} min".format(
            susTime), job["ClusterId"], "@", job["RemoteHost"]
    elif jStatus == "5":
        susTime = (time.time()
                   - int(job["LastSuspensionTime"])) / 60.
        print name, "\033[97m HELD\033[00m", job["ClusterId"]
    else:
        print "job status = ", jStatus
print getSummary()

print nrRun, "out of", (nrRun
                        + nrIdle + nrSupended), "\033[92m running\033[00m"
print nrIdle, "out of", (nrRun
                         + nrIdle + nrSupended), "\033[96m idle\033[00m"
print nrSupended, "out of", (nrRun
                             + nrIdle + nrSupended), "\033[93m suspended\033[00m"
