#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <map>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include <TBranch.h>
#include <vector>

using namespace std;
using namespace edm;
using namespace math;

#ifndef DRACARYS_H
#define DRACARYS_H


class Dracarys : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
 public:
  /// Constructor
  explicit Dracarys(const edm::ParameterSet&);
 

  /// Destructor
  ~Dracarys();
  
  // Operations
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  

  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------                   
  /*Here declare the tokens*/
      
  /*Trigger*/
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAlone> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  /**/
  edm::EDGetTokenT<edm::View<pat::Jet> > tok_jets_;
  edm::EDGetTokenT<edm::View<pat::MET> >  tok_met_;
  edm::EDGetTokenT<edm::View<pat::Muon> > tok_muons_;
 
  /// histograms
  //  std::map<std::string,TH1F*> histContainer_;
  //Counters
  static int NoCuts; 
  static int TriggerPathCut;
  static int aJetatLessCut;
  static int LeadingMuPtM3;
  // TTree
  TTree* tree_;

  };
#endif
