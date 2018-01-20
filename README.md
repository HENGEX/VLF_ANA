# VLF_ANA

## Installation instructions:

## lxplus 6  
export SCRAM_ARCH=slc6_amd64_gcc630

cmsrel CMSSW_9_4_3

cd CMSSW_9_4_3/src

cmsenv

git cms-init  
git cms-addpkg RecoMET/METProducers  
scram b -j 10  


## Running with crab:
Create a new crab task and submit the jobs:
crab submit -c python/YOUR_CRAB_CONFIG_FILE.py
Checking status:
crab status -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/
Resubmitting failed jobs (check in the status output if the jobs can be resubmitted):
crab resubmit -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/

A good tutorial on crab can be found here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial
