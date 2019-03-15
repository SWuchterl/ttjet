#!/bin/bash

# source /cvmfs/cms.cern.ch/cmsset_default.sh
# source /cvmfs/cms.cern.ch/crab3/crab.sh
# export SCRAM_ARCH=slc6_amd64_gcc630
#
# eval `scramv1 project CMSSW CMSSW_9_4_11_patch1`
# cd CMSSW_9_4_11_patch1/src/
# eval `scramv1 runtime -sh`

# mv ../../ChargedHiggs/ ./
# mv ../../x509 ./

export thisBatchPath=$PWD



# export X509_USER_PROXY=$CMSSW_BASE/src/x509
export X509_USER_PROXY=/afs/desy.de/user/s/sewuchte/.vomsproxy/x509


# scram b

# source /nfs/dust/cms/user/$USER/ttjetFWK/CMSSW_9_4_13_patch1/src/ttjet/setup.sh

cd /nfs/dust/cms/user/sewuchte/ttjetFWK/CMSSW_9_4_13_patch1/src/ttjet
echo 1
pwd

#if needed:
export PATH=$PATH:/nfs/dust/cms/user/sewuchte/ttjetFWK/anaconda2/bin
echo 2
pwd

source activate conda_ttjet
echo 3
pwd
export SCRAM_ARCH="slc6_amd64_gcc630"
echo 4
pwd
source $VO_CMS_SW_DIR/cmsset_default.sh
echo 5
pwd
cd /nfs/dust/cms/user/sewuchte/ttjetFWK/CMSSW_9_4_13_patch1/src
echo 6
pwd
eval `scramv1 runtime -sh`
#alias gotoWorkDir="cd /nfs/dust/cms/user/$USER/ttjetFWK/CMSSW_9_4_13_patch1/src/ttjet"
echo 7
pwd
cd /nfs/dust/cms/user/sewuchte/ttjetFWK/CMSSW_9_4_13_patch1/src/
echo 8
pwd
export X509_USER_PROXY=/afs/desy.de/user/s/sewuchte/.vomsproxy/x509
source $VO_CMS_SW_DIR/crab3/crab.sh
echo 9
pwd
export X509_USER_PROXY=$thisBatchPath/x509
echo $X509_USER_PROXY
# chmod 755 $X509_USER_PROXY
echo 10
ls /afs/desy.de/user/s/sewuchte/.vomsproxy/
echo 11
ls
cd $thisBatchPath
echo 12
ls
xrdcp $1 $(echo $1 | tr '/' '_')
echo 13
ls
echo $1
voms-proxy-info
# python ttjet/nanoskimmer/python/skim.py --filename $(echo $1 | tr '/' '_') --out-name $2 --channel $3 $4
python /nfs/dust/cms/user/sewuchte/ttjetFWK/CMSSW_9_4_13_patch1/src/ttjet/nanoskimmer/python/skim.py --filename $(echo $1 | tr '/' '_')
rm $(echo $1 | tr '/' '_')
# mv *.root ../../
