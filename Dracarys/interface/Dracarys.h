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
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include <TBranch.h>
#include <TLorentzVector.h>
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
  virtual void Clean();

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
  edm::EDGetTokenT<reco::VertexCollection> tok_vertex_;
  edm::EDGetTokenT<std::vector< PileupSummaryInfo > > tok_pileup_;
  edm::EDGetTokenT<edm::View<pat::Jet> > tok_jets_;
  edm::EDGetTokenT<pat::METCollection> tok_met_;
  edm::EDGetTokenT<edm::View<pat::Muon> > tok_muons_;
 
  /// histograms
  //  std::map<std::string,TH1F*> histContainer_;
  //Counters
  static int NoCuts; 
  static int TriggerPathCut;
  static int GoodVertex;
  static int aJetatLessCut;
  static int LeadingMuPtM3;
  static int MissingETCut;
  static int BasicJetsCut;
  static int bJetsCut;
  static int MuonMetMTCut;
  //Is data boolean
  bool is_data_;
  //determine if event passes triggers
  bool isTrigger_;
  bool isTriggerToo_;
  string TriggerPath1_;
  string TriggerPath2_;
  //Debugging option boolean
  bool debug_;
  //Cuts
  int Pvtx_ndof_min_;
  double Pvtx_vtx_max_;
  double Pvtx_vtxdxy_max_;
  double MinMuonPt_;
  double MaxMuonPt_;
  double MuonIso_;
  int MuonID_;
  int MinNMuons_;
  int MaxNMuons_;
  double MinMET_;
  double MinJetPt_;
  double MaxJetEta_;
  int MinNJets_;
  int MaxNJets_;
  double bJetTag_;
  double MinbJetPt_;
  double MaxbJetEta_;
  int MinNbJets_;
  int MaxNbJets_;
  double MinMTMuonMet_;
  double MaxMTMuonMet_;
  // TTree
  TTree* tree_;

  //Analysis variables
  std::vector<XYZTLorentzVector> AnaMuons;
  std::vector<XYZTLorentzVector> AnaJets;
  XYZTLorentzVector MET;
  int Nvertices, NObservedInTimePUVertices, NTruePUInteractions;
  std::vector<double> Muon_charge, Combined_Iso;
  std::vector <bool> Muon_loose, Muon_medium, Muon_tight;
  std::vector<double> bJetDiscriminator;
  double MT_LeadingMuon_MET;
  int NMuons;
  int NJets, NbJets;

  };
#endif
