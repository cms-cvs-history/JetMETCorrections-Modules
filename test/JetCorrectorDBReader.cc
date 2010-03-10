// -*- C++ -*-
//
// Package:    JetCorrectorDBReader
// Class:      
// 
/**\class JetCorrectorDBReader

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benedikt Hegner 
//         Created:  Tue Mar 09 01:32:51 CET 2010
// $Id: JetCorrectorDBReader.cc,v 1.3 2009/12/14 22:23:35 wmtan Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/DataRecord/interface/JetCorrectorParametersRecord.h"
#include "CondFormats/JetMETObjects/interface/SimpleJetCorrector.h"
//
// class decleration
//

class JetCorrectorDBReader : public edm::EDAnalyzer {
public:
  explicit JetCorrectorDBReader(const edm::ParameterSet&);
  ~JetCorrectorDBReader();
  
  
private:
  std::string label;
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
JetCorrectorDBReader::JetCorrectorDBReader(const edm::ParameterSet& iConfig):
  label(iConfig.getUntrackedParameter<std::string>("label"))
{

}


JetCorrectorDBReader::~JetCorrectorDBReader()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
JetCorrectorDBReader::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::ESHandle<JetCorrectorParameters> params;
  std::cout <<" Studying correction parameters with label "<< label <<std::endl;
  iSetup.get<JetCorrectorParametersRecord>().get(label,params);
  // print the parameters to screen
  params->printScreen();
  // create a SimpleJetCorrector
  SimpleJetCorrector theCorrector(*params);
}


// ------------ method called once each job just before starting event loop  ------------
void 
JetCorrectorDBReader::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetCorrectorDBReader::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetCorrectorDBReader);
