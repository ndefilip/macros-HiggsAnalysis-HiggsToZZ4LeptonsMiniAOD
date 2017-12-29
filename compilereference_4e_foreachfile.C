#if !defined(__CINT__) || defined(__MAKECINT__)

#include "HZZ4LeptonsAnalysis_4e.h"
#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
//#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <TSystem.h>
#include <TH2.h>
#include "TChain.h"
#include <stdlib.h>

#endif

using namespace std;


int main (int argc, char ** argv){

  cout << "Ciao" << endl;
  string site=argv[7];
  cout << site << " configuration" <<endl;
  
  string dataconf=argv[8];
  

  if (dataconf.find("2012_postICHEP")<15) dataconf="2012";
  cout << dataconf << " data configuration" <<endl;
  
  string mcconf=argv[9];
  cout << mcconf << " mc configuration" <<endl;

  
  ifstream fsig;
  fsig.open(argv[1]);

  const int signlines = atoi(argv[2]);

  string sigsamples[signlines];
  float signinput[signlines];
  float signhlt[signlines];
  float signskim[signlines];
  float sigxsection[signlines];
  
  // Signal
  cout << "Signal samples" << endl;
  for(int i=0;i<signlines;i++){
    fsig >> sigsamples[i] >> signinput[i] >> signhlt[i] >> signskim[i] >> sigxsection[i];
    //cout << "Sample=" << sigsamples[i] << " Ninput=" << signinput[i] << " NHLT=" << signhlt[i] << " NSkim=" << signskim[i] << " Xsection(pb)=" << sigxsection[i] << endl;
  }


  // bkg
  ifstream fbkg;
  fbkg.open(argv[3]);

  const int nlines = atoi(argv[4]);

  string bkgsamples[nlines];
  float bkgninput[nlines];
  float bkgnhlt[nlines];
  float bkgnskim[nlines];
  float bkgxsection[nlines];
  
  cout << "Bkg samples" << endl;

  for(int i=0;i<nlines;i++){
    fbkg >> bkgsamples[i] >> bkgninput[i] >> bkgnhlt[i] >> bkgnskim[i] >> bkgxsection[i];
    //cout << "Sample=" << bkgsamples[i] << " Ninput=" << bkgninput[i] << " NHLT=" << bkgnhlt[i] << " NSkim=" << bkgnskim[i] << " Xsection(pb)=" << bkgxsection[i] << endl;
  }


  // data
  ifstream fdata;
  fdata.open(argv[5]);
  
  cout << "Data samples" << endl;

  const int ndata = atoi(argv[6]);
  string datasamples[ndata];
  
  for(int i=0;i<ndata;i++){
    fdata >> datasamples[i];
    cout << "Sample=" << datasamples[i] << endl;
  }


  // 

  //float lumifb=1127./1000.;
  float lumipb=4710.;

  // running on each signal and all bkg
  for(int i=0;i<signlines;i++){

    string name= "roottree_leptons_"+sigsamples[i]+".root";
    TString dirInput="/lustre/cms/store/user/ndefilip/Spring11_EScale42X_LP11_merged";    
    TString sigFile=name;
    sigFile=sigFile.ReplaceAll("-4e","");

    Char_t nome[300];
    sprintf(nome,"%s/%s",dirInput.Data(),sigFile.Data());

    TString mhstring=sigFile.ReplaceAll("GluGluToHToZZTo4L_M-","");
    mhstring=mhstring.ReplaceAll("_7TeV-powheg-pythia6","");
    mhstring=mhstring.ReplaceAll("roottree_leptons_","");
    mhstring=mhstring.ReplaceAll(".root","");
  
    Double_t mH=0.;
    mH=atof(mhstring.Data());
    cout << "mH= " << mH << endl;
    
    //float weight=(1.16395491972004928/7254.)*191./1000.;
    float weight= lumipb*(sigxsection[i]*signskim[i]/signinput[i])/signskim[i];
    cout << "Weight is= " << weight << endl;

    bool runonsig=false;

    if (runonsig==true){
      TFile *file3;
      file3 = TFile::Open(nome);
      cout << "Read file with name: " << nome << endl;
      TTree *tree3 = (TTree*)file3->Get("HZZ4LeptonsAnalysis");
      HZZ4LeptonsAnalysis make3(tree3,weight,"2011","Fall11");
      
      sprintf(nome,"histos4e/output_%s.root",sigsamples[i].c_str());
      make3.Loop(nome);
      
      cout << "Create file with name: " << nome << endl;
      delete tree3;
      file3 -> Close();
    }

    // data
    bool runondata=true;
    
    if (runondata==true){
      
      bool itera=false;
      
      if (mH<=160.){
	if (i==0) itera=true;  
      }
      else {
	itera=true;
      }

      for(int i=0;i<ndata && itera==true;i++){

	string name= datasamples[i];

	//cout << "Input directory is:" << dirInput<< endl;
	cout << "Name is " << name << endl;
	TString dataFile=name;

	Char_t nome[300];
	sprintf(nome,"%s",dataFile.Data());
	
	
	TFile *file3 = new TFile(nome);
	cout << "Read file with name: " << nome << endl;
	TTree *tree3 = (TTree*)file3->Get("HZZ4LeptonsAnalysis");
	HZZ4LeptonsAnalysis make3(tree3,1.,"2011","Fall11");
	
	//sprintf(nome,"histos4e/output_%s_H%d.root",datasamples[i].c_str(),int(mH));
	//char *path=NULL;
	//size_t size=300;
	//path=getcwd(path,size);
	
	//sprintf(nome,"%s/output_%s.root",path,datasamples[i].c_str());
	sprintf(nome,"output.root");
	make3.Loop(nome);
	
	cout << "Create file with name: " << nome << endl;
	delete tree3;
	file3 -> Close();

      }

    }


    // Run on bkg
    bool runonbkg=false;
   
    if (runonbkg==true){

      bool itera=false;
      
      if (mH<=160.){
	if (i==0) itera=true;  
      }
      else {
	itera=true;
      }
      
      for(int i=0;i<nlines && itera==true;i++){
	
	string name= "roottree_leptons_"+bkgsamples[i]+".root";
	//TString dirInput="/lustre/cms/store/user/ndefilip/Summer11_42X_merged";   

	TString dirInput;

	if ( name.find("Mu_")<18 || name.find("EG_")<18  || (name.find("Electron_")<18 && name.find("2010B")<85 ) ) {
          dirInput="/lustre/cms/store/user/ndefilip/Data2010_merged";     
        }
        else if ( name.find("2011")<38 ) {
          dirInput="/lustre/cms/store/user/ndefilip/Data2011_16Jan2012_merged";
        }
	else if ( name.find("2012A")<38 || name.find("2012B")<38 || name.find("2012C")<38 || name.find("2012D")<38 ){
          dirInput="/lustre/cms/store/user/defilip/Data2012_Moriond_step_analysis_merged";        
        }

        // cout << name.find("DYJetsToLL") << endl;
//         if ( name.find("DYJetsToLL")<50 ) {
//           dirInput="/lustre/cms/store/user/ndefilip/Summer11_42X_merged";
//         }
//         else {
//           dirInput="/lustre/cms/store/user/ndefilip/Spring11_EScale42X_LP11_merged";
//         }

 
	TString bkgFile=name;
	
	Char_t nome[300];
	//sprintf(nome,"%s/%s",dirInput.Data(),bkgFile.Data());
	sprintf(nome,"%s",bkgsamples[i].c_str());
	
	//float bkgweight= lumipb*(bkgxsection[i]*bkgnskim[i]/bkgninput[i])/bkgnskim[i];
	//cout << "Bkg Weight is= " << bkgweight << endl;

	
	TFile *file3 = new TFile(nome);
	cout << "Read file with name: " << nome << endl;
	TTree *tree3 = (TTree*)file3->Get("HZZ4LeptonsAnalysis");
	HZZ4LeptonsAnalysis make3(tree3,1.,dataconf,mcconf);
		
	char *path=NULL;
	size_t size;
	path=getcwd(path,size);
	
	//cout << "This the path " << path << endl;
	//sprintf(nome,"%s/output_%s.root",path,datasamples[i].c_str());
	// make3.Loop(nome);

	// TString out = bkgsamples[i];
// 	TString datasetName=out.ReplaceAll(".root","");
// 	TString alpha=datasetName.ReplaceAll(path,"");
//  	cout << "Alpha is= " << alpha.Data() << endl;
// 	//sprintf(nome,"histos4e/output_%s_H%d.root",bkgsamples[i].c_str(),int(mH));
        sprintf(nome,"output.root");

// 	sprintf(nome,"histos4e_DoubleMu_Run2012B_PromptReco_Jun22_190456-196509_noLowPU/output_%s_H%d.root",alpha.Data(),int(mH));
 	make3.Loop(nome);
	
	cout << "Create file with name: " << nome << endl;
	delete tree3;
	file3 -> Close();
	
      }

    }

    
    
  }
  
  return 0; 

}

