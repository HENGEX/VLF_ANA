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

// Counters
int Dracarys::NoCuts; 
int Dracarys::TriggerPathCut;
int Dracarys::aJetatLessCut;
int Dracarys::LeadingMuPtM3;

Dracarys::Dracarys(const edm::ParameterSet& iConfig):
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAlone>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  tok_jets_(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("objet"))),
  tok_met_(consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag>("obmet"))),
  tok_muons_(consumes<edm::View<pat::Muon> >(iConfig.getParameter<edm::InputTag>("obmuon")))
  //,histContainer_()
{
  //now do what ever initialization is needed
  usesResource("TFileService"); 
  // register to the TFileService
  edm::Service<TFileService> fs;
  //Create a TTree
  tree_ = fs->make<TTree>("VLFTree","VLFTree");
}


Dracarys::~Dracarys()
{
  //delete tree_;
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

   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);
   

   /*Handling Muons*/
   edm::Handle<edm::View<pat::Muon> > muons;
   iEvent.getByToken(tok_muons_, muons);
   /*Handling Jets*/
   edm::Handle<edm::View<pat::Jet> > jets;
   iEvent.getByToken(tok_jets_,jets);
   /*Handling MET*/   
   edm::Handle<edm::View<pat::MET> > mets;
   iEvent.getByToken(tok_met_,mets);
   const pat::MET &met = mets->front();

   ////////////////////////////

   //Cunting events
   Dracarys::NoCuts++;

   // Branches
   std::vector<XYZTLorentzVector> Bmuons;
   std::vector<double> Muon_charge, Combined_Iso;
   std::vector <bool> Muon_loose, Muon_medium, Muon_tight;

   //Tree Structure -> branches should be declared in decreasing size

   tree_->Branch("Muons",&Bmuons);
   tree_->Branch("Combined_iso_DeltaBetaPU",&Combined_Iso);
   tree_->Branch("Muon_charge",&Muon_charge);
   tree_->Branch("MuonLooseID",&Muon_loose);
   tree_->Branch("MuonMediumID",&Muon_medium);
   //tree_->Branch("MuonTightID",&Muon_tight);
   
   
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
	 //Cunting events pass trigger
	 Dracarys::TriggerPathCut++;
// 	 std::cout << "PASS" << std::endl;
// 	 std::cout <<"Number of muons: " << muons->size() <<std::endl;
// 	 std::cout <<"Number of jets: " << jets->size() <<std::endl;
// 	 if(mets->empty()){
// 	   std::cout <<"METs: 0" <<std::endl;
// 	 }else{
// 	   std::cout <<"METs: " << (*mets)[0].et() <<std::endl;
// 	 }

	 if( jets->size() > 0 ){
	   Dracarys::aJetatLessCut++;
	   if( muons->size() > 0 ){
	     // loop muon collection and fill histograms
	     /* at less a muon Pt>3 GeV*/
	     
	     bool flagLeadingMuPtM3=false;
	     for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
	       double MuonIso = (muon->pfIsolationR04().sumChargedHadronPt + max(0., muon->pfIsolationR04().sumNeutralHadronEt + muon->pfIsolationR04().sumPhotonEt - 0.5*muon->pfIsolationR04().sumPUPt))/muon->pt();
	       if( (muon->pt() > 3) && (MuonIso < 0.15) && (muon->isMediumMuon()))
		 flagLeadingMuPtM3=true;
	     }
 	     
 	     if ( flagLeadingMuPtM3 ){
	       Dracarys::LeadingMuPtM3++;
	       //	       std::cout <<"Number of muons: " << muons->size() <<std::endl;

	       //TTree Filling
	       for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
		 XYZTLorentzVector mu(muon->pt(), muon->eta(), muon->phi(), muon->energy());
		 std::cout <<"Muon Pt: " << mu.E() <<std::endl;
		 Bmuons.push_back(mu);
		 Muon_charge.push_back(muon->charge());
		 Combined_Iso.push_back((muon->pfIsolationR04().sumChargedHadronPt + max(0., muon->pfIsolationR04().sumNeutralHadronEt + muon->pfIsolationR04().sumPhotonEt - 0.5*muon->pfIsolationR04().sumPUPt))/muon->pt());
		 Muon_loose.push_back(muon->isLooseMuon()); 
		 Muon_medium.push_back(muon->isMediumMuon()); 
		 //Muon_tight.push_back(muon->);
	       }

	       for(edm::View<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
		 XYZTLorentzVector je(jet->pt(), jet->eta(), jet->phi(), jet->energy());
		 std::cout <<"Jet Pt: " << je.Px() <<std::endl;
		 // event.Jets.push_back(je);
	       }
	       
	       //Bmet.Et = met.pt();
	       //Bmet.Phi= 0;
	       //	       eventID. = ;
	       //	       eventID. = ;
	       
	       tree_->Fill();
	       Bmuons.clear();
	       
// 	       histContainer_["muons"]->Fill(muons->size() );
// 	       histContainer_["jets" ]->Fill(jets->size()  );
// 	       histContainer_["met"  ]->Fill(mets->empty() ? 0 : (*mets)[0].et());
	     }
	   }/*End cut at less a muon Pt>3 GeV*/
	 }/*End cut a jet at less*/       
       }
     }
     /*end See if path pass*/  
     
     
   }
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
Dracarys::beginJob()
{
 

  // book histograms:
  // histContainer_["muons"  ]=fs->make<TH1F>("muons",   "muon multiplicity",     10, 0,  10);
  // histContainer_["jets"   ]=fs->make<TH1F>("jets",    "jet multiplicity",      10, 0,  10);
  // histContainer_["met"    ]=fs->make<TH1F>("met",     "missing E_{T}",         20, 0, 500);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
Dracarys::endJob() 
{
  std::cout<< "NoCuts= "<< NoCuts <<endl;
  std::cout<< "TriggerPathCut= "<< TriggerPathCut <<endl;
  std::cout<< "aJetatLessCut= "<< aJetatLessCut <<endl;
  std::cout<< "LeadingMuPtM3= "<< LeadingMuPtM3 <<endl;

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
