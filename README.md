# ttjet
Framework for ttbar+1jet analysis

##Setup

mkdir ttjetFWK

git clone https://github.com/sewuchte/ttjet.git

cd ttjet

module load git/1.9

git lfs install --local



git lfs track "Anaconda2-4.4.0-Linux-x86_64.sh.psd"

git add .gitattributes

cd ..

bash /ttjet/$USER/Anaconda2-4.4.0-Linux-x86_64.sh


Answer yes to the terms of the license, then specify installation in a new location:

$PWD/anaconda2

if needed (ie it isn't added to the bashrc or you haven't sourced it):
export PATH=$PATH:/nfs/dust/cms/user/USERNAME/ttjet/anaconda2/bin
cd ttjet
git submodule init #initialise and update the submodule in git
git submodule update #if there is an error here, instead run `git clone https://github.com/aelwood/pandasPlotting.git && git submodule update`



conda create -n ttjet -c nlesc root root_numpy keras pandas seaborn scikit-learn tensorflow matplotlib
source activate ttjet
conda install -c conda-forge lime

conda install -c nlesc xrootd

source $VO_CMS_SW_DIR/cmsset_default.sh
cd ..
export SCRAM_ARCH="slc6_amd64_gcc630"

cmsrel CMSSW_9_4_13_patch1
cd CMSSW_9_4_13_patch1/src
cmsenv

pip install --upgrade --user uproot tensorflow keras


#everytime:
Now everything is setup, when you login you will need to move to your working directory and initialise the environment again. If you didn't add anaconda to your bashrc you'll also have to manually add it to the $PATH
All included in setup.sh

cd /nfs/dust/cms/user/$USER/ttjetFWK/ttjet
#if needed:
export PATH=$PATH:/nfs/dust/cms/user/$USER/ttjetFWK/anaconda2/bin
source activate ttjet

alias sourceCMS="cd /nfs/dust/cms/user/$USER/ttjetFWK/CMSSW_9_4_13_patch1/src && cmsenv"
alias gotoWorkDir="cd /nfs/dust/cms/user/$USER/ttjetFWK/ttjet"


#add to your .bashrc

alias cms="source $VO_CMS_SW_DIR/cmsset_default.sh"
alias voms="voms-proxy-init --voms cms --valid 192:00"
alias scramb="scram b -j 16"
alias crabs="source $VO_CMS_SW_DIR/crab3/crab.sh"
