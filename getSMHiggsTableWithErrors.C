
{

 TFile *f4mu = TFile::Open("plots/htotalfinal_hM4l_7_4mu.root");
 TFile *f4e = TFile::Open("plots/htotalfinal_hM4l_7_4e.root");
 TFile *f2e2mu = TFile::Open("plots/htotalfinal_hM4l_7_2e2mu.root");

 TH1D *f4mu_qqZZ = (TH1D*)f4mu->Get("nEvent_4l_w_qqZZ");
 TH1D *f4e_qqZZ = (TH1D*)f4e->Get("nEvent_4l_w_qqZZ");
 TH1D *f2e2mu_qqZZ = (TH1D*)f2e2mu->Get("nEvent_4l_w_qqZZ");

 TH1D *f4mu_ggZZ = (TH1D*)f4mu->Get("nEvent_4l_w_ggZZ");
 TH1D *f4e_ggZZ = (TH1D*)f4e->Get("nEvent_4l_w_ggZZ");
 TH1D *f2e2mu_ggZZ = (TH1D*)f2e2mu->Get("nEvent_4l_w_ggZZ");

 TH1D *f4mu_ZZ = (TH1D*)f4mu->Get("nEvent_4l_w_ZZ");
 TH1D *f4e_ZZ = (TH1D*)f4e->Get("nEvent_4l_w_ZZ");
 TH1D *f2e2mu_ZZ = (TH1D*)f2e2mu->Get("nEvent_4l_w_ZZ");

 TH1D *f4mu_totSM_H   = (TH1D*)f4mu->Get("nEvent_4l_w_totSM_H");
 TH1D *f4e_totSM_H    = (TH1D*)f4e->Get("nEvent_4l_w_totSM_H");
 TH1D *f2e2mu_totSM_H = (TH1D*)f2e2mu->Get("nEvent_4l_w_totSM_H");

 // bkg no Higgs
 // TH1D *f4mu_totalbkg_noSM_H   = (TH1D*)f4mu->Get("nEvent_4l_w_totbkg_noSM_H");
 // TH1D *f4e_totalbkg_noSM_H    = (TH1D*)f4e->Get("nEvent_4l_w_totbkg_noSM_H");
 // TH1D *f2e2mu_totalbkg_noSM_H = (TH1D*)f2e2mu->Get("nEvent_4l_w_totbkg_noSM_H");

 

 // Total bkg
 TH1D *f4mu_totalbkg   = (TH1D*)f4mu->Get("nEvent_4l_w_totalbkgMC");
 TH1D *f4e_totalbkg    = (TH1D*)f4e->Get("nEvent_4l_w_totalbkgMC");
 TH1D *f2e2mu_totalbkg = (TH1D*)f2e2mu->Get("nEvent_4l_w_totalbkgMC");

 // Data
 TH1D *f4mu_totaldata   = (TH1D*)f4mu->Get("nEvent_4l_w_data");
 TH1D *f4e_totaldata    = (TH1D*)f4e->Get("nEvent_4l_w_data");
 TH1D *f2e2mu_totaldata = (TH1D*)f2e2mu->Get("nEvent_4l_w_data");


 cout << "\\begin{table}" << endl;
 cout << "\\begin{center}" << endl;
 cout << "\\resizebox{\\textwidth}{!}{% " << endl;
 cout << "\\begin{tabular}{l|c|c|c|c}" << endl;
 cout << "\\hline \\hline" << endl;
 cout << "{\\textbf{Channel}} & {\\textbf{$4e$}} & {\\textbf{$4\\mu$}} & {\\textbf{$2e2\\mu$}} & {\\textbf{$4l$}} \\\\ " << endl;
 cout << "\\hline" << endl;

 Char_t outformat[20000];

 sprintf(outformat,"$q \\bar{q}\\rightarrow ZZ$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_qqZZ->GetBinContent(15), f4e_qqZZ->GetBinError(15),
	 f4mu_qqZZ->GetBinContent(15), f4mu_qqZZ->GetBinError(15),
	 f2e2mu_qqZZ->GetBinContent(15), f2e2mu_qqZZ->GetBinError(15),
	 f4e_qqZZ->GetBinContent(15)+f4mu_qqZZ->GetBinContent(15)+f2e2mu_qqZZ->GetBinContent(15),
	 sqrt(f4e_qqZZ->GetBinError(15)*f4e_qqZZ->GetBinError(15) + f4mu_qqZZ->GetBinError(15)*f4mu_qqZZ->GetBinError(15) + f2e2mu_qqZZ->GetBinError(15)*f2e2mu_qqZZ->GetBinError(15) ) 
	 );
 cout << outformat <<endl;
 
 sprintf(outformat,"$gg\\rightarrow ZZ$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_ggZZ->GetBinContent(15), f4e_ggZZ->GetBinError(15),
	 f4mu_ggZZ->GetBinContent(15), f4mu_ggZZ->GetBinError(15),
	 f2e2mu_ggZZ->GetBinContent(15), f2e2mu_ggZZ->GetBinError(15),
	 f4e_ggZZ->GetBinContent(15)+f4mu_ggZZ->GetBinContent(15)+f2e2mu_ggZZ->GetBinContent(15),
	 sqrt(f4e_ggZZ->GetBinError(15)*f4e_ggZZ->GetBinError(15) + f4mu_ggZZ->GetBinError(15)*f4mu_ggZZ->GetBinError(15) + f2e2mu_ggZZ->GetBinError(15)*f2e2mu_ggZZ->GetBinError(15) ) 
	 );
 cout << outformat <<endl;

 float ZX_4e=27.2;    float ZX_4e_err=ZX_4e*0.43;
 float ZX_4mu=31.0;   float ZX_4mu_err=ZX_4mu*0.36;
 float ZX_2e2mu=62.0; float ZX_2e2mu_err=ZX_2e2mu*0.40;
 float sumbkg_4e    = f4e_ZZ->GetBinContent(15)+ZX_4e;  float sumbkg_4e_err=sqrt(f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err);
 float sumbkg_4mu   = f4mu_ZZ->GetBinContent(15)+ZX_4mu; float sumbkg_4mu_err=sqrt(f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err);
 float sumbkg_2e2mu = f2e2mu_ZZ->GetBinContent(15)+ZX_2e2mu; float sumbkg_2e2mu_err=sqrt(f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err);
 float sumbkg_4l    = sumbkg_4e+sumbkg_4mu+sumbkg_2e2mu;  
 float sumbkg_4l_err=sqrt(
	      (f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err)+
	      (f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err)+
	      (f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err)
			  );

 sprintf(outformat,"$Z+X$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\",
	 ZX_4e, ZX_4e_err,
	 ZX_4mu, ZX_4mu_err,
	 ZX_2e2mu, ZX_2e2mu_err,
	 ZX_4e+ZX_4mu+ZX_2e2mu, sqrt( ZX_4e_err*ZX_4e_err+ZX_4mu_err*ZX_4mu_err+ZX_2e2mu_err*ZX_2e2mu_err)
	 );
 cout << outformat <<endl;

 // sprintf(outformat,"Sum of bkgs & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
 // 	 f4e_totalbkg_noSM_H->GetBinContent(15)+ZX_4e, sqrt(f4e_totalbkg_noSM_H->GetBinError(15)*f4e_totalbkg_noSM_H->GetBinError(15)+ZX_4e_err*ZX_4e_err),
 // 	 f4mu_totalbkg_noSM_H->GetBinContent(15)+ZX_4mu, sqrt(f4mu_totalbkg_noSM_H->GetBinError(15)*f4mu_totalbkg_noSM_H->GetBinError(15)+ZX_4mu_err*ZX_4mu_err),
 // 	 f2e2mu_totalbkg_noSM_H->GetBinContent(15)+ZX_2e2mu, sqrt(f2e2mu_totalbkg_noSM_H->GetBinError(15)*f2e2mu_totalbkg_noSM_H->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err),
 // 	 f4e_totalbkg_noSM_H->GetBinContent(15)+ZX_4e+f4mu_totalbkg_noSM_H->GetBinContent(15)+ZX_4mu+f2e2mu_totalbkg_noSM_H->GetBinContent(15)+ZX_2e2mu,
 // 	 sqrt(
 // 	      (f4e_totalbkg_noSM_H->GetBinError(15)*f4e_totalbkg_noSM_H->GetBinError(15)+ZX_4e_err*ZX_4e_err) +
 // 	      (f4mu_totalbkg_noSM_H->GetBinError(15)*f4mu_totalbkg_noSM_H->GetBinError(15)+ZX_4mu_err*ZX_4mu_err) +
 // 	      (f2e2mu_totalbkg_noSM_H->GetBinError(15)*f2e2mu_totalbkg_noSM_H->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err)
 // 	      ) 
 // 	 );
 // cout << outformat <<endl;

 sprintf(outformat,"Sum of bkgs & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 sumbkg_4e, sqrt(f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err),
	 sumbkg_4mu, sqrt(f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err),
	 sumbkg_2e2mu, sqrt(f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err),
	 sumbkg_4l,
	 sqrt(
	      (f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err)+
	      (f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err)+
	      (f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err)
	      )
	 );
 cout << outformat <<endl;

 sprintf(outformat,"SM Higgs ($m_{H}=125$ GeV)) & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_totSM_H->GetBinContent(15), f4e_totSM_H->GetBinError(15),
	 f4mu_totSM_H->GetBinContent(15), f4mu_totSM_H->GetBinError(15),
	 f2e2mu_totSM_H->GetBinContent(15), f2e2mu_totSM_H->GetBinError(15),
	 f4e_totSM_H->GetBinContent(15)+f4mu_totSM_H->GetBinContent(15)+f2e2mu_totSM_H->GetBinContent(15),
	 sqrt(f4e_totSM_H->GetBinError(15)*f4e_totSM_H->GetBinError(15) + f4mu_totSM_H->GetBinError(15)*f4mu_totSM_H->GetBinError(15) + f2e2mu_totSM_H->GetBinError(15)*f2e2mu_totSM_H->GetBinError(15) ) 
	 );
 cout << outformat <<endl;

 float H_sumbkg_4e    = sumbkg_4e+f4e_totSM_H->GetBinContent(15);
 float H_sumbkg_4mu   = sumbkg_4mu+f4mu_totSM_H->GetBinContent(15);
 float H_sumbkg_2e2mu = sumbkg_2e2mu+f2e2mu_totSM_H->GetBinContent(15);
 float H_sumbkg_4l    = H_sumbkg_4e+H_sumbkg_4mu+H_sumbkg_2e2mu;

 cout << "\\hline " << endl;
 sprintf(outformat,"Total expected & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 H_sumbkg_4e, sqrt(f4e_totSM_H->GetBinError(15)*f4e_totSM_H->GetBinError(15)          +  sumbkg_4e_err*sumbkg_4e_err),
	 H_sumbkg_4mu, sqrt(f4mu_totSM_H->GetBinError(15)*f4mu_totSM_H->GetBinError(15)       +  sumbkg_4mu_err*sumbkg_4mu_err),
	 H_sumbkg_2e2mu, sqrt(f2e2mu_totSM_H->GetBinError(15)*f2e2mu_totSM_H->GetBinError(15) +  sumbkg_2e2mu_err*sumbkg_2e2mu_err),
	 H_sumbkg_4l, 
	 sqrt(
	      (f4e_totSM_H->GetBinError(15)*f4e_totSM_H->GetBinError(15)          +  sumbkg_4e_err*sumbkg_4e_err)   +
	      (f4mu_totSM_H->GetBinError(15)*f4mu_totSM_H->GetBinError(15)       +  sumbkg_4mu_err*sumbkg_4mu_err)  +
	      (f2e2mu_totSM_H->GetBinError(15)*f2e2mu_totSM_H->GetBinError(15) +  sumbkg_2e2mu_err*sumbkg_2e2mu_err)
	      )
	 );
 cout << outformat <<endl;

 cout << "\\hline" << endl; 
 sprintf(outformat,"Observed & %d & %d & %d & %d \\\\",
	 int(f4e_totaldata->GetBinContent(15)),
	 int(f4mu_totaldata->GetBinContent(15)),
	 int(f2e2mu_totaldata->GetBinContent(15)),
	 int(f4e_totaldata->GetBinContent(15)+f4mu_totaldata->GetBinContent(15)+f2e2mu_totaldata->GetBinContent(15))
	 );
 cout << outformat <<endl;
 
 cout << "\\hline \\hline" << endl;
 cout << "\\end{tabular}" << endl;
 cout << "}" << endl;
 cout << "\\caption{Number of estimated background and signal events and number of observed candidates, after the SM Higgs selection, in the mass range $m_{4l}>$ 70 GeV. SM Higgs signal and ZZ background are estimated from Monte Carlo simulation, while Z+X is estimated from data; only statistical errors are quoted.}" << endl;

 cout << "\\label{tab:SMHiggs_yields}" <<endl;	
 cout << "\\end{center}" << endl;
 cout << "\\end{table}" << endl;
 
}
