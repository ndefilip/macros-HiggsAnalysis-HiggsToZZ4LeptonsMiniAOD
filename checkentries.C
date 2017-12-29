#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <string>
#include <iostream>
#include <TSystem.h>
#include <TH2.h>
#include "TChain.h"
#include <stdlib.h>
#include <TDCacheFile.h>

#endif

using namespace std;

int main(int argc, char ** argv){

  Char_t nome[300];  
  sprintf(nome,"filename");
  

  TFile *file3;
  file3 = TFile::Open(nome);
  
  // cout << "Read file with name: " << nome << endl;
  TTree *tree3 = (TTree*)file3->Get("HZZ4LeptonsAnalysis");
  cout << "Read file with name: " << nome << " " << tree3->GetEntries() << endl;

  delete tree3;
  file3 -> Close();

  return 0; 

}

