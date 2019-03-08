

cd /nfs/dust/cms/user/$USER/ttjetFWK/ttjet
#if needed:
export PATH=$PATH:/nfs/dust/cms/user/$USER/ttjetFWK/anaconda2/bin
source activate ttjet

export SCRAM_ARCH="slc6_amd64_gcc630"

source $VO_CMS_SW_DIR/cmsset_default.sh

alias sourceCMS="cd /nfs/dust/cms/user/$USER/ttjetFWK/CMSSW_9_4_13_patch1/src && cmsenv"
alias gotoWorkDir="cd /nfs/dust/cms/user/$USER/ttjetFWK/ttjet"

sourceCMS
gotoWorkDir
