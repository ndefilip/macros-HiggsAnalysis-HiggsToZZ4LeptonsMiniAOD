#include "ZZStyle.C"

class doRebin{
  
public: 
  doRebin();
};


doRebin::doRebin(){

  TFile *_file0 = TFile::Open("plots/htotalfinal_hPFMET_12_4l.root");
  TH1F *hdata= (TH1F*)_file0->Get("htotaldata");
  TH1F *hMC= (TH1F*)_file0->Get("htotalHisto");

  

  const int NMOBINS = 5;
  const double MOMIN = 0.0, MOMAX = 1000.0;
  double loglinMbins[6]={0.,25.,50.,200., 500.,1000.};

  TH1F *hLogLinXPFMETData = dynamic_cast<TH1F*>(hdata->Rebin(NMOBINS,"hLogLinXPFMETData",loglinMbins));
  //hLogLinXPFMETData->Draw("EP");
  cout << "Data: bin 1 " << hLogLinXPFMETData->GetBinContent(1) << " \n" 
       << "Data: bin 2 " << hLogLinXPFMETData->GetBinContent(2) << " \n" 
       << "Data: bin 3 " << hLogLinXPFMETData->GetBinContent(3) << " \n" 
       << "Data: bin 4 " << hLogLinXPFMETData->GetBinContent(4) << " \n" 
       << "Data: bin 5 " << hLogLinXPFMETData->GetBinContent(5) << endl;


  TH1F *hLogLinXPFMETMC = dynamic_cast<TH1F*>(hMC->Rebin(NMOBINS,"hLogLinXPFMETMC",loglinMbins));
  //hLogLinXPFMETMC->Draw("EP");
  
  //hLogLinXPFMETData->Add(hLogLinXPFMETMC,-1);


  hLogLinXPFMETData->Divide(hLogLinXPFMETMC);


  cout << "Uncert: bin 1 " << hLogLinXPFMETData->GetBinContent(1) << " \n" 
       << "Uncert: bin 2 " << hLogLinXPFMETData->GetBinContent(2) << " \n" 
       << "Uncert: bin 3 " << hLogLinXPFMETData->GetBinContent(3) << " \n" 
       << "Uncert: bin 4 " << hLogLinXPFMETData->GetBinContent(4) << " \n" 
       << "Uncert: bin 5 " << hLogLinXPFMETData->GetBinContent(5) << endl;

  //hLogLinXPFMETData->Fit("pol2");

  TStyle * style = getStyle("ZZ");
  //style->SetMarkerSize(0.8);
  style->cd();
  style->SetNdivisions(508, "X");
  style->SetNdivisions(508, "Y");
  style->SetMarkerSize(0.8);

  TCanvas *c1=new TCanvas("c1","c1",600,600);  

  TH2F *hframe=NULL,*hframe2=NULL; 
  hframe= new TH2F("hframe","hframe",100,0.,1000.,100,0.,2.);// 4l analysis mass nrebin=10 GeV

  hframe->SetYTitle("Data/MC");
  hframe->SetXTitle("PF MET (GeV)"); // PFMET

  hframe->Draw();
  hLogLinXPFMETData->Draw("EPsame");
  
  c1->SaveAs("Data_MC_Ratio_off4lpeak.pdf");
  c1->SaveAs("Data_MC_Ratio_off4lpeak.png");
  c1->SaveAs("Data_MC_Ratio_off4lpeak.eps");

};
