import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source("PoolSource",
                            
                            fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/120000/14473FEF-1ACD-E611-8C84-00266CFFBC60.root'
        
        #                            fileNames = cms.untracked.vstring(
        #        'file:/afs/cern.ch/user/c/csalazar/WorkPublic/VLF_Fill/CMSSW_8_0_25/src/VLF_Fill/Tyrion/test/savep1.root'
        
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
                              
                              )
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("Tree.root"),
                                   closeFileFast = cms.untracked.bool(True)
                                   )


process.p = cms.Path(process.demo)
