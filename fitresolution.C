#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "tdrstyle.C"
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
#include "TSystem.h"
#include <libgen.h>
#include "CMS_lumi.C"

class fitresolution{
 public:
  fitresolution();

};

fitresolution::fitresolution(){
 

  TStyle * style = setTDRStyle();


  writeExtraText = true;       // if extra text
  extraText  = "Simulation";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_13TeV  = "35.9 fb^{-1}";  // default is "35.9 fb^{-1}"
  lumi_14TeV  = "3000 fb^{-1}";  // default is "35.9 fb^{-1}"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 4=13TeV, 0=free form (uses lumi_sqrtS)

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  int W = 800;
  int H = 600;
  int iPos=11;
  
   // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  // Updated by:   Dinko Ferencek (Rutgers)
  //
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString canvName = "FigExample_";
  canvName += W;
  canvName += "-";
  canvName += H;
  canvName += "_";  
  canvName += iPeriod;
  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";

  TCanvas* c1 = new TCanvas(canvName,canvName,50,50,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  c1->SetTickx(0);
  c1->SetTicky(0);
  //canv->cd();
  //canv->SetTicks(1,1);
  //canv->SetLogx(1);
  //canv->SetLogy(1);

  int histLineColor = kOrange+7;
  int histFillColor = kOrange-2;
  float markerSize  = 1.0;
  

 
 

  // Muons and electrons acceptance

  TFile *_file1 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_MonoHZZ4l_ZpBaryonic_MZp-500_MChi-150_13TeV-madgraph.root");

  TLegend* legend_1 = new TLegend( 0.65, 0.75, 0.9, 0.9);
  legend_1->SetFillColor(kWhite);
  legend_1->SetTextSize(0.05);
  legend_1->SetTextFont(42);
  legend_1->SetTextAngle(0);
  legend_1->SetTextColor(kBlack);    
  legend_1->SetTextAlign(12); 

  // 
  TH2F *hframe_6=NULL;
  hframe_6= new TH2F("hframe_6","hframe_6",100,0.,3.1,100,0.,3);
  hframe_6->GetYaxis()->SetTitle("#sigma(m_{4#mu})");
  hframe_6->GetYaxis()->SetTitleOffset(0.8);
  hframe_6->GetXaxis()->SetTitle("max |#eta|");
  hframe_6->Draw();  

  TLegend* legend = new TLegend( 0.65, 0.75, 0.9, 0.9);
  legend->SetFillColor(kWhite);
  legend->SetTextSize(0.05);
  legend->SetTextFont(42);
  legend->SetTextAngle(0);
  legend->SetTextColor(kBlack);    
  legend->SetTextAlign(12); 

  Char_t histoname[500];  
  int i=2, bin=0;
  float bineta=0.1,binrms,binrmserror;
  TGraphErrors *resolution = new TGraphErrors();

  for (int i=1; i<9; i++){
    sprintf(histoname,"hM4lres_7_bin%d",i);
    cout << "Histo name is = " << histoname<< endl;
    
    TH1F *histo = (TH1F*)_file1->Get(histoname);  
    histo->SetLineColor(4);
    histo->SetLineWidth(2);  
    bineta=0.1+0.3*(i-1);
    binrms=histo->GetRMS();
    binrmserror=histo->GetRMSError();
    bin=i-1;
    cout << "Bineta= " << bineta << " RMS is= " << histo->GetRMS() << " RMS error= " << histo->GetRMSError()<< endl;   
    resolution->SetPoint(bin,bineta,binrms);
    resolution->SetPointError(bin,0.0,binrmserror);        
  }

  resolution->SetMarkerStyle(21);
  resolution->SetMarkerColor(4);
  legend->AddEntry(resolution,"H #rightarrow ZZ #rightarrow 4#mu", "P");
  resolution->Draw("EP1same");
  legend->Draw("same");
  // writing the lumi information and the CMS "logo"
  CMS_lumi( c1, iPeriod, iPos );
    
  c1->Update();
  c1->RedrawAxis();
  c1->GetFrame()->Draw();
  c1->SaveAs("plotsgen/fitM4mures.png");
  c1->SaveAs("plotsgen/fitM4mures.pdf");
  c1->SaveAs("plotsgen/fitM4mures.eps");  
}
