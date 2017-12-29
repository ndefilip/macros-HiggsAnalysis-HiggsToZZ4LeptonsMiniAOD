
{

 TFile *f4mu = TFile::Open("plots/htotalfinal_hM4l_7_4mu.root");
 TFile *f4e = TFile::Open("plots/htotalfinal_hM4l_7_4e.root");
 TFile *f2e2mu = TFile::Open("plots/htotalfinal_hM4l_7_2e2mu.root");

 TH1F *f4mu_qqZZ   = (TH1F*)f4mu->Get("hfourlepbestmass_4l_afterSel_new_qqZZ");
 TH1F *f4e_qqZZ    = (TH1F*)f4e->Get("hfourlepbestmass_4l_afterSel_new_qqZZ");
 TH1F *f2e2mu_qqZZ = (TH1F*)f2e2mu->Get("hfourlepbestmass_4l_afterSel_new_qqZZ");

 TH1F *f4mu_ggZZ   = (TH1F*)f4mu->Get("hfourlepbestmass_4l_afterSel_new_ggZZ");
 TH1F *f4e_ggZZ    = (TH1F*)f4e->Get("hfourlepbestmass_4l_afterSel_new_ggZZ");
 TH1F *f2e2mu_ggZZ = (TH1F*)f2e2mu->Get("hfourlepbestmass_4l_afterSel_new_ggZZ");
 
 TH1F *f4mu_totSM_H   = (TH1F*)f4mu->Get("hfourlepbestmass_4l_afterSel_new_totSM_H");
 TH1F *f4e_totSM_H    = (TH1F*)f4e->Get("hfourlepbestmass_4l_afterSel_new_totSM_H");
 TH1F *f2e2mu_totSM_H = (TH1F*)f2e2mu->Get("hfourlepbestmass_4l_afterSel_new_totSM_H");

 // bkg no Higgs
 TH1F *f4mu_totalbkg_noSM_H   = (TH1F*)f4mu->Get("hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H");
 TH1F *f4e_totalbkg_noSM_H    = (TH1F*)f4e->Get("hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H");
 TH1F *f2e2mu_totalbkg_noSM_H = (TH1F*)f2e2mu->Get("hfourlepbestmass_4l_afterSel_new_totbkg_noSM_H");

 // Total bkg
 TH1F *f4mu_totalbkg   = (TH1F*)f4mu->Get("htotalHisto");
 TH1F *f4e_totalbkg    = (TH1F*)f4e->Get("htotalHisto");
 TH1F *f2e2mu_totalbkg = (TH1F*)f2e2mu->Get("htotalHisto");


 // Data
 TH1F *f4mu_totaldata   = (TH1F*)f4mu->Get("htotaldata");
 TH1F *f4e_totaldata    = (TH1F*)f4e->Get("htotaldata");
 TH1F *f2e2mu_totaldata = (TH1F*)f2e2mu->Get("htotaldata");


 cout << "\\begin{table}" << endl;
 cout << "\\caption{The number of estimated background and signal events and number of observed candidates, after final inclusive selection, in the full measurement range $m_{4l}>$ 70 GeV. Signal and ZZ background are estimated from Monte Carlo simulation, while Z+X is estimated from data}" << endl;

 cout << "\\begin{center}" << endl;
 cout << "\\label{tab:EventYields}" << endl;
 cout << "\\begin{tabular}{l|c|c|c|c}" << endl;
 cout << "\\hline \\hline" << endl;
 cout << "{\\textbf{Channel}} & {\\textbf{$4e$}} & {\\textbf{$4\\mu$}} & {\\textbf{$2e2\\mu$}} & {\\textbf{$4l$}} \\\\ " << endl;
 cout << "\\hline" << endl;

 Char_t outformat[20000];

 sprintf(outformat,"$q \\bar{q}\\rightarrow ZZ$ & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
	 f4e_qqZZ->Integral(), f4mu_qqZZ->Integral(), f2e2mu_qqZZ->Integral(), 
	 f4e_qqZZ->Integral()+f4mu_qqZZ->Integral()+f2e2mu_qqZZ->Integral());
 cout << outformat <<endl;
  
 sprintf(outformat,"$gg\\rightarrow ZZ$ & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
	 f4e_ggZZ->Integral(), f4mu_ggZZ->Integral(), f2e2mu_ggZZ->Integral(), 
	 f4e_ggZZ->Integral()+f4mu_ggZZ->Integral()+f2e2mu_ggZZ->Integral());
 cout << outformat <<endl;

 //sprintf(outformat,"$Z+X$ & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
 // f4e_ggZZ->Integral(), f4mu_ggZZ->Integral(), f2e2mu_ggZZ->Integral(), 
 //	 f4e_ggZZ->Integral()+f4mu_ggZZ->Integral()+f2e2mu_ggZZ->Integral());
 //cout << outformat <<endl;
 
 cout << "\\hline" << endl;
 sprintf(outformat,"Sum of bkgs & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
 	 f4e_totalbkg_noSM_H->Integral(), f4mu_totalbkg_noSM_H->Integral(), f2e2mu_totalbkg_noSM_H->Integral(), 
	 f4e_totalbkg_noSM_H->Integral()+f4mu_totalbkg_noSM_H->Integral()+f2e2mu_totalbkg_noSM_H->Integral());
 cout << outformat <<endl;

 cout << "\\hline" << endl;
 sprintf(outformat,"SM Higgs ($m_{H}=125$ GeV)) & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
	 f4e_totSM_H->Integral(), f4mu_totSM_H->Integral(), f2e2mu_totSM_H->Integral(), 
	 f4e_totSM_H->Integral()+f4mu_totSM_H->Integral()+f2e2mu_totSM_H->Integral());
 cout << outformat <<endl;

 cout << "\\hline" << endl;
 sprintf(outformat,"Total expected & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
	 f4e_totalbkg->Integral(), f4mu_totalbkg->Integral(), f2e2mu_totalbkg->Integral(), 
	 f4e_totalbkg->Integral()+f4mu_totalbkg->Integral()+f2e2mu_totalbkg->Integral());
 cout << outformat <<endl;

 cout << "\\hline" << endl;
 sprintf(outformat,"Observed & %.2f $\\pm$ xx & %.2f $\\pm$ xx & %.2f $\\pm$ xx  & %.2f $\\pm$ xx \\\\",
	 f4e_totaldata->Integral(), f4mu_totaldata->Integral(), f2e2mu_totaldata->Integral(), 
	 f4e_totaldata->Integral()+f4mu_totaldata->Integral()+f2e2mu_totaldata->Integral());
 cout << outformat <<endl;

 // cout << "\\hline" << endl;

 // sprintf (outformat,"HLT & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(5),nEvent_4l_w_new_DY->GetBinContent(5),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(5),nEvent_4l_w_new_TT->GetBinContent(5),nEvent_4l_w_new_TTV->GetBinContent(5),nEvent_4l_w_new_VVV->GetBinContent(5),nEvent_4l_w_new_totSM_H->GetBinContent(5),nEvent_4l_w_new_totalbkgMC->GetBinContent(5),nEvent_4l_w_new_signal->GetBinContent(5),nEvent_4l_w_new_data->GetBinContent(5));
 // cout << outformat <<endl;

 // sprintf (outformat,"$l^{+} l^{-}$, $12<m_{l^{+}l^{-}}<120$ & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e & %.2e  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(8),nEvent_4l_w_new_DY->GetBinContent(8),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(8),nEvent_4l_w_new_TT->GetBinContent(8),nEvent_4l_w_new_TTV->GetBinContent(8),nEvent_4l_w_new_VVV->GetBinContent(8),nEvent_4l_w_new_totSM_H->GetBinContent(8),nEvent_4l_w_new_totalbkgMC->GetBinContent(8),nEvent_4l_w_new_signal->GetBinContent(8),nEvent_4l_w_new_data->GetBinContent(8));
 // cout << outformat <<endl;

 // sprintf (outformat,"$Z_{1},Z_{2}$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(9),nEvent_4l_w_new_DY->GetBinContent(9),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(9),nEvent_4l_w_new_TT->GetBinContent(9),nEvent_4l_w_new_TTV->GetBinContent(9),nEvent_4l_w_new_VVV->GetBinContent(9),nEvent_4l_w_new_totSM_H->GetBinContent(9),nEvent_4l_w_new_totalbkgMC->GetBinContent(9),nEvent_4l_w_new_signal->GetBinContent(9),nEvent_4l_w_new_data->GetBinContent(9));
 // cout << outformat <<endl;

 // sprintf (outformat,"$p_{T}>20/10$, $m_{OS-SF}>4$, $m_{Z_{1}}>40$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(12),nEvent_4l_w_new_DY->GetBinContent(12),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(12),nEvent_4l_w_new_TT->GetBinContent(12),nEvent_4l_w_new_TTV->GetBinContent(12),nEvent_4l_w_new_VVV->GetBinContent(12),nEvent_4l_w_new_totSM_H->GetBinContent(12),nEvent_4l_w_new_totalbkgMC->GetBinContent(12),nEvent_4l_w_new_signal->GetBinContent(12),nEvent_4l_w_new_data->GetBinContent(12));
 // cout << outformat <<endl;

 // sprintf (outformat,"$m_{4l}>70$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(15),nEvent_4l_w_new_DY->GetBinContent(15),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(15),nEvent_4l_w_new_TT->GetBinContent(15),nEvent_4l_w_new_TTV->GetBinContent(15),nEvent_4l_w_new_VVV->GetBinContent(15),nEvent_4l_w_new_totSM_H->GetBinContent(15),nEvent_4l_w_new_totalbkgMC->GetBinContent(15),nEvent_4l_w_new_signal->GetBinContent(15),nEvent_4l_w_new_data->GetBinContent(15));
 // cout << outformat <<endl;

 // sprintf (outformat,"$|m_{4l}-125|<=10$, $N_{good \\, l}=4$, $n_{b-jets}<=1$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",nEvent_4l_w_new_ZZ->GetBinContent(22),nEvent_4l_w_new_DY->GetBinContent(22),nEvent_4l_w_new_WZ_WW_Wj->GetBinContent(22),nEvent_4l_w_new_TT->GetBinContent(22),nEvent_4l_w_new_TTV->GetBinContent(22),nEvent_4l_w_new_VVV->GetBinContent(22),nEvent_4l_w_new_totSM_H->GetBinContent(22),nEvent_4l_w_new_totalbkgMC->GetBinContent(22),nEvent_4l_w_new_signal->GetBinContent(22),nEvent_4l_w_new_data->GetBinContent(22));
 // cout << outformat <<endl;

 
  cout << "\\hline \\hline" << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\label{tab:SMHiggs_yields}" <<endl;	
  cout << "\\end{center}" << endl;
  cout << "\\end{table}" << endl;
 
}
