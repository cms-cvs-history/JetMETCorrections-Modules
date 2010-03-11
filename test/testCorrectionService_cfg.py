import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:JEC.db'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1)
        )

process.source = cms.Source("EmptySource")

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
        process.CondDBCommon,
        toGet = cms.VPSet(
        cms.PSet(
        record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('dunno'),
            label = cms.untracked.string('L2Relative_AK5Calo_')
            ))

)

ak5CaloL2Relative = cms.ESProducer('LXXXCorrectionService',
            level     = cms.string('L2Relative'),
            algorithm = cms.string('AK5Calo'),
            section   = cms.string('')                       
            )

process.demo2 = cms.EDAnalyzer('JetCorrectorDBReader', label = cms.untracked.string('L2Relative_AK5Calo_'))

process.get = cms.EDAnalyzer("EventSetupRecordDataGetter",
                             toGet = cms.VPSet(cms.PSet(
                                 record = cms.string('JetCorrectionsRecord'),
                                 data = cms.vstring('ak5CaloL2Relative')
                             )),
                                 verbose = cms.untracked.bool(True)
                             )

process.p = cms.Path(process.demo2 * process.get)
