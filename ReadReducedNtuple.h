//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 17 18:26:12 2017 by ROOT version 6.06/01
// from TTree HZZ4LeptonsAnalysisReduced/reduced ttree
// found on file: histos2e2mu_25ns/output_GluGluToZZTo4e_BackgroundOnly_13TeV_MCFM.root
//////////////////////////////////////////////////////////

#ifndef ReadReducedNtuple_h
#define ReadReducedNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ReadReducedNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           f_run;
   Int_t           f_lumi;
   Int_t           f_event;
   Float_t         f_weight;
   Float_t         f_int_weight;
   Float_t         f_pu_weight;
   Float_t         f_eff_weight;
   Float_t         f_lept1_pt;
   Float_t         f_lept1_eta;
   Float_t         f_lept1_phi;
   Float_t         f_lept1_charge;
   Float_t         f_lept1_pfx;
   Float_t         f_lept1_sip;
   Int_t           f_lept1_pdgid;
   Float_t         f_lept2_pt;
   Float_t         f_lept2_eta;
   Float_t         f_lept2_phi;
   Float_t         f_lept2_charge;
   Float_t         f_lept2_pfx;
   Float_t         f_lept2_sip;
   Int_t           f_lept2_pdgid;
   Float_t         f_lept3_pt;
   Float_t         f_lept3_eta;
   Float_t         f_lept3_phi;
   Float_t         f_lept3_charge;
   Float_t         f_lept3_pfx;
   Float_t         f_lept3_sip;
   Int_t           f_lept3_pdgid;
   Float_t         f_lept4_pt;
   Float_t         f_lept4_eta;
   Float_t         f_lept4_phi;
   Float_t         f_lept4_charge;
   Float_t         f_lept4_pfx;
   Float_t         f_lept4_sip;
   Int_t           f_lept4_pdgid;
   Float_t         f_iso_max;
   Float_t         f_sip_max;
   Float_t         f_Z1mass;
   Float_t         f_Z2mass;
   Float_t         f_angle_costhetastar;
   Float_t         f_angle_costheta1;
   Float_t         f_angle_costheta2;
   Float_t         f_angle_phi;
   Float_t         f_angle_phistar1;
   Float_t         f_pt4l;
   Float_t         f_eta4l;
   Float_t         f_mass4l;
   Float_t         f_mass4lErr;
   Float_t         f_njets_pass;
   Float_t         f_deltajj;
   Float_t         f_massjj;
   Float_t         f_D_jet;
   Float_t         f_jet1_pt;
   Float_t         f_jet1_eta;
   Float_t         f_jet1_phi;
   Float_t         f_jet1_e;
   Float_t         f_jet2_pt;
   Float_t         f_jet2_eta;
   Float_t         f_jet2_phi;
   Float_t         f_jet2_e;
   Float_t         f_D_bkg_kin;
   Float_t         f_D_bkg;
   Float_t         f_D_gg;
   Float_t         f_D_g4;
   Float_t         f_Djet_VAJHU;
   Float_t         f_pfmet;
   Float_t         f_genmet;
   Float_t         f_mT;
   Float_t         f_dphi;
   Int_t           f_category;
   Int_t           f_Ngood;
   Int_t           f_Nbjets;

   // List of branches
   TBranch        *b_f_run;   //!
   TBranch        *b_f_lumi;   //!
   TBranch        *b_f_event;   //!
   TBranch        *b_f_weight;   //!
   TBranch        *b_f_int_weight;   //!
   TBranch        *b_f_pu_weight;   //!
   TBranch        *b_f_eff_weight;   //!
   TBranch        *b_f_lept1_pt;   //!
   TBranch        *b_f_lept1_eta;   //!
   TBranch        *b_f_lept1_phi;   //!
   TBranch        *b_f_lept1_charge;   //!
   TBranch        *b_f_lept1_pfx;   //!
   TBranch        *b_f_lept1_sip;   //!
   TBranch        *b_f_lept1_pdgid;   //!
   TBranch        *b_f_lept2_pt;   //!
   TBranch        *b_f_lept2_eta;   //!
   TBranch        *b_f_lept2_phi;   //!
   TBranch        *b_f_lept2_charge;   //!
   TBranch        *b_f_lept2_pfx;   //!
   TBranch        *b_f_lept2_sip;   //!
   TBranch        *b_f_lept2_pdgid;   //!
   TBranch        *b_f_lept3_pt;   //!
   TBranch        *b_f_lept3_eta;   //!
   TBranch        *b_f_lept3_phi;   //!
   TBranch        *b_f_lept3_charge;   //!
   TBranch        *b_f_lept3_pfx;   //!
   TBranch        *b_f_lept3_sip;   //!
   TBranch        *b_f_lept3_pdgid;   //!
   TBranch        *b_f_lept4_pt;   //!
   TBranch        *b_f_lept4_eta;   //!
   TBranch        *b_f_lept4_phi;   //!
   TBranch        *b_f_lept4_charge;   //!
   TBranch        *b_f_lept4_pfx;   //!
   TBranch        *b_f_lept4_sip;   //!
   TBranch        *b_f_lept4_pdgid;   //!
   TBranch        *b_f_iso_max;   //!
   TBranch        *b_f_sip_max;   //!
   TBranch        *b_f_Z1mass;   //!
   TBranch        *b_f_Z2mass;   //!
   TBranch        *b_f_angle_costhetastar;   //!
   TBranch        *b_f_angle_costheta1;   //!
   TBranch        *b_f_angle_costheta2;   //!
   TBranch        *b_f_angle_phi;   //!
   TBranch        *b_f_angle_phistar1;   //!
   TBranch        *b_f_pt4l;   //!
   TBranch        *b_f_eta4l;   //!
   TBranch        *b_f_mass4l;   //!
   TBranch        *b_f_mass4lErr;   //!
   TBranch        *b_f_njets_pass;   //!
   TBranch        *b_f_deltajj;   //!
   TBranch        *b_f_massjj;   //!
   TBranch        *b_f_D_jet;   //!
   TBranch        *b_f_jet1_pt;   //!
   TBranch        *b_f_jet1_eta;   //!
   TBranch        *b_f_jet1_phi;   //!
   TBranch        *b_f_jet1_e;   //!
   TBranch        *b_f_jet2_pt;   //!
   TBranch        *b_f_jet2_eta;   //!
   TBranch        *b_f_jet2_phi;   //!
   TBranch        *b_f_jet2_e;   //!
   TBranch        *b_f_D_bkg_kin;   //!
   TBranch        *b_f_D_bkg;   //!
   TBranch        *b_f_D_gg;   //!
   TBranch        *b_f_D_g4;   //!
   TBranch        *b_f_Djet_VAJHU;   //!
   TBranch        *b_f_pfmet;   //!
   TBranch        *b_f_genmet;   //!
   TBranch        *b_f_mT;   //!
   TBranch        *b_f_dphi;   //!
   TBranch        *b_f_category;   //!
   TBranch        *b_f_Ngood;   //!
   TBranch        *b_f_Nbjets;   //!

   ReadReducedNtuple(TTree *tree=0);
   virtual ~ReadReducedNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ReadReducedNtuple_cxx
ReadReducedNtuple::ReadReducedNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("histos2e2mu_25ns/output_GluGluToZZTo4e_BackgroundOnly_13TeV_MCFM.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("histos2e2mu_25ns/output_GluGluToZZTo4e_BackgroundOnly_13TeV_MCFM.root");
      }
      f->GetObject("HZZ4LeptonsAnalysisReduced",tree);

   }
   Init(tree);
}

ReadReducedNtuple::~ReadReducedNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadReducedNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadReducedNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ReadReducedNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("f_run", &f_run, &b_f_run);
   fChain->SetBranchAddress("f_lumi", &f_lumi, &b_f_lumi);
   fChain->SetBranchAddress("f_event", &f_event, &b_f_event);
   fChain->SetBranchAddress("f_weight", &f_weight, &b_f_weight);
   fChain->SetBranchAddress("f_int_weight", &f_int_weight, &b_f_int_weight);
   fChain->SetBranchAddress("f_pu_weight", &f_pu_weight, &b_f_pu_weight);
   fChain->SetBranchAddress("f_eff_weight", &f_eff_weight, &b_f_eff_weight);
   fChain->SetBranchAddress("f_lept1_pt", &f_lept1_pt, &b_f_lept1_pt);
   fChain->SetBranchAddress("f_lept1_eta", &f_lept1_eta, &b_f_lept1_eta);
   fChain->SetBranchAddress("f_lept1_phi", &f_lept1_phi, &b_f_lept1_phi);
   fChain->SetBranchAddress("f_lept1_charge", &f_lept1_charge, &b_f_lept1_charge);
   fChain->SetBranchAddress("f_lept1_pfx", &f_lept1_pfx, &b_f_lept1_pfx);
   fChain->SetBranchAddress("f_lept1_sip", &f_lept1_sip, &b_f_lept1_sip);
   fChain->SetBranchAddress("f_lept1_pdgid", &f_lept1_pdgid, &b_f_lept1_pdgid);
   fChain->SetBranchAddress("f_lept2_pt", &f_lept2_pt, &b_f_lept2_pt);
   fChain->SetBranchAddress("f_lept2_eta", &f_lept2_eta, &b_f_lept2_eta);
   fChain->SetBranchAddress("f_lept2_phi", &f_lept2_phi, &b_f_lept2_phi);
   fChain->SetBranchAddress("f_lept2_charge", &f_lept2_charge, &b_f_lept2_charge);
   fChain->SetBranchAddress("f_lept2_pfx", &f_lept2_pfx, &b_f_lept2_pfx);
   fChain->SetBranchAddress("f_lept2_sip", &f_lept2_sip, &b_f_lept2_sip);
   fChain->SetBranchAddress("f_lept2_pdgid", &f_lept2_pdgid, &b_f_lept2_pdgid);
   fChain->SetBranchAddress("f_lept3_pt", &f_lept3_pt, &b_f_lept3_pt);
   fChain->SetBranchAddress("f_lept3_eta", &f_lept3_eta, &b_f_lept3_eta);
   fChain->SetBranchAddress("f_lept3_phi", &f_lept3_phi, &b_f_lept3_phi);
   fChain->SetBranchAddress("f_lept3_charge", &f_lept3_charge, &b_f_lept3_charge);
   fChain->SetBranchAddress("f_lept3_pfx", &f_lept3_pfx, &b_f_lept3_pfx);
   fChain->SetBranchAddress("f_lept3_sip", &f_lept3_sip, &b_f_lept3_sip);
   fChain->SetBranchAddress("f_lept3_pdgid", &f_lept3_pdgid, &b_f_lept3_pdgid);
   fChain->SetBranchAddress("f_lept4_pt", &f_lept4_pt, &b_f_lept4_pt);
   fChain->SetBranchAddress("f_lept4_eta", &f_lept4_eta, &b_f_lept4_eta);
   fChain->SetBranchAddress("f_lept4_phi", &f_lept4_phi, &b_f_lept4_phi);
   fChain->SetBranchAddress("f_lept4_charge", &f_lept4_charge, &b_f_lept4_charge);
   fChain->SetBranchAddress("f_lept4_pfx", &f_lept4_pfx, &b_f_lept4_pfx);
   fChain->SetBranchAddress("f_lept4_sip", &f_lept4_sip, &b_f_lept4_sip);
   fChain->SetBranchAddress("f_lept4_pdgid", &f_lept4_pdgid, &b_f_lept4_pdgid);
   fChain->SetBranchAddress("f_iso_max", &f_iso_max, &b_f_iso_max);
   fChain->SetBranchAddress("f_sip_max", &f_sip_max, &b_f_sip_max);
   fChain->SetBranchAddress("f_Z1mass", &f_Z1mass, &b_f_Z1mass);
   fChain->SetBranchAddress("f_Z2mass", &f_Z2mass, &b_f_Z2mass);
   fChain->SetBranchAddress("f_angle_costhetastar", &f_angle_costhetastar, &b_f_angle_costhetastar);
   fChain->SetBranchAddress("f_angle_costheta1", &f_angle_costheta1, &b_f_angle_costheta1);
   fChain->SetBranchAddress("f_angle_costheta2", &f_angle_costheta2, &b_f_angle_costheta2);
   fChain->SetBranchAddress("f_angle_phi", &f_angle_phi, &b_f_angle_phi);
   fChain->SetBranchAddress("f_angle_phistar1", &f_angle_phistar1, &b_f_angle_phistar1);
   fChain->SetBranchAddress("f_pt4l", &f_pt4l, &b_f_pt4l);
   fChain->SetBranchAddress("f_eta4l", &f_eta4l, &b_f_eta4l);
   fChain->SetBranchAddress("f_mass4l", &f_mass4l, &b_f_mass4l);
   fChain->SetBranchAddress("f_mass4lErr", &f_mass4lErr, &b_f_mass4lErr);
   fChain->SetBranchAddress("f_njets_pass", &f_njets_pass, &b_f_njets_pass);
   fChain->SetBranchAddress("f_deltajj", &f_deltajj, &b_f_deltajj);
   fChain->SetBranchAddress("f_massjj", &f_massjj, &b_f_massjj);
   fChain->SetBranchAddress("f_D_jet", &f_D_jet, &b_f_D_jet);
   fChain->SetBranchAddress("f_jet1_pt", &f_jet1_pt, &b_f_jet1_pt);
   fChain->SetBranchAddress("f_jet1_eta", &f_jet1_eta, &b_f_jet1_eta);
   fChain->SetBranchAddress("f_jet1_phi", &f_jet1_phi, &b_f_jet1_phi);
   fChain->SetBranchAddress("f_jet1_e", &f_jet1_e, &b_f_jet1_e);
   fChain->SetBranchAddress("f_jet2_pt", &f_jet2_pt, &b_f_jet2_pt);
   fChain->SetBranchAddress("f_jet2_eta", &f_jet2_eta, &b_f_jet2_eta);
   fChain->SetBranchAddress("f_jet2_phi", &f_jet2_phi, &b_f_jet2_phi);
   fChain->SetBranchAddress("f_jet2_e", &f_jet2_e, &b_f_jet2_e);
   fChain->SetBranchAddress("f_D_bkg_kin", &f_D_bkg_kin, &b_f_D_bkg_kin);
   fChain->SetBranchAddress("f_D_bkg", &f_D_bkg, &b_f_D_bkg);
   fChain->SetBranchAddress("f_D_gg", &f_D_gg, &b_f_D_gg);
   fChain->SetBranchAddress("f_D_g4", &f_D_g4, &b_f_D_g4);
   fChain->SetBranchAddress("f_Djet_VAJHU", &f_Djet_VAJHU, &b_f_Djet_VAJHU);
   fChain->SetBranchAddress("f_pfmet", &f_pfmet, &b_f_pfmet);
   fChain->SetBranchAddress("f_genmet", &f_genmet, &b_f_genmet);
   fChain->SetBranchAddress("f_mT", &f_mT, &b_f_mT);
   fChain->SetBranchAddress("f_dphi", &f_dphi, &b_f_dphi);
   fChain->SetBranchAddress("f_category", &f_category, &b_f_category);
   fChain->SetBranchAddress("f_Ngood", &f_Ngood, &b_f_Ngood);
   fChain->SetBranchAddress("f_Nbjets", &f_Nbjets, &b_f_Nbjets);
   Notify();
}

Bool_t ReadReducedNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadReducedNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadReducedNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadReducedNtuple_cxx
