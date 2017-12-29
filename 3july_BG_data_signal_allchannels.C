#include "TCanvas.h"
#include "TFile.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "THStack.h"
#include "TStyle.h"
#include "TAxis.h"
#include <vector>
#include <iostream>

//---------------> To do <-------------------

void BG_data_signal_allchannels()
{
// ==================== >>> HOW TO USE THIS <<< ======================
// 1. Do a find+replace for the observable you want to plot -- use names of ROOT leaves
// 2. Change the titles of the histograms (just below) and the axis labels at the end where the histograms are drawn
// 3. Adjust the range by using a find+replace on eg 200,70.,2070.
// 4. Choose loglog or semilog by commenting/uncommenting the appropriate lines at the end
// 5. Note: You only need to do the Yield table once... Comment out!

// ----------------------------- HISTOGRAMS ---------------------------------
// ---> 4 mu
  THStack *hs_mu = new THStack("hs_mu","m_{4l}, 4#mu channel. #sqrt{s} = 13TeV, L = 2.9fb^{-1}");
  hs_mu->SetMaximum(50);
  hs_mu->SetMinimum(0.0000001);
  gStyle->SetTitleFont(62,"t");
  gStyle->SetTitleSize(0.05,"t"); 
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleBorderSize(0); 
  gStyle->SetTitleX(0.08);
  gStyle->SetOptStat(0);

  TLegend *mulegend = new TLegend(0.77,0.65,0.9,0.89);
  TLegend *muSlegend = new TLegend(0.69,0.65,0.77,0.89);

// ---> 4 e
  THStack *hs_e = new THStack("hs_e","m_{4l}, 4e channel. #sqrt{s} = 13TeV, L = 2.9fb^{-1}");
  hs_e->SetMaximum(50);
  hs_e->SetMinimum(0.0000001);

  TLegend *elegend = new TLegend(0.77,0.65,0.9,0.89);
  TLegend *eSlegend = new TLegend(0.69,0.65,0.77,0.89);

// ---> 2 e 2 mu
  THStack *hs_2e2mu = new THStack("hs_2e2mu","m_{4l}, 2e2mu channel. #sqrt{s} = 13TeV, L = 2.9fb^{-1}");
  hs_2e2mu->SetMaximum(50);
  hs_2e2mu->SetMinimum(0.0000001);

  TLegend *emulegend = new TLegend(0.77,0.65,0.9,0.89);
  TLegend *emuSlegend = new TLegend(0.69,0.65,0.77,0.89);


// Booleans for later use
  bool logmu = false;
  bool loge = false;
  bool log2e2mu = false;

// For yield table
  char outputstring[20000];   // For the table entries
  char outputstringS[20000]; 
  char outputsumBG[2000];
  char outputsumBGer[2000];
  char outputData[2000];

  vector<std::string> yieldstring4mu;  // For the names (eg VBF)
  vector<std::string> yieldstring4e;  // Create also for 4e and 2e2mu to double-check that they are the same; will use only one for the table.
  vector<std::string> yieldstring2e2mu;  

  vector<float> yields4mu;   // For numbers
  vector<float> eryields4mu; // ...and errors
  vector<float> yields4e;
  vector<float> eryields4e;
  vector<float> yields2e2mu;
  vector<float> eryields2e2mu;

  vector<std::string> Syieldstring4mu;  // For the names (eg VBF)
  vector<std::string> Syieldstring4e;  // Create also for 4e and 2e2mu to double-check that they are the same; will use only one for the table.
  vector<std::string> Syieldstring2e2mu;  

  vector<float> Syields4mu;   // For numbers
  vector<float> erSyields4mu; // ...and errors
  vector<float> Syields4e;
  vector<float> erSyields4e;
  vector<float> Syields2e2mu;
  vector<float> erSyields2e2mu;

// ========== GET FILENAMES IN ORDER TO OPEN FILES USING A LOOP ===============================
// BG, Signal and Data are in separate folders, this is how I can pick them
// up based on file extension only. 

// ---------------- Background (except QCD, SMZZ, ST, WH, ZH) ----------------------------

  const char* ext = ".root";
  const char* inDir4mu = "histos4mu_25ns/bgMC";
  const char* inDir4e = "histos4e_25ns/bgMC";
  const char* inDir2e2mu = "histos2e2mu_25ns/bgMC";

  char* dir4mu = gSystem->ExpandPathName(inDir4mu);
  void* dirp4mu = gSystem->OpenDirectory(dir4mu);

  char* dir4e = gSystem->ExpandPathName(inDir4e);
  void* dirp4e = gSystem->OpenDirectory(dir4e);

  char* dir2e2mu = gSystem->ExpandPathName(inDir2e2mu);
  void* dirp2e2mu = gSystem->OpenDirectory(dir2e2mu);

  const char* entry4mu;
  const char* entry4e;
  const char* entry2e2mu;
  const char* filename4mu[100];
  const char* filename4e[100];
  const char* filename2e2mu[100];

  Int_t n4mu = 0;
  TString str4mu;

  Int_t n4e = 0;
  TString str4e;

  Int_t n2e2mu = 0;
  TString str2e2mu;

  while((entry4mu = (char*)gSystem->GetDirEntry(dirp4mu))) {
    str4mu = entry4mu;
    if(str4mu.EndsWith(ext))
      filename4mu[n4mu++] = gSystem->ConcatFileName(dir4mu, entry4mu);
  }

  while((entry4e = (char*)gSystem->GetDirEntry(dirp4e))) {
    str4e = entry4e;
    if(str4e.EndsWith(ext))
      filename4e[n4e++] = gSystem->ConcatFileName(dir4e, entry4e);
  }

  while((entry2e2mu = (char*)gSystem->GetDirEntry(dirp2e2mu))) {
    str2e2mu = entry2e2mu;
    if(str2e2mu.EndsWith(ext))
      filename2e2mu[n2e2mu++] = gSystem->ConcatFileName(dir2e2mu, entry2e2mu);
  }

// --------------------- QCD Background ------------------------------

  const char* inDir4muQCD = "histos4mu_25ns/bgMC/QCD";
  const char* inDir4eQCD = "histos4e_25ns/bgMC/QCD";
  const char* inDir2e2muQCD = "histos2e2mu_25ns/bgMC/QCD";

  char* dir4muQCD = gSystem->ExpandPathName(inDir4muQCD);
  void* dirp4muQCD = gSystem->OpenDirectory(dir4muQCD);

  char* dir4eQCD = gSystem->ExpandPathName(inDir4eQCD);
  void* dirp4eQCD = gSystem->OpenDirectory(dir4eQCD);

  char* dir2e2muQCD = gSystem->ExpandPathName(inDir2e2muQCD);
  void* dirp2e2muQCD = gSystem->OpenDirectory(dir2e2muQCD);

  const char* entry4muQCD;
  const char* entry4eQCD;
  const char* entry2e2muQCD;
  const char* filename4muQCD[100];
  const char* filename4eQCD[100];
  const char* filename2e2muQCD[100];

  Int_t n4muQCD = 0;
  TString str4muQCD;

  Int_t n4eQCD = 0;
  TString str4eQCD;

  Int_t n2e2muQCD = 0;
  TString str2e2muQCD;

  while((entry4muQCD = (char*)gSystem->GetDirEntry(dirp4muQCD))) {
    str4muQCD = entry4muQCD;
    if(str4muQCD.EndsWith(ext))
      filename4muQCD[n4muQCD++] = gSystem->ConcatFileName(dir4muQCD, entry4muQCD);
  }

  while((entry4eQCD = (char*)gSystem->GetDirEntry(dirp4eQCD))) {
    str4eQCD = entry4eQCD;
    if(str4eQCD.EndsWith(ext))
      filename4eQCD[n4eQCD++] = gSystem->ConcatFileName(dir4eQCD, entry4eQCD);
  }

  while((entry2e2muQCD = (char*)gSystem->GetDirEntry(dirp2e2muQCD))) {
    str2e2muQCD = entry2e2muQCD;
    if(str2e2muQCD.EndsWith(ext))
      filename2e2muQCD[n2e2muQCD++] = gSystem->ConcatFileName(dir2e2muQCD, entry2e2muQCD);
  }


// --------------------- SMZZ Background ------------------------------

  const char* inDir4muSMZZ = "histos4mu_25ns/bgMC/SMZZ";
  const char* inDir4eSMZZ = "histos4e_25ns/bgMC/SMZZ";
  const char* inDir2e2muSMZZ = "histos2e2mu_25ns/bgMC/SMZZ";

  char* dir4muSMZZ = gSystem->ExpandPathName(inDir4muSMZZ);
  void* dirp4muSMZZ = gSystem->OpenDirectory(dir4muSMZZ);

  char* dir4eSMZZ = gSystem->ExpandPathName(inDir4eSMZZ);
  void* dirp4eSMZZ = gSystem->OpenDirectory(dir4eSMZZ);

  char* dir2e2muSMZZ = gSystem->ExpandPathName(inDir2e2muSMZZ);
  void* dirp2e2muSMZZ = gSystem->OpenDirectory(dir2e2muSMZZ);

  const char* entry4muSMZZ;
  const char* entry4eSMZZ;
  const char* entry2e2muSMZZ;
  const char* filename4muSMZZ[100];
  const char* filename4eSMZZ[100];
  const char* filename2e2muSMZZ[100];

  Int_t n4muSMZZ = 0;
  TString str4muSMZZ;

  Int_t n4eSMZZ = 0;
  TString str4eSMZZ;

  Int_t n2e2muSMZZ = 0;
  TString str2e2muSMZZ;

  while((entry4muSMZZ = (char*)gSystem->GetDirEntry(dirp4muSMZZ))) {
    str4muSMZZ = entry4muSMZZ;
    if(str4muSMZZ.EndsWith(ext))
      filename4muSMZZ[n4muSMZZ++] = gSystem->ConcatFileName(dir4muSMZZ, entry4muSMZZ);
  }

  while((entry4eSMZZ = (char*)gSystem->GetDirEntry(dirp4eSMZZ))) {
    str4eSMZZ = entry4eSMZZ;
    if(str4eSMZZ.EndsWith(ext))
      filename4eSMZZ[n4eSMZZ++] = gSystem->ConcatFileName(dir4eSMZZ, entry4eSMZZ);
  }

  while((entry2e2muSMZZ = (char*)gSystem->GetDirEntry(dirp2e2muSMZZ))) {
    str2e2muSMZZ = entry2e2muSMZZ;
    if(str2e2muSMZZ.EndsWith(ext))
      filename2e2muSMZZ[n2e2muSMZZ++] = gSystem->ConcatFileName(dir2e2muSMZZ, entry2e2muSMZZ);
  }

// --------------------- ST Background ------------------------------

  const char* inDir4muST = "histos4mu_25ns/bgMC/ST";
  const char* inDir4eST = "histos4e_25ns/bgMC/ST";
  const char* inDir2e2muST = "histos2e2mu_25ns/bgMC/ST";

  char* dir4muST = gSystem->ExpandPathName(inDir4muST);
  void* dirp4muST = gSystem->OpenDirectory(dir4muST);

  char* dir4eST = gSystem->ExpandPathName(inDir4eST);
  void* dirp4eST = gSystem->OpenDirectory(dir4eST);

  char* dir2e2muST = gSystem->ExpandPathName(inDir2e2muST);
  void* dirp2e2muST = gSystem->OpenDirectory(dir2e2muST);

  const char* entry4muST;
  const char* entry4eST;
  const char* entry2e2muST;
  const char* filename4muST[100];
  const char* filename4eST[100];
  const char* filename2e2muST[100];

  Int_t n4muST = 0;
  TString str4muST;

  Int_t n4eST = 0;
  TString str4eST;

  Int_t n2e2muST = 0;
  TString str2e2muST;

  while((entry4muST = (char*)gSystem->GetDirEntry(dirp4muST))) {
    str4muST = entry4muST;
    if(str4muST.EndsWith(ext))
      filename4muST[n4muST++] = gSystem->ConcatFileName(dir4muST, entry4muST);
  }

  while((entry4eST = (char*)gSystem->GetDirEntry(dirp4eST))) {
    str4eST = entry4eST;
    if(str4eST.EndsWith(ext))
      filename4eST[n4eST++] = gSystem->ConcatFileName(dir4eST, entry4eST);
  }

  while((entry2e2muST = (char*)gSystem->GetDirEntry(dirp2e2muST))) {
    str2e2muST = entry2e2muST;
    if(str2e2muST.EndsWith(ext))
      filename2e2muST[n2e2muST++] = gSystem->ConcatFileName(dir2e2muST, entry2e2muST);
  }

// --------------------- WH Background ------------------------------

  const char* inDir4muWpWm = "histos4mu_25ns/bgMC/WpWm";
  const char* inDir4eWpWm = "histos4e_25ns/bgMC/WpWm";
  const char* inDir2e2muWpWm = "histos2e2mu_25ns/bgMC/WpWm";

  char* dir4muWpWm = gSystem->ExpandPathName(inDir4muWpWm);
  void* dirp4muWpWm = gSystem->OpenDirectory(dir4muWpWm);

  char* dir4eWpWm = gSystem->ExpandPathName(inDir4eWpWm);
  void* dirp4eWpWm = gSystem->OpenDirectory(dir4eWpWm);

  char* dir2e2muWpWm = gSystem->ExpandPathName(inDir2e2muWpWm);
  void* dirp2e2muWpWm = gSystem->OpenDirectory(dir2e2muWpWm);

  const char* entry4muWpWm;
  const char* entry4eWpWm;
  const char* entry2e2muWpWm;
  const char* filename4muWpWm[100];
  const char* filename4eWpWm[100];
  const char* filename2e2muWpWm[100];

  Int_t n4muWpWm = 0;
  TString str4muWpWm;

  Int_t n4eWpWm = 0;
  TString str4eWpWm;

  Int_t n2e2muWpWm = 0;
  TString str2e2muWpWm;

  while((entry4muWpWm = (char*)gSystem->GetDirEntry(dirp4muWpWm))) {
    str4muWpWm = entry4muWpWm;
    if(str4muWpWm.EndsWith(ext))
      filename4muWpWm[n4muWpWm++] = gSystem->ConcatFileName(dir4muWpWm, entry4muWpWm);
  }

  while((entry4eWpWm = (char*)gSystem->GetDirEntry(dirp4eWpWm))) {
    str4eWpWm = entry4eWpWm;
    if(str4eWpWm.EndsWith(ext))
      filename4eWpWm[n4eWpWm++] = gSystem->ConcatFileName(dir4eWpWm, entry4eWpWm);
  }

  while((entry2e2muWpWm = (char*)gSystem->GetDirEntry(dirp2e2muWpWm))) {
    str2e2muWpWm = entry2e2muWpWm;
    if(str2e2muWpWm.EndsWith(ext))
      filename2e2muWpWm[n2e2muWpWm++] = gSystem->ConcatFileName(dir2e2muWpWm, entry2e2muWpWm);
  }

// --------------------- ZH Background ------------------------------

  const char* inDir4muZH = "histos4mu_25ns/bgMC/ZH";
  const char* inDir4eZH = "histos4e_25ns/bgMC/ZH";
  const char* inDir2e2muZH = "histos2e2mu_25ns/bgMC/ZH";

  char* dir4muZH = gSystem->ExpandPathName(inDir4muZH);
  void* dirp4muZH = gSystem->OpenDirectory(dir4muZH);

  char* dir4eZH = gSystem->ExpandPathName(inDir4eZH);
  void* dirp4eZH = gSystem->OpenDirectory(dir4eZH);

  char* dir2e2muZH = gSystem->ExpandPathName(inDir2e2muZH);
  void* dirp2e2muZH = gSystem->OpenDirectory(dir2e2muZH);

  const char* entry4muZH;
  const char* entry4eZH;
  const char* entry2e2muZH;
  const char* filename4muZH[100];
  const char* filename4eZH[100];
  const char* filename2e2muZH[100];

  Int_t n4muZH = 0;
  TString str4muZH;

  Int_t n4eZH = 0;
  TString str4eZH;

  Int_t n2e2muZH = 0;
  TString str2e2muZH;

  while((entry4muZH = (char*)gSystem->GetDirEntry(dirp4muZH))) {
    str4muZH = entry4muZH;
    if(str4muZH.EndsWith(ext))
      filename4muZH[n4muZH++] = gSystem->ConcatFileName(dir4muZH, entry4muZH);
  }

  while((entry4eZH = (char*)gSystem->GetDirEntry(dirp4eZH))) {
    str4eZH = entry4eZH;
    if(str4eZH.EndsWith(ext))
      filename4eZH[n4eZH++] = gSystem->ConcatFileName(dir4eZH, entry4eZH);
  }

  while((entry2e2muZH = (char*)gSystem->GetDirEntry(dirp2e2muZH))) {
    str2e2muZH = entry2e2muZH;
    if(str2e2muZH.EndsWith(ext))
      filename2e2muZH[n2e2muZH++] = gSystem->ConcatFileName(dir2e2muZH, entry2e2muZH);
  }

// --------------------------------- Data -----------------------------------------------

  const char* inDir4mu2 = "histos4mu_25ns/data/";
  const char* inDir4e2 = "histos4e_25ns/data/";
  const char* inDir2e2mu2 = "histos2e2mu_25ns/data/";

  char* dir4mu2 = gSystem->ExpandPathName(inDir4mu2);
  void* dirp4mu2 = gSystem->OpenDirectory(dir4mu2);

  char* dir4e2 = gSystem->ExpandPathName(inDir4e2);
  void* dirp4e2 = gSystem->OpenDirectory(dir4e2);

  char* dir2e2mu2 = gSystem->ExpandPathName(inDir2e2mu2);
  void* dirp2e2mu2 = gSystem->OpenDirectory(dir2e2mu2);

  const char* entry4mu2;
  const char* entry4e2;
  const char* entry2e2mu2;

  const char* filename4mu2[100];
  const char* filename4e2[100];
  const char* filename2e2mu2[100];

  Int_t n4mu2 = 0;
  TString str4mu2;
  
  Int_t n4e2 = 0;
  TString str4e2;

  Int_t n2e2mu2 = 0;
  TString str2e2mu2;

  while((entry4mu2 = (char*)gSystem->GetDirEntry(dirp4mu2))) {
    str4mu2 = entry4mu2;
    if(str4mu2.EndsWith(ext))
      filename4mu2[n4mu2++] = gSystem->ConcatFileName(dir4mu2, entry4mu2);
  }

  while((entry4e2 = (char*)gSystem->GetDirEntry(dirp4e2))) {
    str4e2 = entry4e2;
    if(str4e2.EndsWith(ext))
      filename4e2[n4e2++] = gSystem->ConcatFileName(dir4e2, entry4e2);
  }

  while((entry2e2mu2 = (char*)gSystem->GetDirEntry(dirp2e2mu2))) {
    str2e2mu2 = entry2e2mu2;
    if(str2e2mu2.EndsWith(ext))
      filename2e2mu2[n2e2mu2++] = gSystem->ConcatFileName(dir2e2mu2, entry2e2mu2);
  }


// -------------------------- Signal MC ------------------------------

  const char* inDir4muS = "histos4mu_25ns/signal";
  const char* inDir4eS = "histos4e_25ns/signal";
  const char* inDir2e2muS = "histos2e2mu_25ns/signal";

  char* dir4muS = gSystem->ExpandPathName(inDir4muS);
  void* dirp4muS = gSystem->OpenDirectory(dir4muS);

  char* dir4eS = gSystem->ExpandPathName(inDir4eS);
  void* dirp4eS = gSystem->OpenDirectory(dir4eS);

  char* dir2e2muS = gSystem->ExpandPathName(inDir2e2muS);
  void* dirp2e2muS = gSystem->OpenDirectory(dir2e2muS);

  const char* entry4muS;
  const char* entry4eS;
  const char* entry2e2muS;
  const char* filename4muS[100];
  const char* filename4eS[100];
  const char* filename2e2muS[100];

  Int_t n4muS = 0;
  TString str4muS;

  Int_t n4eS = 0;
  TString str4eS;

  Int_t n2e2muS = 0;
  TString str2e2muS;

  while((entry4muS = (char*)gSystem->GetDirEntry(dirp4muS))) {
    str4muS = entry4muS;
    if(str4muS.EndsWith(ext))
      filename4muS[n4muS++] = gSystem->ConcatFileName(dir4muS, entry4muS);
  }

  while((entry4eS = (char*)gSystem->GetDirEntry(dirp4eS))) {
    str4eS = entry4eS;
    if(str4eS.EndsWith(ext))
      filename4eS[n4eS++] = gSystem->ConcatFileName(dir4eS, entry4eS);
  }

  while((entry2e2muS = (char*)gSystem->GetDirEntry(dirp2e2muS))) {
    str2e2muS = entry2e2muS;
    if(str2e2muS.EndsWith(ext))
      filename2e2muS[n2e2muS++] = gSystem->ConcatFileName(dir2e2muS, entry2e2muS);
  }


//------------------- 4 mu channel ----------------------------------
// ---> All background except QCD, SMZZ, ST, WplusWminus

  // sort files alphabetically
    vector<string> v_path_4mu;                 // create vector for storing paths

    for (Int_t i = 0; i < n4mu; i++){          // fill the vector
      v_path_4mu.push_back(filename4mu[i]);
    }

//    cout << "Before sorting 4mu: " << endl; 
  
  /*  for (Int_t i = 0; i < n4mu; i++){
      cout << v_path_4mu[i] << endl;
    }*/

    sort(v_path_4mu.begin(), v_path_4mu.end());   // sort

 //   cout << "After sorting 4mu: " << endl; // ok this works

   /* for (Int_t i = 0; i < n4mu; i++){
      cout << v_path_4mu[i] << endl;
    }*/

  TH1F *h_nonQCD4mu = new TH1F("h_nonQCD4mu","4 mu invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);

  for (Int_t i = 0; i < n4mu; i++){
    TFile *d_i = new TFile((v_path_4mu[i]).c_str(),"READONLY"); 
    TTree *tree_d_i = (TTree*) d_i->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i->SetName("Tree[i]");

    TH1F *h_i = new TH1F("m4l[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
      if (i<9) 
	h_i->SetFillColor(i+1);
      else if (i<19)  
	h_i->SetFillColor((i+1)*2);
      else   
	h_i->SetFillColor((i+1)*4);
    tree_d_i->TTree::Project("m4l[i]","f_mass4l","f_weight");

    std::string str1 = v_path_4mu[i];
    std::string str2 = str1.substr(27);

    std::string::size_type const p(str2.find_last_of('.'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_BG_mu = h_i->Integral(0,-1);
    double err_BG_mu = sqrt(h_i->GetEntries())*h_i->Integral(0,-1)/h_i->GetEntries();

    /*std::string appendix = std::string(", ") + std::to_string(entries_BG_mu) + std::string(" exp.");  < -- Uncomment (for all channels) to get yields in the legend
    str3.append(appendix);*/

    const char * reducedfile = str3.c_str();

    TH1F *h_iClone = (TH1F*)h_i->Clone("h_iClone");
    hs_mu->Add(h_i);
    h_nonQCD4mu->Add(h_iClone);

    yieldstring4mu.push_back(yieldname);  // for yield table
    yields4mu.push_back(entries_BG_mu);
	if (entries_BG_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_i->GetEntries())*h_i->Integral(0,-1)/h_i->GetEntries());

    if (entries_BG_mu == 0.) continue;   // only add to legend if not zero
      mulegend->AddEntry(h_i,reducedfile);

    h_i->SetDirectory(0);
    gROOT->cd();
    delete d_i;
    }

  cout << "Yieldstring size after bgMC muons: " << yieldstring4mu.size() << endl;

// ---> QCD Background

    TH1F *h_4muQCD = new TH1F("h_4muQCD","4 mu invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4muQCD->SetFillColor(kTeal);

  for (Int_t i = 0; i < n4muQCD; i++){
    TFile *d_i4muQCD = new TFile(filename4muQCD[i],"READONLY"); 
    TTree *tree_d_i4muQCD = (TTree*) d_i4muQCD->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muQCD->SetName("Tree4muQCD[i]");

    TH1F *h_i4muQCD = new TH1F("m4l4muQCD[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4muQCD->TTree::Project("m4l4muQCD[i]","f_mass4l","f_weight");
    h_4muQCD->Add(h_i4muQCD);

    h_4muQCD->SetDirectory(0);
    gROOT->cd();
    delete d_i4muQCD;
    }

  hs_mu->Add(h_4muQCD);

  double entries_QCD_mu = h_4muQCD->Integral(0,-1);
  const char * app4muQCD = (std::string("QCD")).c_str();//, ") + std::to_string(entries_QCD_mu) + std::string(" exp.")).c_str();  <-- fix/uncomment this (in all BG:s except the first in each channel) to get yields in the legend

    yieldstring4mu.push_back("QCD");  // for yield table
    yields4mu.push_back(entries_QCD_mu);
	if (entries_QCD_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_4muQCD->GetEntries())*h_4muQCD->Integral(0,-1)/h_4muQCD->GetEntries());

  if (entries_QCD_mu != 0.)
    mulegend->AddEntry(h_4muQCD,app4muQCD);

// ---> SMZZ Background

    TH1F *h_4muSMZZ = new TH1F("h_4muSMZZ","4 mu invariant mass SMZZ BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4muSMZZ->SetFillColor(kOrange);

  for (Int_t i = 0; i < n4muSMZZ; i++){
    TFile *d_i4muSMZZ = new TFile(filename4muSMZZ[i],"READONLY"); 
    TTree *tree_d_i4muSMZZ = (TTree*) d_i4muSMZZ->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muSMZZ->SetName("Tree4muSMZZ[i]");

    TH1F *h_i4muSMZZ = new TH1F("m4l4muSMZZ[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4muSMZZ->TTree::Project("m4l4muSMZZ[i]","f_mass4l","f_weight");
    h_4muSMZZ->Add(h_i4muSMZZ);

    h_4muSMZZ->SetDirectory(0);
    gROOT->cd();
    delete d_i4muSMZZ;
    }

  hs_mu->Add(h_4muSMZZ);

  double entries_SMZZ_mu = h_4muSMZZ->Integral(0,-1);
  const char * app4muSMZZ = (std::string("SM ZZ")).c_str();//, ") + std::to_string(entries_SMZZ_mu) + std::string(" exp.")).c_str();

    yieldstring4mu.push_back("SMZZ");  // for yield table
    yields4mu.push_back(entries_SMZZ_mu);
	if (entries_SMZZ_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_4muSMZZ->GetEntries())*h_4muSMZZ->Integral(0,-1)/h_4muSMZZ->GetEntries());

  if (entries_SMZZ_mu != 0.)
  mulegend->AddEntry(h_4muSMZZ,app4muSMZZ);

// ---> ST Background

    TH1F *h_4muST = new TH1F("h_4muST","4 mu invariant mass ST BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4muST->SetFillColor(kViolet);

  for (Int_t i = 0; i < n4muST; i++){
    TFile *d_i4muST = new TFile(filename4muST[i],"READONLY"); 
    TTree *tree_d_i4muST = (TTree*) d_i4muST->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muST->SetName("Tree4muST[i]");

    TH1F *h_i4muST = new TH1F("m4l4muST[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4muST->TTree::Project("m4l4muST[i]","f_mass4l","f_weight");
    h_4muST->Add(h_i4muST);

    h_i4muST->SetDirectory(0);
    gROOT->cd();
    delete d_i4muST;
    }

  hs_mu->Add(h_4muST);

  double entries_ST_mu = h_4muST->Integral(0,-1);
  const char * app4muST = (std::string("ST")).c_str();//, ") + std::to_string(entries_ST_mu) + std::string(" exp.")).c_str();  

    yieldstring4mu.push_back("ST");  // for yield table
    yields4mu.push_back(entries_ST_mu);
	if (entries_ST_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_4muST->GetEntries())*h_4muST->Integral(0,-1)/h_4muST->GetEntries());


  if (entries_ST_mu != 0.)
  mulegend->AddEntry(h_4muST,app4muST);

// ---> WH Background

    TH1F *h_4muWpWm = new TH1F("h_4muWpWm","4 mu invariant mass WpWm BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4muWpWm->SetFillColor(kSpring+10);

  for (Int_t i = 0; i < n4muWpWm; i++){
    TFile *d_i4muWpWm = new TFile(filename4muWpWm[i],"READONLY"); 
    TTree *tree_d_i4muWpWm = (TTree*) d_i4muWpWm->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muWpWm->SetName("Tree4muWpWm[i]");

    TH1F *h_i4muWpWm = new TH1F("m4l4muWpWm[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4muWpWm->TTree::Project("m4l4muWpWm[i]","f_mass4l","f_weight");
    h_4muWpWm->Add(h_i4muWpWm);

    h_i4muWpWm->SetDirectory(0);
    gROOT->cd();
    delete d_i4muWpWm;
    }

  hs_mu->Add(h_4muWpWm);

  double entries_WpWm_mu = h_4muWpWm->Integral(0,-1);
  const char * app4muWpWm = (std::string("WH")).c_str();//, ") + std::to_string(entries_WpWm_mu) + std::string(" exp.")).c_str();

    yieldstring4mu.push_back("WpWm");  // for yield table
    yields4mu.push_back(entries_WpWm_mu);
	if (entries_WpWm_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_4muWpWm->GetEntries())*h_4muWpWm->Integral(0,-1)/h_4muWpWm->GetEntries());

  if (entries_WpWm_mu != 0.)
  mulegend->AddEntry(h_4muWpWm,app4muWpWm);

// ---> ZH Background

    TH1F *h_4muZH = new TH1F("h_4muZH","4 mu invariant mass ZH BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4muZH->SetFillColor(kPink+10);

  for (Int_t i = 0; i < n4muZH; i++){
    TFile *d_i4muZH = new TFile(filename4muZH[i],"READONLY"); 
    TTree *tree_d_i4muZH = (TTree*) d_i4muZH->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muZH->SetName("Tree4muZH[i]");

    TH1F *h_i4muZH = new TH1F("m4l4muZH[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4muZH->TTree::Project("m4l4muZH[i]","f_mass4l","f_weight");

  double entries_ZH_mu = h_i4muZH->Integral(0,-1);
	if (entries_ZH_mu == 0.) continue;

    h_4muZH->Add(h_i4muZH);

    h_i4muZH->SetDirectory(0);
    gROOT->cd();
    delete d_i4muZH;
    }

  hs_mu->Add(h_4muZH);

  double entries_ZH_mu = h_4muZH->Integral(0,-1);
  const char * app4muZH = (std::string("ZH")).c_str();//, ") + std::to_string(entries_ZH_mu) + std::string(" exp.")).c_str();

    yieldstring4mu.push_back("ZH");  // for yield table
    yields4mu.push_back(entries_ZH_mu);
	if (entries_ZH_mu == 0)
	    eryields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4mu.push_back(sqrt(h_4muZH->GetEntries())*h_4muZH->Integral(0,-1)/h_4muZH->GetEntries());

  if (entries_ZH_mu != 0.)
    mulegend->AddEntry(h_4muZH,app4muZH);


//------------------- 4 e channel ----------------------------------
// ---> All background except QCD, SMZZ, ST, WpWm

  // sort files alphabetically
    vector<string> v_path_4e;                 // create vector for storing paths

    for (Int_t i = 0; i < n4e; i++){          // fill the vector
      v_path_4e.push_back(filename4e[i]);
    }

  //  cout << "Before sorting 4e: " << endl;
  
  /*  for (Int_t i = 0; i < n4e; i++){
      cout << v_path_4e[i] << endl;
    }*/

    sort(v_path_4e.begin(), v_path_4e.end());   // sort

  //  cout << "After sorting 4e: " << endl; // ok this works

   /* for (Int_t i = 0; i < n4e; i++){
      cout << v_path_4e[i] << endl;
    }*/

  TH1F *h_nonQCD4e = new TH1F("h_nonQCD4e","4 e invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);

  for (Int_t i = 0; i < n4e; i++){
    TFile *d_i = new TFile((v_path_4e[i]).c_str(),"READONLY");
    TTree *tree_d_i = (TTree*) d_i->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i->SetName("Tree[i]");
    TH1F *h_i = new TH1F("m4l[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
      if (i<9) 
	h_i->SetFillColor(i+1);
      else if (i<19)  
	h_i->SetFillColor((i+1)*2);
      else   
	h_i->SetFillColor((i+1)*4);
    tree_d_i->TTree::Project("m4l[i]","f_mass4l","f_weight");

    std::string str1 = v_path_4e[i];
    std::string str2 = str1.substr(26);

    std::string::size_type const p(str2.find_last_of('.'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_BG_e = h_i->Integral(0,-1);

    //std::string appendix = std::string(" (4e), ") + std::to_string(entries_BG_e) + std::string(" entries");
   /* std::string appendix = std::string(", ") + std::to_string(entries_BG_e) + std::string(" exp.");
    str3.append(appendix);*/

    const char * reducedfile = str3.c_str();

    TH1F *h_iClone = (TH1F*)h_i->Clone("h_iClone");
    hs_e->Add(h_i);
    h_nonQCD4e->Add(h_iClone);

    yieldstring4e.push_back(yieldname);  // for yield table
    yields4e.push_back(entries_BG_e);
	if (entries_BG_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_i->GetEntries())*h_i->Integral(0,-1)/h_i->GetEntries());


    if (entries_BG_e == 0.) continue;
      elegend->AddEntry(h_i,reducedfile);

    h_i->SetDirectory(0);
    gROOT->cd();
    delete d_i;

    }

  cout << "Yieldstring size after bgMC electrons: " << yieldstring4e.size() << endl;

// ---> QCD Background

    TH1F *h_4eQCD = new TH1F("h_4eQCD","4 e invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4eQCD->SetFillColor(kTeal);

  for (Int_t i = 0; i < n4eQCD; i++){
    TFile *d_i4eQCD = new TFile(filename4eQCD[i],"READONLY"); 
    TTree *tree_d_i4eQCD = (TTree*) d_i4eQCD->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eQCD->SetName("Tree4eQCD[i]");

    TH1F *h_i4eQCD = new TH1F("m4l4eQCD[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4eQCD->TTree::Project("m4l4eQCD[i]","f_mass4l","f_weight");
    h_4eQCD->Add(h_i4eQCD);
    }

  hs_e->Add(h_4eQCD);

  double entries_QCD_e = h_4eQCD->Integral(0,-1);
  const char * app4eQCD = (std::string("QCD")).c_str();//, ") + std::to_string(entries_QCD_e) + std::string(" exp.")).c_str();

    yieldstring4e.push_back("QCD");  // for yield table
    yields4e.push_back(entries_QCD_e);
	if (entries_QCD_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_4eQCD->GetEntries())*h_4eQCD->Integral(0,-1)/h_4eQCD->GetEntries());

  if (entries_QCD_e != 0.)
    elegend->AddEntry(h_4eQCD,app4eQCD);

// ---> SMZZ Background

    TH1F *h_4eSMZZ = new TH1F("h_4eSMZZ","4 e invariant mass SMZZ BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4eSMZZ->SetFillColor(kOrange);

  for (Int_t i = 0; i < n4eSMZZ; i++){
    TFile *d_i4eSMZZ = new TFile(filename4eSMZZ[i],"READONLY"); 
    TTree *tree_d_i4eSMZZ = (TTree*) d_i4eSMZZ->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eSMZZ->SetName("Tree4eSMZZ[i]");

    TH1F *h_i4eSMZZ = new TH1F("m4l4eSMZZ[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4eSMZZ->TTree::Project("m4l4eSMZZ[i]","f_mass4l","f_weight");
    h_4eSMZZ->Add(h_i4eSMZZ);
    }

  hs_e->Add(h_4eSMZZ);

  double entries_SMZZ_e = h_4eSMZZ->Integral(0,-1);
  const char * app4eSMZZ = (std::string("SM ZZ")).c_str();//, ") + std::to_string(entries_SMZZ_e) + std::string(" exp.")).c_str();

    yieldstring4e.push_back("SMZZ");  // for yield table
    yields4e.push_back(entries_SMZZ_e);
	if (entries_SMZZ_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_4eSMZZ->GetEntries())*h_4eSMZZ->Integral(0,-1)/h_4eSMZZ->GetEntries());

  if (entries_SMZZ_e != 0.)
    elegend->AddEntry(h_4eSMZZ,app4eSMZZ);

// ---> ST Background

    TH1F *h_4eST = new TH1F("h_4eST","4 e invariant mass ST BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4eST->SetFillColor(kViolet);

  for (Int_t i = 0; i < n4eST; i++){
    TFile *d_i4eST = new TFile(filename4eST[i],"READONLY"); 
    TTree *tree_d_i4eST = (TTree*) d_i4eST->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eST->SetName("Tree4eST[i]");

    TH1F *h_i4eST = new TH1F("m4l4eST[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4eST->TTree::Project("m4l4eST[i]","f_mass4l","f_weight");
    h_4eST->Add(h_i4eST);
    }

  hs_e->Add(h_4eST);

  double entries_ST_e = h_4eST->Integral(0,-1);
  const char * app4eST = (std::string("ST")).c_str();//, ") + std::to_string(entries_ST_e) + std::string(" exp.")).c_str();

    yieldstring4e.push_back("ST");  // for yield table
    yields4e.push_back(entries_ST_e);
	if (entries_ST_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_4eST->GetEntries())*h_4eST->Integral(0,-1)/h_4eST->GetEntries());

  if (entries_ST_e != 0.)
    elegend->AddEntry(h_4eST,app4eST);

// ---> WHBackground

    TH1F *h_4eWpWm = new TH1F("h_4eWpWm","4 e invariant mass WpWm BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4eWpWm->SetFillColor(kSpring+10);

  for (Int_t i = 0; i < n4eWpWm; i++){
    TFile *d_i4eWpWm = new TFile(filename4eWpWm[i],"READONLY"); 
    TTree *tree_d_i4eWpWm = (TTree*) d_i4eWpWm->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eWpWm->SetName("Tree4eWpWm[i]");

    TH1F *h_i4eWpWm = new TH1F("m4l4eWpWm[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4eWpWm->TTree::Project("m4l4eWpWm[i]","f_mass4l","f_weight");
    h_4eWpWm->Add(h_i4eWpWm);
    }

  hs_e->Add(h_4eWpWm);

  double entries_WpWm_e = h_4eWpWm->Integral(0,-1);
  const char * app4eWpWm = (std::string("WH")).c_str();//, ") + std::to_string(entries_WpWm_e) + std::string(" exp.")).c_str();

    yieldstring4e.push_back("WpWm");  // for yield table
    yields4e.push_back(entries_WpWm_e);
	if (entries_WpWm_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_4eWpWm->GetEntries())*h_4eWpWm->Integral(0,-1)/h_4eWpWm->GetEntries());

  if (entries_WpWm_e != 0.)
    elegend->AddEntry(h_4eWpWm,app4eWpWm);

// ---> ZHBackground

    TH1F *h_4eZH = new TH1F("h_4eZH","4 e invariant mass ZH BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_4eZH->SetFillColor(kPink+10);

  for (Int_t i = 0; i < n4eZH; i++){
    TFile *d_i4eZH = new TFile(filename4eZH[i],"READONLY"); 
    TTree *tree_d_i4eZH = (TTree*) d_i4eZH->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eZH->SetName("Tree4eZH[i]");

    TH1F *h_i4eZH = new TH1F("m4l4eZH[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4eZH->TTree::Project("m4l4eZH[i]","f_mass4l","f_weight");
    h_4eZH->Add(h_i4eZH);
    }

  hs_e->Add(h_4eZH);

  double entries_ZH_e = h_4eZH->Integral(0,-1);
  const char * app4eZH = (std::string("ZH")).c_str();//, ") + std::to_string(entries_ZH_e) + std::string(" exp.")).c_str();

    yieldstring4e.push_back("ZH");  // for yield table
    yields4e.push_back(entries_ZH_e);
	if (entries_ZH_e == 0)
	    eryields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields4e.push_back(sqrt(h_4eZH->GetEntries())*h_4eZH->Integral(0,-1)/h_4eZH->GetEntries());

  if (entries_ZH_e != 0.)
    elegend->AddEntry(h_4eZH,app4eZH);

//------------------- 2 e 2 mu channel -------------------------------

// ---> All background except QCD, SMZZ, ST, WpWm

  // sort files alphabetically
    vector<string> v_path_2e2mu;                 // create vector for storing paths

    for (Int_t i = 0; i < n2e2mu; i++){          // fill the vector
      v_path_2e2mu.push_back(filename2e2mu[i]);
    }

 //   cout << "Before sorting 2e2mu: " << endl;
  
  /*  for (Int_t i = 0; i < n2e2mu; i++){
      cout << v_path_2e2mu[i] << endl;
    }*/

    sort(v_path_2e2mu.begin(), v_path_2e2mu.end());   // sort

  //  cout << "After sorting 2e2mu: " << endl; // ok this works

   /* for (Int_t i = 0; i < n2e2mu; i++){
      cout << v_path_2e2mu[i] << endl;
    }*/

  TH1F *h_nonQCD2e2mu = new TH1F("h_nonQCD2e2mu","2e2mu invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);

  // loop over files
  for (Int_t i = 0; i < n2e2mu; i++){
    TFile *d_i = new TFile((v_path_2e2mu[i]).c_str(),"READONLY");  
    TTree *tree_d_i = (TTree*) d_i->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i->SetName("Tree[i]");
    TH1F *h_i = new TH1F("m4l[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
      if (i<9) 
	h_i->SetFillColor(i+1);
      else if (i<19)  
	h_i->SetFillColor((i+1)*2);
      else   
	h_i->SetFillColor((i+1)*4);
    tree_d_i->TTree::Project("m4l[i]","f_mass4l","f_weight");

    std::string str1 = v_path_2e2mu[i];
    std::string str2 = str1.substr(29);

    std::string::size_type const p(str2.find_last_of('.'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_BG_2e2mu = h_i->Integral(0,-1);

   // std::string appendix = std::string(", ") + std::to_string(entries_BG_2e2mu) + std::string(" exp.");
   // str3.append(appendix);

    const char * reducedfile = str3.c_str();

    TH1F *h_iClone = (TH1F*)h_i->Clone("h_iClone");
    hs_2e2mu->Add(h_i);
    h_nonQCD2e2mu->Add(h_iClone);

    yieldstring2e2mu.push_back(yieldname);  // for yield table
    yields2e2mu.push_back(entries_BG_2e2mu);
	if (entries_BG_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_i->GetEntries())*h_i->Integral(0,-1)/h_i->GetEntries());

    if (entries_BG_2e2mu == 0.) continue;
      emulegend->AddEntry(h_i,reducedfile);  // add to legend only if not zero

    h_i->SetDirectory(0);
    gROOT->cd();
    delete d_i;
    }


  cout << "Yieldstring size after bgMC 2e2mu: " << yieldstring2e2mu.size() << endl;

// ---> QCD Background

    TH1F *h_2e2muQCD = new TH1F("h_2e2muQCD","4 e invariant mass QCD BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_2e2muQCD->SetFillColor(kTeal);

  for (Int_t i = 0; i < n2e2muQCD; i++){
    TFile *d_i2e2muQCD = new TFile(filename2e2muQCD[i],"READONLY"); 
    TTree *tree_d_i2e2muQCD = (TTree*) d_i2e2muQCD->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muQCD->SetName("Tree2e2muQCD[i]");

    TH1F *h_i2e2muQCD = new TH1F("m4l2e2muQCD[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2muQCD->TTree::Project("m4l2e2muQCD[i]","f_mass4l","f_weight");
    h_2e2muQCD->Add(h_i2e2muQCD);
    }

  hs_2e2mu->Add(h_2e2muQCD);

  double entries_QCD_2e2mu = h_2e2muQCD->Integral(0,-1);
  const char * app2e2muQCD = (std::string("QCD")).c_str();//, ") + std::to_string(entries_QCD_2e2mu) + std::string(" exp.")).c_str();

    yieldstring2e2mu.push_back("QCD");  // for yield table
    yields2e2mu.push_back(entries_QCD_2e2mu);
	if (entries_QCD_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_2e2muQCD->GetEntries())*h_2e2muQCD->Integral(0,-1)/h_2e2muQCD->GetEntries());

  if (entries_QCD_2e2mu != 0.)
    emulegend->AddEntry(h_2e2muQCD,app2e2muQCD);

// ---> SMZZ Background

    TH1F *h_2e2muSMZZ = new TH1F("h_2e2muSMZZ","4 e invariant mass SMZZ BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_2e2muSMZZ->SetFillColor(kOrange);

  for (Int_t i = 0; i < n2e2muSMZZ; i++){
    TFile *d_i2e2muSMZZ = new TFile(filename2e2muSMZZ[i],"READONLY"); 
    TTree *tree_d_i2e2muSMZZ = (TTree*) d_i2e2muSMZZ->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muSMZZ->SetName("Tree2e2muSMZZ[i]");

    TH1F *h_i2e2muSMZZ = new TH1F("m4l2e2muSMZZ[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2muSMZZ->TTree::Project("m4l2e2muSMZZ[i]","f_mass4l","f_weight");
    h_2e2muSMZZ->Add(h_i2e2muSMZZ);
    }

  hs_2e2mu->Add(h_2e2muSMZZ);

  double entries_SMZZ_2e2mu = h_2e2muSMZZ->Integral(0,-1);
  const char * app2e2muSMZZ = (std::string("SM ZZ")).c_str();//, ") + std::to_string(entries_SMZZ_2e2mu) + std::string(" exp.")).c_str();

    yieldstring2e2mu.push_back("SMZZ");  // for yield table
    yields2e2mu.push_back(entries_SMZZ_2e2mu);
	if (entries_SMZZ_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_2e2muSMZZ->GetEntries())*h_2e2muSMZZ->Integral(0,-1)/h_2e2muSMZZ->GetEntries());

  if (entries_SMZZ_2e2mu != 0.)
    emulegend->AddEntry(h_2e2muSMZZ,app2e2muSMZZ);

// ---> ST Background

    TH1F *h_2e2muST = new TH1F("h_2e2muST","4 e invariant mass ST BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_2e2muST->SetFillColor(kViolet);

  for (Int_t i = 0; i < n2e2muST; i++){
    TFile *d_i2e2muST = new TFile(filename2e2muST[i],"READONLY"); 
    TTree *tree_d_i2e2muST = (TTree*) d_i2e2muST->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muST->SetName("Tree2e2muST[i]");

    TH1F *h_i2e2muST = new TH1F("m4l2e2muST[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2muST->TTree::Project("m4l2e2muST[i]","f_mass4l","f_weight");
    h_2e2muST->Add(h_i2e2muST);
    }

  hs_2e2mu->Add(h_2e2muST);

  double entries_ST_2e2mu = h_2e2muST->Integral(0,-1);
  const char * app2e2muST = (std::string("ST")).c_str();//, ") + std::to_string(entries_ST_2e2mu) + std::string(" exp.")).c_str();

    yieldstring2e2mu.push_back("ST");  // for yield table
    yields2e2mu.push_back(entries_ST_2e2mu);
	if (entries_ST_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_2e2muST->GetEntries())*h_2e2muST->Integral(0,-1)/h_2e2muST->GetEntries());

  if (entries_ST_2e2mu != 0.)
    emulegend->AddEntry(h_2e2muST,app2e2muST);

// ---> WH Background

    TH1F *h_2e2muWpWm = new TH1F("h_2e2muWpWm","4 e invariant mass WpWm BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_2e2muWpWm->SetFillColor(kSpring+10);

  for (Int_t i = 0; i < n2e2muWpWm; i++){
    TFile *d_i2e2muWpWm = new TFile(filename2e2muWpWm[i],"READONLY"); 
    TTree *tree_d_i2e2muWpWm = (TTree*) d_i2e2muWpWm->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muWpWm->SetName("Tree2e2muWpWm[i]");

    TH1F *h_i2e2muWpWm = new TH1F("m4l2e2muWpWm[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2muWpWm->TTree::Project("m4l2e2muWpWm[i]","f_mass4l","f_weight");
    h_2e2muWpWm->Add(h_i2e2muWpWm);
    }

  hs_2e2mu->Add(h_2e2muWpWm);

  double entries_WpWm_2e2mu = h_2e2muWpWm->Integral(0,-1);
  const char * app2e2muWpWm = (std::string("WH")).c_str();//, ") + std::to_string(entries_WpWm_2e2mu) + std::string(" exp.")).c_str();

    yieldstring2e2mu.push_back("WpWm");  // for yield table
    yields2e2mu.push_back(entries_WpWm_2e2mu);
	if (entries_WpWm_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_2e2muWpWm->GetEntries())*h_2e2muWpWm->Integral(0,-1)/h_2e2muWpWm->GetEntries());

  if (entries_WpWm_2e2mu != 0.)
    emulegend->AddEntry(h_2e2muWpWm,app2e2muWpWm);

// ---> ZH Background

    TH1F *h_2e2muZH = new TH1F("h_2e2muZH","4 e invariant mass ZH BG;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_2e2muZH->SetFillColor(kPink+10);

  for (Int_t i = 0; i < n2e2muZH; i++){
    TFile *d_i2e2muZH = new TFile(filename2e2muZH[i],"READONLY"); 
    TTree *tree_d_i2e2muZH = (TTree*) d_i2e2muZH->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muZH->SetName("Tree2e2muZH[i]");

    TH1F *h_i2e2muZH = new TH1F("m4l2e2muZH[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2muZH->TTree::Project("m4l2e2muZH[i]","f_mass4l","f_weight");
    h_2e2muZH->Add(h_i2e2muZH);
    }

  hs_2e2mu->Add(h_2e2muZH);

  double entries_ZH_2e2mu = h_2e2muZH->Integral(0,-1);
  const char * app2e2muZH = (std::string("ZH")).c_str();//, ") + std::to_string(entries_ZH_2e2mu) + std::string(" exp.")).c_str();

    yieldstring2e2mu.push_back("ZH");  // for yield table
    yields2e2mu.push_back(entries_ZH_2e2mu);
	if (entries_ZH_2e2mu == 0)
	    eryields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    eryields2e2mu.push_back(sqrt(h_2e2muZH->GetEntries())*h_2e2muZH->Integral(0,-1)/h_2e2muZH->GetEntries());

  if (entries_ZH_2e2mu != 0.)
    emulegend->AddEntry(h_2e2muZH,app2e2muZH);

// ====================== Plot signal MC ===========================
 
// ---> 4 mu channel
  vector<TH1F*> vSignal4mu;

  for (Int_t i = 0; i < n4muS; i++){
    TFile *d_i4muS = new TFile(filename4muS[i],"READONLY"); 
    TTree *tree_d_i4muS = (TTree*) d_i4muS->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4muS->SetName("Tree2[i]");

    TH1F *h_i4muS = new TH1F("m4muS[i]","Signal invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_i4muS->SetLineColor(i+2); 
    h_i4muS->SetLineWidth(2); 
    h_i4muS->SetMaximum(10);
    h_i4muS->SetMinimum(0.0000001);

    tree_d_i4muS->TTree::Project("m4muS[i]","f_mass4l","f_weight");
    vSignal4mu.push_back(h_i4muS);

    std::string str1 = filename4muS[i];
    std::string str2 = str1.substr(29);
    std::string::size_type const p(str2.find_last_of('_'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_S_mu = h_i4muS->Integral(0,-1);
   /* std::string appendix = std::string(", ") + std::to_string(entries_S_mu) + std::string(" exp.");
    str3.append(appendix);*/

    const char * reducedfile = str3.c_str();

    Syieldstring4mu.push_back(yieldname);  // for yield table
    Syields4mu.push_back(entries_S_mu);
	if (entries_S_mu == 0)
	    erSyields4mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    erSyields4mu.push_back(sqrt(h_i4muS->GetEntries())*h_i4muS->Integral(0,-1)/h_i4muS->GetEntries());

   
    muSlegend->AddEntry(h_i4muS,reducedfile);

    h_i4muS->SetDirectory(0); // To close open ROOT files
    gROOT->cd();
    delete d_i4muS;

    }

  int vSignal4muSize = vSignal4mu.size();

// ---> 4 e channel
  vector<TH1F*> vSignal4e;

  for (Int_t i = 0; i < n4eS; i++){
    TFile *d_i4eS = new TFile(filename4eS[i],"READONLY"); 
    TTree *tree_d_i4eS = (TTree*) d_i4eS->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4eS->SetName("Tree2[i]");

    TH1F *h_i4eS = new TH1F("m4eS[i]","Signal invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_i4eS->SetLineColor(i+2); 
    h_i4eS->SetLineWidth(2); 
    h_i4eS->SetMaximum(10);
    h_i4eS->SetMinimum(0.0000001);

    tree_d_i4eS->TTree::Project("m4eS[i]","f_mass4l","f_weight");
    vSignal4e.push_back(h_i4eS);

    std::string str1 = filename4eS[i];
    std::string str2 = str1.substr(28);
    std::string::size_type const p(str2.find_last_of('_'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_S_e = h_i4eS->Integral(0,-1);

   /* std::string appendix = std::string(", ") + std::to_string(entries_S_e) + std::string(" exp.");
    str3.append(appendix);*/

    const char * reducedfile = str3.c_str();

    Syieldstring4e.push_back(yieldname);  // for yield table
    Syields4e.push_back(entries_S_e);
	if (entries_S_e == 0)
	    erSyields4e.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    erSyields4e.push_back(sqrt(h_i4eS->GetEntries())*h_i4eS->Integral(0,-1)/h_i4eS->GetEntries());
   
    eSlegend->AddEntry(h_i4eS,reducedfile);

    h_i4eS->SetDirectory(0); // To close open ROOT files
    gROOT->cd();
    delete d_i4eS;

    }

  int vSignal4eSize = vSignal4e.size();

// ---> 2e2mu channel
  vector<TH1F*> vSignal2e2mu;

  for (Int_t i = 0; i < n2e2muS; i++){
    TFile *d_i2e2muS = new TFile(filename2e2muS[i],"READONLY"); 
    TTree *tree_d_i2e2muS = (TTree*) d_i2e2muS->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2muS->SetName("Tree2[i]");

    TH1F *h_i2e2muS = new TH1F("m2e2muS[i]","Signal invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_i2e2muS->SetLineColor(i+2); 
    h_i2e2muS->SetLineWidth(2); 
    h_i2e2muS->SetMaximum(10);
    h_i2e2muS->SetMinimum(0.0000001);

    tree_d_i2e2muS->TTree::Project("m2e2muS[i]","f_mass4l","f_weight");
    vSignal2e2mu.push_back(h_i2e2muS);

    std::string str1 = filename2e2muS[i];
    std::string str2 = str1.substr(31);
    std::string::size_type const p(str2.find_last_of('_'));
    std::string str3 = str2.substr(0, p);
    std::string yieldname = str3;   // for yield table

    double entries_S_2e2mu = h_i2e2muS->Integral(0,-1);
   /* std::string appendix = std::string(", ") + std::to_string(entries_S_2e2mu) + std::string(" exp.");
    str3.append(appendix);*/

    const char * reducedfile = str3.c_str();

    Syieldstring2e2mu.push_back(yieldname);  // for yield table
    Syields2e2mu.push_back(entries_S_2e2mu);
	if (entries_S_2e2mu == 0)
	    erSyields2e2mu.push_back(0);     // to avoid dividing by zero when entries = 0
	else
	    erSyields2e2mu.push_back(sqrt(h_i2e2muS->GetEntries())*h_i2e2muS->Integral(0,-1)/h_i2e2muS->GetEntries());
   
    emuSlegend->AddEntry(h_i2e2muS,reducedfile);

    h_i2e2muS->SetDirectory(0);  // To close ROOT files
    gROOT->cd();
    delete d_i2e2muS;

    }

  int vSignal2e2muSize = vSignal2e2mu.size();

// ============= SUM DATA AND OVERLAY ON BG HISTOGRAM ==============

// ------------ Create data histos -------------------------

    TH1F *h_data4mu = new TH1F("h_data4mu","4 muon invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_data4mu->SetLineWidth(1);
    h_data4mu->SetMarkerStyle(20); 
    h_data4mu->SetMarkerColor(1); 

    TH1F *h_data4e = new TH1F("h_data4e","4 electron invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_data4e->SetLineWidth(1);
    h_data4e->SetMarkerStyle(20); 
    h_data4e->SetMarkerColor(1); 

    TH1F *h_data2e2mu = new TH1F("h_data2e2mu","2e2mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);
    h_data2e2mu->SetLineWidth(1);
    h_data2e2mu->SetMarkerStyle(20); 
    h_data2e2mu->SetMarkerColor(1); 

// ----------- Loop over files and fill histo ----------------
// ---> 4 mu channel
  for (Int_t i = 0; i < n4mu2; i++){
    TFile *d_i4mu2 = new TFile(filename4mu2[i],"READONLY"); 
    TTree *tree_d_i4mu2 = (TTree*) d_i4mu2->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4mu2->SetName("Tree2[i]");

    TH1F *h_i4mu2 = new TH1F("m4mu2[i]","4 mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4mu2->TTree::Project("m4mu2[i]","f_mass4l");
    h_data4mu->Add(h_i4mu2);

    h_i4mu2->SetDirectory(0);
    gROOT->cd();
    delete d_i4mu2;
    }

  int entries_data_mu = h_data4mu->GetEntries();
  const char * app4muD = (std::string("Data, ") + std::to_string(entries_data_mu) + std::string(" entries")).c_str();
  mulegend->AddEntry(h_data4mu,app4muD);


// ---> 4 e channel
  for (Int_t i = 0; i < n4e2; i++){
    TFile *d_i4e2 = new TFile(filename4e2[i],"READONLY"); 
    TTree *tree_d_i4e2 = (TTree*) d_i4e2->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i4e2->SetName("Tree2[i]");

    TH1F *h_i4e2 = new TH1F("m4e2[i]","4 e invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i4e2->TTree::Project("m4e2[i]","f_mass4l");
    h_data4e->Add(h_i4e2);

    }

  int entries_data_e = h_data4e->GetEntries();
  const char * app4eD = (std::string("Data, ") + std::to_string(entries_data_e) + std::string(" entries")).c_str();
  elegend->AddEntry(h_data4e,app4eD);

// ---> 2 e 2 mu channel

  for (Int_t i = 0; i < n2e2mu2; i++){
    TFile *d_i2e2mu2 = new TFile(filename2e2mu2[i],"READONLY"); 
    TTree *tree_d_i2e2mu2 = (TTree*) d_i2e2mu2->Get("HZZ4LeptonsAnalysisReduced");
    tree_d_i2e2mu2->SetName("Tree2[i]");

    TH1F *h_i2e2mu2 = new TH1F("m2e2mu2[i]","2e2mu invariant mass;Inv.mass [GeV];# of entries",200,70.,2070.);

    tree_d_i2e2mu2->TTree::Project("m2e2mu2[i]","f_mass4l");
    h_data2e2mu->Add(h_i2e2mu2);

    }

  int entries_data_2e2mu = h_data2e2mu->GetEntries();
  const char * app2e2muD = (std::string("Data, ") + std::to_string(entries_data_2e2mu) + std::string(" entries")).c_str();

  emulegend->AddEntry(h_data2e2mu,app2e2muD);

// ======================== Data/BG_MC ratio ===============================

// Sum BG MC histos

  TH1F *h_sumBG4mu = new TH1F("h_sumBG4mu","4 muon sum MC;[GeV];# of entries",200,70.,2070.);
  h_sumBG4mu->SetFillColor(15);
  h_sumBG4mu->Add(h_nonQCD4mu);
  h_sumBG4mu->Add(h_4muQCD);
  h_sumBG4mu->Add(h_4muSMZZ);
  h_sumBG4mu->Add(h_4muST);
  h_sumBG4mu->Add(h_4muWpWm);
  h_sumBG4mu->Add(h_4muZH);

  TH1F *h_sumBG4e = new TH1F("h_sumBG4e","4 e sum MC;[GeV];# of entries",200,70.,2070.);
  h_sumBG4e->SetFillColor(15);
  h_sumBG4e->Add(h_nonQCD4e);
  h_sumBG4e->Add(h_4eQCD);
  h_sumBG4e->Add(h_4eSMZZ);
  h_sumBG4e->Add(h_4eST);
  h_sumBG4e->Add(h_4eWpWm);
  h_sumBG4e->Add(h_4eZH);

  TH1F *h_sumBG2e2mu = new TH1F("h_sumBG2e2mu","2e2mu sum MC;[GeV];# of entries",200,70.,2070.);
  h_sumBG2e2mu->SetFillColor(15);
  h_sumBG2e2mu->Add(h_nonQCD2e2mu);
  h_sumBG2e2mu->Add(h_2e2muQCD);
  h_sumBG2e2mu->Add(h_2e2muSMZZ);
  h_sumBG2e2mu->Add(h_2e2muST);
  h_sumBG2e2mu->Add(h_2e2muWpWm);
  h_sumBG2e2mu->Add(h_2e2muZH);


// ============================== DRAW ===============================

// ---->> Muons
  TCanvas *cmu = new TCanvas();
  TPad *pad1mu = new TPad("pad1mu", "The pad 0.8 of the height",0.0,0.2,1.0,1.0,0);
  TPad *pad2mu = new TPad("pad2mu", "The pad 0.2 of the height",0.0,0.0,1.0,0.2,0);

  pad1mu->SetBottomMargin(0.1);
  pad2mu->SetBottomMargin(0.2);
  pad2mu->SetTopMargin(0.03);

  pad1mu->Draw();
  pad2mu->Draw();

  pad1mu->cd()->SetLogy();
 // pad1mu->cd()->SetLogx(); pad2mu->cd()->SetLogx(); logmu = true;  // <--------------- Uncomment to get logarithmic x scale, comment out to get linear

  pad1mu->cd();
  hs_mu->Draw("hist");
  for (int j=0; j<8; ++j){
    vSignal4mu[j]->Draw("same");
  }
  h_data4mu->Draw("samePE1"); 
  mulegend->SetTextSize(0.02);
  muSlegend->SetTextSize(0.02);
  mulegend->SetBorderSize(0); 
  muSlegend->SetBorderSize(0);

  mulegend->Draw();
  muSlegend->Draw();
  hs_mu->GetXaxis()->SetTitle("m_{4l} [GeV]");          //<------------ CHANGE AXIS TITLES HERE
  hs_mu->GetYaxis()->SetTitle("Events / 10 GeV");     // ...AND HERE
  gPad->SetTickx();
  gPad->SetTicky();

  pad2mu->cd();  // Data over MC histo
  TH1F *h_data4muClone = (TH1F*)h_data4mu->Clone("h_data4muClone");
  h_data4muClone->Divide(h_sumBG4mu);
  h_data4muClone->Draw();
  gPad->Update();
  cmu->Update();

  h_data4muClone->GetYaxis()->SetTitle("Data/MC");
  h_data4muClone->GetYaxis()->SetLabelSize(0.1);
  h_data4muClone->GetYaxis()->SetTitleSize(0.15);
  pad2mu->Update();
  h_data4muClone->GetYaxis()->SetTitleOffset(0.25);

  h_data4muClone->GetXaxis()->SetTitle("");
  h_data4muClone->GetXaxis()->SetLabelSize(0.1);  

  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGrid();
  
  pad2mu->Update();
  h_data4muClone->SetTitle("");
  h_data4muClone->Draw();

  pad2mu->Modified();
  cmu->Update();


// ---->> Electrons 
  TCanvas *ce = new TCanvas();
  TPad *pad1e = new TPad("pad1e", "The pad 0.8 of the height",0.0,0.2,1.0,1.0,0);
  TPad *pad2e = new TPad("pad2e", "The pad 0.2 of the height",0.0,0.0,1.0,0.2,0);

  pad1e->SetBottomMargin(0.1);
  pad2e->SetBottomMargin(0.2);
  pad2e->SetTopMargin(0.03);

  pad1e->Draw();
  pad2e->Draw();

  pad1e->cd()->SetLogy();
 // pad1e->cd()->SetLogx(); pad2e->cd()->SetLogx(); loge = true;  // <--------------- Uncomment to get logarithmic x scale, comment out to get linear

  pad1e->cd();
  hs_e->Draw("hist");
  for (int j=0; j<8; ++j){
    vSignal4e[j]->Draw("same");
  }
  h_data4e->Draw("samePE1"); 
  elegend->SetTextSize(0.02);
  eSlegend->SetTextSize(0.02);
  elegend->SetBorderSize(0); 
  eSlegend->SetBorderSize(0);

  elegend->Draw();
  eSlegend->Draw();
  hs_e->GetXaxis()->SetTitle("m_{4l} [GeV]");          //<------------ CHANGE AXIS TITLES HERE
  hs_e->GetYaxis()->SetTitle("Events / 10 GeV");     // ...AND HERE
  gPad->SetTickx();
  gPad->SetTicky();

  pad2e->cd();  // Data over MC histo
  TH1F *h_data4eClone = (TH1F*)h_data4e->Clone("h_data4eClone");
  h_data4eClone->Divide(h_sumBG4e);
  h_data4eClone->Draw();
  gPad->Update();
  ce->Update();

  h_data4eClone->GetYaxis()->SetTitle("Data/MC");
  h_data4eClone->GetYaxis()->SetLabelSize(0.1);
  h_data4eClone->GetYaxis()->SetTitleSize(0.15);
  pad2e->Update();
  h_data4eClone->GetYaxis()->SetTitleOffset(0.25);

  h_data4eClone->GetXaxis()->SetTitle("");
  h_data4eClone->GetXaxis()->SetLabelSize(0.1);

  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGrid();
  
  pad2e->Update();
  h_data4eClone->SetTitle("");
  gStyle->SetOptStat(0);
  h_data4eClone->Draw();

  pad2e->Modified();
  ce->Update();


// ---->> 2e2mu
  TCanvas *cemu = new TCanvas();
  TPad *pad1emu = new TPad("pad1emu", "The pad 0.8 of the height",0.0,0.2,1.0,1.0,0);
  TPad *pad2emu = new TPad("pad2emu", "The pad 0.2 of the height",0.0,0.0,1.0,0.2,0);

  pad1emu->SetBottomMargin(0.1);
  pad2emu->SetBottomMargin(0.2);
  pad2emu->SetTopMargin(0.03);

  pad1emu->Draw();
  pad2emu->Draw();

  pad1emu->cd()->SetLogy();
  //pad1emu->cd()->SetLogx(); pad2emu->cd()->SetLogx(); log2e2mu = true;  // <--------------- Uncomment to get logarithmic x scale, comment out to get linear

  pad1emu->cd();
  hs_2e2mu->Draw("hist");
  for (int j=0; j<8; ++j){
    vSignal2e2mu[j]->Draw("same");
  }
  h_data2e2mu->Draw("samePE1"); 
  emulegend->SetTextSize(0.02);
  emuSlegend->SetTextSize(0.02);
  emulegend->SetBorderSize(0); 
  emuSlegend->SetBorderSize(0);

  emulegend->Draw();
  emuSlegend->Draw();
  hs_2e2mu->GetXaxis()->SetTitle("m_{4l} [GeV]");          //<------------ CHANGE AXIS TITLES HERE
  hs_2e2mu->GetYaxis()->SetTitle("Events / 10 GeV");     // ...AND HERE
  gPad->SetTickx();
  gPad->SetTicky();

  pad2emu->cd();  // Data over MC histo
  TH1F *h_data2e2muClone = (TH1F*)h_data2e2mu->Clone("h_data2e2muClone");
  h_data2e2muClone->Divide(h_sumBG2e2mu);
  h_data2e2muClone->Draw();
  gPad->Update();
  cemu->Update();

  h_data2e2muClone->GetYaxis()->SetTitle("Data/MC");
  h_data2e2muClone->GetYaxis()->SetLabelSize(0.1);
  h_data2e2muClone->GetYaxis()->SetTitleSize(0.15);
  pad2emu->Update();
  h_data2e2muClone->GetYaxis()->SetTitleOffset(0.25);

  h_data2e2muClone->GetXaxis()->SetTitle("");
  h_data2e2muClone->GetXaxis()->SetLabelSize(0.1);  

  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGrid();
  
  pad2emu->Update();
  h_data2e2muClone->SetTitle("");
  gStyle->SetOptStat(0);
  h_data2e2muClone->Draw();

  pad2emu->Modified();
  cemu->Update();


// ----------------- Save to .eps ---------------------------------------

  if (logmu == true)
    cmu->Print("plots/f_mass4l_4mu_loglog.eps");
  else
    cmu->Print("plots/f_mass4l_4mu_semilog.eps");

  if (loge == true)
    ce->Print("plots/f_mass4l_4e_loglog.eps");
  else
    ce->Print("plots/f_mass4l_4e_semilog.eps");

  if (log2e2mu == true)
    cemu->Print("plots/f_mass4l_2e2mu_loglog.eps");
  else
    cemu->Print("plots/f_mass4l_2e2mu_semilog.eps");


// ================= CREATE YIELD TABLE ===================================

  Char_t tableOUT[500];
  sprintf(tableOUT,"Yieldtable_monoHiggs4l_3aug.tex");
  ofstream output;
  output.open(tableOUT);

  output << "\\documentclass[a4paper,10pt]{article}" << endl;
  output << "\\usepackage[landscape]{geometry}" << endl;
  output << "\\usepackage[pdftex]{graphicx}" << endl;
  output << "\\usepackage{caption}" << endl;
  output << "\\usepackage{amsmath}" << endl;
  output << "\\usepackage{multirow}" << endl;
  output << " " << endl;    
  output << "\\begin{document}" << endl;
  output << " " << endl;
  output << "\\begin{table}" << endl;
  output << "\\caption{The number of estimated background and signal events and number of observed candidates (using histos3aug), after final selection, in the full measurement range 70 $< \\, m_{4l} \\, <$ 1000 GeV.}" << endl;
  output << "\\begin{center}" << endl;
  output << "\\label{tab:EventYields}" << endl;
  output << "\\begin{tabular}{|l|c|c|c|c|}" << endl;
  output << "\\hline" << endl;
  output << "{\\textbf{Channel}} & {\\textbf{$4\\mu$}} & {\\textbf{$4e$}} & {\\textbf{$2e2\\mu$}} & {\\textbf{$4l$}}\\\\ " << endl;
  output << "\\hline \\hline" << endl;

  // BG
  for (int i=0; i<yieldstring4mu.size(); i++){
    if (yieldstring4mu[i] == std::string("VBF_HToZZTo4L")){  // fix underscore interpretation in LaTeX
	yieldstring4mu[i] = std::string("VBF\\_HToZZTo4L");  
	yieldstring4e[i] = std::string("VBF\\_HToZZTo4L");
	yieldstring2e2mu[i] = std::string("VBF\\_HToZZTo4L");
    }
    if (yieldstring4mu[i] == std::string("ttH_HToZZ_4L")){
	yieldstring4mu[i] = std::string("ttH\\_HToZZ\\_4L");
	yieldstring4e[i] = std::string("ttH\\_HToZZ\\_4L");
	yieldstring2e2mu[i] = std::string("ttH\\_HToZZ\\_4L");
    }
    if (yieldstring4mu[i] == std::string("WpWm")){
	yieldstring4mu[i] = std::string("WH");
	yieldstring4e[i] = std::string("WH");
	yieldstring2e2mu[i] = std::string("WH");
    }
	//if (yields4mu[i]==0 && yields4e[i]==0 && yields2e2mu[i]==0) continue;  // Remove lines where all numbers are zero - not used yet so haven't put this on all lines that would need it
  // Print the "s" background
	sprintf(outputstring,"%s & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f  & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",  
	  yieldstring4mu[i].c_str(),
	  yields4mu[i], eryields4mu[i],   
	  yields4e[i], eryields4e[i],
	  yields2e2mu[i], eryields2e2mu[i],
	  (yields4mu[i]+yields4e[i]+yields2e2mu[i]),sqrt(eryields4mu[i]*eryields4mu[i]+eryields4e[i]*eryields4e[i]+eryields2e2mu[i]*eryields2e2mu[i]));
	//cout << outputstring << endl;  // Print table output to terminal for immediate inspection
	output << outputstring << endl;
	output << "\\hline" << endl;
	
  }
  output << "\\hline" << endl;

  // Sum BG
  float sumBG4mu = 0;
  float sumBG4e = 0;
  float sumBG2e2mu = 0;

  for(int i=0; i<yieldstring4mu.size(); i++){
    sumBG4mu += yields4mu[i];
  }

  for(int i=0; i<yieldstring4e.size(); i++){
    sumBG4e += yields4e[i];
  }

  for(int i=0; i<yieldstring2e2mu.size(); i++){
    sumBG2e2mu += yields2e2mu[i];
  }

  // Sum BG errors (quadrature)
  float sumBG4muer = 0;
  float sumBG4eer = 0;
  float sumBG2e2muer = 0;

  for(int i=0; i<yieldstring4mu.size(); i++){
    sumBG4muer += eryields4mu[i]*eryields4mu[i];
  }
  sumBG4muer = sqrt(sumBG4muer);

  for(int i=0; i<yieldstring4e.size(); i++){
    sumBG4eer += eryields4e[i]*eryields4e[i];
  }
  sumBG4eer = sqrt(sumBG4eer);

  for(int i=0; i<yieldstring2e2mu.size(); i++){
    sumBG2e2muer += eryields2e2mu[i]*eryields2e2mu[i];
  }
  sumBG2e2muer = sqrt(sumBG2e2muer);

  sprintf(outputsumBG,"{\\textbf{Total background}} & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f  & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
	sumBG4mu, sumBG4muer, 
	sumBG4e, sumBG4eer, 
	sumBG2e2mu, sumBG2e2muer,
	(sumBG4mu+sumBG4e+sumBG2e2mu),sqrt(sumBG4muer*sumBG4muer+sumBG4eer*sumBG4eer+sumBG2e2muer*sumBG2e2muer));
  //cout << outputsumBG << endl; 
  output << outputsumBG << endl;

  output << "\\hline \\hline" << endl;
 
  // Signal
  for (int i=0; i<Syieldstring4mu.size(); i++){
	//if (yields4mu[i]==0 && yields4e[i]==0 && yields2e2mu[i]==0) continue;  // Remove lines where all numbers are zero - not used yet so haven't put this on all lines that would need it
  // Print the "s" background
	sprintf(outputstringS,"%s & %5.2e $\\pm$ %5.2e & %5.2e $\\pm$ %5.2e  & %5.2e $\\pm$ %5.2e & %5.2e $\\pm$ %5.2e \\\\",  
	  Syieldstring4mu[i].c_str(),
	  Syields4mu[i], erSyields4mu[i], 
	  Syields4e[i], erSyields4e[i],
	  Syields2e2mu[i], erSyields2e2mu[i],
	  (Syields4mu[i]+Syields4e[i]+Syields2e2mu[i]),sqrt(erSyields4mu[i]*erSyields4mu[i]+erSyields4e[i]*erSyields4e[i]+erSyields2e2mu[i]*erSyields2e2mu[i]));
	//cout << outputstringS << endl;  // Print table output to terminal for immediate inspection
	output << outputstringS << endl;
	output << "\\hline" << endl;
	
  }
  output << "\\hline" << endl;

  // Data
  sprintf(outputData,"{\\textbf{Observed}} & %d & %d & %d & %d \\\\",
	entries_data_mu, entries_data_e, entries_data_2e2mu, (entries_data_mu+entries_data_e+entries_data_2e2mu));
 // cout << outputData << endl; 
  output << outputData << endl;
  output << "\\hline" << endl;

  output << "\\end{tabular}" << endl;
  output << "\\end{center}" << endl;
  output << "\\end{table}" << endl;
  output << "%============" << endl;
  
  output << " " <<endl;
  output << "\\end{document}" << endl;

  output.close();

  if (yieldstring4mu != yieldstring4e)    // Check that the BG is in the same order for all channels -- otherwise the numbers will be wrong.
    cout << "Warning! yieldstring4mu not equal to yieldstring4e! The yield table will be messed up." << endl;
  if (yieldstring2e2mu != yieldstring4e)
    cout << "Warning! yieldstring2e2mu not equal to yieldstring4e! The yield table will be messed up." << endl;
  if (yieldstring4mu == yieldstring4e)
    cout << "All is good, yieldstring4mu is equal to yieldstring4e." << endl;
  if (yieldstring2e2mu == yieldstring4e)
    cout << "All is good, yieldstring2e2mu is equal to yieldstring4e." << endl;

gSystem->Exec("ls");
gSystem->Exec("pdflatex Yieldtable_monoHiggs4l_3aug.tex");  // Create pdf file with the table


}








