// -*- C++ -*-
//
// Package:    VLF_ANA/Dracarys
// Class:      Dracarys
// 
/**\class Dracarys Dracarys.cc VLF_ANA/Dracarys/plugins/Dracarys.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jose Ruiz
//         Created:  Tue, 08 Aug 2017 09:38:40 GMT
//
//


// system include files
#include <memory>
#include <cmath>
#include <string> /*Usig of strigs*/
#include <iostream>

// user include files
/*
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
*/
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
//User defined
//

#include "VLF_ANA/Dracarys/interface/Dracarys.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.
/*
class Dracarys : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit Dracarys(const edm::ParameterSet&);
      ~Dracarys();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

      edm::EDGetTokenT triggerBits_;
      edm::EDGetTokenT triggerObjects_;
      edm::EDGetTokenT triggerPrescales_;
};
*/
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Dracarys::Dracarys(const edm::ParameterSet& iConfig):
  triggerBits_ (consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAlone>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales")))
//{
//triggerBits_ = iCC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"));
  //triggerObjects_ = consumes<pat::TriggerObjectStandAlone>(iConfig.getParameter("objects"));
  //  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter("prescales")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");

}


Dracarys::~Dracarys()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Dracarys::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   //Counters
   int c1;
   
   //Trigger
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAlone> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
   
   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);
   ////////////////////////////

   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
   //   std::cout << "\n == TRIGGER PATHS= " << std::endl;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i){

     /*Cut the version of the trigger path*/
     std::string nameV = names.triggerName(i);
     std::string version ="_v";
     size_t start_pos = nameV.rfind(version);
     std::string TriggerNameVersionOff;
     if (start_pos != std::string::npos){
       TriggerNameVersionOff= nameV.erase(start_pos, version.length()+4);
     } 
     
     /*End cut de version*/
     
     /*See if path pass*/
     std::string TriggerWanted="HLT_PFMET110_PFMHT110_IDTight";

     if( TriggerNameVersionOff ==  TriggerWanted ) {
       if(triggerBits->accept(i)){
	 //std::cout << "PASS" << std::endl;
	 c1++;
       }
     }
     /*end See if path pass*/  
     
     
   }
   
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
Dracarys::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Dracarys::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Dracarys::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Dracarys);
