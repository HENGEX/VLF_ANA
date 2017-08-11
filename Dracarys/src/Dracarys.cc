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

// user include files

#include "VLF_ANA/Dracarys/interface/Dracarys.h"

Dracarys::Dracarys(const edm::ParameterSet& iConfig){
  //now do what ever initialization is needed
  
  usesResource("TFileService");  
  
  /*Muons*/
  tok_muons_=consumes< pat::Muon>(iConfig.getParameter<edm::InputTag>("obmuon"));
  
  /*Jets*/
  tok_jets_=consumes< pat::Jet>(iConfig.getParameter<edm::InputTag>("objet"));
  /*MET*/
  tok_met_=consumes< pat::MET>(iConfig.getParameter<edm::InputTag>("obmet"));
  /*Trigger*/
  triggerBits_ =consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"));
  triggerObjects_=consumes<pat::TriggerObjectStandAlone>(iConfig.getParameter<edm::InputTag>("objects"));
  triggerPrescales_=consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"));
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
   
 
   //Trigger
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAlone> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
   edm::Handle<pat::Muon>muonObjets;
   
   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);
   iEvent.getByToken(tok_muons_, muonObjets);

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
	 std::cout << "PASS" << std::endl;
       }
     }
     /*end See if path pass*/  
     
     
   }
   
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
