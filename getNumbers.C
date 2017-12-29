{

  //TFile *_file0 = TFile::Open("plots/htotalfinal_hM4l_7_2e2mu.root");
  //TFile *_file0 = TFile::Open("plots/htotalfinal_hM4l_7_4mu.root");
  //TFile *_file0 = TFile::Open("plots/htotalfinal_hM4l_7_2e2mu.root");
  //TFile *_file0 = TFile::Open("plots/htotalfinal_hMZ_3_2e2mu.root");         

  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_WminusH_HToZZTo4L_M125_13TeV_powheg2-minlo-HWJ_JHUgenV6_pythia8.root");
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_ZH_HToZZ_4LFilter_M125_13TeV_powheg2-minlo-HZJ_JHUgenV6_pythia8.root");
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_ZZTo4L_13TeV_powheg_pythia8.root");
  //TFile *_file0 = TFile::Open("plots/htotalfinal_hPFMET_3_2e2mu.root");  
  //TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/output_DoubleMuon_Run2016B-23Sep2016-v3_miniaod_1.root");
  TFile *_file0 = TFile::Open("/lustre/cms/store/user/defilip/MonoHiggs/80X/histos4mu_25ns/Final_Estimation_4mu_data_miniAOD_new3ss.root");

  //TH1F *Histo = (TH1F*)_file0->Get("htotaldata");
  //TH1F *Histo = (TH1F*)_file0->Get("htotalHisto");
  //TH1F *Histo = (TH1F*)_file0->Get("hM4l_7");
  //TH1F *Histo = (TH1F*)_file0->Get("hMZ_3");   
  //TH1F *Histo = (TH1F*)_file0->Get("hfourlepbestmass_4l_afterSel_new_qqZZ");
  //TH1F *Histo = (TH1F*)_file0->Get("hfourlepbestmass_4l_afterSel_new_ggZZ");
  //TH1F *Histo = (TH1F*)_file0->Get("hfourlepbestmass_4l_afterSel_new_totSM_H"); 
  TH1F *Histo = (TH1F*)_file0->Get("h_3P1F_2P2F");

  TAxis *axis = Histo->GetXaxis();

  //float xmin=0.,xmax=10000.;
  float xmin=118.,xmax=130.;
  //float xmin=70.,xmax=10000.;
  //float xmin=70.,xmax=170.;
  //float xmin=100.,xmax=150.;
  //float xmin=4.5,xmax=1204.5;


 int bmin = axis->FindBin(xmin); 
 int bmax = axis->FindBin(xmax); 
 double integral = Histo->Integral(bmin,bmax);
 cout << "Integral before= " << integral << endl;
 integral-=Histo->GetBinContent(bmin)*(xmin-(axis->GetBinLowEdge(bmin)))/(axis->GetBinWidth(bmin));
 integral-=Histo->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax)/(axis->GetBinWidth(bmax));
 cout << "Integral after= " << integral << endl;

 double entry=0;
 for (int i=bmin;i<bmax;i++){
   entry+=Histo->GetBinContent(i)*Histo->GetEntries()/Histo->Integral();
   // cout << "Entry= " << entry << endl;
 }
 double error=sqrt(entry)*Histo->Integral()/Histo->GetEntries();
 cout << "Entry final= "<< entry << " " << integral << " weighted statistical error= " << error << " weighted systematic error (20%)= " << integral*0.2<< endl;
}
