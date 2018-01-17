from WMCore.Configuration import Configuration
config = Configuration()

#from CRABClient.UserUtilities import config, getUsernameFromSiteDB
#config = config()

config.section_("General")
config.General.requestName = 'TASK'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_data_cfg.py'
#config.JobType.maxMemoryMB = 2500
config.JobType.allowUndistributedCMSSW = True


config.section_("Data")

#to run over data, not mc
#config.Data.inputDataset = '/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD'
#obtained from DAS with 'dataset=/DoubleMu*/*Run2016C*/MINIAOD*'
#as in https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial#CRAB_configuration_file_examples
#for mc the configuration files looks different

config.Data.inputDataset = 'DATASAMPLE'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 50
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
#config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.outLFNDirBase = '/store/user/nvanegas/VLF_ANA/OUTPUTDIR/'
config.Data.publication = False
config.Data.outputDatasetTag = 'TASK'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
