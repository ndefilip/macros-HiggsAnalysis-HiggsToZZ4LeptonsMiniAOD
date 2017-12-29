
{

 TFile *f2 = TFile::Open("plots/htotalfinal_hPFMET_10_4mu.root");
     

 TH1D *nEvent_4l_w_new_ZZ = (TH1D*)f2->Get("nEvent_4l_w_ZZ");
 TH1D *nEvent_4l_w_new_DY = (TH1D*)f2->Get("nEvent_4l_w_DY"); 
 TH1D *nEvent_4l_w_new_WZ_WW_Wj = (TH1D*)f2->Get("nEvent_4l_w_WZ_WW_Wj");
 TH1D *nEvent_4l_w_new_TT = (TH1D*)f2->Get("nEvent_4l_w_TT");
 TH1D *nEvent_4l_w_new_TTV = (TH1D*)f2->Get("nEvent_4l_w_TTV");
 TH1D *nEvent_4l_w_new_VVV = (TH1D*)f2->Get("nEvent_4l_w_VVV");
 TH1D *nEvent_4l_w_new_totSM_H = (TH1D*)f2->Get("nEvent_4l_w_totSM_H");
 TH1D *nEvent_4l_w_new_totalbkgMC = (TH1D*)f2->Get("nEvent_4l_w_totalbkgMC");
 TH1D *nEvent_4l_w_new_signal=  (TH1D*)f2->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");
 TH1D *nEvent_4l_w_new_data = (TH1D*)f2->Get("nEvent_4l_w_data");

 Char_t outformat[20000];

 cout << "Sample & $Z\\gamma^{*},ZZ$ & $Z+jets$ & $WZ, WW, W+jets$ & $t \\bar{t}$ & $t \\bar{t}V$ & $VVV$ & $SM \\, Higgs$ & $Total \\, Bkg$  & Z' baryonic & Observed \\\\" << endl; 
 cout << "\\hline" << endl;

 sprintf (outformat,"HLT & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(5),nEvent_4l_w_new_DY->GetBinContent(5),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(5),nEvent_4l_w_new_TT->GetBinContent(5),nEvent_4l_w_new_TTV->GetBinContent(5),nEvent_4l_w_new_VVV->GetBinContent(5),nEvent_4l_w_new_totSM_H->GetBinContent(5),nEvent_4l_w_new_totalbkgMC->GetBinContent(5),nEvent_4l_w_new_signal->GetBinContent(5),nEvent_4l_w_new_data->GetBinContent(5));
 cout << outformat <<endl;

 sprintf (outformat,"$l^{+} l^{-}$, $12<m_{l^{+}l^{-}}<120$ & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(8),nEvent_4l_w_new_DY->GetBinContent(8),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(8),nEvent_4l_w_new_TT->GetBinContent(8),nEvent_4l_w_new_TTV->GetBinContent(8),nEvent_4l_w_new_VVV->GetBinContent(8),nEvent_4l_w_new_totSM_H->GetBinContent(8),nEvent_4l_w_new_totalbkgMC->GetBinContent(8),nEvent_4l_w_new_signal->GetBinContent(8),nEvent_4l_w_new_data->GetBinContent(8));
 cout << outformat <<endl;

 sprintf (outformat,"$Z_{1},Z_{2}$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(9),nEvent_4l_w_new_DY->GetBinContent(9),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(9),nEvent_4l_w_new_TT->GetBinContent(9),nEvent_4l_w_new_TTV->GetBinContent(9),nEvent_4l_w_new_VVV->GetBinContent(9),nEvent_4l_w_new_totSM_H->GetBinContent(9),nEvent_4l_w_new_totalbkgMC->GetBinContent(9),nEvent_4l_w_new_signal->GetBinContent(9),nEvent_4l_w_new_data->GetBinContent(9));
 cout << outformat <<endl;

 sprintf (outformat,"$p_{T}>20/10$, $m_{OS-SF}>4$, $m_{Z_{1}}>40$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(12),nEvent_4l_w_new_DY->GetBinContent(12),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(12),nEvent_4l_w_new_TT->GetBinContent(12),nEvent_4l_w_new_TTV->GetBinContent(12),nEvent_4l_w_new_VVV->GetBinContent(12),nEvent_4l_w_new_totSM_H->GetBinContent(12),nEvent_4l_w_new_totalbkgMC->GetBinContent(12),nEvent_4l_w_new_signal->GetBinContent(12),nEvent_4l_w_new_data->GetBinContent(12));
 cout << outformat <<endl;

 sprintf (outformat,"$m_{4l}>70$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(15),nEvent_4l_w_new_DY->GetBinContent(15),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(15),nEvent_4l_w_new_TT->GetBinContent(15),nEvent_4l_w_new_TTV->GetBinContent(15),nEvent_4l_w_new_VVV->GetBinContent(15),nEvent_4l_w_new_totSM_H->GetBinContent(15),nEvent_4l_w_new_totalbkgMC->GetBinContent(15),nEvent_4l_w_new_signal->GetBinContent(15),nEvent_4l_w_new_data->GetBinContent(15));
 cout << outformat <<endl;

 sprintf (outformat,"$|m_{4l}-125|<=10$, $N_{good \\, l}=4$, $n_{b-jets}<=1$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(22),nEvent_4l_w_new_DY->GetBinContent(22),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(22),nEvent_4l_w_new_TT->GetBinContent(22),nEvent_4l_w_new_TTV->GetBinContent(22),nEvent_4l_w_new_VVV->GetBinContent(22),nEvent_4l_w_new_totSM_H->GetBinContent(22),nEvent_4l_w_new_totalbkgMC->GetBinContent(22),nEvent_4l_w_new_signal->GetBinContent(22),nEvent_4l_w_new_data->GetBinContent(22));
 cout << outformat <<endl;

}
