# VLF_ANA

## Installation instructions:

export SCRAM_ARCH=slc6_amd64_gcc530

cmsrel CMSSW_8_0_25

cd CMSSW_8_0_25/src

cmsenv

git cms-init  
git cms-addpkg RecoMET/METProducers  
scram b -j 10  
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter  
scram b -j 10  


## Running with crab:
Create a new crab task and submit the jobs:  
crab submit -c python/YOUR_CRAB_CONFIG_FILE.py  
Checking status:  
crab status -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/  
Resubmitting failed jobs (check in the status output if the jobs can be resubmitted):  
crab resubmit -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/  

A good tutorial on crab can be found here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial  
