#ifndef JetCorrectionProducer_h
#define JetCorrectionProducer_h

#include <sstream>
#include <string>
#include <vector>

#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

namespace edm 
{
  class ParameterSet;
}

class JetCorrector;

namespace cms 
{
  template<class T>
  class JetCorrectionProducer : public edm::EDProducer {
  public:
    typedef std::vector<T> JetCollection;
    explicit JetCorrectionProducer (const edm::ParameterSet& fParameters);
    virtual ~JetCorrectionProducer () {}
    virtual void produce(edm::Event&, const edm::EventSetup&);
  private:
    edm::InputTag mInput;
    std::vector <std::string> mCorrectorNames;
    // cache
    std::vector <const JetCorrector*> mCorrectors;
    unsigned long long mCacheId;
    bool mVerbose;
  };
}

// ---------- implementation ----------

namespace cms {

  template<class T>
    JetCorrectionProducer<T>::JetCorrectionProducer (const edm::ParameterSet& fConfig) 
    : 
    mInput (fConfig.getParameter <edm::InputTag> ("src")),
    mCorrectorNames (fConfig.getParameter <std::vector <std::string> > ("correctors")),
    mCorrectors (mCorrectorNames.size(), 0),
    mCacheId (0),
    mVerbose (fConfig.getUntrackedParameter <bool> ("verbose", false)) 
    {
      
      std::string alias = fConfig.getUntrackedParameter <std::string> ("alias", "");
      if (alias.empty ())
	produces <JetCollection>();
      else 
	produces <JetCollection>().setBranchAlias (alias);
    }

  template<class T>
    void JetCorrectionProducer<T>::produce(edm::Event& fEvent, const edm::EventSetup& fSetup) 
    {
      // look for correctors
      const JetCorrectionsRecord& record = fSetup.get <JetCorrectionsRecord> ();
      if (record.cacheIdentifier() != mCacheId) 
	{ // need to renew cache
	  for (unsigned i = 0; i < mCorrectorNames.size(); i++) 
	    {
	      edm::ESHandle <JetCorrector> handle;
	      record.get (mCorrectorNames [i], handle);
	      mCorrectors [i] = &*handle;
	    }
	  mCacheId = record.cacheIdentifier();
	}
      edm::Handle<JetCollection> jets;                       //Define Inputs
      fEvent.getByLabel (mInput, jets);                      //Get Inputs
      std::auto_ptr<JetCollection> result (new JetCollection);    //Corrected jets
      typename JetCollection::const_iterator jet;
      for (jet = jets->begin(); jet != jets->end(); jet++) 
	{
	  const T* referenceJet = &*jet;
	  T correctedJet = *jet; //copy original jet
	  if (mVerbose)
	    std::cout << "JetCorrectionProducer::produce-> original jet: " << jet->print () << std::endl; 
	  for (unsigned i = 0; i < mCorrectors.size(); ++i) 
	    {
	      if ( !(mCorrectors[i]->vectorialCorrection()) ) {
		// Scalar correction
		double scale = mCorrectors[i]->correction (*referenceJet, fEvent, fSetup);
		if (mVerbose)
		  std::cout << "JetCorrectionProducer::produce-> Corrector # " << i << ", correction factor: " << scale << std::endl;
		correctedJet.scaleEnergy (scale); // apply correction
		referenceJet = &correctedJet;
	      } else {
		// Vectorial correction
		JetCorrector::LorentzVector corr(0.,0.,0.,0.);
		double scale = mCorrectors[i]->correction (*referenceJet, fEvent, fSetup, corr);
		if (mVerbose)
		  std::cout << "JetCorrectionProducer::produce-> Corrector # " << i << ", correction factor: " << scale << std::endl;
		correctedJet.setP4( corr ); // apply correction
		referenceJet = &correctedJet;
	      }
	    }
	  if (mVerbose)
	    std::cout << "JetCorrectionProducer::produce-> corrected jet: " << correctedJet.print () << std::endl; 
	  result->push_back (correctedJet);
	}
      NumericSafeGreaterByPt<T> compJets;
      std::sort (result->begin (), result->end (), compJets); // reorder corrected jets
      fEvent.put(result);  //Puts Corrected Jet Collection into event
    }

}

#endif
