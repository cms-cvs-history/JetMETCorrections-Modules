import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:JEC.db'


process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1)
        )
process.source = cms.Source("EmptySource")

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                              process.CondDBCommon,
                                              toPut = cms.VPSet(
            cms.PSet(
            record = cms.string('someCorrectiongJ'),
                    tag = cms.string('dunno'),
                    label = cms.string('dunno')
            )
            )
)

process.mywriter = cms.EDAnalyzer("JetCorrectorDBWriter",
                                  inputTxtFile = cms.untracked.string('input.txt'),
                                  option = cms.untracked.string('gJ'),
                                  label = cms.untracked.string('someCorrection')
                                  )


process.p = cms.Path(process.mywriter)
