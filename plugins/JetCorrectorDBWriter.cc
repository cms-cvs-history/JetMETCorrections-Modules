// Author: Benedikt Hegner
// Email:  benedikt.hegner@cern.ch

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

class  JetCorrectorDBWriter : public edm::EDAnalyzer
{
 public:
  JetCorrectorDBWriter(const edm::ParameterSet&);
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&) {}
  virtual void endJob() {}
  ~JetCorrectorDBWriter() {}

 private:
  std::string era;
  std::string algo;
  std::string inputTxtFile;
  std::string payloadLabel;
};

// Constructor
JetCorrectorDBWriter::JetCorrectorDBWriter(const edm::ParameterSet& pSet)
{
  era    = pSet.getUntrackedParameter<std::string>("era");
  algo   = pSet.getUntrackedParameter<std::string>("algo");
  payloadLabel = "JEC_"+era+"_"+algo;
}

// Begin Job
void JetCorrectorDBWriter::beginJob()
{
  std::string path("CondFormats/JetMETObjects/data/");

  JetCorrectorParametersCollection * payload = new JetCorrectorParametersCollection();
  std::cout << "Starting to import payload " << payloadLabel << " from text files." << std::endl;
  for ( int i = 0; i < JetCorrectorParametersCollection::N_LEVELS; ++i ) {
    
    std::string append("_");
    std::string ilev = JetCorrectorParametersCollection::findLabel( static_cast<JetCorrectorParametersCollection::Level_t>(i) );
    append += ilev;
    append += "_";
    append += algo;
    append += ".txt"; 
    inputTxtFile = path+era+append;
    std::ifstream input( ("../../../"+inputTxtFile).c_str() );
    if ( input.good() ) {
      edm::FileInPath fip(inputTxtFile);
      std::cout << "Opened file " << inputTxtFile << std::endl;
      // create the parameter object from file 
      std::vector<std::string> sections;
      JetCorrectorParametersCollection::getSections("../../../"+inputTxtFile, sections );
      if ( sections.size() == 0 ) {
	payload->push_back( i, JetCorrectorParameters(fip.fullPath(),"") );
      }
      else {
	for ( std::vector<std::string>::const_iterator isectbegin = sections.begin(), isectend = sections.end(), isect = isectbegin;
	      isect != isectend; ++isect ) {
	  payload->push_back( i, JetCorrectorParameters(fip.fullPath(),*isect), *isect );	  
	}
      }
      std::cout << "Added as record " << i << std::endl;
    } else {
      std::cout << "Did not find JEC file " << inputTxtFile << std::endl;
    }
    
  }
  
  std::cout << "Opening PoolDBOutputService" << std::endl;

  // now write it into the DB
  edm::Service<cond::service::PoolDBOutputService> s;
  if (s.isAvailable()) 
    {
      std::cout << "Setting up payload label " << payloadLabel << std::endl;
      if (s->isNewTagRequest(payloadLabel)) 
        s->createNewIOV<JetCorrectorParametersCollection>(payload, s->beginOfTime(), s->endOfTime(), payloadLabel);
      else 
        s->appendSinceTime<JetCorrectorParametersCollection>(payload, 111, payloadLabel);
    }
  std::cout << "Wrote in CondDB payload label: " << payloadLabel << std::endl;
}


DEFINE_FWK_MODULE(JetCorrectorDBWriter);

