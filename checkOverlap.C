#define checkOverlap_cxx
#include "checkOverlap.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <sstream>

void checkOverlap::Loop(Char_t *output)
{
//   In a ROOT session, you can do:
//      Root > .L checkOverlap.C
//      Root > checkOverlap t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  
  ofstream outputfile;
  outputfile.open (output);

  TString DoubleFile=output;
  Bool_t isDoubleMu=false;
  isDoubleMu=DoubleFile.Contains("DoubleMu");
  cout << "IsDoubleMu= " << isDoubleMu << endl;

  vector<long int> listruns;
  vector<long int> listevents;
  vector<long int> listlumi;  

  if (!isDoubleMu) {
    // bouble Mu or EG file to compare with
    TString DoubleMuFile;
    if (DoubleFile.Contains("DoubleElectron")){
      DoubleMuFile=DoubleFile.ReplaceAll("DoubleElectron","DoubleMu");
      DoubleMuFile=DoubleFile.ReplaceAll("-v1","*");
      DoubleMuFile=DoubleFile.ReplaceAll("-v2","*");
      DoubleMuFile=DoubleFile.ReplaceAll("-v3","*");
      DoubleMuFile=DoubleFile.ReplaceAll("_1","*");
      DoubleMuFile=DoubleFile.ReplaceAll("_2","*");
      DoubleMuFile=DoubleFile.ReplaceAll(".root",".txt");
      
      Char_t command[500];
      sprintf(command,"ls *%s* > tmpfileforoverlapcheck.txt",DoubleMuFile.Data());
      cout << "command is " << command << endl;
      system(command);
    }
    if (DoubleFile.Contains("MuEG")){
      TString DoubleFileNew=output;
      TString MuEGFile;
      MuEGFile=DoubleFileNew.ReplaceAll("MuEG","DoubleMu");
      MuEGFile=DoubleFileNew.ReplaceAll("-v1","*");
      MuEGFile=DoubleFileNew.ReplaceAll("-v2","*");
      MuEGFile=DoubleFileNew.ReplaceAll("-v3","*");
      MuEGFile=DoubleFileNew.ReplaceAll("_1","*");
      MuEGFile=DoubleFileNew.ReplaceAll("_2","*");
      MuEGFile=DoubleFileNew.ReplaceAll(".root",".txt");
      
      Char_t commandnew[500];
      sprintf(commandnew,"ls *%s* > tmpfileforoverlapcheck.txt",MuEGFile.Data());
      cout << "commandnew is " << commandnew << endl;
      system(commandnew);

      TString DoubleFileNewNew=output;
      TString MuEGFileNew;
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("MuEG","DoubleElectron");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("-v1","*");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("-v2","*");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("-v3","*");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("_1","*");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll("_2","*");
      MuEGFileNew=DoubleFileNewNew.ReplaceAll(".root",".txt");
      
      Char_t commandnewnew[500];
      sprintf(commandnewnew,"ls *%s* >> tmpfileforoverlapcheck.txt",MuEGFileNew.Data());
      cout << "commandnewnew is " << commandnewnew << endl;
      system(commandnewnew);

    }

    ifstream inputfilelist;    
    inputfilelist.open("tmpfileforoverlapcheck.txt");

    char lline[300];
    char *ppch;
    int i=0;
    
    while (inputfilelist.getline(lline, 300) ){
      ppch=strtok(lline," ");

      ifstream inputfile;    
      //inputfile.open(DoubleMuFile);
       //cout << "Checking runs in DoubleMu " << DoubleMuFile.Data()<< endl;
      inputfile.open(ppch);
      cout << "Checking runs in DoubleMu and MuEG" << ppch << endl;
      
      //  int i=0;
      //     long int dummy_a[1000],dummy_b[1000],dummy_c[1000];
      
      //     while (!inputfile.eof()){
      //       if (i==1000) i=0;
      //       //cout << inputfile.eof() << endl;
      //       inputfile >> dummy_a[i] >> dummy_b[i] >> dummy_c[i] ; 
      //       //cout << dummy_a[i] << " " << dummy_b[i] << " " << dummy_c[i] << endl;
      //       if ( dummy_a[i]>0 && dummy_b[i]>0 && dummy_c[i]>0){
      //         //cout << i << " " << dummy_a[i] << " " << dummy_b[i] << " " << dummy_c[i] << endl;
      // 	listruns.push_back(dummy_a[i]);
      // 	listevents.push_back(dummy_b[i]);
      // 	listlumi.push_back(dummy_c[i]);
      //       }
      //       i++;
      //     } 
      
      
      char line[300];
      char *pch;
      int i=0;
      
      while (inputfile.getline(line, 300) ){
	//cout << "read line: "<< line <<endl;
	pch=strtok(line," ");
	listruns.push_back(atoi(pch));
	//cout << atoi(pch) << " ";
	pch=strtok (NULL, " ");
	listevents.push_back(atoi(pch));
	//cout << atoi(pch) << " ";
	pch=strtok (NULL, " ");
	listlumi.push_back(atoi(pch));
	//cout << atoi(pch) << endl;	
      }
      
    }
    cout << "Number of runs in DoubleMu/MuEG read from input file= " << listruns.size() << endl; 
  }


  ofstream overlapfile;
  TString DoubleGoodFile=output;
  TString DoubleOutFile;
  DoubleOutFile=DoubleGoodFile.ReplaceAll(".txt",".overlap");
  char outfile[500];
  sprintf(outfile,"%s",DoubleOutFile.Data());

  if (!isDoubleMu) {
    cout << "Opening file " << outfile << endl;
    overlapfile.open (outfile);
  }
  
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    bool debug=true;

    if( debug ) cout << "\nAnalyzing entry: " << jentry << " Run: " << Run << " Event: " << Event << " LumiSection: " << LumiSection << endl ;

    // HLT Paths
    //cout << "This is HLT in data" << endl;
    
    stringstream ss (stringstream::in | stringstream::out);
    ss << HLTPathsFired;
    TString hlt(ss.str());
    
    //cout<<" HLTPathsFired... "<<hlt<<endl;
    
    if( DATA_type == "2011"){
		
	if( DoubleFile.Contains("DoubleElectron")){
	  
	  if( debug ){ cout << "\n ** Step 2 (Trigger): "<< endl ;
	    
	    cout << "This is HLT in data" << endl;
	    cout<<" HLTPathsFired... "<<hlt<<endl;
	  }
	  
	  if(!hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") &&	// OR mu and e trigger
	     !hlt.Contains("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL") &&
	     !hlt.Contains("HLT_Mu17_Mu8")   &&
	     !hlt.Contains("HLT_DoubleMu7")   &&
	     !hlt.Contains("HLT_Mu13_Mu8")
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger paths" << endl;
	    continue;
	  }
	  
	}
	else if( DoubleFile.Contains("DoubleMu") ){
	  
	  if( debug ){ cout << "\n ** Step 2 (Trigger): "<< endl ;
	    
	    cout << "This is HLT in data" << endl;
	    cout<<" HLTPathsFired... "<<hlt<<endl;
	  }
	  
	  if(!hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") &&	// OR mu and e trigger
	     !hlt.Contains("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL") &&
	     !hlt.Contains("HLT_Mu17_Mu8")   &&
	     !hlt.Contains("HLT_DoubleMu7")   &&
	     !hlt.Contains("HLT_Mu13_Mu8")
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger paths" << endl;
	    continue;
	  }
	  if(hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") || 
	     hlt.Contains("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL") 
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger vetos" << endl;
	    continue;
	  }
	  
	  
	  // HLT emulation
	  bool pt_17_emu = 0;
	  int i_17_emu = -1;
	  bool pt_8_emu = 0;
	  
	  for(int i = 0; i < RECO_NMU; ++i){
	    if( RECOMU_PT[i] > 17 && !pt_17_emu ){ pt_17_emu = 1; i_17_emu = i; }
	  }
	  if( !pt_17_emu ) continue;
	  for(int i = 0; i < RECO_NMU; ++i){
	    if( i == i_17_emu ) continue;
	    if( RECOMU_PT[i] > 8 && !pt_8_emu ){ pt_8_emu = 1; }
	  }
	  if( !pt_8_emu ) continue;
	  
	}
	
	
      }
      else if( DATA_type == "2012"){
	
	if( DoubleFile.Contains("DoubleElectron")){
	  if( debug ){ cout << "\n ** Step 2 (Trigger): "<< endl ;
	    
	    cout << "This is HLT in data" << endl;
	    cout<<" HLTPathsFired... "<<hlt<<endl;
	  }
	  
	  if(!hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") &&	// OR mu and e trigger
	     !hlt.Contains("HLT_Mu17_Mu8")   &&
	     !hlt.Contains("HLT_Mu17_TkMu8") &&
	     !hlt.Contains("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")   &&
	     !hlt.Contains("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger paths" << endl;
	    continue;
	  }
	  
	}
	else if( DoubleFile.Contains("DoubleMu")){
	  if( debug ){ cout << "\n ** Step 2 (Trigger): "<< endl ;
	    
	    cout << "This is HLT in data" << endl;
	    cout<<" HLTPathsFired... "<<hlt<<endl;
	  }
	  
	  if(!hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") &&	// OR mu and e trigger
	     !hlt.Contains("HLT_Mu17_Mu8")   &&
	     !hlt.Contains("HLT_Mu17_TkMu8") &&
	     !hlt.Contains("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")   &&
	     !hlt.Contains("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger paths" << endl;
	    continue;
	  }
	  if( hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")
	      ) {
	    if( debug )cout << "Event not passing the HLT trigger vetos" << endl;
	    continue;
	  }
	  
	}
	else if( DoubleFile.Contains("MuEG") ){
	  if( debug ){ cout << "\n ** Step 2 (Trigger): "<< endl ;
	    
	    cout << "This is HLT in data" << endl;
	    cout<<" HLTPathsFired... "<<hlt<<endl;
	  }
	  
	  if(!hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") &&	// OR mu and e trigger
	     !hlt.Contains("HLT_Mu17_Mu8")   &&
	     !hlt.Contains("HLT_Mu17_TkMu8") &&
	     !hlt.Contains("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")   &&
	     !hlt.Contains("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")
	     ) {
	    if( debug )cout << "Event not passing the HLT trigger paths" << endl;
	    continue;
	  }
	  if( hlt.Contains("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")
	      || hlt.Contains("HLT_Mu17_Mu8")
	      || hlt.Contains("HLT_Mu17_TkMu8")
	      ) {
	    if( debug )cout << "Event not passing the HLT trigger vetos" << endl;
	    continue;
	  }
	  
	}			
      }    
                
    //cout << "Run= " << Run << " Event= " << Event << " LumiSection= " << LumiSection << endl;
    bool included=false;
    for (int j=0;j<listruns.size();j++){
      if (Run==listruns.at(j) && Event==listevents.at(j) && LumiSection==listlumi.at(j) ){
	cout << "Event already included in DoubleMu...skipping " 
	     << "Run= " << Run << " Event= " << Event << " LumiSection= " << LumiSection << endl;
	included=true;
	overlapfile << Run << " " << Event << " " << LumiSection << endl;
      }
    }    
    if (!included) outputfile << Run << " " << Event << " " << LumiSection << endl;
  }
  
  
  outputfile.close();
  
}
