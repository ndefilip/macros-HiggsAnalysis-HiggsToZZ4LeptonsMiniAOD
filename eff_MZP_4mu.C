{

  /*
#include <TObject.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TLegend.h>
#include <algorithm>
#include <TMath.h>
#include "ZZStyle.C"
#include "vector.h"
#include "string.h"
#include <TROOT.h>
  */
using namespace std;
  
//gROOT->Reset();
//gROOT->Clear();
  
  
  //  TStyle * style = getStyle("ZZ");
  //style->SetMarkerSize(0.8);
  //style->cd();
  //style->SetNdivisions(508, "X");
  //style->SetMarkerSize(0.8);
  //
  
//  TCanvas *c1 = new TCanvas ("c1", "c1");
//  c1->SetLogy(0);
//  c1->SetLogx(0);
//  c1->SetTitle("Signal Efficiency for MZP");
// c1->cd();
    
 std::vector <std::string> fileNameMZP;
  
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP600_MA0300.root");
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP800_MA0300.root");
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP1000_MA0300.root");
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP1700_MA0300.root");
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP2000_MA0300.root");
  fileNameMZP.push_back("/lustre/cms/store/user/gminiell/MonoHiggs/76X/histos4mu_25ns/output_MZP2500_MA0300.root");
  
  
  cout<<"///////////////////////////////"<<endl;

  for(i=0; i<fileNameMZP.size(); i++){
    cout << fileNameMZP.at(i) << endl;
  }

  cout<<"///////////////////////////////"<<endl;

  
  int MZP[6]={600,800,1000,1700,2000,2500};
  
  for(i=0; i<6; i++){
    cout << MZP[i] << endl;
  }

}
