# HLT template for JetCorrectionServiceChain

import FWCore.ParameterSet.Config as cms

# L2L3 correction service
hltJetCorrectionServiceChain = cms.ESProducer( 'JetCorrectionESChain',
    appendToDataLabel = cms.string( '' ),
    label      = cms.string( 'hltJetCorrectionServiceChain' ),
    correctors = cms.vstring(
      'hltESSL2RelativeCorrectionService',
      'hltESSL3AbsoluteCorrectionService'
    )
)
