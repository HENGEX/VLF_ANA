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

git cms-addpkg MagneticField/GeomBuilder  
scram b -j 10  

git clone https://github.com/HENGEX/VLF_ANA -b cmssw-9.4.3  
scram b -j 10  


## Running with crab:  
NOTE: you need to have a Grid cetrificate registered with VOMS   
source /cvmfs/cms.cern.ch/crab3/crab.sh  
voms-proxy-init --voms cms --valid 168:00  

Create a new crab task and submit the jobs:
crab submit -c python/YOUR_CRAB_CONFIG_FILE.py
Checking status:
crab status -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/
Resubmitting failed jobs (check in the status output if the jobs can be resubmitted):
crab resubmit -d crab_projects/YOUR_CRAB_TASK_DIRECTORY/

A good tutorial on crab can be found here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial
