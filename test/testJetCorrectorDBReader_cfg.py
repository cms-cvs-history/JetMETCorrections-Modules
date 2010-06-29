import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:JEC_Summer09_7TeV_ReReco332.db'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1)
        )

process.source = cms.Source("EmptySource")

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
        process.CondDBCommon,
        toGet = cms.VPSet(
          cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('AK5Calo'),
            label  = cms.untracked.string('AK5Calo')
          ),
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('AK5PF'),
            label  = cms.untracked.string('AK5PF')
          )                                          
                                          ),
      connect = cms.string('sqlite_file:JEC_Spring10.db')
#      connect=cms.string('frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS')
)

process.demo2 = cms.EDAnalyzer('JetCorrectorDBReader', 
        label          = cms.untracked.string('AK5Calo'),
        createTextFile = cms.untracked.bool(True)
)


process.demo3 = cms.EDAnalyzer('JetCorrectorDBReader', 
        label          = cms.untracked.string('AK5PF'),
        createTextFile = cms.untracked.bool(True)
)

process.p = cms.Path(process.demo2 * process.demo3)
