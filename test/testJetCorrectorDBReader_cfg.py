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
        record = cms.string('JetCorrectorParametersRecord'),
            tag = cms.string('dunno'),
            label = cms.untracked.string('someCorrectiongJ')
            ))

)

process.demo2 = cms.EDAnalyzer('JetCorrectorDBReader', label = cms.untracked.string('someCorrectiongJ'))

process.p = cms.Path(process.demo2)
