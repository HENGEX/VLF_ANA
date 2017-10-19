import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.load('TrackingTools.TransientTrack.TransientTrackBuilder_cfi')

process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_PostLS1_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# NOTE: the pick the right global tag!
#    for Spring15 50ns MC: global tag is 'auto:run2_mc_50ns'
#    for Spring15 25ns MC: global tag is 'auto:run2_mc'
#    for Run 2 data: global tag is 'auto:run2_data'
#  as a rule, find the "auto" global tag in $CMSSW_RELEASE_BASE/src/Configuration/AlCa/python/autoCond.py
#  This auto global tag will look up the "proper" global tag
#  that is typically found in the DAS under the Configs for given dataset
#  (although it can be "overridden" by requirements of a given release)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring([
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_1.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_10.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_11.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_12.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_13.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_14.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_15.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_16.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_17.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_18.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_2.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_20.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_21.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_22.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_23.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_24.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_27.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_28.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_3.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_30.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_33.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_35.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_36.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_37.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_38.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_39.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_40.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_41.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_42.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_43.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_44.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_46.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_47.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_48.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_49.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_5.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_50.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_51.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_52.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_53.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_55.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_57.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_59.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_6.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_60.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_62.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_63.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_64.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_65.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_66.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_67.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_7.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_72.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_73.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_79.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_8.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_80.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_81.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_82.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_83.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_85.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_86.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_87.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_90.root',
            'file:/eos/user/j/jruizalv/VLF_Samples/MINIAODSIM/MINIAODSIM_91.root']
                                                              )
                            )

process.demo = cms.EDAnalyzer('Dracarys',
                              bits = cms.InputTag("TriggerResults","","HLT"),
                              prescales = cms.InputTag("patTrigger"),
                              objects = cms.InputTag("selectedPatTrigger"),
                              vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
                              pileupInfo = cms.InputTag("slimmedAddPileupInfo"),
                              obmuon=cms.InputTag("slimmedMuons"),
                              objet=cms.InputTag("slimmedJets"),
                              obmet=cms.InputTag("slimmedMETs"),
                              #Is Data boolean
                              is_data = cms.bool(False),
                              #Activate debug option
                              debug = cms.bool(False),
                              #Cuts
                              Pvtx_ndof_min   = cms.int32(4), #Vertices DOF
                              Pvtx_vtx_max  = cms.double(24.),
                              Pvtx_vtxdxy_max = cms.double(24.),
                              MinMuonPt = cms.double(3.0), #Min muon pt - for all muons -
                              MaxMuonPt = cms.double(50.0), #Min muon pt - for all muons -
                              MuonIso = cms.double(0.15), #Combined isolation with delta beta PU corrections
                              MuonID = cms.int32(1), #0: Loose, 1: Medium, 2: Tight
                              MinNMuons = cms.int32(1), #Minimal number of muons following our definition
                              MaxNMuons = cms.int32(999), #Maximum number of muons following our defintiion
                              MinMET = cms.double(50.0), #Min MET
                              MinJetPt = cms.double(30.0), #Min Jet Pt
                              MaxJetEta = cms.double(5.0), #Max Jet Eta
                              bJetTag = cms.double(0.8484), #b-jet ID working point
                              MinbJetPt = cms.double(30.0), #Min b Jet Pt
                              MaxbJetEta = cms.double(2.4), #Max b Jet Eta
                              MinNJets = cms.int32(1), #Minimal number of jets following our definition
                              MaxNJets = cms.int32(999), #Maximum number of jets following our defintion
                              MinNbJets = cms.int32(0), #Minimal number of jets following our definition
                              MaxNbJets = cms.int32(999), #Maximum number of jets following our defintion
                              MinMTMuonMet =  cms.double(0.0),
                              MaxMTMuonMet =  cms.double(100.0),
                              )
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("Signal.root"),
                                   closeFileFast = cms.untracked.bool(True)
                                   )

# include bad muon filter
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")

# include bad charged hadron filter
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")

# met filters
process.load("VLF_ANA.Dracarys.AdditionalFilters_cfi")

process.p = cms.Path(process.goodVerticesFilterPAT * 
                     process.EcalDeadCellTriggerPrimitiveFilterPAT *
                     process.HBHENoiseFilterPAT * 
                     process.HBHENoiseIsoFilterPAT * 
		     process.BadPFMuonFilter *
		     process.BadChargedCandidateFilter *
                     process.demo)
