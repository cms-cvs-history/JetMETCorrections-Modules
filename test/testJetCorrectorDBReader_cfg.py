import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.load("CondCore.DBCommon.CondDBCommon_cfi")


process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1)
        )

process.source = cms.Source("EmptySource")



process.PoolDBESSource = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0)
        ),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('Summer09_7TeV_ReReco332_L2Relative_AK5Calo'),
            label  = cms.untracked.string('L2Relative_AK5Calo')
            )
       ),
#       connect=cms.string('sqlite:Summer09_7TeV_ReReco332_L2Relative_AK5Calo@6fdda042-46fd-11df-add9-001e4f3e5642.db')
#       connect = cms.string('frontier://FrontierInt/CMS_COND_31X_FRONTIER')                                      
      connect=cms.string('frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS')
)

process.demo2 = cms.EDAnalyzer('JetCorrectorDBReader', 
        label          = cms.untracked.string('L2Relative_AK5Calo'),
        createTextFile = cms.untracked.bool(True)
)

process.p = cms.Path(process.demo2)
