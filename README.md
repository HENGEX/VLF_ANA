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
