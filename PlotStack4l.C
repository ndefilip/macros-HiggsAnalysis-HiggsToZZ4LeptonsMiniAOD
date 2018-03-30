#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "ZZStyle.C"
#include "TFile.h"
#include "TColor.h"
#include "TPaveText.h"
#include "THStack.h"
#include "TGraphAsymmErrors.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"
#include "TMath.h"
#include "TList.h"
#include "TSystem.h"
#include <libgen.h>

using namespace std;

// Usage:
// .include /cmshome/nicola/tmp/test/Paper/last/last/CMSSW_5_3_9/src
//  gSystem->Load("libHiggsHiggs_CS_and_Width.so")
// .L PlotStack4l.C+
// PlotStack4l()

class PlotStack4l{
  
public: 
  PlotStack4l();
  void plotm4l(std::string);
  void setSamplesNames4l();
  void printnumbers(char*, TH1F*);
  /*void createdatacards(
		       float Higgsm, float channel, float energy, 
		       float masslow, float masshigh,
		       float ggH, float qqH, float WH, float ZH, float ttH, 
		       float bkg_qqzz, float bkg_ggzz, float bkg_zjets
		       );*/
  //void getMassWindow(float Higgsm);

private:
  std::vector<string> Vdatasetnamebkg,Vdatasetnamesig,Vdatasetnamedata,Vdatasetnamebkgdata;
  std::vector<string> Vlabelbkg,Vlabelsig,Vlabeldata,Vlabelbkgdata;
  std::vector<float> Vxsectionbkg,Vxsectionsig,Vxsectiondata,Vxsectionbkgdata;
  std::vector<Color_t> Vcolorbkg, Vcolorsig/*, Vcolordata*/;

  double Nbins;
  double Xmin;
  double Xmax;
  int nRebin,nRebinZ_X;
  double Ymax;
  bool useLogY,useLogX;
  bool useDYJets,useDYJetsFromData;
  bool useRatio;
  std::string histosdir; 
  std::string inputfile;
  std::string whichchannel,whichenergy,whichsample;
  char histotitle[500];
  ofstream outputyields;
  float errorZZ,errorH125,errorH126,errorH200,errorH350,errorH500,errorH800;
  TSystem LoadLib;
public:
  //float Higgsm, channel, energy, masslow, masshigh;
  //float ggH, qqH, WH, ZH, ttH, bkg_qqzz, bkg_ggzz, bkg_zjets;

};

PlotStack4l::PlotStack4l(){
  //TSystem LoadLib;
  //LoadLib.Load("/cmshome/nicola/slc6/MonoHiggs/Analysis13TeV/CMSSW_7_2_0/lib/slc6_amd64_gcc481/libHiggsHiggs_CS_and_Width.so");
  //getMassWindow(500.);
    
  //inputfile="filelist_4l_2016_Spring16_AN_Bari_miniaod_m4l_MC.txt";
  //inputfile="filelist_4e_2016_Spring16_AN_Bari_miniaod_met_step3.txt";
  //inputfile="filelist_2e2mu_2016_Spring16_AN_Bari_miniaod.txt";
  inputfile="filelist_4l_2016_Spring16_AN_Bari_miniaod_met_step8.txt";
  //inputfile="test4mu_13TeV.txt";

  setSamplesNames4l(); 
  cout << "\t Analysing samples for " << whichchannel << " analysis" << endl; 


  //WARNING: depending on histolabel, modify the declaration and the settings of hframe below
  //also choose a sensible value for nRebin

  //std::string histolabel = "hPUvertices";    // numPU
  //std::string histolabel = "hPUvertices_ReWeighted";    // numPY reweighted

  // Step 0
  // std::string histolabel = "hPFMET_0"; // PFMET
  
  // Step 1  loose iso
  //std::string histolabel = "hPFMET_1"; // PFMET                                                                               

  //std::string histolabel = "hPtLep_0"; // pt not cuts (only pt>5)
  //std::string histolabel = "hIsoLep_0"; // PF isol _ delta B
  //std::string histolabel = "hSipLep_0"; // SIP
  //std::string histolabel = "hDxyLep_0"; // d_xy
  //std::string histolabel = "hDzLep_0"; // d_z
  //std::string histolabel = "hMuHitLep_0"; // n. muon hits
  //std::string histolabel = "hPxHitLep_0"; // n. pixel hits
  //std::string histolabel = "hTKLayLep_0"; // n. tracker layers
  //std::string histolabel = "hTKIsoLep_0"; // track isolation = sumpT

  // ****** Standard candle: Z1 selection: step 3 ******

  // std::string histolabel = "hMZ_3";    // Z mass 
  //std::string histolabel = "hMZBB_3";    // Z mass 
  //std::string histolabel = "hMZEE_3";    // Z mass 
  //std::string histolabel = "hPtZ_3"; // Z pt 
  //std::string histolabel = "hYZ_3"; // Z Y

  //std::string histolabel = "hPtLep_3";    // pT lepton from Z 
  //std::string histolabel = "hIsoLep_3";    // isolation of lowest pT lepton from Z 
  //std::string histolabel = "hSipLep_3";  // sip the lowest pT lepton from Z
  //std::string histolabel = "hIpLep_3";   // IP of the lowest pT lepton from Z
  //std::string histolabel = "hIpErLep_3";   // Iperror of the lowest pT lepton from Z

  //std::string histolabel = "hIso_3";    // worst isolation value of lepton not coming from Z1
  //std::string histolabel = "hSip_3";  // worst sip value of lepton not coming from Z1
  //std::string histolabel = "hIp_3";   // worst IP value of lepton not coming from Z1

  //std::string histolabel = "hMjj_3"; // mass of di-jet for VBF analysis
  //std::string histolabel = "hDjj_3"; // delta eta between jets for VBF analysis
  //std::string histolabel = "hVD_3"; // Fisher discriminant for VBF analysis

  //std::string histolabel = "hPFMET_3"; // PFMET
  //std::string histolabel = "hLogLinXPFMET_3"; //PF MET log
  // ****** After cuts on ,Z1, mZ2 and pT >20/10: step 5 ******

  //std::string histolabel = "hMZ1_5";    // Z1 mass   
  //std::string histolabel = "hMZ2_5";    // Z2 mass 
  //std::string histolabel = "hM4l_5";    // 4l mass 

  //std::string histolabel = "hIso_5";    // worst isolation 
  //std::string histolabel = "hSip_5";  // worst sip 
  //std::string histolabel = "hIp_5";   // worst IP


  // After full selection
  //std::string histolabel = "hMZ1_7";    // Z1 mass   
  //std::string histolabel = "hM4l_7"; // 4l mass after full selection but m4l > 70

  //std::string histolabel = "hM4l_8"; // 4l mass after full selection
  //std::string histolabel = "hM4l_9"; // 4l mass after full selection
  
  //std::string histolabel = "hM4l_8_100_800"; // 4l mass in the range [100,800] after full selection
  //std::string histolabel = "hMZ1_8"; // Z1 mass after full selection
  //std::string histolabel = "hMZ2_8"; // Z2 mass after full selection
  //std::string histolabel = "hMZ1_noFSR_8"; // Z1 mass after full selection without FSR recovery
  //std::string histolabel = "hMZ2_noFSR_8"; // Z2 mass after full selection without FSR recovery
  //std::string histolabel = "hPtZ1_8"; // Z1 pt after full selection
  //std::string histolabel = "hPtZ2_8"; // Z2 pt after full selection
  //std::string histolabel = "hYZ1_8"; // Z1 rapidity after full selection
  //std::string histolabel = "hYZ2_8"; // Z2 rapidity after full selection
  //std::string histolabel = "hIso_8"; // worst isolated lepton: isolation value after full selection
  //std::string histolabel = "hSip_8"; // worst sip lepton: sip value after full selection
  //std::string histolabel = "hMELA_8"; // MELA discriminant after full selection 
  //std::string histolabel = "hPFMET_8"; // PFMET
  //std::string histolabel = "hLogLinXPFMET_8"; //PF MET log
  //std::string histolabel = "hM4l_T_8"; // Transverse mass
  //std::string histolabel = "hLogLinXM4l_T_8"; //PF MET log
  //std::string histolabel = "DPHI_8"; // DeltaPhi - 4l + MET  

  //std::string histolabel = "hDjj_8"; // delta eta between jets for VBF analysis
  //std::string histolabel = "hMjj_8"; // dimass between jets for VBF analysis

  //std::string histolabel = "hNbjets"; // Number of b-jets
  //std::string histolabel = "hNgood"; // Number of good leptons  

  //std::string histolabel = "hLogLinXPFMET_8a"; //PF MET log
  std::string histolabel = "hLogLinXPFMET_8b"; //PF MET log                                                                                                                              
  //std::string histolabel = "hNbjets_8a"; // Number of b-jets
  //std::string histolabel = "hNgood_8a"; // Number of good leptons  

  //std::string histolabel = "hNbjets_9"; // Number of b-jets
  //std::string histolabel = "hNgood_9"; // Number of good leptons  
  //std::string histolabel = "hPFMET_10";
  //std::string histolabel = "hLogLinXPFMET_10"; //PF MET log 

  //std::string histolabel = "hPFMET_12";
  //std::string histolabel = "hLogLinXPFMET_12"; //PF MET log

  useLogY = true;
  useLogX = false;

  useRatio = true;

  useDYJets=true;
  useDYJetsFromData=false;
  
  nRebin=1;
  std::cout << "Histogram label is= " << histolabel << std::endl;
  
  // Final yields
  system("mkdir plots");

  Char_t yieldsOUT[500];
  sprintf(yieldsOUT,"plots/yields_%s_%s.txt",whichchannel.c_str(),whichenergy.c_str());
  if (histolabel.find("hM4l_9")<10 ) {
    cout << "Opening a file for final numbers= " << yieldsOUT << endl;
    outputyields.open(yieldsOUT);
  }
  
  // Execute the analysis
  errorZZ=0.,errorH125=0.,errorH126=0.,errorH200=0.,errorH350=0.,errorH500=0.,errorH800=0.;
  plotm4l(histolabel);
  
  // close file for final yields
  if (histolabel.find("hM4l_9")<10 ) outputyields.close();

}

void PlotStack4l::plotm4l(std::string histlabel){
  
  TStyle * style = getStyle("ZZ");
  //style->SetMarkerSize(0.8);
  style->cd();
  style->SetNdivisions(508, "X");
  style->SetNdivisions(508, "Y");
  style->SetMarkerSize(0.8);

//   double ytitleOffset = 1.36;
//   double xtitleOffset = 1.18;
//   double labelSize = 0.05;
//   double titleSize = 0.05;
//   double lineWidth = 2;
  
  TCanvas *c1 ;
  if (useRatio==true)  c1=new TCanvas("c1","c1",600,800);  
  else  c1=new TCanvas("c1","c1",600,600);

  c1->cd();
  c1->SetTicks(1,1);

  //  ratioPad->cd();

  // TString lumist="5.2 fb^{-1}";
//   TPaveText *ll = new TPaveText(0.15, 0.95, 0.95, 0.99, "NDC");
//   ll->SetTextSize(0.03);
//   ll->SetTextFont(42);
//   ll->SetFillColor(0);
//   ll->SetBorderSize(0);
//   ll->SetMargin(0.01);
//   ll->SetTextAlign(12); // align left
//   TString text = "CMS Preliminary 2011";
//   ll->AddText(0.01,0.5,text);
//   text = "#sqrt{s} = 7 TeV  L = ";
//   text = text + lumist;
//   //  ll->SetTextAlign(32); // align right
//   ll->AddText(0.65, 0.6, text);
 

  TPaveText *ll = new TPaveText(0.15, 0.95, 0.95, 0.99, "NDC");
  ll->SetTextSize(0.027);
  ll->SetTextFont(42);
  ll->SetFillColor(0);
  ll->SetBorderSize(0);
  ll->SetMargin(0.01);
  ll->SetTextAlign(12); // align left
  TString text = "CMS Preliminary";
  //TString text = "CMS";
  ll->AddText(0.01,0.5,text);
  cout << "Energy= " << whichenergy << endl;
  if (whichenergy.find("RunI")<50) {
    text = "#sqrt{s} = 7 TeV, L = 5.05 fb^{-1} ; #sqrt{s} = 8 TeV, L = 19.71 fb^{-1}" ;
    ll->AddText(0.3, 0.6, text);
  }
  else if (whichenergy.find("7TeV")<50) {
    text = "#sqrt{s} = 7 TeV, L = 5.05 fb^{-1}" ;
    ll->AddText(0.65, 0.6, text);
  }
  else if (whichenergy.find("8TeV")<50) {
    text = "#sqrt{s} = 8 TeV, L = 19.71 fb^{-1}" ;
    ll->AddText(0.65, 0.6, text);
  }
  else if (whichenergy.find("13TeV")<50) {
    text = "#sqrt{s} = 13 TeV, L = 35.9 fb^{-1}" ;
    //text = "#sqrt{s} = 13 TeV, L = 14.77 fb^{-1}" ;
    ll->AddText(0.65, 0.6, text);
  }
  //ll->Draw();



  TLegend *leg0 = new TLegend(0.6,0.40,0.8,0.90,NULL,"brNDC");
  leg0->SetTextSize(0.020);
  leg0->SetLineColor(0);
  leg0->SetLineWidth(1);
  leg0->SetFillColor(kWhite);
  leg0->SetBorderSize(0);
 
  TLegend* legend = new TLegend( 0.55, 0.67, 0.9, 0.92);
  //TLegend* legend = new TLegend( 0.55, 0.45, 0.9, 0.72);                                                                      

  legend->SetFillColor(kWhite);
  legend->SetTextSize(0.020);


//   TLegend *leg1 = new TLegend(0.25,0.80,0.4,0.9,NULL,"brNDC");
//   leg1->SetTextSize(0.030);
//   leg1->SetLineColor(0);
//   leg1->SetLineWidth(1);
//   leg1->SetFillColor(kWhite);
//   leg1->SetBorderSize(0);
  
//   Color_t redBgColor = kGreen-5;
  Color_t ZZBgColor = kAzure-9;
//   Color_t h200Color = kOrange;
//   Color_t h350Color = kRed+1;
//   Color_t h400Color = kRed;
  



  if(useLogY) c1->SetLogy(1);
  else        c1->SetLogy(0);

  if(useLogX) c1->SetLogx(1);
  else        c1->SetLogx(0);

  
  cout << "Vdatasetnamedata " <<  Vdatasetnamedata.size() << endl;

  TFile *ff=NULL; 
 
  if(Vdatasetnamedata.size()>0)
    ff = TFile::Open(Vdatasetnamedata.at(0).c_str());  // just a random file, to determine the binning
  else if(Vdatasetnamebkg.size()>0)  
    ff = TFile::Open(Vdatasetnamebkg.at(0).c_str());  
  else if(Vdatasetnamesig.size()>0)  
    ff = TFile::Open(Vdatasetnamesig.at(0).c_str());  
 
  TH1F *hfourlepbestmass_4l_afterSel_new = (TH1F*)ff->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new"*/);

  Nbins = hfourlepbestmass_4l_afterSel_new->GetNbinsX() / nRebin;
  Xmin  = hfourlepbestmass_4l_afterSel_new->GetXaxis()->GetXmin();
  Xmax  = hfourlepbestmass_4l_afterSel_new->GetXaxis()->GetXmax() ;
  Ymax  = hfourlepbestmass_4l_afterSel_new->GetBinContent(hfourlepbestmass_4l_afterSel_new->GetMaximumBin()) * 580.;
  cout << "NBinsX= " << Nbins << " Ymax = " << Ymax << endl;

  // logaritmic bin width                                                                                                                                              
  const int NMBINS = Nbins;
  const double MMIN = Xmin, MMAX = Xmax;
  double logMbins[NMBINS+1];
  cout << "NMBinsX= " << NMBINS << endl;

  if (histlabel.find("hLogX")<10 ){
    for (int ibin = 0; ibin <= NMBINS; ibin++) {
      logMbins[ibin] = exp(log(MMIN) + (log(MMAX)-log(MMIN))*ibin/NMBINS);
      cout << logMbins[ibin] << endl;
    }
  }
  else if (histlabel.find("hLogLinX")<10 ) {
  	//logMbins[6]={0.,25.,50.,200., 500.,1000.};
  	for (int ibin = 0; ibin <= NMBINS; ibin++) {
  		logMbins[ibin]=hfourlepbestmass_4l_afterSel_new->GetBinLowEdge(ibin+1);
  	}
  }

  TH2F *hframe=NULL,*hframe2=NULL;
 
  hframe= new TH2F("hframe","hframe",80,70.,1000.,500,5.,700.);// 4l analysis mass nrebin=10 GeV
  hframe2= new TH2F("hframe2","hframe2",80,70.,1000.,1000, 0.5, 20.);// 4l analysis mass

  if (histlabel.find("hPFMET_0")<10){
    hframe= new TH2F("hframe","hframe",5000, 0., 5000., 1000, 0.00001, 10000000000000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0., 1000., 1000, 0.5, 2.);// PFMET
  }

  if (histlabel.find("hPtLep_0")<10){
    hframe= new TH2F("hframe","hframe",80,5.,200.,500,0.01,10000000.);// pT  
    hframe2= new TH2F("hframe2","hframe2",80,5.,200.,500, 0.5, 2.);// pT     
  }

  if (histlabel.find("hIsoLep_0")<10){
    hframe= new TH2F("hframe","hframe",80,0.,10.,500,0.01,10000000.);// Isolation   
    hframe2= new TH2F("hframe2","hframe2",80,0.,10.,500, 0.5, 2.);// Isolation     
  }
  
  if (histlabel.find("hTKIsoLep_0")<10){
    hframe= new TH2F("hframe","hframe",80,0.,10.,500,0.01,10000000.);// Tracker Isolation
    hframe2= new TH2F("hframe2","hframe2",80,0.,10.,500, 0.5, 2.);// Tk Isolation          
  }

  if (histlabel.find("hPFMET_1")<10 || histlabel.find("hLogLinXPFMET_1")<10 ){
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.00001, 100000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0., 1000., 1000, 0.5, 2.);// PFMET
  }

  if (histlabel.find("hM4l_7")<10 && 
      (whichchannel.find("4e")<20 || whichchannel.find("4#mu")<20 || whichchannel.find("2e2#mu")<20)){
    //hframe= new TH2F("hframe","hframe",80,70.,270.,500,0.004,42.);// 4l analysis mass nrebin=2 GeV
    if (!useLogY)  hframe= new TH2F("hframe","hframe",80,70.,300.,500,0.0004,42.);
    else hframe= new TH2F("hframe","hframe",80,70.,300.,500,0.0004,100000.);
    hframe2= new TH2F("hframe2","hframe2",6000, 70., 300., 1000, 0.5, 1.5);// 
  }
  if (histlabel.find("hM4l_7")<10 && whichchannel.find("4l")<20){
    if (!useLogY)  hframe= new TH2F("hframe","hframe",80,70.,300.,500,0.004,110.);// 4l analysis mass nrebin=3
    else hframe= new TH2F("hframe","hframe",80,70.,300.,500,0.0004,300.);
    hframe2= new TH2F("hframe2","hframe2",6000, 70., 300., 1000, 0.5, 1.5);// 
  }

  if (histlabel.find("hM4l_8")<10 && (whichchannel.find("4l")<20)){
    hframe= new TH2F("hframe","hframe",80,70.,182.,500,0.00000004,350000000.);// 4l analysis mass nrebin=3
    hframe2= new TH2F("hframe2","hframe2",6000, 70., 182., 1000, 0.5, 2.);// 
  }


  if (histlabel.find("hM4l_9")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,70.,182.,500,0.000004,35.);// 4l analysis mass nrebin=3
    hframe2= new TH2F("hframe2","hframe2",6000, 70., 182., 1000, 0.5, 2.);// 
  }
  

  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,2600000.);// mZ1 ee/mumu
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee/mumu
  
  if (histlabel.find("hMZ_3")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.01,8000.);// mZ1 mumu
    hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 mumu
  }
  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,400000.);// mZ1 mumu  7TeV
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 mumu 7TeV
  
  if (histlabel.find("hMZ_3")<10 && whichchannel.find("4e")<20){
    hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,15000.);// mZ1 ee                                       
    hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee
  }

  if (histlabel.find("hMZ_3")<10 && whichchannel.find("2e2#mu")<20){
    hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,20000.);// mZ1 ee/mumu  
    hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee/mumu
  }

   if (histlabel.find("hMZ_3")<10 && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,20000.);// mZ1 4l
    hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 4l
  }


  if (histlabel.find("hPtLep_3")<10){
    hframe= new TH2F("hframe","hframe",80,5.,300.,500,0.001,10000.);// pT                                          
    hframe2= new TH2F("hframe2","hframe2",80,5.,200.,500, 0.5, 2.);// pT                                           
  }
  
  if (histlabel.find("hIsoLep_3")<10){
    hframe= new TH2F("hframe","hframe",80,0.,5.,500,0.001,100000.);// Isolation                                    
    hframe2= new TH2F("hframe2","hframe2",80,0.,5.,500, 0.5, 2.);// Isolation                                      
  }

   if (histlabel.find("hSipLep_3")<10){
    hframe= new TH2F("hframe","hframe",600, 0., 5., 1000, 0.0004, 1000000000.);// sip
    hframe2= new TH2F("hframe2","hframe2",6000, 0., 5., 1000, 0.5, 2.);// sip
  }
  

  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,1100000.);// mZ1 ee
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee
  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,700000.);// mZ1 ee BB
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee BB
  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,100000.);// mZ1 ee EE
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee EE
  
  //hframe= new TH2F("hframe","hframe",80,60.,120.,500,0.4,300000.);// mZ1 ee 7TeV
  //hframe2= new TH2F("hframe2","hframe2",6000, 60., 120., 1000, 0.5, 2.);// mZ1 ee 7TeV

  if (histlabel.find("hMjj_3")<10){
    hframe= new TH2F("hframe","hframe",600,20.,500.,600,0.0004,10E7);//mass jet jet
    hframe2= new TH2F("hframe2","hframe2",6000, 20., 500., 1000, 0.5, 2.);// mass jet jet
  }

  if (histlabel.find("hDjj_3")<10){
    hframe= new TH2F("hframe","hframe",600,0.,10.,600,0.0004,10E7);//delta eta jet jet
    hframe2= new TH2F("hframe2","hframe2",600, 0., 10., 1000, 0.5, 2.);// delta eta jet jet
  }

  if (histlabel.find("hVD_3")<10){
    hframe= new TH2F("hframe","hframe",600,0.,2.,600,4E-4,5E11);// fisher
    hframe2= new TH2F("hframe2","hframe2",600, 0., 2., 1000, 0.5, 2.);// fisher
  }

  // hframe= new TH2F("hframe","hframe",Nbins*nRebin, Xmin, Xmax, Nbins*nRebin, 0.0004, Ymax);//mass

  if (histlabel.find("hSip_3")<10){
    hframe= new TH2F("hframe","hframe",600, 0., 10., 1000, 0.0004, 1000000000.);// sip
    hframe2= new TH2F("hframe2","hframe2",6000, 0., 10., 1000, 0.5, 2.);// sip
  }
  if (histlabel.find("hIp_3")<10){
    hframe= new TH2F("hframe","hframe",600, 0., 2., 1000, 0.000004, 1000000000.);// Ip
    hframe2= new TH2F("hframe2","hframe2",6000, 0., 2., 1000, 0.5, 2.);// Ip
  }
  //TH2F *hframe= new TH2F("hframe","hframe",600, 0., 10., 1000, 0.04, 10000000.);// chi2
  //TH2F *hframe= new TH2F("hframe","hframe",600, 0., 1., 1000, 0.004, 6.);// prob
  // TH2F *hframe= new TH2F("hframe","hframe",600, 0., 0.35, 1000, 0.04, 10000000.);// prob

  if (histlabel.find("hIso_3")<10){
    hframe= new TH2F("hframe","hframe",6000, 0., 3., 1000, 0.0004, 1000000000.);// iso
    hframe2= new TH2F("hframe2","hframe2",6000, 0., 3., 1000, 0.5, 2.);// iso
  }

  if (histlabel.find("hPFMET_3")<10 || (histlabel.find("hLogXPFMET_3")<10 || histlabel.find("hLogLinXPFMET_3")<10) ){
    cout << "Plotting PFMET at step 3" << endl;
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 100000000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 10., 1000., 1000, 0.5, 1.5);// PFMET
  }
  
  if ( (histlabel.find("hPFMET_3")<10 ||( histlabel.find("hLogXPFMET_3")<10 || histlabel.find("hLogLinXPFMET_3")<10) ) && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 100000000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0., 1000., 1000, 0.5, 1.5);// PFMET                                                                                 
  }

  if (histlabel.find("hMZ1_5")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,40.,200.,500,0.0001,100000.);// mZ1 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 160., 1000, 0.5, 2.);// mZ1 
  }

  if (histlabel.find("hMZ2_5")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,40.,200.,500,0.0000000001,1000000.);// mZ2 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 200., 1000, 0.5, 2.);// mZ2 
  }

  if (histlabel.find("hMZ1_7")<10 && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",80,0.,130.,500,0.0001,10.);// mZ1 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 160., 1000, 0.5, 2.);// mZ1 
  }

  if (histlabel.find("hMZ2_7")<10 && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",80,0.,130.,500,0.0000000001,10.);// mZ2 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 200., 1000, 0.5, 2.);// mZ2 
  }
  
  if (histlabel.find("hMZ1_8")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,40.,130.,500,0.0001,100000.);// mZ1 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 160., 1000, 0.5, 2.);// mZ1 
  }
  
  if (histlabel.find("hMZ2_8")<10 && whichchannel.find("4#mu")<20){
    hframe= new TH2F("hframe","hframe",80,40.,200.,500,0.0001,100000.);// mZ2 
    hframe2= new TH2F("hframe2","hframe2",6000, 40., 160., 1000, 0.5, 2.);// mZ2 
  }
  
  if (histlabel.find("hM4l_T_8")<10 || histlabel.find("hLogLinXM4l_T_8")<10 ){
    hframe= new TH2F("hframe","hframe",80,10.,1000.,500,0.00000004,100000000.);// transverse mass , M4l+MET
    hframe2= new TH2F("hframe2","hframe2",6000, 10., 1200., 1000, 0.5, 1.5);// 
  }

  if (histlabel.find("DPHI_8")<10 ){ // Rebin=40
    hframe= new TH2F("hframe","hframe",80,0,3.14,500,0.00001,1E11);// deltaphi 4l,MET
    hframe2= new TH2F("hframe2","hframe2",80,0,3.14, 1000, 0.5, 1.5);// 
  }

  if (histlabel.find("hMELA_8")<10){
    hframe= new TH2F("hframe","hframe",600,0.,1.,600,0.,20.);// MELA at final stage
    hframe2= new TH2F("hframe2","hframe2",600, 0., 1., 1000, 0.5, 2.);// MELA at final stage
  }

  if (histlabel.find("hPFMET_8")<10 || histlabel.find("hPFMET_10")<10){
    //hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.0000004, 50000.);// PFMET
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 100000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0.,1000., 1000, 0.5, 2.);// PFMET
  }
  
  if (histlabel.find("hPFMET_8")<10 || (histlabel.find("hLogXPFMET_8")<10 || histlabel.find("hLogLinXPFMET_8")<10) ){
    cout << "Plotting PFMET at step 8" << endl;
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 1000000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 10., 1000., 1000, 0.5, 1.5);// PFMET
  }
  
  if ( (histlabel.find("hPFMET_8")<10 ||( histlabel.find("hLogXPFMET_8")<10 || histlabel.find("hLogLinXPFMET_8")<10) ) && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 1000000.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0., 1000., 1000, 0.5, 1.5);// PFMET                                                                                 
  }

  if (histlabel.find("hPFMET_9")<10){
    //hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.0000004, 50000.);// PFMET
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 100.);// PFMET
    hframe2= new TH2F("hframe2","hframe2",1000, 0.,1000., 1000, 0.5, 2.);// PFMET
  }

  if (histlabel.find("hMjj_8")<10){
    hframe= new TH2F("hframe","hframe",600,20.,500.,600,0.000004,10E4);//mass jet jet
    hframe2= new TH2F("hframe2","hframe2",6000, 20., 500., 1000, 0.5, 2.);// mass jet jet
  }

  if (histlabel.find("hDjj_8")<10){
    hframe= new TH2F("hframe","hframe",600,0.,10.,600,0.000004,10E4);//delta eta jet jet
    hframe2= new TH2F("hframe2","hframe2",600, 0., 10., 1000, 0.5, 2.);// delta eta jet jet
  }

  if (histlabel.find("hNbjets")<10){
    hframe= new TH2F("hframe","hframe",600,-0.5,9.,600,0.000004,1E4);// number of b-jets
    hframe2= new TH2F("hframe2","hframe2",600, -0.5, 9., 1000, 0.5, 1.5);// number of b-jets
    hframe->SetXTitle("# bjets");
  }

  if (histlabel.find("hNbjets_9")<10){
    hframe= new TH2F("hframe","hframe",600,-0.5,9.,600,0.000004,1E3);// number of b-jets
    hframe2= new TH2F("hframe2","hframe2",600, -0.5, 9., 1000, 0.5, 1.5);// number of b-jets
    hframe->SetXTitle("# bjets");
  }

  if (histlabel.find("hNgood")<10){
    hframe= new TH2F("hframe","hframe",600,3.5,10.5,600,0.000004,10E5);// number of good leptons
    hframe2= new TH2F("hframe2","hframe2",600, 3.5, 9., 1000, 0.5, 1.5);// number of good leptons
    hframe->SetXTitle("# good lept.");
  }

  if (histlabel.find("hNgood_9")<10){
    hframe= new TH2F("hframe","hframe",600,3.5,10.5,600,0.000004,1E4);// number of good leptons
    hframe2= new TH2F("hframe2","hframe2",600, 3.5, 9., 1000, 0.5, 1.5);// number of good leptons
    hframe->SetXTitle("# good lept.");
  }

  if (histlabel.find("hPFMET_10")<10 || (histlabel.find("hLogXPFMET_10")<10 || histlabel.find("hLogLinXPFMET_10")<10) ){
    cout << "Plotting PFMET at step 10" << endl;
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 1000000.);// PFMET                                      
    hframe2= new TH2F("hframe2","hframe2",1000, 10., 1000., 1000, 0.5, 1.5);// PFMET                                            
  }

  if ( (histlabel.find("hPFMET_10")<10 ||( histlabel.find("hLogXPFMET_10")<10 || histlabel.find("hLogLinXPFMET_10")<10) ) && whichchannel.find("4l")<20){
    hframe= new TH2F("hframe","hframe",1000, 0., 1000., 1000, 0.000001, 1000000.);// PFMET                                                                                               
    hframe2= new TH2F("hframe2","hframe2",1000, 0., 1000., 1000, 0.5, 1.5);// PFMET                                                                                                      
  }


  //TH2F *hframe= new TH2F("hframe","hframe",6000, 0., 200., 1000, 0.004, 700000.);// ptZ

  if (nRebin==1) {
    if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
      hframe->SetYTitle("Events / bin");
    }
    else hframe->SetYTitle("Events/1 GeV");
  }
      
  if (nRebin==2) hframe->SetYTitle("Events/2 GeV");
  if (nRebin==1 && histlabel.find("hNbjets")<10) hframe->SetYTitle("Events");  
  if (nRebin==1 && histlabel.find("hNgood")<10) hframe->SetYTitle("Events");

  if (nRebin==3) hframe->SetYTitle("Events/3 GeV");
  if (nRebin==10) hframe->SetYTitle("Events/10 GeV");
  if (histlabel.find("hSip_3")<10) hframe->SetYTitle("Events/bin=0.12"); // nRebin=2 sip
  if (nRebin==4 && histlabel.find("hSip_3")<10) hframe->SetYTitle("Events/bin=0.24"); // nRebin=4 sip

  if (histlabel.find("hIso_3")<10) hframe->SetYTitle("Events/bin=0.04"); //nrebin=4 iso
  if (nRebin==5 && histlabel.find("hIso_3")<10) hframe->SetYTitle("Events/bin=0.05"); //nrebin=5 iso

  if (nRebin==2 && histlabel.find("hMjj_3")<10)  hframe->SetYTitle("Events/5 GeV"); // nRebin=2 mass jet jet
  if (nRebin==2 && histlabel.find("hDjj_3")<10)  hframe->SetYTitle("Events/bin=0.4"); // nRebin=2 deltetaeta
  if (nRebin==2 && histlabel.find("hVD_3")<10)   hframe->SetYTitle("Events/bin=0.1"); // nRebin=2 fisher
  if (nRebin==10 && histlabel.find("hMELA_8")<10) hframe->SetYTitle("Events / 0.033"); // MELA
  if (nRebin==5 && (histlabel.find("hPFMET_8")<10 ||histlabel.find("hPFMET_3")<10 )) hframe->SetYTitle("Events/5 GeV"); // PFMET
  

  if (histlabel.find("hM4l_7")<10 || histlabel.find("hM4l_8")<10  || histlabel.find("hM4l_9")<10  ){
    sprintf(histotitle,"m_{%s} [GeV]",whichchannel.c_str());
    hframe->SetXTitle(histotitle);
  }
  
  if (histlabel.find("hM4l_T_8")<10 || histlabel.find("hLogLinXM4l_T_8")<10 ){
    sprintf(histotitle,"m_{T} (%s+MET) [GeV]",whichchannel.c_str());
    hframe->SetXTitle(histotitle);
  }

  if (histlabel.find("DPHI_8")<10 ){
    sprintf(histotitle,"#Delta#phi (%s,MET) [rad]",whichchannel.c_str());
    hframe->SetXTitle(histotitle);
    hframe->SetYTitle("Events / 0.2 rad");
  }
  

  //hframe->SetXTitle("M_{Z2} [GeV]");
  if ((histlabel.find("hMZ_3")<10 || histlabel.find("hMZ1_8")<10) && whichchannel.find("4#mu")<20) 
    hframe->SetXTitle("M_{Z#rightarrow#mu#mu} [GeV]");
  if ((histlabel.find("hMZ_3")<10 || histlabel.find("hMZ1_8")<10) && whichchannel.find("4e")<20) 
    hframe->SetXTitle("M_{Z#rightarrow ee} [GeV]");
  //hframe->SetXTitle("M_{Z#rightarrow ee} (BB)  [GeV]");
  //hframe->SetXTitle("M_{Z#rightarrow ee} (EE)  [GeV]");
  // hframe->SetXTitle("Sign. 3DIP");  
  // hframe->SetXTitle("R^{iso}_{12} [GeV/c^{2}]");
  if (histlabel.find("hIso_3")<10 && whichchannel.find("4e")<20)   hframe->SetXTitle("electron worst rel. iso.");
  if (histlabel.find("hIso_3")<10 && whichchannel.find("4#mu")<20) hframe->SetXTitle("muon worst iso.");
  if (histlabel.find("hIso_3")<10 && whichchannel.find("2e2#mu")<20) hframe->SetXTitle("lepton worst iso.");
  //hframe->SetXTitle("lepton worst iso.");
  if (histlabel.find("hSip_3")<10 && whichchannel.find("4e")<20) hframe->SetXTitle("electron worst SIP_{3D}");
  if (histlabel.find("hSip_3")<10 && whichchannel.find("4#mu")<20) hframe->SetXTitle("muon worst sign. 3DIP");
  if (histlabel.find("hSip_3")<10 && whichchannel.find("2e2#mu")<20) hframe->SetXTitle("lepton worst sign. 3DIP");
  //hframe->SetXTitle("lepton worst sign. 3DIP");
  // hframe->SetXTitle("Prob(#chi^{2}/ndof.) of 4#mu vertex fitter (best 4#mu comb.)");
  // hframe->SetXTitle("#chi^{2}/ndof. of 4#mu vertex fitter (best 4#mu comb.)");
  if (histlabel.find("hMjj_3")<10 || histlabel.find("hMjj_8")<10) hframe->SetXTitle("di jet mass"); //Mjj
  if (histlabel.find("hDjj_3")<10 || histlabel.find("hDjj_3")<10) hframe->SetXTitle("#Delta#eta jets"); //deltaetajj
  //if (histlabel.find("hVD_3")<10) hframe->SetXTitle("Fisher discriminant"); // fisher
  if (histlabel.find("hVD_3")<10) hframe->SetXTitle("D_{jet}"); // fisher

  if (histlabel.find("hMELA_8")<10) hframe->SetXTitle("D_{bkg}^{kin}"); // MELA
  if (histlabel.find("PFMET_8")<10 || histlabel.find("PFMET_3")<10 ) hframe->SetXTitle("PF MET (GeV)"); // PFMET

 


  hframe->GetXaxis()->SetLabelOffset(0.007);
  hframe->GetXaxis()->SetTitleOffset(0.9);
  hframe->GetYaxis()->SetLabelOffset(0.007);

  hframe->Draw();

TH1F *htotaldata=NULL;
 if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10 ) {
    htotaldata    = new TH1F("htotaldata","htotaldata",NMBINS, logMbins);
  }
  else htotaldata = new TH1F("htotaldata", "htotaldata", Nbins, Xmin, Xmax);

  //htotaldata->Sumw2();
  htotaldata->SetMarkerColor(1);
  htotaldata->SetMarkerStyle(20);
  THStack *htotal=new THStack("Nicola",""); 

  TH1F *htotalHisto=NULL;
  TH1F *htotalHistoRatio=NULL;

if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    htotalHisto         = new TH1F("htotalHisto","htotalHisto",NMBINS, logMbins);
    htotalHistoRatio    = new TH1F("htotalHistoRatio","htotalHistoRatio",NMBINS, logMbins);
  }
  else {
    htotalHisto = new TH1F("htotalHisto", "htotalHisto", Nbins, Xmin, Xmax);
    htotalHistoRatio = new TH1F("htotalHistoRatio", "htotalHistoRatio", Nbins, Xmin, Xmax);
  }

  TH1D *nEvent_4l_w_totalbkgMC = new TH1D("nEvent_4l_w_totalbkgMC", "nEventComplete MC Weighted", 23, 0., 23.);
  nEvent_4l_w_totalbkgMC ->Sumw2();
  TH1D *nEvent_4l_totalbkgMC = new TH1D("nEvent_4l_totalbkgMC", "nEventComplete MC", 23, 0., 23.);
  nEvent_4l_totalbkgMC->Sumw2();
  TList *listtotalbkgMC_w = new TList;
  TList *listtotalbkgMC = new TList;


  // data
  TH1D *nEvent_4l_w_data = new TH1D("nEvent_4l_w_data", "nEventComplete data Weighted", 23, 0., 23.);
  nEvent_4l_w_data->Sumw2();
  TList *listdata = new TList;

  for (unsigned int datasetIdData=0; datasetIdData<Vdatasetnamedata.size(); datasetIdData++){
    
    char dataset[328];
    sprintf(dataset,"%s",Vdatasetnamedata.at(datasetIdData).c_str());
    //cout << "Root-ple= " << dataset << endl;
    // cout << "Counter=" << datasetIdData << " Root-ple=" << dataset << " Label=" << Vlabelbkg.at(datasetIdData) <<endl; 
    
    TFile *f1 = TFile::Open(dataset);
    TH1D *nEvent_4l_w_new = (TH1D*)f1->Get("nEvent_4l_w");

    hfourlepbestmass_4l_afterSel_new = (TH1F*)f1->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new"*/);
    //hfourlepbestmass_4l_afterSel_new->Sumw2();                                                                                                                 
        
    
    TH1 *hfourlepbestmass_4l_afterSel_new_new=NULL;

    if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10)  {
      hfourlepbestmass_4l_afterSel_new_new = (TH1F*)f1->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);    
    }
    else hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin, histlabel.c_str()/*"hfourlepbestmass_4l_afterSel_new_new"*/);

    //hfourlepbestmass_4l_afterSel_new_new->Sumw2();  
    hfourlepbestmass_4l_afterSel_new_new->SetMarkerColor(1);
    hfourlepbestmass_4l_afterSel_new_new->SetMarkerStyle(20);
    hfourlepbestmass_4l_afterSel_new_new->SetMarkerSize(0.95);
    // hfourlepbestmass_4l_afterSel_new_new->Draw("EPsame");

    //leg0->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabeldata.at(datasetIdData).c_str(), "P");  

    //cout << "Nbins=" << hfourlepbestmass_4l_afterSel_new_new->GetNbinsX() << endl;
    //cout << "htotaldata nBins = " << htotaldata->GetNbinsX() << ", hfourlepbestmass_4l_afterSel_new_new nBins = " << hfourlepbestmass_4l_afterSel_new_new->GetNbinsX() << endl;
    //cout << "htotaldata lowestX = " << htotaldata->GetXaxis()->GetXmin() <<  ", htotaldata highestX = " << htotaldata->GetXaxis()->GetXmax() << ", hfourlepbestmass_4l_afterSel_new_new lowestX = " << hfourlepbestmass_4l_afterSel_new_new->GetXaxis()->GetXmin() << ", hfourlepbestmass_4l_afterSel_new_new highestX = " << hfourlepbestmass_4l_afterSel_new_new->GetXaxis()->GetXmax() << endl;
    cout << "Adding data " << dataset << endl;
	//cout << htotaldata->GetNbinsX() << " " << hfourlepbestmass_4l_afterSel_new_new->GetNbinsX() << endl;
    htotaldata->Add(hfourlepbestmass_4l_afterSel_new_new);
    cout << "Label= " << Vlabeldata.at(datasetIdData) <<"  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;
    if (datasetIdData==(Vdatasetnamedata.size()-1)) {
      leg0->AddEntry(hfourlepbestmass_4l_afterSel_new_new,"Data 2016", "P"); 
      legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,"DATA 2016", "P"); 
      //htotaldata->Draw("EPsame");
    }
    listdata->Add(nEvent_4l_w_new);
  }

  nEvent_4l_w_data->Merge(listdata);

  cout << "Data= " << htotaldata->Integral() << " and in the bins= " 
       << htotaldata->GetBinContent(1) << " err= " << htotaldata->GetBinError(1) << " " 
       << htotaldata->GetBinContent(2) << " err= " << htotaldata->GetBinError(2) << " " 
       << htotaldata->GetBinContent(3) << " err= " << htotaldata->GetBinError(3) << " "
       << htotaldata->GetBinContent(4) << " err= " << htotaldata->GetBinError(4) << " "
       << htotaldata->GetBinContent(5) << " err= " << htotaldata->GetBinError(5) 
       << endl;

  TGraphAsymmErrors *gr=NULL;

  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    cout << "Plotting htotaldata with log bins" << endl;
  }
  else {
    // Set Errors as in http://www-cdf.fnal.gov/physics/statistics/notes/pois_eb.txt
    //Float_t x[51],y[51],exl[51],exh[51],eyl[51],eyh[51];
    
    int* arraysize = new int[1];
    arraysize[0] = htotaldata->GetNbinsX();
    //std::cout << "arraysize = " << arraysize[0] << std::endl;
    Float_t x[arraysize[0]],y[arraysize[0]],exl[arraysize[0]],exh[arraysize[0]],eyl[arraysize[0]],eyh[arraysize[0]];
    delete [] arraysize;
    
    float totaldataentries=0.,totaldataentries100=0.;
    
    for (int nbins=1;nbins<=htotaldata->GetNbinsX(); nbins++){
      // cout << "BinCenter=" << htotaldata->GetBinCenter(nbins) << " BinContent=" << htotaldata->GetBinContent(nbins) << " BinErrorContent=" << htotaldata->GetBinError(nbins) << endl;
      x[nbins-1]=htotaldata->GetBinCenter(nbins);
      y[nbins-1]=htotaldata->GetBinContent(nbins);
      exl[nbins-1]=0.;
      exh[nbins-1]=0.;
      totaldataentries=totaldataentries+htotaldata->GetBinContent(nbins);
      if (htotaldata->GetBinCenter(nbins)>100. && htotaldata->GetBinCenter(nbins)<800.) totaldataentries100=totaldataentries100+htotaldata->GetBinContent(nbins);
      if (htotaldata->GetBinContent(nbins)>0){
        eyh[nbins-1]=+0.5 + sqrt(htotaldata->GetBinContent(nbins)+0.25);   
        eyl[nbins-1]=-0.5 + sqrt(htotaldata->GetBinContent(nbins)+0.25);
      }
      else{
	x[nbins-1] = 0.;
	eyl[nbins-1] = 0.;
	eyh[nbins-1] = 0.;
      }
    }
    
    cout << "Total data= " << totaldataentries << endl;
    //if (histlabel.find("hM4l_9")<10 ) outputyields << "Data " << totaldataentries << " +/- 0" << endl;
    //cout << "Total data in the range m4l>100 and  m4l<800= " << totaldataentries100 << endl;
    
    gr = new TGraphAsymmErrors(Nbins,x,y,exl,exh,eyl,eyh);
    gr->SetMarkerColor(1);
    gr->SetMarkerStyle(20);
    gr->SetMarkerSize(0.95);
    //
  }

  // Z+X from data
  if (useDYJets==false && useDYJetsFromData==true){
    if (histlabel.find("hM4l_7")<10 || histlabel.find("hPFMET_8")<10){
      for (unsigned int datasetIdbkgData=0; datasetIdbkgData<Vdatasetnamebkgdata.size(); datasetIdbkgData++){
	char dataset[328];
	sprintf(dataset,"%s",Vdatasetnamebkgdata.at(datasetIdbkgData).c_str());
	cout << "Root-ple= " << dataset << endl;
	TFile *f3 = TFile::Open(dataset);
	//TH1F *hfourlepbestmass_4l_afterSel_orig = new TH1F("hfourlepbestmass_4l_afterSel_orig", "Mass of four leptons after fullselection", 1000, 0.,1000. );
        //if (histlabel.find("hPFMET_8")<10) hfourlepbestmass_4l_afterSel_orig = (TH1F*)f3->Get("h_MassZplusX_FR");
	
	TH1F *hfourlepbestmass_4l_afterSel_new = new TH1F("hfourlepbestmass_4l_afterSel_new", "Mass of four leptons after fullselection", 1000, 0,1000.);
	if (histlabel.find("hPFMET_8")<10) hfourlepbestmass_4l_afterSel_new = (TH1F*)f3->Get("h_MassZplusX_FR");

        //int mbins=1;
        //for (int nbins=1;nbins<=hfourlepbestmass_4l_afterSel_orig->GetNbinsX(); nbins++){
        //  if (hfourlepbestmass_4l_afterSel_orig->GetBinCenter(nbins)>4.5 && hfourlepbestmass_4l_afterSel_orig->GetBinCenter(nbins)<1204.5){
	//    hfourlepbestmass_4l_afterSel_new->SetBinContent(mbins,double(hfourlepbestmass_4l_afterSel_orig->GetBinContent(nbins)));
        //    mbins++;
        //  }
        //}

	TH1 *hfourlepbestmass_4l_afterSel_new_new = NULL;
	if (histlabel.find("hPFMET_8")<10) {
	  //hfourlepbestmass_4l_afterSel_new_new = (TH1F*)f3->Get("h_MassZplusX_FR");	
	  nRebinZ_X=nRebin;
	  hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebinZ_X, "h_MassZplusX_FR");      
	}
	hfourlepbestmass_4l_afterSel_new_new->SetLineColor(kCyan-2);
	hfourlepbestmass_4l_afterSel_new_new->SetFillColor(kCyan-2);
	hfourlepbestmass_4l_afterSel_new_new->SetMarkerStyle(24);
	hfourlepbestmass_4l_afterSel_new_new->SetLineWidth(1);
	
	char temp[328];
        sprintf(temp,"%s",histosdir.c_str());
	//cout << temp << " " << whichenergy << " " << whichsample << endl;

	if ( 
	    histlabel.find("hM4l_7")<10 ) {
	  cout << "Adding Z+X for m4l > 70. GeV" << endl;
	  cout << "N bins Z+X= " << hfourlepbestmass_4l_afterSel_new_new->GetNbinsX()<< endl;
	  cout << "Z+X entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) << endl;
	  htotal->Add(hfourlepbestmass_4l_afterSel_new_new);
	  htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_new);
	  if ( 
	      Vdatasetnamebkgdata.at(datasetIdbkgData).find(temp) <200 ){
	    //(Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichenergy) < 200 || Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichsample) < 200) ){     
	    //Vdatasetnamebkgdata.at(datasetIdbkgData).find("2mu2e")>85 ) {
	    cout << "Adding legend for Z+X" << endl;
	    legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkgdata.at(datasetIdbkgData).c_str(), "F"); }
	}
	else if ( 		
		 Vdatasetnamebkgdata.at(datasetIdbkgData).find(temp) <200 && 
		 //(Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichenergy) < 200 || Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichsample) < 200) &&
		 (histlabel.find("hM4l_8")<10 || histlabel.find("hPFMET_8")<10 )) {
	  cout << "Adding Z+X" << endl;
	  //cout << "Z+X entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) << endl;
	  htotal->Add(hfourlepbestmass_4l_afterSel_new_new);
	  htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_new);	  
	  if (
	      Vdatasetnamebkgdata.at(datasetIdbkgData).find(temp) <200 && 
	      (Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichenergy) < 200 || Vdatasetnamebkgdata.at(datasetIdbkgData).find(whichsample) < 200) ){
	    //	      Vdatasetnamebkgdata.at(datasetIdbkgData).find("2mu2e")>85 ){
	    cout << "Adding legend for Z+X" << endl;
	    legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkgdata.at(datasetIdbkgData).c_str(), "F");}
	}
      }
    }
  }
  
  //cout << "Total Z+X is= " << htotal->GetHistogram()->GetEntries() << endl;
  cout << "Total Z+X is= " << htotalHisto->Integral(0,-1)  << endl;
  //outputyields << "Z+X "   << htotal->GetHistogram()->GetEntries() << " +/- 0"<< endl;
  if (histlabel.find("hM4l_9")<10 ) outputyields << "Z+X " << htotalHisto->Integral(0,-1) << " +/- 0" << endl;


  // Background

  TH1F *hfourlepbestmass_4l_afterSel_new_qqZZ;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_qqZZ    = new TH1F("hfourlepbestmass_4l_afterSel_new_qqZZ","hfourlepbestmass_4l_afterSel_new_qqZZ",NMBINS, logMbins);
  }
  else  hfourlepbestmass_4l_afterSel_new_qqZZ = new TH1F("hfourlepbestmass_4l_afterSel_new_qqZZ", "hfourlepbestmass_4l_afterSel_new_qqZZ", Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_qqZZ = new TH1D("nEvent_4l_w_qqZZ", "nEventComplete qqZZ Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_qqZZ = new TH1D("nEvent_4l_qqZZ", "nEventComplete qqZZ", 23, 0., 23.);
  nEvent_4l_w_qqZZ->Sumw2();
  nEvent_4l_qqZZ->Sumw2();
  TList *listqqZZ_w = new TList;
  TList *listqqZZ = new TList;

  TH1F *hfourlepbestmass_4l_afterSel_new_ggZZ;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ggZZ    = new TH1F("hfourlepbestmass_4l_afterSel_new_ggZZ","hfourlepbestmass_4l_afterSel_new_ggZZ",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ggZZ = new TH1F("hfourlepbestmass_4l_afterSel_new_ggZZ", "hfourlepbestmass_4l_afterSel_new_ggZZ", Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_ggZZ = new TH1D("nEvent_4l_w_ggZZ", "nEventComplete ggZZ Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_ggZZ = new TH1D("nEvent_4l_ggZZ", "nEventComplete ggZZ", 23, 0., 23.);
  nEvent_4l_w_ggZZ->Sumw2();
  nEvent_4l_ggZZ->Sumw2();
  TList *listggZZ_w = new TList;
  TList *listggZZ = new TList;



  TH1F *hfourlepbestmass_4l_afterSel_new_ZZ;
  if ( histlabel.find("hLogX")<10  || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ZZ    = new TH1F("hfourlepbestmass_4l_afterSel_new_ZZ","hfourlepbestmass_4l_afterSel_new_ZZ",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ZZ = new TH1F("hfourlepbestmass_4l_afterSel_new_ZZ", "hfourlepbestmass_4l_afterSel_new_ZZ", Nbins, Xmin, Xmax);

  TH1D *nEvent_4l_w_ZZ = new TH1D("nEvent_4l_w_ZZ", "nEventComplete ZZ Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_ZZ = new TH1D("nEvent_4l_ZZ", "nEventComplete ZZ", 23, 0., 23.);
  nEvent_4l_w_ZZ->Sumw2();
  nEvent_4l_ZZ->Sumw2();
  TList *listZZ_w = new TList;
  TList *listZZ = new TList;
  
  TH1F *hfourlepbestmass_4l_afterSel_new_qcdDEM;
  if ( histlabel.find("hLogX")<10  || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_qcdDEM    = new TH1F("hfourlepbestmass_4l_afterSel_new_qcdDEM","hfourlepbestmass_4l_afterSel_new_qcdDEM",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_qcdDEM = new TH1F("hfourlepbestmass_4l_afterSel_new_qcdDEM", "hfourlepbestmass_4l_afterSel_new_qcdDEM", Nbins, Xmin, Xmax);


  TH1F *hfourlepbestmass_4l_afterSel_new_qcdMu;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_qcdMu = new TH1F("hfourlepbestmass_4l_afterSel_new_qcdMu", "hfourlepbestmass_4l_afterSel_new_qcdMu",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_qcdMu= new TH1F("hfourlepbestmass_4l_afterSel_new_qcdMu", "hfourlepbestmass_4l_afterSel_new_qcdMu", Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_qcdBC;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_qcdBC = new TH1F("hfourlepbestmass_4l_afterSel_new_qcdBC", "hfourlepbestmass_4l_afterSel_new_qcdBC",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_qcdBC = new TH1F("hfourlepbestmass_4l_afterSel_new_qcdBC", "hfourlepbestmass_4l_afterSel_new_qcdBC", Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_qcd;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_qcd = new TH1F("hfourlepbestmass_4l_afterSel_new_qcd", "hfourlepbestmass_4l_afterSel_new_qcd",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_qcd= new TH1F("hfourlepbestmass_4l_afterSel_new_qcd", "hfourlepbestmass_4l_afterSel_new_qcd", Nbins, Xmin, Xmax);
  
  TH1D *nEvent_4l_w_QCD = new TH1D("nEvent_4l_w_QCD", "nEventComplete QCD Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_QCD = new TH1D("nEvent_4l_QCD", "nEventComplete QCD", 23, 0., 23.);
  nEvent_4l_w_QCD->Sumw2();
  nEvent_4l_QCD->Sumw2();
  TList *listQCD_w = new TList;
  TList *listQCD = new TList;



  TH1F *hfourlepbestmass_4l_afterSel_new_singlet;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_singlet = new TH1F("hfourlepbestmass_4l_afterSel_new_singlet", "hfourlepbestmass_4l_afterSel_new_singlet",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_singlet = new TH1F("hfourlepbestmass_4l_afterSel_new_singlet", "hfourlepbestmass_4l_afterSel_new_singlet", Nbins, Xmin, Xmax);
  
  TH1D *nEvent_4l_w_ST = new TH1D("nEvent_4l_w_ST", "nEventComplete ST Weighted", 23, 0., 23.);
  nEvent_4l_w_ST->Sumw2();
  TH1D *nEvent_4l_ST = new TH1D("nEvent_4l_ST", "nEventComplete ST", 23, 0., 23.);
  nEvent_4l_ST->Sumw2();
  TList *listST_w = new TList;
  TList *listST = new TList;

  TH1F *hfourlepbestmass_4l_afterSel_new_DY;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_DY = new TH1F("hfourlepbestmass_4l_afterSel_new_DY", "hfourlepbestmass_4l_afterSel_new_DY",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_DY = new TH1F("hfourlepbestmass_4l_afterSel_new_DY", "hfourlepbestmass_4l_afterSel_new_DY",Nbins, Xmin, Xmax);    

  TH1F *hfourlepbestmass_4l_afterSel_new_DYlight;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_DYlight = new TH1F("hfourlepbestmass_4l_afterSel_new_DYlight", "hfourlepbestmass_4l_afterSel_new_DYlight",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_DYlight = new TH1F("hfourlepbestmass_4l_afterSel_new_DYlight", "hfourlepbestmass_4l_afterSel_new_DYlight",Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_DYbb;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_DYbb = new TH1F("hfourlepbestmass_4l_afterSel_new_DYbb", "hfourlepbestmass_4l_afterSel_new_DYbb",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_DYbb= new TH1F("hfourlepbestmass_4l_afterSel_new_DYbb", "hfourlepbestmass_4l_afterSel_new_DYbb",Nbins, Xmin, Xmax);        
  
  TH1F *hfourlepbestmass_4l_afterSel_new_DYcc;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_DYcc = new TH1F("hfourlepbestmass_4l_afterSel_new_DYcc", "hfourlepbestmass_4l_afterSel_new_DYcc",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_DYcc = new TH1F("hfourlepbestmass_4l_afterSel_new_DYcc", "hfourlepbestmass_4l_afterSel_new_DYcc",Nbins, Xmin, Xmax);        
  
  TH1D *nEvent_4l_w_DY = new TH1D("nEvent_4l_w_DY", "nEventComplete DY Weighted", 23, 0., 23.);
  nEvent_4l_w_DY->Sumw2();
  TH1D *nEvent_4l_DY = new TH1D("nEvent_4l_DY", "nEventComplete DY", 23, 0., 23.);
  nEvent_4l_DY->Sumw2();
  TList *listDY_w = new TList;
  TList *listDY = new TList;
  
  
  TH1F *hfourlepbestmass_4l_afterSel_new_WW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_WW = new TH1F("hfourlepbestmass_4l_afterSel_new_WW", "hfourlepbestmass_4l_afterSel_new_WW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_WW = new TH1F("hfourlepbestmass_4l_afterSel_new_WW", "hfourlepbestmass_4l_afterSel_new_WW",Nbins, Xmin, Xmax); 
  
  TH1F *hfourlepbestmass_4l_afterSel_new_WZ;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_WZ = new TH1F("hfourlepbestmass_4l_afterSel_new_WZ", "hfourlepbestmass_4l_afterSel_new_WZ",NMBINS, logMbins);
  }  
  else hfourlepbestmass_4l_afterSel_new_WZ= new TH1F("hfourlepbestmass_4l_afterSel_new_WZ", "hfourlepbestmass_4l_afterSel_new_WZ",Nbins, Xmin, Xmax);                        

  TH1F *hfourlepbestmass_4l_afterSel_new_Wj;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_Wj = new TH1F("hfourlepbestmass_4l_afterSel_new_Wj", "hfourlepbestmass_4l_afterSel_new_Wj",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_Wj= new TH1F("hfourlepbestmass_4l_afterSel_new_Wj", "hfourlepbestmass_4l_afterSel_new_Wj",Nbins, Xmin, Xmax);
  
  TH1D *nEvent_4l_w_WZ_WW_Wj = new TH1D("nEvent_4l_w_WZ_WW_Wj", "nEventComplete WZ_WW_Wj Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_WZ_WW_Wj = new TH1D("nEvent_4l_WZ_WW_Wj", "nEventComplete WZ_WW_Wj", 23, 0., 23.);
  nEvent_4l_w_WZ_WW_Wj->Sumw2();
  nEvent_4l_WZ_WW_Wj->Sumw2();
  TList *listWZ_WW_Wj_w = new TList;
  TList *listWZ_WW_Wj = new TList;
  
  TH1F *hfourlepbestmass_4l_afterSel_new_TT;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_TT = new TH1F("hfourlepbestmass_4l_afterSel_new_TT", "hfourlepbestmass_4l_afterSel_new_TT",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_TT= new TH1F("hfourlepbestmass_4l_afterSel_new_TT", "hfourlepbestmass_4l_afterSel_new_TT",Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_TT = new TH1D("nEvent_4l_w_TT", "nEventComplete TT Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_TT = new TH1D("nEvent_4l_TT", "nEventComplete TT", 23, 0., 23.);
  nEvent_4l_w_TT->Sumw2();
  nEvent_4l_TT->Sumw2();
  TList *listTT_w = new TList;
  TList *listTT = new TList;

  TH1F *hfourlepbestmass_4l_afterSel_new_VVV;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_VVV = new TH1F("hfourlepbestmass_4l_afterSel_new_VVV", "hfourlepbestmass_4l_afterSel_new_VVV",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_VVV= new TH1F("hfourlepbestmass_4l_afterSel_new_VVV", "hfourlepbestmass_4l_afterSel_new_VVV",Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_VVV = new TH1D("nEvent_4l_w_VVV", "nEventComplete VVV Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_VVV = new TH1D("nEvent_4l_VVV", "nEventComplete VVV", 23, 0., 23.);
  nEvent_4l_w_VVV->Sumw2();
  nEvent_4l_VVV->Sumw2();
  TList *listVVV_w = new TList;
  TList *listVVV = new TList;

  TH1F *hfourlepbestmass_4l_afterSel_new_TTV;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_TTV = new TH1F("hfourlepbestmass_4l_afterSel_new_TTV", "hfourlepbestmass_4l_afterSel_new_TTV",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_TTV= new TH1F("hfourlepbestmass_4l_afterSel_new_TTV", "hfourlepbestmass_4l_afterSel_new_TTV",Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_TTV = new TH1D("nEvent_4l_w_TTV", "nEventComplete TTV Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_TTV = new TH1D("nEvent_4l_TTV", "nEventComplete TTV", 23, 0., 23.);
  nEvent_4l_w_TTV->Sumw2();
  nEvent_4l_TTV->Sumw2();
  TList *listTTV_w = new TList;
  TList *listTTV = new TList;

  // Higgs ZZ as background
  TH1F *hfourlepbestmass_4l_afterSel_new_ggH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ggH = new TH1F("hfourlepbestmass_4l_afterSel_new_ggH", "hfourlepbestmass_4l_afterSel_new_ggH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ggH= new TH1F("hfourlepbestmass_4l_afterSel_new_ggH", "hfourlepbestmass_4l_afterSel_new_ggH",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_VH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_VH = new TH1F("hfourlepbestmass_4l_afterSel_new_VH", "hfourlepbestmass_4l_afterSel_new_VH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_VH= new TH1F("hfourlepbestmass_4l_afterSel_new_VH", "hfourlepbestmass_4l_afterSel_new_VH",Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_ZH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ZH = new TH1F("hfourlepbestmass_4l_afterSel_new_ZH", "hfourlepbestmass_4l_afterSel_new_ZH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ZH = new TH1F("hfourlepbestmass_4l_afterSel_new_ZH", "hfourlepbestmass_4l_afterSel_new_ZH",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_WH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_WH = new TH1F("hfourlepbestmass_4l_afterSel_new_WH", "hfourlepbestmass_4l_afterSel_new_WH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_WH= new TH1F("hfourlepbestmass_4l_afterSel_new_WH", "hfourlepbestmass_4l_afterSel_new_WH",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_VBFH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_VBFH = new TH1F("hfourlepbestmass_4l_afterSel_new_VBFH", "hfourlepbestmass_4l_afterSel_new_VBFH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_VBFH= new TH1F("hfourlepbestmass_4l_afterSel_new_VBFH", "hfourlepbestmass_4l_afterSel_new_VBFH",Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_ttH;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ttH = new TH1F("hfourlepbestmass_4l_afterSel_new_ttH", "hfourlepbestmass_4l_afterSel_new_ttH",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ttH= new TH1F("hfourlepbestmass_4l_afterSel_new_ttH", "hfourlepbestmass_4l_afterSel_new_ttH",Nbins, Xmin, Xmax);

  // Higgs WW as background
  TH1F *hfourlepbestmass_4l_afterSel_new_ggHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ggHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_ggHWW", "hfourlepbestmass_4l_afterSel_new_ggHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ggHWW= new TH1F("hfourlepbestmass_4l_afterSel_new_ggHWW", "hfourlepbestmass_4l_afterSel_new_ggHWW",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_VHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_VHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_VHWW", "hfourlepbestmass_4l_afterSel_new_VHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_VHWW= new TH1F("hfourlepbestmass_4l_afterSel_new_VHWW", "hfourlepbestmass_4l_afterSel_new_VHWW",Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_ZHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_ZHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_ZHWW", "hfourlepbestmass_4l_afterSel_new_ZHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_ZHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_ZHWW", "hfourlepbestmass_4l_afterSel_new_ZHWW",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_WHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_WHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_WHWW", "hfourlepbestmass_4l_afterSel_new_WHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_WHWW= new TH1F("hfourlepbestmass_4l_afterSel_new_WHWW", "hfourlepbestmass_4l_afterSel_new_WHWW",Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_afterSel_new_VBFHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_VBFHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_VBFHWW", "hfourlepbestmass_4l_afterSel_new_VBFHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_VBFHWW= new TH1F("hfourlepbestmass_4l_afterSel_new_VBFHWW", "hfourlepbestmass_4l_afterSel_new_VBFHWW",Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_bbHWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_bbHWW = new TH1F("hfourlepbestmass_4l_afterSel_new_bbHWW", "hfourlepbestmass_4l_afterSel_new_bbHWW",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_bbHWW= new TH1F("hfourlepbestmass_4l_afterSel_new_bbHWW", "hfourlepbestmass_4l_afterSel_new_bbHWW",Nbins, Xmin, Xmax);


  TH1F *hfourlepbestmass_4l_afterSel_new_totSM_H,*hfourlepbestmass_4l_afterSel_new_totSM_HZZ,*hfourlepbestmass_4l_afterSel_new_totSM_HWW;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_totSM_H = new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_H", "hfourlepbestmass_4l_afterSel_new_totSM_H",NMBINS, logMbins);
    hfourlepbestmass_4l_afterSel_new_totSM_HZZ = new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_HZZ", "hfourlepbestmass_4l_afterSel_new_totSM_HZZ",NMBINS, logMbins);
    hfourlepbestmass_4l_afterSel_new_totSM_HWW = new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_HWW", "hfourlepbestmass_4l_afterSel_new_totSM_HWW",NMBINS, logMbins);    
  }
  else {
    hfourlepbestmass_4l_afterSel_new_totSM_H= new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_H", "hfourlepbestmass_4l_afterSel_new_totSM_H",Nbins, Xmin, Xmax);
    hfourlepbestmass_4l_afterSel_new_totSM_HZZ= new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_HZZ", "hfourlepbestmass_4l_afterSel_new_totSM_HZZ",Nbins, Xmin, Xmax);
    hfourlepbestmass_4l_afterSel_new_totSM_HWW= new TH1F("hfourlepbestmass_4l_afterSel_new_totSM_HWW", "hfourlepbestmass_4l_afterSel_new_totSM_HWW",Nbins, Xmin, Xmax);
  }
  
  TH1D *nEvent_4l_w_totSM_H = new TH1D("nEvent_4l_w_totSM_H", "nEventComplete totSM_H Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_totSM_H = new TH1D("nEvent_4l_totSM_H", "nEventComplete totSM_H", 23, 0., 23.);
  nEvent_4l_w_totSM_H->Sumw2();
  nEvent_4l_totSM_H->Sumw2();
  TList *listtotSM_H_w = new TList;
  TList *listtotSM_H = new TList;


  TH1D *nEvent_4l_w_totSM_HZZ = new TH1D("nEvent_4l_w_totSM_HZZ", "nEventComplete totSM_HZZ Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_totSM_HZZ = new TH1D("nEvent_4l_totSM_HZZ", "nEventComplete totSM_HZZ", 23, 0., 23.);
  nEvent_4l_w_totSM_HZZ->Sumw2();
  nEvent_4l_totSM_HZZ->Sumw2();
  TList *listtotSM_HZZ_w = new TList;
  TList *listtotSM_HZZ = new TList;


  TH1D *nEvent_4l_w_totSM_HWW = new TH1D("nEvent_4l_w_totSM_HWW", "nEventComplete totSM_HWW Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_totSM_HWW = new TH1D("nEvent_4l_totSM_HWW", "nEventComplete totSM_HWW", 23, 0., 23.);
  nEvent_4l_w_totSM_HWW->Sumw2();
  nEvent_4l_totSM_HWW->Sumw2();
  TList *listtotSM_HWW_w = new TList;
  TList *listtotSM_HWW = new TList;

  // Total bkg - no Higgs
  TH1F *hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H = new TH1F("hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H", "hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H",NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H = new TH1F("hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H", "hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H",Nbins, Xmin, Xmax);
  TH1D *nEvent_4l_w_totbkg_noSM_H = new TH1D("nEvent_4l_w_totbkg_noSM_H", "nEventComplete totbkg_noSM_H Weighted", 23, 0., 23.);
  TH1D *nEvent_4l_totbkg_noSM_H = new TH1D("nEvent_4l_totbkg_noSM_H", "nEventComplete totbkg_noSM_H", 23, 0., 23.);
  nEvent_4l_w_totbkg_noSM_H->Sumw2();
  nEvent_4l_totbkg_noSM_H->Sumw2();
  TList *listtotbkg_noSM_H_w = new TList;
  TList *listtotbkg_noSM_H = new TList;
  
  for ( int datasetId=Vdatasetnamebkg.size()-1; datasetId >=0; datasetId--){  

    char dataset[328];
    sprintf(dataset,"%s",Vdatasetnamebkg.at(datasetId).c_str());
    //cout << "Root-ple= " << dataset << "N entries= " <<  hfourlepbestmass_4l_afterSel_new->GetEntries() << endl;
    cout << "Counter=" << datasetId << " Root-ple=" << dataset << " Label=" << Vlabelbkg.at(datasetId) <<endl; 
    
    std::string datasetnamebkg = "";
    datasetnamebkg = Vdatasetnamebkg.at(datasetId);

    TFile *f2 = TFile::Open(dataset);
    hfourlepbestmass_4l_afterSel_new = (TH1F*)f2->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new"*/);

    TH1D *nEvent_4l_w_new = (TH1D*)f2->Get("nEvent_4l_w");
    TH1D *nEvent_4l_new = (TH1D*)f2->Get("nEvent_4l");
    cout << "Bin content= " << nEvent_4l_w_new->GetBinContent(5) << " " << nEvent_4l_w_new->GetBinError(5) << endl;

    TH1 *hfourlepbestmass_4l_afterSel_new_new;

    if(datasetnamebkg.find("WZTo")   < 200 ||
       datasetnamebkg.find("WWTo")  < 200 ||
       datasetnamebkg.find("DYJetsToLL") < 200 ||
       datasetnamebkg.find("DYlightJetsToLL") < 200 ||
       datasetnamebkg.find("DYbbJetsToLL") < 200 ||
       datasetnamebkg.find("DYccJetsToLL") < 200 ||
       datasetnamebkg.find("ZToEE")<200 ||
       //datasetnamebkg.find("DYToEE")   < 200 ||
       //datasetnamebkg.find("DYToMuMu") < 200 ||
       // datasetnamebkg.find("TTTo2L2Nu2B")< 200 ||
       datasetnamebkg.find("TTT")< 200 ||
       datasetnamebkg.find("WJetsToLNu") < 200 || 
       datasetnamebkg.find("M125") < 200 || 
       datasetnamebkg.find("M-125") < 200 || 
       datasetnamebkg.find("ZZZ") < 200 ||
       datasetnamebkg.find("WWZ") < 200 || 
       datasetnamebkg.find("WZZ") < 200 ||
       datasetnamebkg.find("TTWJet") < 200 ||
       datasetnamebkg.find("TTZTo") < 200 
       ){
      
   
      if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
	hfourlepbestmass_4l_afterSel_new_new = (TH1*)f2->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
      }
      else hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin, histlabel.c_str()/*"hfourlepbestmass_4l_afterSel_new_new"*/);

      //hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin, histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
      hfourlepbestmass_4l_afterSel_new_new->SetLineColor(Vcolorbkg.at(datasetId)/*datasetId+2*/);
      hfourlepbestmass_4l_afterSel_new_new->SetFillColor(Vcolorbkg.at(datasetId)/*datasetId+2*/);
      hfourlepbestmass_4l_afterSel_new_new->SetMarkerStyle(24);
      hfourlepbestmass_4l_afterSel_new_new->SetLineWidth(1);
      cout << "Label= " << Vlabelbkg.at(datasetId) 
	   << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->GetEntries()
	   << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1);
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0) 
	cout << "  Error= " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries();
      cout << endl;

      //nEvent_4l_w_totalbkgMC->Add(nEvent_4l_w_new);
      //nEvent_4l_totalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC_w->Add(nEvent_4l_w_new);

      // Higgs as background
      if(datasetnamebkg.find("GluGluHToZZTo4L") < 200){
	cout << "ggH" << endl;
	hfourlepbestmass_4l_afterSel_new_ggH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_ggH->SetMarkerColor(kOrange-3); 
	hfourlepbestmass_4l_afterSel_new_ggH->SetFillColor(kOrange-3);
	hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_ggH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HZZ->Add(nEvent_4l_new);
	listtotSM_HZZ_w->Add(nEvent_4l_w_new);

      }
      if(datasetnamebkg.find("GluGluHToWWTo2L2Nu") < 200){
	cout << "ggHWW" << endl;
	hfourlepbestmass_4l_afterSel_new_ggHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_ggHWW->SetMarkerColor(kOrange-3); 
	hfourlepbestmass_4l_afterSel_new_ggHWW->SetFillColor(kOrange-3);
	hfourlepbestmass_4l_afterSel_new_totSM_HWW->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_ggH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HWW->Add(nEvent_4l_new);
	listtotSM_HWW_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("ttH_HToZZ") < 200){
	cout << "ttH" << endl;
	hfourlepbestmass_4l_afterSel_new_ttH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_ttH->SetMarkerColor(kOrange); 
	hfourlepbestmass_4l_afterSel_new_ttH->SetFillColor(kOrange);
	hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_ttH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HZZ->Add(nEvent_4l_new);
	listtotSM_HZZ_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("bbHToWWTo2L2Nu") < 200){
	cout << "bbH" << endl;
	hfourlepbestmass_4l_afterSel_new_bbHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_bbHWW->SetMarkerColor(kOrange); 
	hfourlepbestmass_4l_afterSel_new_bbHWW->SetFillColor(kOrange);
	hfourlepbestmass_4l_afterSel_new_totSM_HWW->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_ttH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HWW->Add(nEvent_4l_new);
	listtotSM_HWW_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("VBF_HToZZTo4L") < 200){
	cout << "VBF" << endl;
	hfourlepbestmass_4l_afterSel_new_VBFH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VBFH->SetMarkerColor(kOrange-2); 
	hfourlepbestmass_4l_afterSel_new_VBFH->SetFillColor(kOrange-2);
	hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);		
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VBFH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    
	
	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HZZ->Add(nEvent_4l_new);
	listtotSM_HZZ_w->Add(nEvent_4l_w_new);	
      }

      if(datasetnamebkg.find("VBFHToWWTo2L2Nu") < 200){
	cout << "VBF HWW" << endl;
	hfourlepbestmass_4l_afterSel_new_VBFHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VBFHWW->SetMarkerColor(kOrange-2); 
	hfourlepbestmass_4l_afterSel_new_VBFHWW->SetFillColor(kOrange-2);
	hfourlepbestmass_4l_afterSel_new_totSM_HWW->Add(hfourlepbestmass_4l_afterSel_new_new);	
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);		
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && histlabel.find("hM4l_7")>10 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VBFH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    
	
	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HWW->Add(nEvent_4l_new);
	listtotSM_HWW_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("WplusH_HToZZTo4L") < 200 || datasetnamebkg.find("WminusH_HToZZTo4L") < 200){
        cout << "WH" << endl;
        hfourlepbestmass_4l_afterSel_new_WH->Add(hfourlepbestmass_4l_afterSel_new_new); 
        hfourlepbestmass_4l_afterSel_new_WH->SetMarkerColor(kOrange+2); 
        hfourlepbestmass_4l_afterSel_new_WH->SetFillColor(kOrange+2);
	hfourlepbestmass_4l_afterSel_new_WH->SetLineColor(kOrange+2); 

	hfourlepbestmass_4l_afterSel_new_VH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VH->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_VH->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_VH->SetLineColor(kOrange-1); 

	hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Add(hfourlepbestmass_4l_afterSel_new_new);	
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

        char temp[328];
        sprintf(temp,"%s",histosdir.c_str());
        //if(datasetnamebkg.find("WminusH") < 200 && histlabel.find("hM4l_7")>10 && datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_WH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_WH,"WH, m_{H}=125 GeV", "F");  
        //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HZZ->Add(nEvent_4l_new);
	listtotSM_HZZ_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("HWplusJ_HToWWTo2L2Nu") < 200 || datasetnamebkg.find("HWminusJ_HToWWTo2L2Nu") < 200){
        cout << "WH HWW" << endl;
        hfourlepbestmass_4l_afterSel_new_WHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
        hfourlepbestmass_4l_afterSel_new_WHWW->SetMarkerColor(kOrange+2); 
        hfourlepbestmass_4l_afterSel_new_WHWW->SetFillColor(kOrange+2);
	hfourlepbestmass_4l_afterSel_new_WHWW->SetLineColor(kOrange+2); 

	hfourlepbestmass_4l_afterSel_new_VHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VHWW->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_VHWW->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_VHWW->SetLineColor(kOrange-1); 

	hfourlepbestmass_4l_afterSel_new_totSM_HWW->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

        char temp[328];
        sprintf(temp,"%s",histosdir.c_str());
        //if(datasetnamebkg.find("WminusH") < 200 && histlabel.find("hM4l_7")>10 && datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_WH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_WH,"WH, m_{H}=125 GeV", "F");  
        //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HWW->Add(nEvent_4l_new);
	listtotSM_HWW_w->Add(nEvent_4l_w_new);	
      }

      if(datasetnamebkg.find("ZH_HToZZ_4L") < 200){
	cout << "ZH" << endl;
	hfourlepbestmass_4l_afterSel_new_ZH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_ZH->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_ZH->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_ZH->SetLineColor(kOrange-1); 

	hfourlepbestmass_4l_afterSel_new_VH->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VH->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_VH->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_VH->SetLineColor(kOrange-1); 
	
	hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find("ZH_H") < 200 && histlabel.find("hM4l_7")>10 && datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HZZ->Add(nEvent_4l_new);
	listtotSM_HZZ_w->Add(nEvent_4l_w_new);
      }

      if(datasetnamebkg.find("HZJ_HToWWTo2L2Nu") < 200){
	cout << "ZH HWW" << endl;
	hfourlepbestmass_4l_afterSel_new_ZHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_ZHWW->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_ZHWW->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_ZHWW->SetLineColor(kOrange-1); 

	hfourlepbestmass_4l_afterSel_new_VHWW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	hfourlepbestmass_4l_afterSel_new_VHWW->SetMarkerColor(kOrange-1); 
	hfourlepbestmass_4l_afterSel_new_VHWW->SetFillColor(kOrange-1);
	hfourlepbestmass_4l_afterSel_new_VHWW->SetLineColor(kOrange-1); 
	
	hfourlepbestmass_4l_afterSel_new_totSM_HWW->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_totSM_H->Add(hfourlepbestmass_4l_afterSel_new_new);
	cout << "Integral= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;

	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find("ZH_H") < 200 && histlabel.find("hM4l_7")>10 && datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VH->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	//nEvent_4l_w_totSM_H->Add(nEvent_4l_w_new);
	//nEvent_4l_totSM_H->Add(nEvent_4l_new);
	listtotSM_H->Add(nEvent_4l_new);
	listtotSM_H_w->Add(nEvent_4l_w_new);
	listtotSM_HWW->Add(nEvent_4l_new);
	listtotSM_HWW_w->Add(nEvent_4l_w_new);
      }
      

      // DYJetsToLL check normalization
      if(datasetnamebkg.find("DYJetsToLL") <200){
	//hfourlepbestmass_4l_afterSel_new_new->Scale(double(6532812.*9153492../36277961.)*double(hfourlepbestmass_4l_afterSel_new_new->GetEntries()/12245114./hfourlepbestmass_4l_afterSel_new_new->GetEntries()));
	//hfourlepbestmass_4l_afterSel_new_new->Scale(double(4710.*3048.*11974371./80767910.)*double(hfourlepbestmass_4l_afterSel_new_new->GetEntries()/11974371./hfourlepbestmass_4l_afterSel_new_new->GetEntries()));
	// hfourlepbestmass_4l_afterSel_new_new->Scale(double(4710.*3048.*12238430./36257961.)*double(hfourlepbestmass_4l_afterSel_new_new->GetEntries()/12238430./hfourlepbestmass_4l_afterSel_new_new->GetEntries()));
	hfourlepbestmass_4l_afterSel_new_DY->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_DY->SetMarkerColor(kAzure+2);
	hfourlepbestmass_4l_afterSel_new_DY->SetFillColor(kAzure+2);                                       
               
	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	if(datasetnamebkg.find(temp) <200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0 && (datasetnamebkg.find("DYJetsToLL_M-50_TuneZ2Star")<200 || datasetnamebkg.find("DYJetsToLL_M-50")<200)) {
          cout << "DY= " << hfourlepbestmass_4l_afterSel_new_DY->Integral(0,-1) << endl;
	  if (useDYJets==true) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	}
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");

	
	//nEvent_4l_w_DY->Add(nEvent_4l_w_new);
	//nEvent_4l_DY->Add(nEvent_4l_new);
	listDY->Add(nEvent_4l_new);
	listDY_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);

      }

      if(datasetnamebkg.find("ZToEE") <200){
        hfourlepbestmass_4l_afterSel_new_DY->Add(hfourlepbestmass_4l_afterSel_new_new);
        hfourlepbestmass_4l_afterSel_new_DY->SetMarkerColor(kAzure+2);
        hfourlepbestmass_4l_afterSel_new_DY->SetFillColor(kAzure+2);      
        hfourlepbestmass_4l_afterSel_new_DY->SetLineColor(kAzure+2);
               
        char temp[328];
        sprintf(temp,"%s",histosdir.c_str());
        if(datasetnamebkg.find(temp) <200 && (datasetnamebkg.find(whichenergy) < 200 && hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0 && datasetnamebkg.find("ZToEE_NNPDF30_13TeV-powheg_M_1400_2300")<200)){
          cout << "DY= " << hfourlepbestmass_4l_afterSel_new_DY->Integral(0,-1) << endl;
          if (useDYJets==true) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
        }
        //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");

	//nEvent_4l_w_DY->Add(nEvent_4l_w_new);
	//nEvent_4l_DY->Add(nEvent_4l_new);
	listDY->Add(nEvent_4l_new);
	listDY_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);

      }


      // DYlightJetsToLL check normalization
      if(datasetnamebkg.find("DYlightJetsToLL") <200){	
	hfourlepbestmass_4l_afterSel_new_DYlight->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_DYlight->SetMarkerColor(kAzure+6);
	//hfourlepbestmass_4l_afterSel_new_DYlight->SetLineColor(kAzure+6);
	//hfourlepbestmass_4l_afterSel_new_DYlight->SetLineWidth(2); 
	hfourlepbestmass_4l_afterSel_new_DYlight->SetFillColor(kAzure+6); 
	
	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	if(datasetnamebkg.find(temp) <200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0 && datasetnamebkg.find("DYlightJetsToLL_TuneZ2_M-50")<200) {
          cout << "DYlight= " << hfourlepbestmass_4l_afterSel_new_DYlight->Integral(0,-1) << endl;
	  if (useDYJets==false) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
        }
	//hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");
	//nEvent_4l_w_DY->Add(nEvent_4l_w_new);
	//nEvent_4l_DY->Add(nEvent_4l_new);
	listDY->Add(nEvent_4l_new);
	listDY_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }
      
      // DYbb
      if(datasetnamebkg.find("DYbbJetsToLL") <200){
	hfourlepbestmass_4l_afterSel_new_DYbb->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_DYbb->SetMarkerColor(kAzure+2);
	//	hfourlepbestmass_4l_afterSel_new_DYbb->SetLineColor(kAzure+2);
	//	hfourlepbestmass_4l_afterSel_new_DYbb->SetLineWidth(2);
	hfourlepbestmass_4l_afterSel_new_DYbb->SetFillColor(kAzure+2);                                                        
	
	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	if(datasetnamebkg.find(temp) <200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0 && datasetnamebkg.find("DYbbJetsToLL_TuneZ2_M-50")<200) {
          cout << "DYbb= " << hfourlepbestmass_4l_afterSel_new_DYbb->Integral(0,-1) << endl;
	  if (useDYJets==false) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
        }

	//nEvent_4l_w_DY->Add(nEvent_4l_w_new);
	//nEvent_4l_DY->Add(nEvent_4l_new);
	listDY->Add(nEvent_4l_new);
	listDY_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }

      //DYCC
      if(datasetnamebkg.find("DYccJetsToLL") < 200){
	
	hfourlepbestmass_4l_afterSel_new_DYcc->Add(hfourlepbestmass_4l_afterSel_new_new);
	hfourlepbestmass_4l_afterSel_new_DYcc->SetMarkerColor(kRed+0);
	// hfourlepbestmass_4l_afterSel_new_DYcc->SetLineColor(kRed+0);
	// hfourlepbestmass_4l_afterSel_new_DYcc->SetLineWidth(2);
       	hfourlepbestmass_4l_afterSel_new_DYcc->SetFillColor(kRed+0);                                                        
	char temp[328];
	sprintf(temp,"%s",histosdir.c_str());
	if(datasetnamebkg.find(temp) <200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0 && datasetnamebkg.find("DYccJetsToLL_M-50_TuneZ2Star")<200) {
          cout << "DYcc= " << hfourlepbestmass_4l_afterSel_new_DYcc->Integral(0,-1) << endl;
	  if (useDYJets==false) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
        }

	//nEvent_4l_w_DY->Add(nEvent_4l_w_new);
	//nEvent_4l_DY->Add(nEvent_4l_new);
	listDY->Add(nEvent_4l_new);
	listDY_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }

      if (useDYJetsFromData==false){
	// WW
	if(datasetnamebkg.find("_WWTo") < 200){
	  hfourlepbestmass_4l_afterSel_new_WW->Add(hfourlepbestmass_4l_afterSel_new_new); 
	  hfourlepbestmass_4l_afterSel_new_WW->SetMarkerColor(kCyan+3); 
	  hfourlepbestmass_4l_afterSel_new_WW->SetFillColor(kCyan+3);
	  hfourlepbestmass_4l_afterSel_new_WW->SetLineColor(kCyan+3);
	  
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_WW->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");    

	  //nEvent_4l_w_WZ_WW_Wj->Add(nEvent_4l_w_new);
	  //nEvent_4l_w_WZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}     
	
	// WZ     
	if(datasetnamebkg.find("_WZTo") < 200){  
	  hfourlepbestmass_4l_afterSel_new_WZ->Add(hfourlepbestmass_4l_afterSel_new_new);
	  hfourlepbestmass_4l_afterSel_new_WZ->SetMarkerColor(kCyan-2);  
	  hfourlepbestmass_4l_afterSel_new_WZ->SetFillColor(kCyan-2);  
	  hfourlepbestmass_4l_afterSel_new_WZ->SetLineColor(kCyan-2);  

	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_WZ->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP"); 

	  //nEvent_4l_w_WZ_WW_Wj->Add(nEvent_4l_w_new);
	  //nEvent_4l_WZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}    
	
	// TTT
	if(datasetnamebkg.find("TTT") < 200){ 
	  hfourlepbestmass_4l_afterSel_new_TT->Add(hfourlepbestmass_4l_afterSel_new_new);     
	  hfourlepbestmass_4l_afterSel_new_TT->SetMarkerColor(kTeal-6); 
	  hfourlepbestmass_4l_afterSel_new_TT->SetFillColor(kTeal-6);   
	  hfourlepbestmass_4l_afterSel_new_TT->SetLineColor(kTeal-6);   
	  
	  cout << "TT+jets= " << hfourlepbestmass_4l_afterSel_new_TT->GetEntries() << endl;
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_TT->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");

	  //nEvent_4l_w_TT->Add(nEvent_4l_w_new);
	  //nEvent_4l_TT->Add(nEvent_4l_new);
	  listTT->Add(nEvent_4l_new);
	  listTT_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}      
	
	
	// W+jets		      					
	if(datasetnamebkg.find("_WJets") < 200){
	  cout << "Wjets" << endl;
	  hfourlepbestmass_4l_afterSel_new_Wj->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_Wj->SetMarkerColor(kSpring);	
	  hfourlepbestmass_4l_afterSel_new_Wj->SetFillColor(kSpring);	
	  
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_Wj->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");	        

	  //nEvent_4l_w_WZ_WW_Wj->Add(nEvent_4l_w_new);
	  //nEvent_4l_WZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj->Add(nEvent_4l_new);
	  listWZ_WW_Wj_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}   

	/// VVV
	if(datasetnamebkg.find("_ZZZ") < 200){
	  cout << "ZZZ" << endl;
	  hfourlepbestmass_4l_afterSel_new_VVV->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_VVV->SetMarkerColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetFillColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetLineColor(kAzure-4);	
	   	  
	  char temp[328];
	  //sprintf(temp,"%s",histosdir.c_str());
	  //if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VVV->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");	        
	  
	  sprintf(temp,"%s/output_ZZZ",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && datasetnamebkg.find("ZZZ") < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VVV->GetEntries()>0. ){ 
	    legend->AddEntry(hfourlepbestmass_4l_afterSel_new_VVV,"VVV", "F");  
	    //cout << "Label= ZZZ     Entries= " << hfourlepbestmass_4l_afterSel_new_ZZZ->Integral(0,-1) <<endl;
	    cout << "Label= Total VVV     Entries= " << hfourlepbestmass_4l_afterSel_new_VVV->Integral(0,-1) <<endl;
	  }
	  //nEvent_4l_w_VVV->Add(nEvent_4l_w_new);
	  //nEvent_4l_VVV->Add(nEvent_4l_new);
	  listVVV->Add(nEvent_4l_new);
	  listVVV_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}  
	
	if(datasetnamebkg.find("_WWZ") < 200){
	  cout << "WWZ" << endl;
	  hfourlepbestmass_4l_afterSel_new_VVV->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_VVV->SetMarkerColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetFillColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetLineColor(kAzure-4);	
	   
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  //if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VVV->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");	        

	  //nEvent_4l_w_VVV->Add(nEvent_4l_w_new);
	  //nEvent_4l_VVV->Add(nEvent_4l_new);
	  listVVV->Add(nEvent_4l_new);
	  listVVV_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}  
	
	if(datasetnamebkg.find("_WZZ") < 200){
	  cout << "WZZ" << endl;
	  hfourlepbestmass_4l_afterSel_new_VVV->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_VVV->SetMarkerColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetFillColor(kAzure-4);	
	  hfourlepbestmass_4l_afterSel_new_VVV->SetLineColor(kAzure-4);	
	   	  
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  //if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_VVV->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");	        

	  //nEvent_4l_w_VVV->Add(nEvent_4l_w_new);
	  //nEvent_4l_VVV->Add(nEvent_4l_new);
	  listVVV->Add(nEvent_4l_new);
	  listVVV_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}  
	
	
	//TTV
	if(datasetnamebkg.find("_TTZ") < 200){
	  cout << "TTZ" << endl;
	  hfourlepbestmass_4l_afterSel_new_TTV->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_TTV->SetMarkerColor(kAzure+4);	
	  hfourlepbestmass_4l_afterSel_new_TTV->SetFillColor(kAzure+4);	
	  hfourlepbestmass_4l_afterSel_new_TTV->SetLineColor(kAzure+4);	
	   	  
	  char temp[328];
	  sprintf(temp,"%s/output_TTZ",histosdir.c_str());
	  if(datasetnamebkg.find(temp) < 200 && datasetnamebkg.find("TTZ") < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_TTV->GetEntries()>0. ){ 
	    legend->AddEntry(hfourlepbestmass_4l_afterSel_new_TTV,"TTV", "F");  
	    //cout << "Label= TTZ     Entries= " << hfourlepbestmass_4l_afterSel_new_TTZ->Integral(0,-1) <<endl;
	    cout << "Label= Total TTV     Entries= " << hfourlepbestmass_4l_afterSel_new_TTV->Integral(0,-1) <<endl;
	  }
	  //nEvent_4l_w_TTV->Add(nEvent_4l_w_new);
	  //nEvent_4l_TTV->Add(nEvent_4l_new);
	  listTTV->Add(nEvent_4l_new);
	  listTTV_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}  

	if(datasetnamebkg.find("_TTW") < 200){
	  cout << "TTW" << endl;
	  hfourlepbestmass_4l_afterSel_new_TTV->Add(hfourlepbestmass_4l_afterSel_new_new);        
	  hfourlepbestmass_4l_afterSel_new_TTV->SetMarkerColor(kAzure+4);	
	  hfourlepbestmass_4l_afterSel_new_TTV->SetFillColor(kAzure+4);	
	  hfourlepbestmass_4l_afterSel_new_TTV->SetLineColor(kAzure+4);	
	  
	  char temp[328];
	  sprintf(temp,"%s",histosdir.c_str());
	  //if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_TTV->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 
	  //hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");	        

	  //nEvent_4l_w_TTV->Add(nEvent_4l_w_new);
	  //nEvent_4l_TTV->Add(nEvent_4l_new);
	  listTTV->Add(nEvent_4l_new);
	  listTTV_w->Add(nEvent_4l_w_new);
	  listtotbkg_noSM_H->Add(nEvent_4l_new);
	  listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
	}  


      } 
            
    }
    //
    else if(datasetnamebkg.find("GluGluToZZTo") < 200 || datasetnamebkg.find("GluGluToContinToZZTo") < 200){
      cout << "Adding sample ggZZ" << endl;
      hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) errorZZ=errorZZ+pow(sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(),2);
      //cout << sqrt(errorZZ) << endl;
      hfourlepbestmass_4l_afterSel_new_ggZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_ggZZ->SetLineColor(1);
      hfourlepbestmass_4l_afterSel_new_ggZZ->SetFillColor(kPink+5);
      hfourlepbestmass_4l_afterSel_new_ggZZ->SetLineWidth(1);
      
      hfourlepbestmass_4l_afterSel_new_ZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineColor(1);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetFillColor(ZZBgColor);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineWidth(1);
      cout << "Label= " << Vlabelbkg.at(datasetId) << 
	"  Entries= " << hfourlepbestmass_4l_afterSel_new_new->GetEntries() <<
	"  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1);
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) cout << "  Error= " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(); 
      cout <<endl;
      //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  

      if(datasetnamebkg.find("GluGluToContinToZZTo2e2mu") < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) ){ 
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_ggZZ,"ggZZ", "F");  
	cout << "Label= ggZZ     Entries= " << hfourlepbestmass_4l_afterSel_new_ggZZ->Integral(0,-1) <<endl;
	cout << "Label= Total ZZ     Entries= " << hfourlepbestmass_4l_afterSel_new_ZZ->Integral(0,-1) <<endl;
      }  
      //nEvent_4l_w_ZZ->Add(nEvent_4l_w_new);
      //nEvent_4l_ZZ->Add(nEvent_4l_new);
      listZZ->Add(nEvent_4l_new);
      listZZ_w->Add(nEvent_4l_w_new);
      listggZZ->Add(nEvent_4l_new);
      listggZZ_w->Add(nEvent_4l_w_new);
      //nEvent_4l_w_totalbkgMC->Add(nEvent_4l_w_new);
      //nEvent_4l_totalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC_w->Add(nEvent_4l_w_new);
      listtotbkg_noSM_H->Add(nEvent_4l_new);
      listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
    }     
    else if( datasetnamebkg.find("_ZZTo4L") < 200 ){
      cout << "Adding sample qqZZ" << endl;
      hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);      
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) errorZZ=errorZZ+pow(sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(),2);
      //cout << sqrt(errorZZ) << endl;
      hfourlepbestmass_4l_afterSel_new_qqZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetLineColor(1);
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetFillColor(kPink+5);
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetLineWidth(1);

      hfourlepbestmass_4l_afterSel_new_ZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineColor(ZZBgColor);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetFillColor(ZZBgColor);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineWidth(1);

      char temp[328];
      if (whichsample.find("8TeV")<200) sprintf(temp,"%s/output_ZZTo2e2mu_%s",histosdir.c_str(),whichsample.c_str());
      else if (whichsample.find("7TeV")<200) sprintf(temp,"%s/output_ZZTo2e2mu_mll4_%s",histosdir.c_str(),whichsample.c_str());
      else if (whichsample.find("13TeV")<200) sprintf(temp,"%s/output_ZZTo4L_%s",histosdir.c_str(),whichsample.c_str());
      //else if (whichsample.find("13TeV")<200) sprintf(temp,"%s/output_ZZ_TuneCUETP8M1_%s",histosdir.c_str(),whichsample.c_str());
      //cout << "Temp is=" << temp<< endl;

      if(datasetnamebkg.find(temp) < 200 ){
	//cout << "Ciao" << endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qqZZ,"ZZ", "F");  
	if (errorZZ>0.) errorZZ=sqrt(errorZZ);
	legend->AddEntry(hfourlepbestmass_4l_afterSel_new_ZZ,"Z#gamma^{*}, ZZ", "F");  
	cout << "Label= qqZZ     Entries= " << hfourlepbestmass_4l_afterSel_new_qqZZ->Integral(0,-1) <<endl;
        cout << "Label= qqZZ+ggZZ   Entries= " << hfourlepbestmass_4l_afterSel_new_ZZ->Integral(0,-1) 
	     << "  Error= " << errorZZ <<endl;
	if (histlabel.find("hM4l_9")<10 ) outputyields << "ZZ " << hfourlepbestmass_4l_afterSel_new_ZZ->Integral(0,-1) << " +/- " << errorZZ << endl;
      }  

      cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1);
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) cout << "  Error= " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(); 
      cout <<endl;

      //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  

      //nEvent_4l_w_ZZ->Add(nEvent_4l_w_new);
      //nEvent_4l_ZZ->Add(nEvent_4l_new);
      listZZ->Add(nEvent_4l_new);
      listZZ_w->Add(nEvent_4l_w_new);
      listqqZZ->Add(nEvent_4l_new);
      listqqZZ_w->Add(nEvent_4l_w_new);
      //nEvent_4l_w_totalbkgMC->Add(nEvent_4l_w_new);
      //nEvent_4l_totalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC_w->Add(nEvent_4l_w_new);
      listtotbkg_noSM_H->Add(nEvent_4l_new);
      listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
    } 

    else if( datasetnamebkg.find("_ZZTo2L2Nu") < 200 ){
      cout << "Adding sample qqZZ2l2nu" << endl;
      hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);      
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) errorZZ=errorZZ+pow(sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(),2);
      //cout << sqrt(errorZZ) << endl;
      hfourlepbestmass_4l_afterSel_new_qqZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetLineColor(1);
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetFillColor(kPink+5);
      hfourlepbestmass_4l_afterSel_new_qqZZ->SetLineWidth(1);

      hfourlepbestmass_4l_afterSel_new_ZZ->Add(hfourlepbestmass_4l_afterSel_new_new);      
      //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineColor(ZZBgColor);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetFillColor(ZZBgColor);
      hfourlepbestmass_4l_afterSel_new_ZZ->SetLineWidth(1);

      char temp[328];
      if (whichsample.find("13TeV")<200) sprintf(temp,"%s/output_ZZTo2L2Nu_%s",histosdir.c_str(),whichsample.c_str());

      if(datasetnamebkg.find(temp) < 200 ){
	//cout << "Ciao" << endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qqZZ,"ZZ", "F");  
	if (errorZZ>0.) errorZZ=sqrt(errorZZ);
	cout << "Label= qqZZ (with 2l2nu)     Entries= " << hfourlepbestmass_4l_afterSel_new_qqZZ->Integral(0,-1) <<endl;
        cout << "Label= qqZZ+ggZZ (with 2l2nu)  Entries= " << hfourlepbestmass_4l_afterSel_new_ZZ->Integral(0,-1) 
	     << "  Error= " << errorZZ <<endl;
	if (histlabel.find("hM4l_9")<10 ) outputyields << "ZZ " << hfourlepbestmass_4l_afterSel_new_ZZ->Integral(0,-1) << " +/- " << errorZZ << endl;
      }  

      cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1);
      if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) cout << "  Error= " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(); 
      cout <<endl;

      //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  

      //nEvent_4l_w_ZZ->Add(nEvent_4l_w_new);
      //nEvent_4l_ZZ->Add(nEvent_4l_new);
      listZZ->Add(nEvent_4l_new);
      listZZ_w->Add(nEvent_4l_w_new);
      listqqZZ->Add(nEvent_4l_new);
      listqqZZ_w->Add(nEvent_4l_w_new);
      //nEvent_4l_w_totalbkgMC->Add(nEvent_4l_w_new);
      //nEvent_4l_totalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC->Add(nEvent_4l_new);
      listtotalbkgMC_w->Add(nEvent_4l_w_new);
      listtotbkg_noSM_H->Add(nEvent_4l_new);
      listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
    } 


    else if (useDYJetsFromData==false){      
      if(datasetnamebkg.find("_MuPt5Enriched") < 200 ){
	hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
	hfourlepbestmass_4l_afterSel_new_qcdMu->Add(hfourlepbestmass_4l_afterSel_new_new);      
	//hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
	hfourlepbestmass_4l_afterSel_new_qcdMu->SetLineColor(1);
	hfourlepbestmass_4l_afterSel_new_qcdMu->SetFillColor(kTeal-8);
	hfourlepbestmass_4l_afterSel_new_qcdMu->SetLineWidth(1);
	
	char temp[328];
	sprintf(temp,"%s/output_QCD_Pt-15to20_MuPt5Enriched",histosdir.c_str());
	
	if(datasetnamebkg.find(temp) < 200 ){ // provided that this is the last single-top sample
	  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qcdMu,"QCD MuPt5", "F");  
	  cout << "Label= QCD MuPt5    Entries= " << hfourlepbestmass_4l_afterSel_new_qcdMu->Integral(0,-1) <<endl;
	}  
	cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  

	listtotalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      } 
      else if(datasetnamebkg.find("_doubleEMEnriched") < 200 ){
	hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
	hfourlepbestmass_4l_afterSel_new_qcdDEM->Add(hfourlepbestmass_4l_afterSel_new_new);      
	//hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
	hfourlepbestmass_4l_afterSel_new_qcdDEM->SetLineColor(1);
	hfourlepbestmass_4l_afterSel_new_qcdDEM->SetFillColor(kTeal+8);
	hfourlepbestmass_4l_afterSel_new_qcdDEM->SetLineWidth(1);
	
	char temp[328];
	sprintf(temp,"%s/output_QCD_Pt-80_doubleEMEnriched",histosdir.c_str());
	
	if(datasetnamebkg.find(temp) < 80 ){ 
	  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qcdDEM,"QCD doubleEM", "F");  
	  cout << "Label= QCD double EM    Entries= " << hfourlepbestmass_4l_afterSel_new_qcdMu->Integral(0,-1) <<endl;
	}  
	cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	listtotalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }  
      else if(datasetnamebkg.find("_BCtoE") < 200 ){
	hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
	hfourlepbestmass_4l_afterSel_new_qcdBC->Add(hfourlepbestmass_4l_afterSel_new_new);      
	//hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
	hfourlepbestmass_4l_afterSel_new_qcdBC->SetLineColor(1);
	hfourlepbestmass_4l_afterSel_new_qcdBC->SetFillColor(kTeal-2);
	hfourlepbestmass_4l_afterSel_new_qcdBC->SetLineWidth(1);
	
	char temp[328];
	sprintf(temp,"%s/output_QCD_Pt-20to30_BCtoE",histosdir.c_str());
	
	if(datasetnamebkg.find(temp) < 200){ // provided that this is the last single-top sample
	  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qcdBC,"QCD BCtoE", "F");  
	  cout << "Label= QCD BCtoE    Entries= " << hfourlepbestmass_4l_afterSel_new_qcdBC->Integral(0,-1) <<endl;
	}  
	cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F");  
	listtotalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }
       else if(datasetnamebkg.find("QCD_Pt") ){
	
	hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
	hfourlepbestmass_4l_afterSel_new_qcd->Add(hfourlepbestmass_4l_afterSel_new_new);      
	//hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(1001); 
	hfourlepbestmass_4l_afterSel_new_qcd->SetLineColor(kTeal-2);
	hfourlepbestmass_4l_afterSel_new_qcd->SetFillColor(kTeal-2);
	hfourlepbestmass_4l_afterSel_new_qcd->SetLineWidth(1);

	char temp[328];
	//sprintf(temp,"%s/output_QCD_Pt_10to15",histosdir.c_str());
        sprintf(temp,"%s/output_QCD_Pt_1000to1400",histosdir.c_str());
	
	//cout << "alpha" << temp << datasetnamebkg.find(temp) << endl;
	//sprintf(temp,"%s",histosdir.c_str());
	//if(datasetnamebkg.find(temp) < 200 && (datasetnamebkg.find(whichenergy) < 200 || datasetnamebkg.find(whichsample) < 200) && hfourlepbestmass_4l_afterSel_new_Wj->GetEntries()>0. ) legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 

	if(datasetnamebkg.find(temp) < 200 && hfourlepbestmass_4l_afterSel_new_qcd->GetEntries()>0.){ 
	  leg0->AddEntry(hfourlepbestmass_4l_afterSel_new_qcd,"QCD", "F");  
	  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_qcd,"QCD", "F");  
	  cout << "Label= QCD Entries= " << hfourlepbestmass_4l_afterSel_new_qcd->Integral(0,-1) <<endl;
	}  
	cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;
	//legend->AddEntry(hfourlepbestmass_4l_afterSel_new_new,Vlabelbkg.at(datasetId).c_str(), "F"); 

	listQCD->Add(nEvent_4l_new);
	listQCD_w->Add(nEvent_4l_w_new);

	listtotalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
       }       
      // single top
      //else if (datasetId>=12 && datasetId<=14){
      else if(datasetnamebkg.find("ST_") < 200 ||  datasetnamebkg.find("Tbar_") < 200 ){
	hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin,histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
	hfourlepbestmass_4l_afterSel_new_singlet->Add(hfourlepbestmass_4l_afterSel_new_new);
	// hfourlepbestmass_4l_afterSel_new_new->SetMarkerColor(datasetId+4);
	//       hfourlepbestmass_4l_afterSel_new_new->SetMarkerStyle(26);
	//       hfourlepbestmass_4l_afterSel_new_new->SetLineWidth(2);
	//       hfourlepbestmass_4l_afterSel_new_new->Draw("sameP");
	hfourlepbestmass_4l_afterSel_new_singlet->SetLineColor(Vcolorbkg.at(datasetId)/*datasetId-12+5*/);
	hfourlepbestmass_4l_afterSel_new_singlet->SetFillColor(kViolet);
	//hfourlepbestmass_4l_afterSel_new_singlet->SetFillStyle(3004);  
	hfourlepbestmass_4l_afterSel_new_singlet->SetLineWidth(1);
	
	
	char temp[328];
	sprintf(temp,"%s/output_ST_",histosdir.c_str());
	
	if(datasetnamebkg.find(temp) < 200 && datasetnamebkg.find("t-channel") < 200 ){ // provided that this is the last single-top sample
	  //hfourlepbestmass_4l_afterSel_new_singlet->Draw("sameP");
	  leg0->AddEntry(hfourlepbestmass_4l_afterSel_new_singlet,"Single Top", "F");  
	  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_singlet,"Single Top", "F");  
	  cout << "Label= single t     Entries= " << hfourlepbestmass_4l_afterSel_new_singlet->Integral(0,-1) <<endl;
	}  
	cout << "Label= " << Vlabelbkg.at(datasetId) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1) <<endl;

	//nEvent_4l_w_ST->Add(nEvent_4l_w_new);
	//nEvent_4l_ST->Add(nEvent_4l_new);
	listST->Add(nEvent_4l_new);
	listST_w->Add(nEvent_4l_w_new);

	listTT->Add(nEvent_4l_new);
	listTT_w->Add(nEvent_4l_w_new);

	//nEvent_4l_w_totalbkgMC->Add(nEvent_4l_w_new);
	//nEvent_4l_totalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC->Add(nEvent_4l_new);
	listtotalbkgMC_w->Add(nEvent_4l_w_new);
	listtotbkg_noSM_H->Add(nEvent_4l_new);
	listtotbkg_noSM_H_w->Add(nEvent_4l_w_new);
      }
    }
    
    char tempp[328];
    if (whichsample.find("8TeV")<200) sprintf(tempp,"%s/output_ZZTo2e2mu_%s",histosdir.c_str(),whichsample.c_str());
    else if (whichsample.find("7TeV")<200) sprintf(tempp,"%s/output_ZZTo2e2mu_mll4_%s",histosdir.c_str(),whichsample.c_str());    
    else if (whichsample.find("13TeV")<200) sprintf(tempp,"%s/output_ZZTo4L_%s",histosdir.c_str(),whichsample.c_str());  
    //else if (whichsample.find("13TeV")<200) sprintf(tempp,"%s/output_ZZ_TuneCUETP8M1_%s",histosdir.c_str(),whichsample.c_str());    
    
    if(datasetnamebkg.find(tempp) < 500) {
      cout << "Stacking ZZ (ggZZ+qqZZ)" << endl;
      htotal->Add(hfourlepbestmass_4l_afterSel_new_ZZ);
      //htotal->Add(hfourlepbestmass_4l_afterSel_new_qqZZ); 
      htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_ZZ);
      hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_ZZ); 
      nEvent_4l_ZZ->Merge(listZZ);
      nEvent_4l_w_ZZ->Merge(listZZ_w);
      nEvent_4l_qqZZ->Merge(listqqZZ);
      nEvent_4l_w_qqZZ->Merge(listqqZZ_w);
      nEvent_4l_ggZZ->Merge(listggZZ);
      nEvent_4l_w_ggZZ->Merge(listggZZ_w);      
    }
    else {
       
       char temppp[328];
       sprintf(temppp,"%s",histosdir.c_str());

       // Higgs bkg
       if(datasetnamebkg.find(temppp) < 400 && (
	   datasetnamebkg.find("output_GluGluHToZZTo4L") < 400 || 
	  (datasetnamebkg.find("output_GluGluHToZZTo4L") < 400 && datasetnamebkg.find(whichenergy.c_str())<400)
					       )
	  )  { 
	 //if (histlabel.find("hM4l_7")>10) {
	   cout << "Adding ggHZZ and gggHWW" << endl;
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_ggH); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_ggH); 	   
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_totSM_H);  
           //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_totSM_H);		 
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_totSM_HWW);  
           htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_totSM_HWW);	
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_totSM_HZZ);  
           htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_totSM_HZZ);
	   nEvent_4l_totSM_H->Merge(listtotSM_H);
	   nEvent_4l_w_totSM_H->Merge(listtotSM_H_w);
	   nEvent_4l_totSM_HZZ->Merge(listtotSM_HZZ);
	   nEvent_4l_w_totSM_HZZ->Merge(listtotSM_HZZ_w);
	   nEvent_4l_totSM_HWW->Merge(listtotSM_HWW);
	   nEvent_4l_w_totSM_HWW->Merge(listtotSM_HWW_w);
	   //}
       }
       if(datasetnamebkg.find(temppp) < 400 && (
          datasetnamebkg.find("output_WminusH_HToZZTo4L") < 400 || 
          (datasetnamebkg.find("output_WminusH_HToZZTo4L") < 400 && datasetnamebkg.find(whichenergy.c_str())<400)
                                               )
          )  { 
	 //if (histlabel.find("hM4l_7")>10) {
	   cout << "Adding WH" << endl;
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_WH); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_WH); 
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_WHWW); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_WHWW); 
	   //}
       }
       if(datasetnamebkg.find(temppp) < 400 && (
	  datasetnamebkg.find("output_ZH_HToZZ_4L") < 400 || 
	  (datasetnamebkg.find("output_ZH_HToZZ_4L") < 400 && datasetnamebkg.find(whichenergy.c_str())<400)
					       )
	  )  { 
	 //if (histlabel.find("hM4l_7")>10) {
	   cout << "Adding ZH" << endl;
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_ZH); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_ZH);
	    //htotal->Add(hfourlepbestmass_4l_afterSel_new_ZHWW); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_ZHWW);
	   //}
       }
       if(datasetnamebkg.find(temppp) < 200 && (
	  datasetnamebkg.find("output_ttH_HToZZ_4L") < 200 || 
	  (datasetnamebkg.find("output_ttH_HToZZ_4L") < 200 && datasetnamebkg.find(whichenergy.c_str())<400)
						)
	  )  { 
	 //if (histlabel.find("hM4l_7")>10) {
	   cout << "Adding ttH and bbH" << endl;
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_ttH); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_ttH); 
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_bbHWW); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_bbHWW); 
	   //}
       }
       if(datasetnamebkg.find(temppp) < 200 && (
	  datasetnamebkg.find("output_VBF_HToZZ4L") < 200 || 
	  (datasetnamebkg.find("output_VBF_HToZZ4L") < 200 && datasetnamebkg.find(whichenergy.c_str())<400)
					       )
	  )  { 
	 //if (histlabel.find("hM4l_7")>10) {
	   cout << "Adding VBF" << endl;
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_VBFH); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_VBFH); 
	   //htotal->Add(hfourlepbestmass_4l_afterSel_new_VBFHWW); 
	   //htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_VBFHWW); 
	   //}
       }

       // other backgrounds
       if (useDYJets==true){
	 if(datasetnamebkg.find(temppp) < 200 && (
						 datasetnamebkg.find("output_DYJetsToLL_M-50_Tune") < 200 || 
						 datasetnamebkg.find("output_ZToEE_NNPDF30_13TeV-powheg_M_1400_2300") <200 ||
						 (datasetnamebkg.find("output_DYJetsToLL_TuneZ2_M-50") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
						 ) 
	    )  {
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_DY);
	   htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_DY);
	   nEvent_4l_DY->Merge(listDY);
	   nEvent_4l_w_DY->Merge(listDY_w);
	   hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_DY); 
	 }
       }
       else if (useDYJets==false){
	 if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_DYlightJetsToLL_TuneZ2_M-50") < 200 )  {
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_DYlight);
	   htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_DYlight);
	   hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_DYlight); 
	   nEvent_4l_DY->Merge(listDY);
	   nEvent_4l_w_DY->Merge(listDY_w);
	 }
	 if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_DYbbJetsToLL_TuneZ2_M-50") < 200 )  {
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_DYbb);
	   htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_DYbb);
	 }
	 if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_DYccJetsToLL_TuneZ2_M-50") < 200 )  {
	   htotal->Add(hfourlepbestmass_4l_afterSel_new_DYcc);
	   htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_DYcc);
	 }
       }

       if(datasetnamebkg.find(temppp) < 200 && (
	  datasetnamebkg.find("output_WWTo") < 200 || 
	  (datasetnamebkg.find("output_WWTo") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
	  )
	  )  { 
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_WW); 
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_WW); 
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_WW); 
       }
       if(datasetnamebkg.find(temppp) < 200 && (
					       datasetnamebkg.find("output_WZTo") < 200 ||
					       (datasetnamebkg.find("output_WZTo") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
					       ) 
	  )  {
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_WZ);         
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_WZ); 
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_WZ); 
	 nEvent_4l_WZ_WW_Wj->Merge(listWZ_WW_Wj);
	 nEvent_4l_w_WZ_WW_Wj->Merge(listWZ_WW_Wj_w);
       }
       if(datasetnamebkg.find(temppp) < 200 && (
					       datasetnamebkg.find("output_TTT") < 200 || 
					       (datasetnamebkg.find("output_TTT") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
					       )
	  )  {
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_TT);                        
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_TT);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_TT); 
	 nEvent_4l_TT->Merge(listTT);
	 nEvent_4l_w_TT->Merge(listTT_w);
       }
       if(datasetnamebkg.find(temppp) < 200 && (
					       datasetnamebkg.find("output_WJ") < 200 ||
					       (datasetnamebkg.find("output_WJ") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
					       )
	  )  {
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_Wj);   
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_Wj);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_Wj); 
       }
       
       if(datasetnamebkg.find(temppp) < 200 && (
					       datasetnamebkg.find("output_ZZZ") < 200 ||
					       (datasetnamebkg.find("output_ZZZ") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
					       )
	  )  {
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_VVV);   
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_VVV);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_VVV); 
	 nEvent_4l_VVV->Merge(listVVV);
	 nEvent_4l_w_VVV->Merge(listVVV_w);
       }

       if(datasetnamebkg.find(temppp) < 200 && (
						datasetnamebkg.find("output_TTZ") < 200 ||
						(datasetnamebkg.find("output_TTZ") < 200 && datasetnamebkg.find(whichenergy.c_str())<200)
						)
	  )  {
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_TTV);   
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_TTV);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_TTV); 
	 nEvent_4l_TTV->Merge(listTTV);
	 nEvent_4l_w_TTV->Merge(listTTV_w);
       }
       
       
       //if(datasetnamebkg.find("GluGluToZZTo4mu_BackgroundOnly") < 200 ) // provided that this is the last single-top sample      
       //htotal->Add(hfourlepbestmass_4l_afterSel_new_ggZZ);      
       
       //if(datasetnamebkg.find(temppp) < 200 datasetnamebkg.find("output_ZZTo2e2mu_8TeV") < 200 ) 
       //	htotal->Add(hfourlepbestmass_4l_afterSel_new_qqZZ); 
       ////htotal->Add(hfourlepbestmass_4l_afterSel_new_qqZZ); 
       
       if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_QCD_Pt-15to20_MuPt5Enriched") < 200 ){ 
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_qcdMu); 
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_qcdMu);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_qcdMu); 
       }
       
       if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_QCD_Pt-40_doubleEMEnriched") < 200 ){ 
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_qcdDEM); 
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_qcdDEM); 
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_qcdDEM); 
       }
       
       if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_QCD_Pt_20to30_BCtoE") < 200 ){     
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_qcdBC);   
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_qcdBC);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_qcdBC); 
       }   

       if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_QCD_Pt_1000to1400") < 200 ){
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_qcd);   
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_qcd);
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_qcd); 
	 nEvent_4l_w_QCD->Merge(listQCD_w);
	 nEvent_4l_QCD->Merge(listQCD);
       }
       
       if(datasetnamebkg.find(temppp) < 200 && datasetnamebkg.find("output_ST_") < 200 && datasetnamebkg.find("t-channel") < 200 ){     	 
	 htotal->Add(hfourlepbestmass_4l_afterSel_new_singlet); 
	 htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_singlet); 
	 hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Add(hfourlepbestmass_4l_afterSel_new_singlet); 
       }     
    }
    
    // htotal->Add(hfourlepbestmass_4l_afterSel_new_new);
    
  }
  
  // 
  nEvent_4l_w_totalbkgMC->Merge(listtotalbkgMC_w);
  nEvent_4l_totalbkgMC->Merge(listtotalbkgMC);	
  nEvent_4l_w_totbkg_noSM_H->Merge(listtotbkg_noSM_H_w);
  nEvent_4l_totbkg_noSM_H->Merge(listtotbkg_noSM_H);	

  // Building the ratio
  htotalHistoRatio->Sumw2();
  htotalHistoRatio->Divide(htotaldata,htotalHisto,1.,1.);

/*
  for (int nbins=1;nbins<=htotaldata->GetNbinsX(); nbins++){
    //cout << "Total: BinCenter=" << htotalHisto->GetBinCenter(nbins) << " BinContent=" << htotalHisto->GetBinContent(nbins) << " BinErrorContent=" << htotalHisto->GetBinError(nbins) << endl;
    if (htotalHisto->GetBinContent(nbins)>0.) {
      htotalHistoRatio->SetBinContent(nbins,double(htotaldata->GetBinContent(nbins)/htotalHisto->GetBinContent(nbins)));
      //htotalHistoRatio->SetBinError(nbins,double(sqrt(htotaldata->GetBinContent(nbins))/htotalHisto->GetBinContent(nbins)));
      htotalHistoRatio->SetBinError(nbins,double(sqrt( 
		 (1./(htotalHisto->GetBinContent(nbins)*htotalHisto->GetBinContent(nbins)))*htotaldata->GetBinContent(nbins) +
		 (htotaldata->GetBinContent(nbins)*htotaldata->GetBinContent(nbins)/pow(htotalHisto->GetBinContent(nbins),4))
		 *htotalHisto->GetBinContent(nbins) 						      
		 )));
		      
    }
  }
*/

  // Signal
  TH1F *hfourlepbestmass_4l_afterSel_new_signal125 = new TH1F("hfourlepbestmass_4l_afterSel_new_signal125", "hfourlepbestmass_4l_afterSel_new_signal125", Nbins, Xmin, Xmax);  
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_DM1 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_DM1", "hfourlepbestmass_4l_afterSel_new_monoH_DM1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_DM10 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_DM10", "hfourlepbestmass_4l_afterSel_new_monoH_DM10", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_DM100 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_DM100", "hfourlepbestmass_4l_afterSel_new_monoH_DM100", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_DM500 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_DM500", "hfourlepbestmass_4l_afterSel_new_monoH_DM500", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_DM1000 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_DM1000", "hfourlepbestmass_4l_afterSel_new_monoH_DM1000", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1", "hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10", "hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100", "hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500", "hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000", "hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000", Nbins, Xmin, Xmax);

  // 2HDM 

  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP600 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP600", "hfourlepbestmass_4l_afterSel_new_monoH_MZP600", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP800 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP800", "hfourlepbestmass_4l_afterSel_new_monoH_MZP800", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP1000 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP1000", "hfourlepbestmass_4l_afterSel_new_monoH_MZP1000", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP1200;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_afterSel_new_monoH_MZP1200 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP1200", "hfourlepbestmass_4l_afterSel_new_monoH_MZP1200", NMBINS, logMbins); 
  }
  else hfourlepbestmass_4l_afterSel_new_monoH_MZP1200 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP1200", "hfourlepbestmass_4l_afterSel_new_monoH_MZP1200", Nbins, Xmin, Xmax);
  
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP1400 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP1400", "hfourlepbestmass_4l_afterSel_new_monoH_MZP1400", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP1700 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP1700", "hfourlepbestmass_4l_afterSel_new_monoH_MZP1700", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP2000 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP2000", "hfourlepbestmass_4l_afterSel_new_monoH_MZP2000", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_afterSel_new_monoH_MZP2500 = new TH1F("hfourlepbestmass_4l_afterSel_new_monoH_MZP2500", "hfourlepbestmass_4l_afterSel_new_monoH_MZP2500", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp10000_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-10000_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-10000_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp1000_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-1000_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-1000_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-100_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-100_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-10_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-10_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp2000_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-2000_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-2000_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp200_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-200_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-200_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp20_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-20_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-20_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp300_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-300_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-300_MChi-1", Nbins, Xmin, Xmax);

  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1;
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
    hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1=new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1","hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1", NMBINS, logMbins);
  }
  else hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1","hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1", Nbins, Xmin, Xmax);

  TH1D *nEvent_4l_w_ZpBaryonic_MZp500_MChi1 = new TH1D("nEvent_4l_w_ZpBaryonic_MZp500_MChi1","nEvent_4l_w_ZpBaryonic_MZp500_MChi1",23,0.,23.);
  TH1D *nEvent_4l_ZpBaryonic_MZp500_MChi1 = new TH1D("nEvent_4l_ZpBaryonic_MZp500_MChi1","nEvent_4l_ZpBaryonic_MZp500_MChi1",23,0.,23.);
  nEvent_4l_w_ZpBaryonic_MZp500_MChi1->Sumw2();
  nEvent_4l_ZpBaryonic_MZp500_MChi1->Sumw2();
  TList *listZpBaryonic_MZp500_MChi1_w = new TList;
  TList *listZpBaryonic_MZp500_MChi1 = new TList;

  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi1 = new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-50_MChi-1","hfourlepbestmass_4l_newZpBaryonic_MZp-50_MChi-1", Nbins, Xmin, Xmax);
  TH1F *hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10=new TH1F("hfourlepbestmass_4l_newZpBaryonic_MZp-50_MChi-10","hfourlepbestmass_4l_newZpBaryonic_MZp-50_MChi-10", Nbins, Xmin, Xmax);
  
  int* arraysizesig = new int[1];
  arraysizesig[0] = Nbins;
  cout <<  "Bins= " << arraysizesig[0] << endl;

  float bincont125[arraysizesig[0]],
        bincontgg125[arraysizesig[0]],bincontvbf125[arraysizesig[0]];
  for (int i=0;i<hfourlepbestmass_4l_afterSel_new_signal125->GetNbinsX();i++){
    bincont125[i]=0.;
    // bincontgg125[i]=0.;
    // bincontvbf125[i]=0.;
  }

  delete [] arraysizesig;
  
  cout << "Number of signal samples= " << Vdatasetnamesig.size() << endl;

  for ( int datasetIdSig=Vdatasetnamesig.size()-1; datasetIdSig >=0; datasetIdSig--){  

    char dataset[500];
    sprintf(dataset,"%s",Vdatasetnamesig.at(datasetIdSig).c_str());
    cout << "Counter=" << datasetIdSig << " Root-ple=" << dataset << " Label=" << Vlabelsig.at(datasetIdSig) <<endl; 

    std::string datasetnamesig = "";
    datasetnamesig = Vdatasetnamesig.at(datasetIdSig);

    TFile *f0 = TFile::Open(dataset);

    TH1D *nEvent_4l_w_new = (TH1D*)f0->Get("nEvent_4l_w");
    TH1D *nEvent_4l_new = (TH1D*)f0->Get("nEvent_4l");   

    hfourlepbestmass_4l_afterSel_new = (TH1F*)f0->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new"*/);
    TH1 *hfourlepbestmass_4l_afterSel_new_new=NULL;

    if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) {
      hfourlepbestmass_4l_afterSel_new_new = (TH1*)f0->Get(histlabel.c_str() /*"hfourlepbestmass_4l_afterSel_new_new"*/);
    }
    else hfourlepbestmass_4l_afterSel_new_new=hfourlepbestmass_4l_afterSel_new->Rebin(nRebin, histlabel.c_str()/*"hfourlepbestmass_4l_afterSel_new_new"*/);


    //hfourlepbestmass_4l_afterSel_new_new->SetLineColor();
    //hfourlepbestmass_4l_afterSel_new_new->SetFillColor(0);
    //hfourlepbestmass_4l_afterSel_new_new->SetFillStyle(3244);
    hfourlepbestmass_4l_afterSel_new_new->SetMarkerSize(1.5);
    //hfourlepbestmass_4l_afterSel_new_new->Draw("same");
    
    cout << "Label= " << Vlabelsig.at(datasetIdSig) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->GetEntries() <<endl;
    cout << "Label= " << Vlabelsig.at(datasetIdSig) << "  Entries= " << hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1);
    if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0) 
      cout << "  Error= " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries();
    cout << endl;

    if(datasetnamesig.find("Higgs_Zprime_nohdecay")<200 && datasetnamesig.find("1GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_DM1->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_Zprime_nohdecay")<200 && datasetnamesig.find("10GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_DM10->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_Zprime_nohdecay")<200 && datasetnamesig.find("100GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_DM100->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_Zprime_nohdecay")<200 && datasetnamesig.find("500GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_DM500->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_Zprime_nohdecay")<200 && datasetnamesig.find("1000GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_DM1000->Add(hfourlepbestmass_4l_afterSel_new_new);

    if(datasetnamesig.find("Higgs_scalar_nohdecay")<200 && datasetnamesig.find("1GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_scalar_nohdecay")<200 && datasetnamesig.find("10GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_scalar_nohdecay")<200 && datasetnamesig.find("100GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_scalar_nohdecay")<200 && datasetnamesig.find("500GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("Higgs_scalar_nohdecay")<200 && datasetnamesig.find("1000GeV")<200) hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000->Add(hfourlepbestmass_4l_afterSel_new_new);

    //2HDM
    if(datasetnamesig.find("2HDM_MZp-600")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP600->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-800")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP800->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-1000")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-1200")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-1400")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-1700")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-2000")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->Add(hfourlepbestmass_4l_afterSel_new_new);
    if(datasetnamesig.find("2HDM_MZp-2500")<200) hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->Add(hfourlepbestmass_4l_afterSel_new_new);
    
    // ZpBaryonic
    if(datasetnamesig.find("ZpBaryonic_MZp-10000_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp10000_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-1000_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp1000_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-100_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-10_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-2000_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp2000_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-200_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp200_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-20_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp20_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-300_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp300_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
    if(datasetnamesig.find("ZpBaryonic_MZp-500_MChi-1")<200) {
      hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new); 
      //nEvent_4l_w_ZpBaryonic_MZp500_MChi1->Add(nEvent_4l_w_new);
      //nEvent_4l_ZpBaryonic_MZp500_MChi1->Add(nEvent_4l_new);
      listZpBaryonic_MZp500_MChi1_w->Add(nEvent_4l_w_new);
      listZpBaryonic_MZp500_MChi1->Add(nEvent_4l_new);
    }
    if(datasetnamesig.find("ZpBaryonic_MZp-50_MChi-1")<200) hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi1->Add(hfourlepbestmass_4l_afterSel_new_new);   
    if(datasetnamesig.find("ZpBaryonic_MZp-50_MChi-10")<200) hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->Add(hfourlepbestmass_4l_afterSel_new_new); 


    //cout << "Nbins=" << hfourlepbestmass_4l_afterSel_new_new->GetNbinsX() << endl;
    for (int nbins=1;nbins<=hfourlepbestmass_4l_afterSel_new_new->GetNbinsX(); nbins++){
      // cout << "BinCenter=" << hfourlepbestmass_4l_afterSel_new_new->GetBinCenter(nbins) << " BinContent=" << hfourlepbestmass_4l_afterSel_new_new->GetBinContent(nbins) << " BinError Content=" << hfourlepbestmass_4l_afterSel_new_new->GetBinError(nbins) << endl;
      
      if (datasetnamesig.find("M125")<100 || datasetnamesig.find("M-125")<100) { // Adding SMHiggs, VBF, TTH, WH, ZH
	if (nbins==1) {
	  cout << "Adding samples at 125 GeV" << dataset << endl;
	  //cout << sqrt(errorH125) << " " << sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries() << endl;
	  if (hfourlepbestmass_4l_afterSel_new_new->GetEntries()>0.) errorH125=errorH125+pow(sqrt(hfourlepbestmass_4l_afterSel_new_new->GetEntries())*hfourlepbestmass_4l_afterSel_new_new->Integral(0,-1)/hfourlepbestmass_4l_afterSel_new_new->GetEntries(),2);
	  //cout << sqrt(errorH125) << endl;
	}	
	bincont125[nbins-1]=bincont125[nbins-1]+float(hfourlepbestmass_4l_afterSel_new_new->GetBinContent(nbins));
	
      }

      // only ggF and VBF
      // if (datasetnamesig.find("SMHiggsToZZTo4L_M-125")<100) { // Adding VBF only
      // 	if (nbins==1) cout << "Adding samples at 125 GeV ggF only" << dataset << endl;
      // 	bincontgg125[nbins-1]=bincontgg125[nbins-1]+float(hfourlepbestmass_4l_afterSel_new_new->GetBinContent(nbins));
      // }
      // if (datasetnamesig.find("VBF_HToZZTo4L_M-125")<100 || datasetnamesig.find("VBF_ToHToZZTo4L_M-125")<100) { // Adding VBF only
      // 	if (nbins==1) cout << "Adding samples at 125 GeV VBF only" << dataset << endl;
      // 	bincontvbf125[nbins-1]=bincontvbf125[nbins-1]+float(hfourlepbestmass_4l_afterSel_new_new->GetBinContent(nbins));
      // }
           
      
      //cout << "BinCont= " << bincont[nbins-1] << endl;

      // char temp[328];
      // sprintf(temp,"%s",histosdir.c_str());
      
      // if (datasetnamesig.find(temp)< 100 && datasetnamesig.find("output_SMHiggsToZZTo4L_M-125") < 180 ) {
      // 	//cout << double(bincont125[nbins-1]) << endl;
      // 	hfourlepbestmass_4l_afterSel_new_signal125->SetBinContent(nbins,double(bincont125[nbins-1]));
	
      // }

      // ongly ggF and VBF
      // if (datasetnamesig.find(temp)< 100 && datasetnamesig.find("output_SMHiggsToZZTo4L_M125") < 180 ) {
      // 	//cout << double(bincontgg125[nbins-1]) << endl;
      // 	hfourlepbestmass_4l_afterSel_new_signalgg125->SetBinContent(nbins,double(bincontgg125[nbins-1]));
      // }
      // if (datasetnamesig.find(temp)< 100 && (datasetnamesig.find("output_VBF_HToZZTo4L_M125") < 180 || datasetnamesig.find("output_VBF_ToHToZZTo4L_M125") < 180) ) {
      // 	//cout << double(bincontvbf125[nbins-1]) << endl;
      // 	hfourlepbestmass_4l_afterSel_new_signalvbf125->SetBinContent(nbins,double(bincontvbf125[nbins-1]));
      // }
      
    }
           
  }

  nEvent_4l_w_ZpBaryonic_MZp500_MChi1->Merge(listZpBaryonic_MZp500_MChi1_w);
  nEvent_4l_ZpBaryonic_MZp500_MChi1->Merge(listZpBaryonic_MZp500_MChi1);

  if (errorH125>0.) errorH125=sqrt(errorH125);

  // cout << "Higgs Signal expected at mH=125 is " << hfourlepbestmass_4l_afterSel_new_signal125->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "mH=125 " << hfourlepbestmass_4l_afterSel_new_signal125->Integral(0,-1) << " +/- " << errorH125 << endl;  

  //cout << "Signal expected at mH=125 ggF only is " << hfourlepbestmass_4l_afterSel_new_signalgg125->Integral(0,-1) << endl;		     
  //cout << "Signal expected at mH=125 VBF only is " << hfourlepbestmass_4l_afterSel_new_signalvbf125->Integral(0,-1) << endl;
  		     
  // Dark Matter monohiggs signal
  // cout << "Mono-Higgs Signal expected at m_DM=1 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_DM1->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "m_DM=1 " << hfourlepbestmass_4l_afterSel_new_monoH_DM1->Integral(0,-1) << " +/- " << errorH125 << endl;  

  // cout << "Mono-Higgs Signal expected at m_DM=10 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_DM10->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "m_DM=1 " << hfourlepbestmass_4l_afterSel_new_monoH_DM10->Integral(0,-1) << " +/- " << errorH125 << endl;  

  // cout << "Mono-Higgs Signal expected at m_DM=100 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_DM100->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "m_DM=1 " << hfourlepbestmass_4l_afterSel_new_monoH_DM100->Integral(0,-1) << " +/- " << errorH125 << endl;  

  //  cout << "Mono-Higgs Signal expected at m_DM=500 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_DM500->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "m_DM=1 " << hfourlepbestmass_4l_afterSel_new_monoH_DM500->Integral(0,-1) << " +/- " << errorH125 << endl;  

  //  cout << "Mono-Higgs Signal expected at m_DM=1 TeV is " << hfourlepbestmass_4l_afterSel_new_monoH_DM1000->Integral(0,-1) << " +/- " << errorH125 << endl;
  // if (histlabel.find("hM4l_9")<10 ) 
  //   outputyields << "m_DM=1 " << hfourlepbestmass_4l_afterSel_new_monoH_DM1000->Integral(0,-1) << " +/- " << errorH125 << endl;  

  // 2HDM
  cout << "Mono-Higgs Signal expected for MZP600 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP600->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP600 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP600->Integral(0,-1) << " +/- " << errorH125 << endl;  
  
  cout << "Mono-Higgs Signal expected for MZP800 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP800->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP800 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP800->Integral(0,-1) << " +/- " << errorH125 << endl;  
  
  cout << "Mono-Higgs Signal expected for MZP1000 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP1000 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->Integral(0,-1) << " +/- " << errorH125 << endl;  
  
  cout << "Mono-Higgs Signal expected for MZP1200 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP1200 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->Integral(0,-1) << " +/- " << errorH125 << endl;  
  
  cout << "Mono-Higgs Signal expected for MZP1400 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP1400 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->Integral(0,-1) << " +/- " << errorH125 << endl;  
  
  cout << "Mono-Higgs Signal expected for MZP1700 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 ) 
    outputyields << "m_ZP1700 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->Integral(0,-1) << " +/- " << errorH125 << endl;  

  cout << "Mono-Higgs Signal expected for MZP2000 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 )
    outputyields << "m_ZP2000 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->Integral(0,-1) << " +/- " << errorH125 << endl;
 
  cout << "Mono-Higgs Signal expected for MZP2500 GeV is " << hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->Integral(0,-1) << " +/- " << errorH125 << endl;
  if (histlabel.find("hM4l_9")<10 )
    outputyields << "m_ZP2500 " << hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->Integral(0,-1) << " +/- " << errorH125 << endl;
  
  

  // hfourlepbestmass_4l_afterSel_new_signal125->SetLineColor(kRed-4);
  // hfourlepbestmass_4l_afterSel_new_signalgg125->SetLineColor(kRed-4);		     
  // hfourlepbestmass_4l_afterSel_new_signalvbf125->SetLineColor(kOrange-4);

  hfourlepbestmass_4l_afterSel_new_signal125->SetMarkerSize(0.95);
  
  hfourlepbestmass_4l_afterSel_new_totSM_H->SetMarkerColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_totSM_H->SetLineColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_totSM_H->SetFillColor(kRed-4);

  hfourlepbestmass_4l_afterSel_new_totSM_HZZ->SetMarkerColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_totSM_HZZ->SetLineColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_totSM_HZZ->SetFillColor(kRed-4);

  hfourlepbestmass_4l_afterSel_new_totSM_HWW->SetMarkerColor(kRed-1);
  hfourlepbestmass_4l_afterSel_new_totSM_HWW->SetLineColor(kRed-1);
  hfourlepbestmass_4l_afterSel_new_totSM_HWW->SetFillColor(kRed-1);
  
  

  //if (histlabel.find("hM4l_7")<10) {
  //  htotal->Add(hfourlepbestmass_4l_afterSel
  cout << "Total higgs (ZZ) 125 rate is= " << hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Integral() << endl;
  cout << "Total higgs (WW) 125 rate is= " << hfourlepbestmass_4l_afterSel_new_totSM_HWW->Integral() << endl; 
  cout << "Total higgs (ZZ+WW) 125 rate is= " << hfourlepbestmass_4l_afterSel_new_totSM_H->Integral() << endl;
  // htotalHisto->Add(hfourlepbestmass_4l_afterSel_new_totSM_H); 
  //hfourlepbestmass_4l_afterSel_new_totSM_H->Draw("hist same");

  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_totSM_HZZ,"H#rightarrowZZ#rightarrow 4l, m_{H}=125 GeV", "F");  
  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_totSM_HWW,"H#rightarrowWW#rightarrow 2l 2#nu, m_{H}=125 GeV", "F");  

  //}

  


  hfourlepbestmass_4l_afterSel_new_monoH_DM1->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_DM1->SetMarkerColor(kGreen-4);
  hfourlepbestmass_4l_afterSel_new_monoH_DM1->SetLineColor(kGreen-4);
  
  hfourlepbestmass_4l_afterSel_new_monoH_DM10->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_DM10->SetMarkerColor(kBlue-4);
  hfourlepbestmass_4l_afterSel_new_monoH_DM10->SetLineColor(kBlue-4);

  hfourlepbestmass_4l_afterSel_new_monoH_DM100->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_DM100->SetMarkerColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_monoH_DM100->SetLineColor(kRed-4);

  hfourlepbestmass_4l_afterSel_new_monoH_DM500->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_DM500->SetMarkerColor(kOrange-3);
  hfourlepbestmass_4l_afterSel_new_monoH_DM500->SetLineColor(kOrange-3);

  hfourlepbestmass_4l_afterSel_new_monoH_DM1000->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_DM1000->SetMarkerColor(kOrange+7);
  hfourlepbestmass_4l_afterSel_new_monoH_DM1000->SetLineColor(kOrange+7);

  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1->SetMarkerColor(kGreen-4);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1->SetLineColor(kGreen-4); 

  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10->SetMarkerColor(kBlue-4);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10->SetLineColor(kBlue-4);

  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100->SetMarkerColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100->SetLineColor(kRed-4);

  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500->SetMarkerColor(kOrange-3);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500->SetLineColor(kOrange-3);

  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000->SetMarkerColor(kOrange+7);
  hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000->SetLineColor(kOrange+7);

  // 2HDM
  hfourlepbestmass_4l_afterSel_new_monoH_MZP600->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP600->SetMarkerColor(kGreen-4);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP600->SetLineColor(kGreen-4);
  
  hfourlepbestmass_4l_afterSel_new_monoH_MZP800->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP800->SetMarkerColor(kBlue-4);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP800->SetLineColor(kBlue-4);
  
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->SetMarkerColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->SetLineColor(kRed-4);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->SetLineWidth(2);
  
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->SetMarkerColor(kOrange-3);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->SetLineColor(kOrange-3);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->SetLineWidth(2);

  hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->SetMarkerColor(kBlack);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->SetLineColor(kBlack);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->SetLineWidth(2);

  hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->SetMarkerColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->SetLineColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->SetLineWidth(2);

  hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->SetMarkerColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->SetLineColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->SetLineWidth(2);

  hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->SetMarkerSize(0.95);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->SetMarkerColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->SetLineColor(kCyan);
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->SetLineWidth(2);

  // Z' baryonic
  hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->SetMarkerSize(0.95);
  hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->SetMarkerColor(kRed);
  hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->SetLineColor(kRed);
  hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->SetLineWidth(2);
  
  hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->SetMarkerSize(0.95);
  hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->SetMarkerColor(kGreen-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->SetLineColor(kGreen-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->SetLineWidth(2);

  hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->SetMarkerSize(0.95);
  hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->SetMarkerColor(kBlue-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->SetLineColor(kBlue-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->SetLineWidth(2);

  hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->SetMarkerSize(0.95);
  hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->SetMarkerColor(kCyan-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->SetLineColor(kCyan-4);
  hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->SetLineWidth(2);

  // MZprime 2HDM
  // htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP600);
  // htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1000);
  // htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1400);
  // htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1700);

  //MZprimeBaryonic
  // htotal->Add(hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1);
  //htotal->Add(hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1);
  //htotal->Add(hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1);
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1,"m_{Z'B}=10 GeV, m_{#chi}=1 GeV","L");
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1,"m_{Z'B}=100 GeV, m_{#chi}=1 GeV","L");
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1,"m_{Z'B}=500 GeV, m_{#chi}=1 GeV","L");
    

  
  htotal->Draw("hist same");
  if ( histlabel.find("hLogX")<10 || histlabel.find("hLogLinX")<10) { 
    htotaldata->Draw("E1Psame");   }
  else {
    cout << "Plotting Data " << endl;
    gr->Draw("EPsame");
  }

  //hfourlepbestmass_4l_afterSel_new_signal350->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_signal200->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_signal125->Draw("same");   // signal overimposed
  //hfourlepbestmass_4l_afterSel_new_signal126->Draw("same");   // signal overimposed
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_signal350);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_signal200);
  
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM10);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM100);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM500);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM1000);

  // hfourlepbestmass_4l_afterSel_new_monoH_DM1->Draw("same");
  // hfourlepbestmass_4l_afterSel_new_monoH_DM10->Draw("same");
  // hfourlepbestmass_4l_afterSel_new_monoH_DM100->Draw("same");
  // hfourlepbestmass_4l_afterSel_new_monoH_DM500->Draw("same");
  // hfourlepbestmass_4l_afterSel_new_monoH_DM1000->Draw("same");
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM10);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM100);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM500);
  

  // Scalar
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000);

  //hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500->Draw("same");
  //hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000->Draw("same");
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500);
  
  // 2HDM
  //hfourlepbestmass_4l_afterSel_new_monoH_MZP600->Draw("hist same");
  //hfourlepbestmass_4l_afterSel_new_monoH_MZP800->Draw("hist same");
  //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP800,"m_{Z'}=800 GeV, m_{A_{0}}=300 GeV","L");
  //hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->Draw("hist same");
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->Draw("hist same");
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1200);
  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP1200,"m_{Z'}=1200 GeV, m_{A_{0}}=300 GeV","L");
  //hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->Draw("hist same");
  //hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->Draw("hist same");
  
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP600);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1000);
  //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_MZP1700);

  //hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1->Draw("hist same");
  //hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1->Draw("hist same");
  //htotal->Add(hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1);
  hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1->Draw("hist same");
  //hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10->Draw("hist same");
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp10_MChi1,"m_{Z'B}=10 GeV, m_{#chi}=1 GeV","L");
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp100_MChi1,"m_{Z'B}=100 GeV, m_{#chi}=1 GeV","L");
  legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp500_MChi1,"m_{Z'B}=500 GeV, m_{#chi}=1 GeV","L");
  //legend->AddEntry(hfourlepbestmass_4l_newZpBaryonic_MZp50_MChi10,"m_{Z'B}=50 GeV, m_{#chi}=10 GeV","L");
  
    

  if (
      histlabel.find("hMELA_8")<10 || 
      histlabel.find("hPFMET_3")<10 ||
      histlabel.find("h_hLogXPFMET_3")<10 ||
      histlabel.find("hLogLinX")<10 ||
      histlabel.find("hPFMET_8")<10 ||
      histlabel.find("hMZ_3")<10  ||
      histlabel.find("hMZ1_5")<10  ||
      histlabel.find("hM4l_T_8")<10 ||
      histlabel.find("DPHI_8")<10 ||
      histlabel.find("hMjj_8")<10 ||
      histlabel.find("hDjj_8")<10 ||
      histlabel.find("hNbjets")<10 ||
      histlabel.find("hNgood")<10 ||
      histlabel.find("hNbjets_9")<10 ||
      histlabel.find("hNgood_9")<10
      ){
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_signal126);  // signal stacked on top of background
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_signal126,"m_{H}=126 GeV","L");
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_signal126);
    //cout << "Plotting 4l+MET" << endl;
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM1);
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM10);
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM100);
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM500);
    //htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM1000);
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM1,"m_{DM}=1 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM10,"m_{DM}=10 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM100,"m_{DM}=100 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM500,"m_{DM}=500 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM1000,"m_{DM}=1 TeV, Z'_{H}", "L");	

    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1,"m_{DM}=1 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM10,"m_{DM}=10 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM100,"m_{DM}=100 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM500,"m_{DM}=500 GeV, Z'_{H}", "L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_scalar_DM1000,"m_{DM}=1 TeV, Z'_{H}", "L");	


    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP600,"m_{Z'}=600 GeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP800,"m_{Z'}=800 GeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP1000,"m_{Z'}=1 TeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP1200,"m_{Z'}=1.2 TeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP1400,"m_{Z'}=1.4 TeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP1700,"m_{Z'}=1.7 TeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP2000,"m_{Z'}=2 TeV, m_{A_{0}}=300 GeV","L");
    //legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_MZP2500,"m_{Z'}=2.5 TeV, m_{A_{0}}=300 GeV","L");       
    
  

  }
  else {
    // if ( histlabel.find("hMjj_3")<10 || histlabel.find("hDjj_3")<10 || histlabel.find("hVD_3")<10 ) {
    //   hfourlepbestmass_4l_afterSel_new_signalgg125->Draw("same");   // signal overimposed
    //   hfourlepbestmass_4l_afterSel_new_signalvbf125->Draw("same");   // signal overimposed
    // }
    //else {
    //  hfourlepbestmass_4l_afterSel_new_signal125->Draw("same");
    //  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_signal125,"m_{H}=125 GeV","L");
    //hfourlepbestmass_4l_afterSel_new_signal126->Draw("same"); 
    //}
  }
  // if (histlabel.find("hMjj_3")<10 || histlabel.find("hDjj_3")<10 || histlabel.find("hVD_3")<10 ) {
  //   legend->AddEntry(hfourlepbestmass_4l_afterSel_new_signalgg125,"ggH, m_{H}=125 GeV","L");
  //   legend->AddEntry(hfourlepbestmass_4l_afterSel_new_signalvbf125,"qqH, m_{H}=125 GeV","L");
  // }
  //else {
  //  cout << "Plotting 4l+MET" << endl;
  //  htotal->Add(hfourlepbestmass_4l_afterSel_new_monoH_DM100);
  //  legend->AddEntry(hfourlepbestmass_4l_afterSel_new_monoH_DM100,"m_{DM}=100 GeV, Z'_{H}", "L");
  //}


//  // Zoom
  // htotal->SetMinimum(0);
//   htotal->SetMaximum(12.4); // 3 GeV bin
//   htotal->Draw();
//   htotal->GetXaxis()->SetRange(23,59); // 3 GeV bin
//   //htotal->GetYaxis()->SetRangeUser(0.,16.);
//   htotal->GetYaxis()->SetTitle("Events / 3 GeV"); // 3 GeV bin
//   sprintf(histotitle,"m_{%s} [GeV]",whichchannel.c_str());
//   htotal->GetXaxis()->SetTitle(histotitle);  
//   htotal->GetXaxis()->SetLabelSize(0.045);
//   htotal->GetXaxis()->SetTitleSize(0.05);
//   htotal->GetXaxis()->SetTitleOffset(1.15);
//   htotal->GetXaxis()->SetTitleFont(42);
//   htotal->GetYaxis()->SetLabelSize(0.045);
//   htotal->GetYaxis()->SetTitleSize(0.05);
//   htotal->GetYaxis()->SetTitleOffset(1.15);
//   htotal->GetYaxis()->SetTitleFont(42);
//   gr->Draw("EPsame");

//   htotal->Draw("same");
//   gr->Draw("EPsame");
  
  //leg0->Draw("same");
  //leg1->Draw("same");

  legend->Draw("same");
  ll->Draw("same");

  cout << "Saving plots for " << whichchannel.c_str() << endl;
  std::string saveaspdfzoom = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom_log.pdf" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom.pdf";
  std::string saveaspngzoom = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom_log.png" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom.png";
  std::string saveasepszoom = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom_log.eps" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_zoom.eps";
//   c1->SaveAs(saveaspdfzoom.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.pdf"*/);
//   c1->SaveAs(saveaspngzoom.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.png"*/);
//   c1->SaveAs(saveasepszoom.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.eps"*/);


  // full spectrum
 //  if (nRebin==10 && histlabel.find("hM4l_8")<10){
//     cout << "Plotting the full spectrum" << endl;
//     // htotal->Add(hfourlepbestmass_4l_afterSel_new_signal350);
//     // legend->AddEntry(hfourlepbestmass_4l_afterSel_new_signal350,"m_{H}=350 GeV","L");
//     htotal->SetMinimum(0);
//     htotal->SetMaximum(24.5); // 10 GeV bin
//     htotal->Draw();
//     htotal->GetXaxis()->SetRange(7,81); // 10 GeV bin
//     //htotal->GetYaxis()->SetRangeUser(0.,16.);
//     htotal->GetYaxis()->SetTitle("Events / 10 GeV"); // 10 GeV bin    
//     sprintf(histotitle,"m_{%s} [GeV]",whichchannel.c_str());
//     htotal->GetXaxis()->SetTitle(histotitle);  
//     htotal->GetXaxis()->SetLabelSize(0.045);
//     htotal->GetXaxis()->SetTitleSize(0.05);
//     htotal->GetXaxis()->SetTitleOffset(1.15);
//     htotal->GetXaxis()->SetTitleFont(42);
//     htotal->GetYaxis()->SetLabelSize(0.045);
//     htotal->GetYaxis()->SetTitleSize(0.05);
//     htotal->GetYaxis()->SetTitleOffset(1.15);
//     htotal->GetYaxis()->SetTitleFont(42);
//     gr->Draw("EPsame");
    
//     legend->Draw("same");
//     ll->Draw("same");
    
    
//     std::string saveaspdf = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_log.pdf" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+".pdf";
//     std::string saveaspng = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_log.png" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+".png";
//     std::string saveaseps = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_log.eps" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+".eps";
//     // c1->SaveAs(saveaspdf.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.pdf"*/);
// //     c1->SaveAs(saveaspng.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.png"*/);
// //     c1->SaveAs(saveaseps.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.eps"*/);
//   }

  gPad->RedrawAxis();

  if (useRatio==true){
    //  c1->Update();
    double canvasratio = 0.3;
    c1->SetBottomMargin(canvasratio + (1-canvasratio)*c1->GetBottomMargin()-canvasratio*c1->GetTopMargin());
    //cout << "Canvas= " << canvasratio + (1-canvasratio)*c1->GetBottomMargin()-canvasratio*c1->GetTopMargin() << endl;
    
    // Ratio: data / total bkg 
    canvasratio = 0.16;
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin((1-canvasratio) - (1-canvasratio)*ratioPad->GetBottomMargin()+canvasratio*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->SetTicks(1,1);
    //ratioPad->SetLogx();
    ratioPad->Draw();
    ratioPad->cd();
    
    //TH2F *hframe2= new TH2F("hframe2","hframe2",6000, 0., 2.2, 1000, 0.5, 2.);// iso
    
    hframe2->GetYaxis()->SetLabelSize(0.020);
    hframe2->GetXaxis()->SetLabelSize(0.020);
    //  hframe2->GetYaxis()->SetTitleSize(0.047);
    hframe2->SetYTitle("Data/MC");
    //  hframe2->GetYaxis()->SetRangeUser(-10,10);
    hframe2->GetYaxis()->SetNdivisions(503);
    //hframe2->GetXaxis()->SetTitleOffset(1.25);
    hframe2->Draw("");
    
    htotalHistoRatio->SetMarkerStyle(20);
    htotalHistoRatio->SetMarkerSize(0.95);
    htotalHistoRatio->SetMarkerColor(kBlack);
    htotalHistoRatio->Draw("Psame");
    
    
    c1->Update();

  }

  if (whichchannel.find("4#mu")<10) whichchannel="4mu";
  if (whichchannel.find("2e2#mu")<10) whichchannel="2e2mu";
  
  std::string saveaspdfratio = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio_log.pdf" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio.pdf";
  std::string saveaspngratio = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio_log.png" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio.png";
  std::string saveasepsratio = useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio_log.eps" : "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio.eps";
  std::string saveasrootratio= useLogY ? "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio_log.root": "plots/h_"+histlabel+"_"+whichchannel+"_"+whichenergy+"_ratio.root";
  
  cout << saveasrootratio.c_str() << endl;
  c1->SaveAs(saveaspdfratio.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.pdf"*/);
  c1->SaveAs(saveaspngratio.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.png"*/);
  c1->SaveAs(saveasepsratio.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.eps"*/);
  c1->SaveAs(saveasrootratio.c_str()/*"plots/hfourlepbestmass_4l_afterSel_new_m4l.root"*/);
  
  
  // Write final histogram in a file 
  char htotalfinal[300];
  cout << whichchannel.c_str() << endl;
  sprintf(htotalfinal,"plots/htotalfinal_%s_%s.root",histlabel.c_str(),whichchannel.c_str());
  cout << "\n Writing final histograms in a file " << htotalfinal << endl;
  TFile *file1 = new TFile(htotalfinal, "RECREATE");
  file1->cd();
  htotalHisto->Write();
  htotaldata->Write();
  hfourlepbestmass_4l_afterSel_new_qqZZ->Write();
  hfourlepbestmass_4l_afterSel_new_ggZZ->Write();
  nEvent_4l_w_DY->Write();
  nEvent_4l_w_TT->Write();
  nEvent_4l_w_ZZ->Write();
  nEvent_4l_w_qqZZ->Write();
  nEvent_4l_w_ggZZ->Write();
  nEvent_4l_w_WZ_WW_Wj->Write();
  nEvent_4l_w_TTV->Write();
  nEvent_4l_w_VVV->Write();
  nEvent_4l_w_QCD->Write();
  hfourlepbestmass_4l_afterSel_new_totSM_H->Write();
  hfourlepbestmass_4l_afterSel_new_totSM_HZZ->Write();
  hfourlepbestmass_4l_afterSel_new_totSM_HWW->Write();
  hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H->Write();
  nEvent_4l_w_totSM_H->Write();
  nEvent_4l_w_totSM_HZZ->Write();
  nEvent_4l_w_totSM_HWW->Write();
  nEvent_4l_w_totalbkgMC->Write();
  nEvent_4l_w_totbkg_noSM_H->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP600->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP800->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1000->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1200->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1400->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP1700->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2000->Write();
  hfourlepbestmass_4l_afterSel_new_monoH_MZP2500->Write();
  nEvent_4l_w_ZpBaryonic_MZp500_MChi1->Write();
  nEvent_4l_w_data->Write();
  file1->Write();
  file1->Close();

  // Write cutflow tables 
  cout << "\n Writing cut flow tables in tex format \n" << endl;

  // DY
  //cout << "Cont.= " << nEvent_4l_w_DY->GetBinContent(5) << " Err= " << nEvent_4l_w_DY->GetBinError(5) << endl;
  //cout << "Cont.= " << nEvent_4l_DY->GetBinContent(5) << " Err= " << nEvent_4l_DY->GetBinError(5) << " " << nEvent_4l_DY->GetBinError(5)*nEvent_4l_w_DY->GetBinContent(5)/nEvent_4l_DY->GetBinContent(5) << endl;

  // QCD
  //cout << "Cont.= " << nEvent_4l_w_QCD->GetBinContent(5) << " Err= " << nEvent_4l_w_QCD->GetBinError(5) << endl;
  //cout << "Cont.= " << nEvent_4l_QCD->GetBinContent(5) << " Err= " << nEvent_4l_QCD->GetBinError(5) << " " << nEvent_4l_QCD->GetBinError(5)*nEvent_4l_w_QCD->GetBinContent(5)/nEvent_4l_QCD->GetBinContent(5) << endl;

  cout << "Cont.= " << nEvent_4l_w_totSM_H->GetBinContent(5) << " Err= " << nEvent_4l_w_totSM_H->GetBinError(5) << endl;
  cout << "Cont.= " << nEvent_4l_totSM_H->GetBinContent(5) << " Err= " << nEvent_4l_totSM_H->GetBinError(5) << " " << nEvent_4l_totSM_H->GetBinError(5)*nEvent_4l_w_totSM_H->GetBinContent(5)/nEvent_4l_totSM_H->GetBinContent(5) << endl;
  

  Char_t outformat[20000];

  cout << 
    "\\begin{table*}[htbH] \n"    <<
    "\\begin{center} \n" <<    
    "\\resizebox{\\textwidth}{!}{% \n" <<  
    "\\begin{tabular}{ l | c | c | c | c | c | c | c | c | c | c | c | c |} \n" <<
    "\\hline    \\hline" 
       << endl;

  if (whichchannel.find("4mu")<10) whichchannel="4\\mu";
  if (whichchannel.find("2e2mu")<10) whichchannel="2e2\\mu";

  cout << "Channel: $" << whichchannel.c_str() <<"$ & $Z\\gamma^{*},ZZ$ & $Z+js$ & $WZ,WW,W+js$ & $t \\bar{t}$ & $t \\bar{t}V$ & $VVV$ & $QCD$ & $SM \\, H \\rightarrow ZZ$ & $SM \\, H \\rightarrow WW$ & $Tot. \\, Bkg$  & Z' baryonic & Obs. \\\\" << endl; 
  cout << "\\hline" << endl;
  
  sprintf (outformat,"HLT & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(5), nEvent_4l_w_ZZ->GetBinError(5),
       nEvent_4l_w_DY->GetBinContent(5), nEvent_4l_w_DY->GetBinError(5),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(5),  nEvent_4l_w_WZ_WW_Wj->GetBinError(5), 
       nEvent_4l_w_TT->GetBinContent(5), nEvent_4l_w_TT->GetBinError(5), 
       nEvent_4l_w_TTV->GetBinContent(5), nEvent_4l_w_TTV->GetBinError(5), 
       nEvent_4l_w_VVV->GetBinContent(5), nEvent_4l_w_VVV->GetBinError(5),
       nEvent_4l_w_QCD->GetBinContent(5), nEvent_4l_w_QCD->GetBinError(5),
       nEvent_4l_w_totSM_HZZ->GetBinContent(5), nEvent_4l_w_totSM_HZZ->GetBinError(5),
       nEvent_4l_w_totSM_HWW->GetBinContent(5), nEvent_4l_w_totSM_HWW->GetBinError(5),
       nEvent_4l_w_totalbkgMC->GetBinContent(5), nEvent_4l_w_totalbkgMC->GetBinError(5),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(5), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(5),
       nEvent_4l_w_data->GetBinContent(5));
  cout << outformat <<endl;
  
  sprintf (outformat,"$l^{+} l^{-}$, $12<m_{l^{+}l^{-}}<120$ & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e &%.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e $ \\pm $ %.2e & %.2e  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(8), nEvent_4l_w_ZZ->GetBinError(8),
       nEvent_4l_w_DY->GetBinContent(8), nEvent_4l_w_DY->GetBinError(8),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(8),  nEvent_4l_w_WZ_WW_Wj->GetBinError(8), 
       nEvent_4l_w_TT->GetBinContent(8), nEvent_4l_w_TT->GetBinError(8), 
       nEvent_4l_w_TTV->GetBinContent(8), nEvent_4l_w_TTV->GetBinError(8), 
       nEvent_4l_w_VVV->GetBinContent(8), nEvent_4l_w_VVV->GetBinError(8),
       nEvent_4l_w_QCD->GetBinContent(8), nEvent_4l_w_QCD->GetBinError(8),
       nEvent_4l_w_totSM_HZZ->GetBinContent(8), nEvent_4l_w_totSM_HZZ->GetBinError(8),
       nEvent_4l_w_totSM_HWW->GetBinContent(8), nEvent_4l_w_totSM_HWW->GetBinError(8),
       nEvent_4l_w_totalbkgMC->GetBinContent(8), nEvent_4l_w_totalbkgMC->GetBinError(8),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(8), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(8),
       nEvent_4l_w_data->GetBinContent(8));
  cout << outformat <<endl;
  

  //%.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e  \\\\",nEvent_4l_w_ZZ->GetBinContent(8),nEvent_4l_w_DY->GetBinContent(8),nEvent_4l_w_WZ_WW_Wj->GetBinContent(8),nEvent_4l_w_TT->GetBinContent(8),nEvent_4l_w_TTV->GetBinContent(8),nEvent_4l_w_VVV->GetBinContent(8),nEvent_4l_w_totSM_H->GetBinContent(8),nEvent_4l_w_totalbkgMC->GetBinContent(8),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(8),nEvent_4l_w_data->GetBinContent(8));
  //  cout << outformat <<endl;
  
  sprintf (outformat,"$Z_{1},Z_{2}$  & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(9), nEvent_4l_w_ZZ->GetBinError(9),
       nEvent_4l_w_DY->GetBinContent(9), nEvent_4l_w_DY->GetBinError(9),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(9),  nEvent_4l_w_WZ_WW_Wj->GetBinError(9), 
       nEvent_4l_w_TT->GetBinContent(9), nEvent_4l_w_TT->GetBinError(9), 
       nEvent_4l_w_TTV->GetBinContent(9), nEvent_4l_w_TTV->GetBinError(9), 
       nEvent_4l_w_VVV->GetBinContent(9), nEvent_4l_w_VVV->GetBinError(9),
       nEvent_4l_w_QCD->GetBinContent(9), nEvent_4l_w_QCD->GetBinError(9),
       nEvent_4l_w_totSM_HZZ->GetBinContent(9), nEvent_4l_w_totSM_HZZ->GetBinError(9),
       nEvent_4l_w_totSM_HWW->GetBinContent(9), nEvent_4l_w_totSM_HWW->GetBinError(9),
       nEvent_4l_w_totalbkgMC->GetBinContent(9), nEvent_4l_w_totalbkgMC->GetBinError(9),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(9), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(9),
       int(nEvent_4l_w_data->GetBinContent(9)));
  cout << outformat <<endl;

//& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(9),nEvent_4l_w_DY->GetBinContent(9),nEvent_4l_w_WZ_WW_Wj->GetBinContent(9),nEvent_4l_w_TT->GetBinContent(9),nEvent_4l_w_TTV->GetBinContent(9),nEvent_4l_w_VVV->GetBinContent(9),nEvent_4l_w_totSM_H->GetBinContent(9),nEvent_4l_w_totalbkgMC->GetBinContent(9),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(9),nEvent_4l_w_data->GetBinContent(9));
  // cout << outformat <<endl;
  
  sprintf (outformat,"$p_{T}>20/10$, $m_{l^{+}l^{-}}>4$, $m_{Z_{1}}>40$  & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(12), nEvent_4l_w_ZZ->GetBinError(12),
       nEvent_4l_w_DY->GetBinContent(12), nEvent_4l_w_DY->GetBinError(12),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(12),  nEvent_4l_w_WZ_WW_Wj->GetBinError(12), 
       nEvent_4l_w_TT->GetBinContent(12), nEvent_4l_w_TT->GetBinError(12), 
       nEvent_4l_w_TTV->GetBinContent(12), nEvent_4l_w_TTV->GetBinError(12), 
       nEvent_4l_w_VVV->GetBinContent(12), nEvent_4l_w_VVV->GetBinError(12),
       nEvent_4l_w_QCD->GetBinContent(12), nEvent_4l_w_QCD->GetBinError(12),
       nEvent_4l_w_totSM_HZZ->GetBinContent(12), nEvent_4l_w_totSM_HZZ->GetBinError(12),
       nEvent_4l_w_totSM_HWW->GetBinContent(12), nEvent_4l_w_totSM_HWW->GetBinError(12),
       nEvent_4l_w_totalbkgMC->GetBinContent(12), nEvent_4l_w_totalbkgMC->GetBinError(12),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(12), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(12),
       int(nEvent_4l_w_data->GetBinContent(12)));
  cout << outformat <<endl;

//& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(12),nEvent_4l_w_DY->GetBinContent(12),nEvent_4l_w_WZ_WW_Wj->GetBinContent(12),nEvent_4l_w_TT->GetBinContent(12),nEvent_4l_w_TTV->GetBinContent(12),nEvent_4l_w_VVV->GetBinContent(12),nEvent_4l_w_totSM_H->GetBinContent(12),nEvent_4l_w_totalbkgMC->GetBinContent(12),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(12),nEvent_4l_w_data->GetBinContent(12));
  //cout << outformat <<endl;
  
  sprintf (outformat,"$m_{4l}>70$  & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(15), nEvent_4l_w_ZZ->GetBinError(15),
       nEvent_4l_w_DY->GetBinContent(15), nEvent_4l_w_DY->GetBinError(15),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(15),  nEvent_4l_w_WZ_WW_Wj->GetBinError(15), 
       nEvent_4l_w_TT->GetBinContent(15), nEvent_4l_w_TT->GetBinError(15), 
       nEvent_4l_w_TTV->GetBinContent(15), nEvent_4l_w_TTV->GetBinError(15), 
       nEvent_4l_w_VVV->GetBinContent(15), nEvent_4l_w_VVV->GetBinError(15),
       nEvent_4l_w_QCD->GetBinContent(15), nEvent_4l_w_QCD->GetBinError(15),
       nEvent_4l_w_totSM_HZZ->GetBinContent(15), nEvent_4l_w_totSM_HZZ->GetBinError(15),
       nEvent_4l_w_totSM_HWW->GetBinContent(15), nEvent_4l_w_totSM_HWW->GetBinError(15),
       nEvent_4l_w_totalbkgMC->GetBinContent(15), nEvent_4l_w_totalbkgMC->GetBinError(15),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(15), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(15),
       int(nEvent_4l_w_data->GetBinContent(15)));
  cout << outformat <<endl;
//& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(15),nEvent_4l_w_DY->GetBinContent(15),nEvent_4l_w_WZ_WW_Wj->GetBinContent(15),nEvent_4l_w_TT->GetBinContent(15),nEvent_4l_w_TTV->GetBinContent(15),nEvent_4l_w_VVV->GetBinContent(15),nEvent_4l_w_totSM_H->GetBinContent(15),nEvent_4l_w_totalbkgMC->GetBinContent(15),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(15),nEvent_4l_w_data->GetBinContent(15));
  //cout << outformat <<endl;
  
  sprintf (outformat,"$|m_{4l}-125| \\leq 10$ & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(17), nEvent_4l_w_ZZ->GetBinError(17),
       nEvent_4l_w_DY->GetBinContent(17), nEvent_4l_w_DY->GetBinError(17),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(17),  nEvent_4l_w_WZ_WW_Wj->GetBinError(17), 
       nEvent_4l_w_TT->GetBinContent(17), nEvent_4l_w_TT->GetBinError(17), 
       nEvent_4l_w_TTV->GetBinContent(17), nEvent_4l_w_TTV->GetBinError(17), 
       nEvent_4l_w_VVV->GetBinContent(17), nEvent_4l_w_VVV->GetBinError(17),
       nEvent_4l_w_QCD->GetBinContent(17), nEvent_4l_w_QCD->GetBinError(17),
       nEvent_4l_w_totSM_HZZ->GetBinContent(17), nEvent_4l_w_totSM_HZZ->GetBinError(17),
       nEvent_4l_w_totSM_HWW->GetBinContent(17), nEvent_4l_w_totSM_HWW->GetBinError(17),	   
       nEvent_4l_w_totalbkgMC->GetBinContent(17), nEvent_4l_w_totalbkgMC->GetBinError(17),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(17), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(17),
       int(nEvent_4l_w_data->GetBinContent(17)));
  cout << outformat <<endl;
// //& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(17),nEvent_4l_w_DY->GetBinContent(17),nEvent_4l_w_WZ_WW_Wj->GetBinContent(17),nEvent_4l_w_TT->GetBinContent(17),nEvent_4l_w_TTV->GetBinContent(17),nEvent_4l_w_VVV->GetBinContent(17),nEvent_4l_w_totSM_H->GetBinContent(17),nEvent_4l_w_totalbkgMC->GetBinContent(17),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(17),nEvent_4l_w_data->GetBinContent(17));
//   //cout << outformat <<endl;


  sprintf (outformat,"$|m_{4l}-125| \\leq 10$, $N_{l}=4$, $n_{b} \\leq 1$ & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(22), nEvent_4l_w_ZZ->GetBinError(22),
       nEvent_4l_w_DY->GetBinContent(22), nEvent_4l_w_DY->GetBinError(22),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(22),  nEvent_4l_w_WZ_WW_Wj->GetBinError(22), 
       nEvent_4l_w_TT->GetBinContent(22), nEvent_4l_w_TT->GetBinError(22), 
       nEvent_4l_w_TTV->GetBinContent(22), nEvent_4l_w_TTV->GetBinError(22), 
       nEvent_4l_w_VVV->GetBinContent(22), nEvent_4l_w_VVV->GetBinError(22),
       nEvent_4l_w_QCD->GetBinContent(22), nEvent_4l_w_QCD->GetBinError(22),
       nEvent_4l_w_totSM_HZZ->GetBinContent(22), nEvent_4l_w_totSM_HZZ->GetBinError(22),
       nEvent_4l_w_totSM_HWW->GetBinContent(22), nEvent_4l_w_totSM_HWW->GetBinError(22),	   
       nEvent_4l_w_totalbkgMC->GetBinContent(22), nEvent_4l_w_totalbkgMC->GetBinError(22),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(22), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(22),
       int(nEvent_4l_w_data->GetBinContent(22)));
  cout << outformat <<endl;
//& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(22),nEvent_4l_w_DY->GetBinContent(22),nEvent_4l_w_WZ_WW_Wj->GetBinContent(22),nEvent_4l_w_TT->GetBinContent(22),nEvent_4l_w_TTV->GetBinContent(22),nEvent_4l_w_VVV->GetBinContent(22),nEvent_4l_w_totSM_H->GetBinContent(22),nEvent_4l_w_totalbkgMC->GetBinContent(22),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(22),nEvent_4l_w_data->GetBinContent(22));
  //cout << outformat <<endl;

  
   sprintf (outformat,"$|m_{4l}-125| \\leq 10$, $N_{l}=4$, $n_{b} \\leq 1$, $MET>50$ & %.2e $ \\pm $ %.2e & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %.2f $ \\pm $ %.2f & %d  \\\\",
       nEvent_4l_w_ZZ->GetBinContent(23), nEvent_4l_w_ZZ->GetBinError(23),
       nEvent_4l_w_DY->GetBinContent(23), nEvent_4l_w_DY->GetBinError(23),
       nEvent_4l_w_WZ_WW_Wj->GetBinContent(23),  nEvent_4l_w_WZ_WW_Wj->GetBinError(23), 
       nEvent_4l_w_TT->GetBinContent(23), nEvent_4l_w_TT->GetBinError(23), 
       nEvent_4l_w_TTV->GetBinContent(23), nEvent_4l_w_TTV->GetBinError(23), 
       nEvent_4l_w_VVV->GetBinContent(23), nEvent_4l_w_VVV->GetBinError(23),
       nEvent_4l_w_QCD->GetBinContent(23), nEvent_4l_w_QCD->GetBinError(23),
       nEvent_4l_w_totSM_HZZ->GetBinContent(23), nEvent_4l_w_totSM_HZZ->GetBinError(23),
       nEvent_4l_w_totSM_HWW->GetBinContent(23), nEvent_4l_w_totSM_HWW->GetBinError(23),	   
       nEvent_4l_w_totalbkgMC->GetBinContent(23), nEvent_4l_w_totalbkgMC->GetBinError(23),
       nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(23), nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinError(23),
       int(nEvent_4l_w_data->GetBinContent(23)));
  cout << outformat <<endl;
//& %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_ZZ->GetBinContent(23),nEvent_4l_w_DY->GetBinContent(23),nEvent_4l_w_WZ_WW_Wj->GetBinContent(23),nEvent_4l_w_TT->GetBinContent(23),nEvent_4l_w_TTV->GetBinContent(23),nEvent_4l_w_VVV->GetBinContent(23),nEvent_4l_w_totSM_H->GetBinContent(23),nEvent_4l_w_totalbkgMC->GetBinContent(23),nEvent_4l_w_ZpBaryonic_MZp500_MChi1->GetBinContent(23),nEvent_4l_w_data->GetBinContent(23));
  //cout << outformat <<endl;

 cout << 
   "\\hline \\hline \n" <<
   "\\end{tabular} \n"  <<
   "}" << endl;  
 

 
 cout << 
   "\\caption{Cut flow table the number of events passing the full selection for the $" << whichchannel.c_str() << "$ final state, as obtained from simulation for background and signal and from real data with a luminosity of $35.9 \\fbinv$. The signal sample correspond to the Z' baryonic model with $m_{Z'}=500$ GeV and $m_{\\chi}=1$ GeV; only statistical errors are quoted.}" 
      << endl;
 
 if (whichchannel.find("4\\mu")<10) whichchannel="4mu";
 if (whichchannel.find("2e2\\mu")<10) whichchannel="2e2mu";

 cout << "\\label{tab:yields"<<whichchannel.c_str()<<"} \n"   
   "\\end{center} \n" <<    
   "\\end{table*}" 
      << endl;
 
}

void PlotStack4l::setSamplesNames4l()
{
  
  std::ifstream infile;
  infile.open(inputfile.c_str());
  
  if (inputfile.find("2011")<500) { 
    whichenergy="7TeV";
    whichsample="7TeV";
  }
  else if (inputfile.find("RunI_")<500){
    whichenergy="RunI_";
    whichsample="8TeV";
  }
  else if (inputfile.find("2015")<500){
    whichenergy="13TeV";
    whichsample="13TeV";
  }
  else if (inputfile.find("2016")<500){
    whichenergy="13TeV";
    whichsample="13TeV";
  }

  
  cout << "Doing plot for " << whichenergy.c_str() << "  and " << whichsample.c_str() << endl;

  if (inputfile.find("4l")<100) {
    cout << "Plotting 4e+4mu+2e2mu combined in 4lepton plots" << endl;
    whichchannel="4l";
    histosdir="histos4mu_25ns";
    cout << "This is " << whichchannel.c_str() << endl;
  }
  else if (inputfile.find("4mu")<100){
    cout << "Plotting 4mu" << endl;
    whichchannel="4#mu";
    histosdir="histos4mu_25ns";
  }
  else if (inputfile.find("4e")<100){
    cout << "Plotting 4e" << endl;
    whichchannel="4e";
    histosdir="histos4e_25ns";
  }
  else if (inputfile.find("2e2mu")<100){
    cout << "Plotting 2e2mu" << endl;
    whichchannel="2e2#mu";
    histosdir="histos2e2mu_25ns";
  };

  Vdatasetnamedata.clear();
  Vdatasetnamebkg.clear();
  Vdatasetnamesig.clear();

  std::string inputfilename;

  while(std::getline(infile,inputfilename)){
    cout << "Reading " << inputfilename.c_str() << endl;
    
    // DATA  
       
    if(inputfilename.find("_DoubleMuon_")<200){ // as many times as it occurs in the input file
      Vdatasetnamedata.push_back(inputfilename);
      Vlabeldata.push_back("Double Muon - 2016");
      Vxsectiondata.push_back(1.); //pb
    }  
             
    if(inputfilename.find("_DoubleEG_")<200){ // as many times as it occurs in the input file
      Vdatasetnamedata.push_back(inputfilename);
      Vlabeldata.push_back("Double EGamma - 2016");
      Vxsectiondata.push_back(1.); //pb
    }   
    
    if(inputfilename.find("_SingleElectron_")<200){ // as many times as it occurs in the input file
      Vdatasetnamedata.push_back(inputfilename);
      Vlabeldata.push_back("Single Electron - 2016");
      Vxsectiondata.push_back(1.); //pb
    }   

    if(inputfilename.find("_SingleMuon_")<200){ // as many times as it occurs in the input file
      Vdatasetnamedata.push_back(inputfilename);
      Vlabeldata.push_back("Single Muon - 2016");
      Vxsectiondata.push_back(1.); //pb
    }   
    
    if(inputfilename.find("_MuonEG_")<200){ // as many times as it occurs in the input file
      Vdatasetnamedata.push_back(inputfilename);
      Vlabeldata.push_back("Muon EGamma - 2016");
      Vxsectiondata.push_back(1.); //pb
    }    
       

    //Z+X from data
    if(inputfilename.find("Z+X")<85){
      Vdatasetnamebkgdata.push_back(inputfilename);
      Vlabelbkgdata.push_back("Z+X");
      Vxsectionbkgdata.push_back(1.); //pb
    }
    
    // SIGNAL
    else if(inputfilename.find("Higgs_scalar")<200 || inputfilename.find("Higgs_scalar_nohdecay")<200 ){
      // if( (inputfilename.find("1GeV")<200) ){
      // 	Vdatasetnamesig.push_back(inputfilename);
      // 	Vlabelsig.push_back("m_{DM}=1 GeV/c^{2}, Zprime");
      // 	Vxsectionsig.push_back(1.); //pb
      // 	Vcolorsig.push_back(kOrange-3);
      // }
      // if( (inputfilename.find("10GeV")<200) ){
      // 	Vdatasetnamesig.push_back(inputfilename);
      // 	Vlabelsig.push_back("m_{DM}=10 GeV/c^{2}, Zprime");
      // 	Vxsectionsig.push_back(1.); //pb
      // 	Vcolorsig.push_back(kOrange-3);
      // }
      // if( (inputfilename.find("100GeV")<200) ){
      // 	Vdatasetnamesig.push_back(inputfilename);
      // 	Vlabelsig.push_back("m_{DM}=100 GeV/c^{2}, Zprime");
      // 	Vxsectionsig.push_back(1.); //pb
      // 	Vcolorsig.push_back(kOrange-3);
      // }
      // if( (inputfilename.find("500GeV")<200) ){
      // 	Vdatasetnamesig.push_back(inputfilename);
      // 	Vlabelsig.push_back("m_{DM}=500 GeV/c^{2}, Zprime");
      // 	Vxsectionsig.push_back(1.); //pb
      // 	Vcolorsig.push_back(kOrange-3);
      // }
      // if( (inputfilename.find("1000GeV")<200) ){
      // 	Vdatasetnamesig.push_back(inputfilename);
      // 	Vlabelsig.push_back("m_{DM}=1 TeV/c^{2}, Zprime");
      // 	Vxsectionsig.push_back(1.); //pb
      // 	Vcolorsig.push_back(kOrange-3);
      // }
    }
    // 2HDM
    else if(inputfilename.find("2HDM_MZp")<200 ){
      if( (inputfilename.find("600")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=600 GeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("800")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=800 GeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("1000")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=1000 GeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("1200")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=1.2 TeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("1400")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=1.4 TeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("1700")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'}=1.7 TeV/c^{2}, Zprime");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }	      
      if( (inputfilename.find("2000")<200) ){
        Vdatasetnamesig.push_back(inputfilename);
        Vlabelsig.push_back("m_{Z'}=2. TeV/c^{2}, Zprime");
        Vxsectionsig.push_back(1.); //pb                                                                                                                                                     
        Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("2500")<200) ){
        Vdatasetnamesig.push_back(inputfilename);
        Vlabelsig.push_back("m_{Z'}=2.5 TeV/c^{2}, Zprime");
        Vxsectionsig.push_back(1.); //pb                                                                                                                                                     
        Vcolorsig.push_back(kOrange-3);
      }
      
      
    }
    // ZpBaryonic
    else if(inputfilename.find("ZpBaryonic_MZp")<200 && inputfilename.find("MChi-1_")<200){
      if( (inputfilename.find("10000_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=10 TeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("1000_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=1 TeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("100_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=100 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("10_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=10 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("2000_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=2 TeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("200_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=200 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("20_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=20 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("300_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=300 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("500_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=500 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      if( (inputfilename.find("50_")<200) ){
	Vdatasetnamesig.push_back(inputfilename);
	Vlabelsig.push_back("m_{Z'_{B}}=50 GeV, m_{#chi}=1 GeV");
	Vxsectionsig.push_back(1.); //pb
	Vcolorsig.push_back(kOrange-3);
      }
      
    }
	    
    // background higgs
    else if(inputfilename.find("GluGluHToZZTo4L")<100 || 
	    inputfilename.find("SMHiggsToZZTo4L")<100   || 
	    inputfilename.find("VBF_HToZZTo4L")<100     ||
	    inputfilename.find("VBF_ToHToZZTo4L")<100   ||
	    inputfilename.find("TTbarH_HToZZTo4L")<100  ||
	    inputfilename.find("ttH_HToZZ_4L")<100  ||
	    inputfilename.find("ZH_HToZZ_4LFilter")<100  || 
	    inputfilename.find("ZH_ll_h2l2v")<100 ||
	    inputfilename.find("WplusH_HToZZTo4L")<100  |
            inputfilename.find("WminusH_HToZZTo4L")<100  || 
	    inputfilename.find("WH_ZH_HToZZ_4LFilter")<100 || 
	    inputfilename.find("bbHToWWTo2L2Nu_M-125_4FS_yb2_13TeV_amcatnlo")<100 || 
	    inputfilename.find("bbHToWWTo2L2Nu_M-125_4FS_ybyt_13TeV_amcatnlo")<100 || 
	    inputfilename.find("GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8")<100 || 
	    inputfilename.find("HZJ_HToWWTo2L2Nu_ZTo2L_M125_13TeV_powheg_pythia8")<100 || 
	    inputfilename.find("HWminusJ_HToWWTo2L2Nu_WToLNu_M125_13TeV_powheg_pythia8")<100 || 
	    inputfilename.find("HWplusJ_HToWWTo2L2Nu_WToLNu_M125_13TeV_powheg_pythia8")<100 || 
	    inputfilename.find("VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8")<100 ){  // provided that signal samples contain 'GluGluHToZZTo4L'
      //Vdatasetnamebkg.push_back(inputfilename);
      

      if( (inputfilename.find("M125")<200 && (inputfilename.find("GluGluHToZZTo4L_M125_13TeV_powheg")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ggH, H #rightarrow ZZ, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-3);
	//cout << "ggH" << endl;
      }

      if( (inputfilename.find("M125")<200 && (inputfilename.find("GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ggH, H #rightarrow WW, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-3);
	//cout << "ggH" << endl;
      }


      if( (inputfilename.find("M125")<200 && (inputfilename.find("VBF_HToZZTo4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("VBF H, H #rightarrow ZZ, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-2);
	//cout << "VBF H" << endl;
      }

      if( (inputfilename.find("M125")<200 && (inputfilename.find("VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("VBF H, H #rightarrow WW, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-2);
	//cout << "VBF H" << endl;
      }
      
      if( (inputfilename.find("M125")<200 && (inputfilename.find("ZH_HToZZ_4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ZH, H #rightarrow ZZ, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-1);
	//cout << "VH" << endl;
      }
      
      if( (inputfilename.find("ZH_ll_h2l2v")<200)){
	  Vdatasetnamebkg.push_back(inputfilename);
	  Vlabelbkg.push_back("ZH,ll,ZZ #rightarrow 2l2#nu, m_{H}=125 GeV");
	  Vxsectionbkg.push_back(1.); //pb                                                                             
	  Vcolorbkg.push_back(kOrange-1);
	  //cout << "ZH" << endl;               
      }

      if( (inputfilename.find("M125")<200 && (inputfilename.find("HZJ_HToWWTo2L2Nu_ZTo2L_M125_13TeV_powheg_pythia8")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ZH, H#rightarrow WW, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-1);
	//cout << "VH" << endl;
      }
      
      if( (inputfilename.find("M125")<200 && (inputfilename.find("WplusH_HToZZTo4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("WplusH, H #rightarrow ZZ, m_{H}=125 GeV");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kOrange+2);
        //cout << "VH" << endl;
      }

      if( (inputfilename.find("M125")<200 && (inputfilename.find("HWplusJ_HToWWTo2L2Nu_WToLNu_M125_13TeV_powheg_pythia8")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("WplusH, H #rightarrow WW, m_{H}=125 GeV");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kOrange+2);
        //cout << "VH" << endl;
      }


      if( (inputfilename.find("M125")<200 && (inputfilename.find("WminusH_HToZZTo4L")<200)) ){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("WminusH, H #rightarrow ZZ, m_{H}=125 GeV");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kOrange+3);
        //cout << "VH" << endl;
      }

      if( (inputfilename.find("M125")<200 && (inputfilename.find("HWminusJ_HToWWTo2L2Nu_WToLNu_M125_13TeV_powheg_pythia8")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("WminusH, H #rightarrow WW, m_{H}=125 GeV");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kOrange+2);
        //cout << "VH" << endl;
      }
      
      if( (inputfilename.find("M125")<200 && (inputfilename.find("WH_HToZZTo4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("WH, H #rightarrow ZZ, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-1);
	//cout << "VH" << endl;
      }
      
      if( (inputfilename.find("M125")<200 && (inputfilename.find("ttH_HToZZ_4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ttH, H #rightarrow ZZ, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange);
	//cout << "ttH" << endl;
      }

      if( (inputfilename.find("M-125")<200 && (inputfilename.find("bbHToWWTo2L2Nu")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("bbH, H #rightarrow WW, m_{H}=125 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange);
	//cout << "bbH" << endl;
      }
            
      if( (inputfilename.find("M-126")<200 && !(inputfilename.find("GluGluToHToZZTo4L")<200)) ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ggH, H #rightarrow ZZ, m_{H}=126 GeV");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kOrange-3);
      }            

    }
    // BACKGROUND from other sources
    else{  // provided that everything that is neither data nor signal is background
      //Vdatasetnamebkg.push_back(inputfilename);
      
      // qqZZ to 4l
      if(inputfilename.find("_ZZTo4L_13TeV_powheg_pythia8")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*},ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      if(inputfilename.find("_ZZ_TuneCUETP8M1_13TeV-pythia8")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Z#gamma^{*},ZZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 4mu
      if(inputfilename.find("_ZZTo4mu")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Z#gamma^{*},ZZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kPink+5);
      }
      
      // qqZZ to 4e
      if(inputfilename.find("_ZZTo4e")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 4tau
      if(inputfilename.find("_ZZTo4tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z\\#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 2e2mu
      if(inputfilename.find("_ZZTo2e2mu")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 2mu2tau
      if(inputfilename.find("_ZZTo2mu2tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 2e2tau
      if(inputfilename.find("_ZZTo2e2tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }

      // qqZZ to 2l2nu
      if(inputfilename.find("_ZZTo2L2Nu_13TeV_powheg_pythia8")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*},ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }
      

      

      // ggZZ 2L2L'
      if(inputfilename.find("GluGluToZZTo2L2L")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("GluGluToZZTo2L2L_8TeV-gg2zz-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kPink+5);
      }  

      // ggZZ 4L
      if(inputfilename.find("GluGluToZZTo4L")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("GluGluToZZTo4L_8TeV-gg2zz-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kPink+5);
      }     
    
      
      // ggZZ 4e
      if(inputfilename.find("GluGluToZZTo4e")<200 || inputfilename.find("GluGluToContinToZZTo4e")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }     
        
       // ggZZ 4mu
      if(inputfilename.find("GluGluToZZTo4mu")<200 || inputfilename.find("GluGluToContinToZZTo4mu")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  
 
      // ggZZ 4tau
      if(inputfilename.find("GluGluToZZTo4tau")<200 || inputfilename.find("GluGluToContinToZZTo4tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  

       // ggZZ 2e2mu
      if(inputfilename.find("GluGluToZZTo2e2mu")<200 || inputfilename.find("GluGluToContinToZZTo2e2mu")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  
 
       // ggZZ 2e2tau
      if(inputfilename.find("GluGluToZZTo2e2tau")<200 || inputfilename.find("GluGluToContinToZZTo2e2tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  

      // ggZZ 2mu2tau
      if(inputfilename.find("GluGluToZZTo2mu2tau")<200 || inputfilename.find("GluGluToContinToZZTo2mu2tau")<200){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  

      // ggZZ 2l2nu
      if(inputfilename.find("GluGluToContinToZZTo2e2nu")<200 || 
	 inputfilename.find("GluGluToContinToZZTo2mu2nu")<200 ||
	 inputfilename.find("GluGluToContinToZZTo2tau2nu")<200
	 ){
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z#gamma^{*],ZZ");
        Vxsectionbkg.push_back(1.); //pb
        Vcolorbkg.push_back(kPink+5);
      }  



      // WZ
      if(inputfilename.find("WZTo")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("WZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kCyan-2);
      } 
      
      // WWT2L2Nu
      if(inputfilename.find("WWTo")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("WW");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kCyan+3);
      } 

      // DYJetsToLL_TuneZ2_M-50_8TeV-madgraph-tauola 
      if( inputfilename.find("DYJetsToLL_TuneZ2_M-50")<200 || inputfilename.find("DYJetsToLL_M-50")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Z+jets");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kAzure+2);
      } 

      // DYJetsToLL_M-10To50
      if(inputfilename.find("DYJetsToLL_M-10To50")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Z+jets");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kAzure+2);
      } 

      
      // DYlighJetsToLL_TuneZ2_M-50_8TeV-madgraph-tauola 
      if(inputfilename.find("DYlightJetsToLL_TuneZ2_M-50")<200){//DYlightJetsToLL_TuneZ2_M-50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zlight");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kAzure+6);
      }   

      // DYlighJetsToLL_TuneZ2_M-10To50_8TeV-madgraph-tauola 
      if(inputfilename.find("DYlightJetsToLL_TuneZ2_M-10To50")<200){//DYlightJetsToLL_TuneZ2_M-10To50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zlight");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kAzure+6);
      }   
    
      
      // DYbbJetsToLL_TuneZ2_M-50_8TeV-madgraph-tauola 
      if(inputfilename.find("DYbbJetsToLL_TuneZ2_M-50")<200){//DYbbJetsToLL_TuneZ2_M-50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zbb");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kAzure+2);
      } 
      
      // DYbbJetsToLL_TuneZ2_M-10To50
      if(inputfilename.find("DYbbJetsToLL_TuneZ2_M-10To50")<200){//DYbbJetsToLL_TuneZ2_M-10To50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zbb");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kAzure+2);
      } 

      // DYccJetsToLL_TuneZ2_M-50_8TeV-madgraph-tauola 
      if(inputfilename.find("DYccJetsToLL_TuneZ2_M-50")<200){//DYccJetsToLL_TuneZ2_M-50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zcc");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kRed+0);
      } 
      
      // DYccJetsToLL_TuneZ2_M-10To50
      if(inputfilename.find("DYccJetsToLL_TuneZ2_M-10To50")<200){//DYccJetsToLL_TuneZ2_M-10To50
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Zcc");
	Vxsectionbkg.push_back(1.); 
	Vcolorbkg.push_back(kRed+0);
      } 


    
      // // DYToEE_M-10To20_TuneZ2_8TeV-pythia6
//       if(inputfilename.find("DYToEE")!=-1){
// 	Vdatasetnamebkg.push_back(inputfilename);
// 	Vlabelbkg.push_back("DYToEE_M-10To20_TuneZ2_8TeV-pythia6");
// 	Vxsectionbkg.push_back(1.); //pb
// 	Vcolorbkg.push_back(kAzure+9);
//       } 
      
//       // DYToMuMu_M-20_TuneZ2_8TeV-pythia6
//       if(inputfilename.find("DYToMuMu")!=-1){
// 	Vdatasetnamebkg.push_back(inputfilename);
// 	Vlabelbkg.push_back("DYToMuMu_M-20_TuneZ2_8TeV-pythia");
// 	Vxsectionbkg.push_back(1.); //pb
// 	Vcolorbkg.push_back(kAzure-7);
//       } 

      // ZToEE_NNPDF30_13TeV-powheg_M
      if(inputfilename.find("ZToEE_NNPDF30_13TeV-powheg_M")<200){//ZToEE_NNPDF30_13TeV-powheg_M
        Vdatasetnamebkg.push_back(inputfilename);
        Vlabelbkg.push_back("Z+jets");
        Vxsectionbkg.push_back(1.); 
        Vcolorbkg.push_back(kAzure-9);
      } 


      // QCD_Pt-30to40_doubleEMEnriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("30to40_doubleEMEnriched_TuneZ2_8TeV-pythia6")<52){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-30to40_doubleEMEnriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal+8);
      }
      // QCD_Pt-40_doubleEMEnriched_TuneZ2_8TeV-pythia6
      if(inputfilename.find("-40_doubleEMEnriched_TuneZ2_8TeV-pythia6")<52){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-40_doubleEMEnriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal+8);
      }


      // QCD_Pt-15to20_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-15to20_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-15to20_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-20to30_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-20to30_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-20to30_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-30to50_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-30to50_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-30to50_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-50to80_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-50to80_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-50to80_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-80to120_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-80to120_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-80to120_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-120to150_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-120to150_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-120to150_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-150_MuPt5Enriched_TuneZ2_8TeV-pythia6 
      if(inputfilename.find("QCD_Pt-150_MuPt5Enriched_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-150_MuPt5Enriched_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-8);
      }

      // QCD_Pt-20to30_BCtoE_TuneZ2_8TeV-pythia6
      if(inputfilename.find("QCD_Pt-20to30_BCtoE_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-20to30_BCtoE_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      // QCD_Pt-30to80_BCtoE_TuneZ2_8TeV-pythia6
      if(inputfilename.find("QCD_Pt-30to80_BCtoE_TuneZ2_8TeV-pythia6")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt-30to80_BCtoE_TuneZ2_8TeV-pythia6");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

        // NEW QCD Pythia 8
      if(inputfilename.find("QCD_Pt_1000to1400")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_10to15")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_10to15_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_120to170")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_1400to1800")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_15to30")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_170to300")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_1800to2400")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_2400to3200")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_300to470")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_30to50")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_3200toInf")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_470to600")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }
      
      if(inputfilename.find("QCD_Pt_50to80")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_5to10")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_5to10_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_600to800")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_800to1000")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }

      if(inputfilename.find("QCD_Pt_80to120")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-2);
      }


      // TTbar 
      if(inputfilename.find("TT_Tune")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("t#bar{t} + jets");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-6);
      } 
      // TTTo2L2Nu2B_8TeV-powheg-pythia6 
      if(inputfilename.find("TTTo2L2Nu")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("t#bar{t}");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kTeal-6);
      } 
      
      // Single Top
      // T_TuneZ2_s-channel_8TeV-madgraph
      if(inputfilename.find("T_s-channel")<200 || inputfilename.find("T_TuneZ2_s-channel")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("T_TuneZ2_s-channel_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 
      
      // T_TuneZ2_t-channel_8TeV-madgraph
      if(inputfilename.find("T_t-channel")<200 || inputfilename.find("T_TuneZ2_t-channel")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("T_TuneZ2_t-channel_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 
      
      // T_TuneZ2_tW-channel_8TeV-madgraph
      if(inputfilename.find("T_tW")<200 || inputfilename.find("T_TuneZ2_tW-channel")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("T_TuneZ2_tW-channel-DR_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 

      // Tbar_TuneZ2_s-channel_8TeV-madgraph
      if(inputfilename.find("Tbar_s-channel")<200 || inputfilename.find("Tbar_TuneZ2_s-channel")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Tbar_TuneZ2_s-channel_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 
      
      // Tbar_TuneZ2_t-channel_8TeV-madgraph
      if(inputfilename.find("Tbar_t-channel")<200 || inputfilename.find("Tbar_TuneZ2_t-channel")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Tbar_TuneZ2_t-channel_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 
      
      // Tbar_TuneZ2_tW-channel-DR_8TeV-madgraph
      if(inputfilename.find("Tbar_tW-channel")<200 || inputfilename.find("Tbar_TuneZ2_tW-channel")<200 ){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("Tbar_TuneZ2_tW-channel-DR_8TeV-powheg-tauola");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kViolet);
      } 


      // W+jets
      // WJetsToLNu_TuneZ2_8TeV-madgraph-tauola 
      if(inputfilename.find("_WJetsToLNu")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("W+Jets");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 
      
      /// VVV
      if (inputfilename.find("ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("ZZZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 
      
      if (inputfilename.find("WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("WWZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 
      
      if (inputfilename.find("WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("WZZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 
      
      // TTV
      if (inputfilename.find("TTWJets")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("TTW");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 

      if (inputfilename.find("TTZ")<200){
	Vdatasetnamebkg.push_back(inputfilename);
	Vlabelbkg.push_back("TTZ");
	Vxsectionbkg.push_back(1.); //pb
	Vcolorbkg.push_back(kSpring);
      } 
      
    }

  }
  
  infile.close();
 
}


void PlotStack4l::printnumbers(char name[400], TH1F *h){

  int nSkim_MC=h->GetBinContent(1);
  int nZLQpt_MC=h->GetBinContent(2);
  int nZLQptLI_MC=h->GetBinContent(3);
  int n4LQptLI_MC=h->GetBinContent(4);
  int n4lAfterPresel_MC=h->GetBinContent(5);
  int nIso_MC=h->GetBinContent(6);
  int nIsopt_MC=h->GetBinContent(7);
  int nIP_MC=h->GetBinContent(8);
  int nKin_MC=h->GetBinContent(9);

  cout << "Sample= " <<  name << endl;
  cout << "Skim MC= " <<  nSkim_MC 
       << " \n ZLQpt_MC="         << nZLQpt_MC
       << " \n ZLQptLI_MC="       << nZLQptLI_MC 
       << " \n 4LQptLI_MC="       << n4LQptLI_MC 
       << " \n BestCand_MC="      << n4lAfterPresel_MC 
       << " \n Iso_MC="           << nIso_MC 
       << " \n Iso(pt)_MC="       << nIsopt_MC 
       << " \n IP_MC="            << nIP_MC
       << " \n Kin_MC="           << nKin_MC
       << endl;
}

/*
void PlotStack4l::createdatacards(float Higgsm, float channel, float energy, float masslow, float masshigh, float ggH, float qqH, float WH, float ZH, float ttH, float bkg_qqzz, float bkg_ggzz, float bkg_zjets){

  
  Char_t txtOUT[500];
  //sprintf(txtOUT,"datacards/%s/hzz4l_%s_txt.txt",Higgsm,datasetName.Data());
  cout << "Opening a datacard file " << txtOUT << endl;
  ofstream output_txt;
  output_txt.open(txtOUT);

  output_txt << "imax 1" << endl; 
  output_txt << "jmax 7" << endl;
  output_txt << "kmax *" << endl;
  output_txt <<"------------" << endl; 
  output_txt <<"shapes * * hzz4l_4muS_8TeV.input.root w:$PROCESS" << endl;
  output_txt <<"------------" << endl;
  output_txt <<"bin a1" << endl; 
  output_txt <<"observation 16" << endl; 
  output_txt <<"------------" << endl;
  output_txt <<"## mass window [105.0,140.0]" << endl; 
  output_txt <<"bin a1 a1 a1 a1 a1 a1 a1 a1" << endl; 
  output_txt <<"process ggH qqH WH ZH ttH bkg2d_qqzz bkg2d_ggzz bkg2d_zjets" << endl; 
  output_txt <<"process -4 -3 -2 -1 0 1 2 3" << endl; 
  output_txt <<"rate 1.0000 1.0000 1.0000 1.0000 1.0000 7.6204 0.1543 1.1796" << endl; 
  output_txt <<"------------" << endl;
  output_txt <<"lumi_8TeV lnN 1.026 1.026 1.026 1.026 1.026 1.026 1.026 -" << endl; 
  output_txt <<"pdf_gg lnN 1.0720 - - - 1.0780 - 1.0708 -" << endl;
  output_txt <<"pdf_qqbar lnN - 1.0270 1.0350 1.0350 - 1.0341 - -" << endl;
  output_txt <<"pdf_hzz4l_accept lnN 1.02 1.02 1.02 1.02 1.02 - - -" << endl; 
  output_txt <<"QCDscale_ggH lnN 1.0750 - - - - - - -" << endl; 
  output_txt <<"QCDscale_qqH lnN - 1.0020 - - - - - -" << endl; 
  output_txt <<"QCDscale_VH lnN - - 1.0040 1.0155 - - - -" << endl; 
  output_txt <<"QCDscale_ttH lnN - - - - 1.0655 - - -" << endl;   
  output_txt <<"QCDscale_ggVV lnN - - - - - - 1.2431 -" << endl;  
  output_txt <<"QCDscale_VV lnN - - - - - 1.0284 - -" << endl;  
  output_txt <<"BRhiggs_hzz4l lnN 1.02 1.02 1.02 1.02 1.02 - - -" << endl;  
  output_txt <<"CMS_eff_m lnN 1.043 1.043 1.043 1.043 1.043 1.043 1.043 -" << endl;  
  output_txt <<"CMS_hzz4mu_Zjets lnN - - - - - - - 0.6/1.4" << endl;  
  output_txt <<"CMS_zz4l_bkgMELA param 0  1  [-3,3]" << endl; 
  output_txt <<"CMS_zz4l_mean_m_sig param 0.0 1.0" << endl;  
  output_txt <<"## CMS_zz4l_mean_m_sig = 0.001" << endl;  
  output_txt <<"CMS_zz4l_sigma_m_sig param 0.0 0.2" << endl;  
  output_txt <<"CMS_zz4l_n_sig_1_8 param 0.0 0.01" << endl;  
  output_txt <<"interf_ggH param 0 1 [-1,1]" << endl;  
  
  output_txt.close();

}
*/

/*
void PlotStack4l::getMassWindow(float Higgsm){

  std::string fileLoc = "/cmshome/nicola/tmp/test/Paper/last/last/CMSSW_5_3_9/src/Higgs/Higgs_CS_and_Width/txtFiles";
  HiggsCSandWidth myCSW = HiggsCSandWidth(fileLoc);

  double widthHVal =  myCSW.HiggsWidth(0,Higgsm);
  double windowVal = max( widthHVal, 1.0);
  double lowside = 100.0;
  double highside = 1000.0;
  
  if (Higgsm >= 275){
     lowside = 180.0;
     highside = 650.0;}
  if (Higgsm >= 350){
     lowside = 200.0;
     highside = 900.0;}
   if (Higgsm >= 500){
     lowside = 250.0;
     highside = 1000.0;}
   if (Higgsm >= 700){
     lowside = 350.0;
     highside = 1400.0;}
  
   float low_M = max( (Higgsm - 20.*windowVal), lowside);
   float high_M = min( (Higgsm + 15.*windowVal), highside);
  
   cout << "Mass window: " << low_M << " " << high_M << endl;

}
*/
