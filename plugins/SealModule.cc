#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/SourceFactory.h"


#include "CondCore/PluginSystem/interface/registration_macros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionService.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionServiceChain.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionProducer.h"
#include "JetMETCorrections/Modules/interface/PlotJetCorrections.h"
#include "JetMETCorrections/Algorithms/interface/ZSPJetCorrector.h"
#include "JetMETCorrections/Algorithms/interface/LXXXCorrector.h"
#include "JetMETCorrections/Algorithms/interface/L1FastjetCorrector.h"
#include "JetMETCorrections/Algorithms/interface/L6SLBCorrector.h"
#include "JetMETCorrections/Algorithms/interface/JetPlusTrackCorrector.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"

REGISTER_PLUGIN (JetCorrectionsRecord, JetCorrector);

using namespace cms;
using namespace reco;

typedef JetCorrectionProducer<CaloJet> CaloJetCorrectionProducer;
DEFINE_FWK_MODULE(CaloJetCorrectionProducer);

typedef JetCorrectionProducer<PFJet> PFJetCorrectionProducer;
DEFINE_FWK_MODULE(PFJetCorrectionProducer);

typedef JetCorrectionProducer<GenJet> GenJetCorrectionProducer;
DEFINE_FWK_MODULE(GenJetCorrectionProducer);

DEFINE_FWK_MODULE(PlotJetCorrections);

DEFINE_FWK_EVENTSETUP_SOURCE(JetCorrectionServiceChain);

//--------------- Generic LX correction service --------------------
DEFINE_JET_CORRECTION_SERVICE (LXXXCorrector, LXXXCorrectionService);

//--------------- L1 fastjet UE&PU subtraction correction service --
DEFINE_JET_CORRECTION_SERVICE (L1FastjetCorrector, L1FastjetCorrectionService);

//---------------  L6 SLB correction service -----------------------
DEFINE_JET_CORRECTION_SERVICE (L6SLBCorrector, L6SLBCorrectionService);

//--------------- Zero suppression correction service --------------
DEFINE_JET_CORRECTION_SERVICE (ZSPJetCorrector, ZSPJetCorrectionService);

//--------------- JPT correction service ---------------------------
DEFINE_JET_CORRECTION_SERVICE (JetPlusTrackCorrector, JetPlusTrackCorrectionService);
