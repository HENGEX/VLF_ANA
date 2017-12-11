import FWCore.ParameterSet.Config as cms
import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt

HBHENoiseFilterPAT = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::PAT'),
    triggerConditions = (
      'Flag_HBHENoiseFilter',
    ),
    l1tResults = '',
    throw = False
)

HBHENoiseIsoFilterPAT = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::PAT'),
    triggerConditions = (
      'Flag_HBHENoiseIsoFilter',
    ),
    l1tResults = '',
    throw = False
)

EcalDeadCellTriggerPrimitiveFilterPAT = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::PAT'),
    triggerConditions = (
      'Flag_EcalDeadCellTriggerPrimitiveFilter',
    ),
    l1tResults = '',
    throw = False
)

goodVerticesFilterPAT = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::PAT'),
    triggerConditions = (
      'Flag_goodVertices',
    ),
    l1tResults = '',
    throw = False
)


HBHENoiseFilterRECO = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::RECO'),
    triggerConditions = (
      'Flag_HBHENoiseFilter',
    ),
    l1tResults = '',
    throw = False
)

HBHENoiseIsoFilterRECO = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::RECO'),
    triggerConditions = (
      'Flag_HBHENoiseIsoFilter',
    ),
    l1tResults = '',
    throw = False
)

EcalDeadCellTriggerPrimitiveFilterRECO = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::RECO'),
    triggerConditions = (
      'Flag_EcalDeadCellTriggerPrimitiveFilter',
    ),
    l1tResults = '',
    throw = False
)

goodVerticesFilterRECO = hlt.triggerResultsFilter.clone(
    hltResults = cms.InputTag('TriggerResults::RECO'),
    triggerConditions = (
      'Flag_goodVertices',
    ),
    l1tResults = '',
    throw = False
)


# this a more better way to see events passing triggers but not working yet for unknown reason.
#
# mySelectionFilterRECO = hlt.triggerResultsFilter.clone(
#     hltResults = cms.InputTag('TriggerResults::RECO'), #or HLT instead of RECO?
#     triggerConditions = 
#       cms.vstring('HLT_PFMET110_PFMHT110_IDTight* OR HLT_DoubleMu3_PFMET50*'), 
#     #l1tResults = cms.InputTag("gtDigis"),
#     throw = False
# )
