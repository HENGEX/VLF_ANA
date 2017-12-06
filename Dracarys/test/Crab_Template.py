from WMCore.Configuration import Configuration
config = Configuration()

#from CRABClient.UserUtilities import config, getUsernameFromSiteDB
#config = config()

config.section_("General")
config.General.requestName = 'data_PFMET110_trigger'
config.General.workArea = 'crab_project'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
#config.JobType.maxMemoryMB = 2500
config.JobType.allowUndistributedCMSSW = True


config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD'


#config.Data.inputDataset = 'dataset'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'FileBased'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 500000
#config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.outLFNDirBase = '/store/user/nvanegas/VLF_ANA/'
config.Data.publication = False
config.Data.outputDatasetTag = 'data_PFMET110_trigger'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
