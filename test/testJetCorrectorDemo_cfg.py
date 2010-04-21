import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")

process.TFileService=cms.Service("TFileService",fileName=cms.string('JECplots.root'))
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(100)
        )

process.source = cms.Source("EmptySource")

process.ak5CaloL2L3Histos = cms.EDAnalyzer(
    'JetCorrectorDemo',
    JetCorrectionService = cms.string('ak5CaloL2L3'),
    NHistoPoints         = cms.int32(10000),
    NGraphPoints         = cms.int32(500),
    EtaMin               = cms.double(-5),
    EtaMax               = cms.double(5),
    PtMin                = cms.double(1),
    PtMax                = cms.double(500),
    VEta                 = cms.vdouble(0.0,1.0,2.0,3.0,4.0),
    VPt                  = cms.vdouble(10,30,50,100,200),
    Debug                = cms.untracked.bool(False)
)

process.ak5PFL2L3Histos    = process.ak5CaloL2L3Histos.clone(JetCorrectionService = 'ak5PFL2L3', Debug = False)
#process.ak5JPTL2L3Histos   = process.ak5CaloL2L3Histos.clone(JetCorrectionService = 'ak5JPTL2L3', Debug = False)
#process.ak5TrackL2L3Histos = process.ak5CaloL2L3Histos.clone(JetCorrectionService = 'ak5TrackL2L3', Debug = False)

#process.p = cms.Path(process.ak5CaloL2L3Histos * process.ak5PFL2L3Histos * process.ak5JPTL2L3Histos * process.ak5TrackL2L3Histos)
process.p = cms.Path(process.ak5CaloL2L3Histos * process.ak5PFL2L3Histos )
