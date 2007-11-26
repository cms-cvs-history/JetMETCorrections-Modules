#include "CondCore/PluginSystem/interface/registration_macros.h"
DEFINE_SEAL_MODULE();

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
REGISTER_PLUGIN (JetCorrectionsRecord, JetCorrector);

#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/SourceFactory.h"

using namespace cms;

#include "JetCorrectionProducer.h"
DEFINE_ANOTHER_FWK_MODULE(JetCorrectionProducer);

#include "JetCorrectionService.icc"
#include "JetMETCorrections/Objects/interface/SimpleJetCorrector.h"
DEFINE_JET_CORRECTION_SERVICE (SimpleJetCorrector, SimpleJetCorrectionService);
#include "JetMETCorrections/MCJet/interface/MCJetCorrector.h"
DEFINE_JET_CORRECTION_SERVICE (MCJetCorrector, MCJetCorrectionService);
#include "JetMETCorrections/MCJet/interface/L5FlavorCorrector.h"
DEFINE_JET_CORRECTION_SERVICE (L5FlavorCorrector, L5FlavorCorrectionService);
#include "JetMETCorrections/GammaJet/interface/GammaJetCorrector.h"
