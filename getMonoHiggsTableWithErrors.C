{

 TFile *f4mu = TFile::Open("plots/htotalfinal_hM4l_7_4mu.root");
 TFile *f4e = TFile::Open("plots/htotalfinal_hM4l_7_4e.root");
 TFile *f2e2mu = TFile::Open("plots/htotalfinal_hM4l_7_2e2mu.root");

 TH1D *f4mu_ZZ = (TH1D*)f4mu->Get("nEvent_4l_w_ZZ");
 TH1D *f4e_ZZ = (TH1D*)f4e->Get("nEvent_4l_w_ZZ");
 TH1D *f2e2mu_ZZ = (TH1D*)f2e2mu->Get("nEvent_4l_w_ZZ");

 TH1D *f4mu_TTV = (TH1D*)f4mu->Get("nEvent_4l_w_TTV");
 TH1D *f4e_TTV = (TH1D*)f4e->Get("nEvent_4l_w_TTV");
 TH1D *f2e2mu_TTV = (TH1D*)f2e2mu->Get("nEvent_4l_w_TTV");

 TH1D *f4mu_VVV = (TH1D*)f4mu->Get("nEvent_4l_w_VVV");
 TH1D *f4e_VVV = (TH1D*)f4e->Get("nEvent_4l_w_VVV");
 TH1D *f2e2mu_VVV = (TH1D*)f2e2mu->Get("nEvent_4l_w_VVV");

 TH1D *f4mu_totSM_H   = (TH1D*)f4mu->Get("nEvent_4l_w_totSM_H");
 TH1D *f4e_totSM_H    = (TH1D*)f4e->Get("nEvent_4l_w_totSM_H");
 TH1D *f2e2mu_totSM_H = (TH1D*)f2e2mu->Get("nEvent_4l_w_totSM_H");

 // Signal Z' baryonic 
 TH1D *f4mu_ZpBaryonic_MZp500_MChi1   = (TH1D*)f4mu->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");
 TH1D *f4e_ZpBaryonic_MZp500_MChi1    = (TH1D*)f4e->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");
 TH1D *f2e2mu_ZpBaryonic_MZp500_MChi1 = (TH1D*)f2e2mu->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");

 // Data
 TH1D *f4mu_totaldata   = (TH1D*)f4mu->Get("nEvent_4l_w_data");
 TH1D *f4e_totaldata    = (TH1D*)f4e->Get("nEvent_4l_w_data");
 TH1D *f2e2mu_totaldata = (TH1D*)f2e2mu->Get("nEvent_4l_w_data");


 cout << "\\begin{table}[htbH]" << endl;
 cout << "\\begin{center}" << endl;
 cout << "\\resizebox{\\textwidth}{!}{% " << endl;
 cout << "\\begin{tabular}{l|c|c|c|c}" << endl;
 cout << "\\hline \\hline" << endl;
 cout << "{\\textbf{Channel}} & {\\textbf{$4e$}} & {\\textbf{$4\\mu$}} & {\\textbf{$2e2\\mu$}} & {\\textbf{$4l$}} \\\\ " << endl;
 cout << "\\hline" << endl;

 Char_t outformat[20000];

 sprintf(outformat,"$Z\\gamma*, ZZ$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_ZZ->GetBinContent(22), f4e_ZZ->GetBinError(22),
	 f4mu_ZZ->GetBinContent(22), f4mu_ZZ->GetBinError(22),
	 f2e2mu_ZZ->GetBinContent(22), f2e2mu_ZZ->GetBinError(22),
	 f4e_ZZ->GetBinContent(22)+f4mu_ZZ->GetBinContent(22)+f2e2mu_ZZ->GetBinContent(22),
	 sqrt(f4e_ZZ->GetBinError(22)*f4e_ZZ->GetBinError(22) + f4mu_ZZ->GetBinError(22)*f4mu_ZZ->GetBinError(22) + f2e2mu_ZZ->GetBinError(22)*f2e2mu_ZZ->GetBinError(22) ) 
	 );
 cout << outformat <<endl;

 sprintf(outformat,"$t \\bar{t} V$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_TTV->GetBinContent(22), f4e_TTV->GetBinError(22),
	 f4mu_TTV->GetBinContent(22), f4mu_TTV->GetBinError(22),
	 f2e2mu_TTV->GetBinContent(22), f2e2mu_TTV->GetBinError(22),
	 f4e_TTV->GetBinContent(22)+f4mu_TTV->GetBinContent(22)+f2e2mu_TTV->GetBinContent(22),
	 sqrt(f4e_TTV->GetBinError(22)*f4e_TTV->GetBinError(22) + f4mu_TTV->GetBinError(22)*f4mu_TTV->GetBinError(22) + f2e2mu_TTV->GetBinError(22)*f2e2mu_TTV->GetBinError(22) ) 
	 );
 cout << outformat <<endl;

 sprintf(outformat,"$VVV$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_VVV->GetBinContent(22), f4e_VVV->GetBinError(22),
	 f4mu_VVV->GetBinContent(22), f4mu_VVV->GetBinError(22),
	 f2e2mu_VVV->GetBinContent(22), f2e2mu_VVV->GetBinError(22),
	 f4e_VVV->GetBinContent(22)+f4mu_VVV->GetBinContent(22)+f2e2mu_VVV->GetBinContent(22),
	 sqrt(f4e_VVV->GetBinError(22)*f4e_VVV->GetBinError(22) + f4mu_VVV->GetBinError(22)*f4mu_VVV->GetBinError(22) + f2e2mu_VVV->GetBinError(22)*f2e2mu_VVV->GetBinError(22) ) 
	 );
 cout << outformat <<endl;

 
 float ZX_4e=3.2;    float ZX_4e_err=ZX_4e*0.43;
 float ZX_4mu=3.9;   float ZX_4mu_err=ZX_4mu*0.36;
 float ZX_2e2mu=10.7; float ZX_2e2mu_err=ZX_2e2mu*0.40;

 sprintf(outformat,"$Z+X$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\",
	 ZX_4e, ZX_4e_err,
	 ZX_4mu, ZX_4mu_err,
	 ZX_2e2mu, ZX_2e2mu_err,
	 ZX_4e+ZX_4mu+ZX_2e2mu, sqrt( ZX_4e_err*ZX_4e_err+ZX_4mu_err*ZX_4mu_err+ZX_2e2mu_err*ZX_2e2mu_err)
	 );
 cout << outformat <<endl;
 
 sprintf(outformat,"SM Higgs ($m_{H}=125$ GeV)) & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_totSM_H->GetBinContent(22), f4e_totSM_H->GetBinError(22),
	 f4mu_totSM_H->GetBinContent(22), f4mu_totSM_H->GetBinError(22),
	 f2e2mu_totSM_H->GetBinContent(22), f2e2mu_totSM_H->GetBinError(22),
	 f4e_totSM_H->GetBinContent(22)+f4mu_totSM_H->GetBinContent(22)+f2e2mu_totSM_H->GetBinContent(22),
	 sqrt(f4e_totSM_H->GetBinError(22)*f4e_totSM_H->GetBinError(22) + f4mu_totSM_H->GetBinError(22)*f4mu_totSM_H->GetBinError(22) + f2e2mu_totSM_H->GetBinError(22)*f2e2mu_totSM_H->GetBinError(22) ) 
	 );
 cout << outformat <<endl;
 
 float sumbkg_4e    = 
   f4e_ZZ->GetBinContent(22)+
   f4e_TTV->GetBinContent(22)+
   f4e_VVV->GetBinContent(22)+
   f4e_totSM_H->GetBinContent(22)+
   ZX_4e;

 float sumbkg_4e_err    = sqrt ( 
   f4e_ZZ->GetBinError(22)*f4e_ZZ->GetBinError(22)   +
   f4e_TTV->GetBinError(22)*f4e_TTV->GetBinError(22) +
   f4e_VVV->GetBinError(22)*f4e_VVV->GetBinError(22) +
   f4e_totSM_H->GetBinError(22)*f4e_totSM_H->GetBinError(22) +
   ZX_4e_err*ZX_4e_err);
 
 float sumbkg_4mu    = 
   f4mu_ZZ->GetBinContent(22)+
   f4mu_TTV->GetBinContent(22)+
   f4mu_VVV->GetBinContent(22)+
   f4mu_totSM_H->GetBinContent(22)+
   ZX_4mu;

 float sumbkg_4mu_err    = sqrt ( 
   f4mu_ZZ->GetBinError(22)*f4mu_ZZ->GetBinError(22)   +
   f4mu_TTV->GetBinError(22)*f4mu_TTV->GetBinError(22) +
   f4mu_VVV->GetBinError(22)*f4mu_VVV->GetBinError(22) +
   f4mu_totSM_H->GetBinError(22)*f4mu_totSM_H->GetBinError(22) +
   ZX_4mu_err*ZX_4mu_err);

 float sumbkg_2e2mu    = 
   f2e2mu_ZZ->GetBinContent(22)+
   f2e2mu_TTV->GetBinContent(22)+
   f2e2mu_VVV->GetBinContent(22)+
   f2e2mu_totSM_H->GetBinContent(22)+
   ZX_2e2mu;

 float sumbkg_2e2mu_err    = sqrt ( 
   f2e2mu_ZZ->GetBinError(22)*f2e2mu_ZZ->GetBinError(22)   +
   f2e2mu_TTV->GetBinError(22)*f2e2mu_TTV->GetBinError(22) +
   f2e2mu_VVV->GetBinError(22)*f2e2mu_VVV->GetBinError(22) +
   f2e2mu_totSM_H->GetBinError(22)*f2e2mu_totSM_H->GetBinError(22) +
   ZX_2e2mu_err*ZX_2e2mu_err);

 float sumbkg_4l=sumbkg_4e+sumbkg_4mu+sumbkg_2e2mu;
 float sumbkg_4l_err= sqrt (sumbkg_4e_err*sumbkg_4e_err+sumbkg_4mu_err*sumbkg_4mu_err+sumbkg_2e2mu_err*sumbkg_2e2mu_err);

 cout << "\\hline" << endl;
 sprintf(outformat,"Sum of bkgs & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 sumbkg_4e,    sumbkg_4e_err,
	 sumbkg_4mu,   sumbkg_4mu_err,
	 sumbkg_2e2mu, sumbkg_2e2mu_err, 
	 sumbkg_4l,sumbkg_4l_err	 
	 );
 cout << outformat <<endl;

 cout << "\\hline" << endl;
 sprintf(outformat,"Signal: ZpBaryonic ($m_{Z'}=500$ GeV, $m_\\chi=1$ GeV)  & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
  	 f4e_ZpBaryonic_MZp500_MChi1->GetBinContent(22), f4e_ZpBaryonic_MZp500_MChi1->GetBinError(22),
  	 f4mu_ZpBaryonic_MZp500_MChi1->GetBinContent(22), f4mu_ZpBaryonic_MZp500_MChi1->GetBinError(22),
  	 f2e2mu_ZpBaryonic_MZp500_MChi1->GetBinContent(22), f2e2mu_ZpBaryonic_MZp500_MChi1->GetBinError(22),
  	 f4e_ZpBaryonic_MZp500_MChi1->GetBinContent(22)+f4mu_ZpBaryonic_MZp500_MChi1->GetBinContent(22)+f2e2mu_ZpBaryonic_MZp500_MChi1->GetBinContent(22),
  	 sqrt(
	      f4e_ZpBaryonic_MZp500_MChi1->GetBinError(22)*f4e_ZpBaryonic_MZp500_MChi1->GetBinError(22)+
	      f4mu_ZpBaryonic_MZp500_MChi1->GetBinError(22)*f4mu_ZpBaryonic_MZp500_MChi1->GetBinError(22)+
	      f2e2mu_ZpBaryonic_MZp500_MChi1->GetBinError(22)*f2e2mu_ZpBaryonic_MZp500_MChi1->GetBinError(22)
	      )

  	 );
 cout << outformat <<endl;

 cout << "\\hline" << endl; 
 sprintf(outformat,"Observed & %d & %d & %d & %d \\\\",
	 int(f4e_totaldata->GetBinContent(22)),
	 int(f4mu_totaldata->GetBinContent(22)),
	 int(f2e2mu_totaldata->GetBinContent(22)),
	 int(f4e_totaldata->GetBinContent(22)+f4mu_totaldata->GetBinContent(22)+f2e2mu_totaldata->GetBinContent(22))
	 );
 cout << outformat <<endl;
 
 cout << "\\hline \\hline" << endl;
 cout << "\\end{tabular}" << endl;
 cout << "}" << endl;
 cout << "\\caption{Number of expected background and signal events and number of observed candidates, after pplying the full mono-Higgs selection; only statistical errors are quoted.}" << endl;

 cout << "\\label{tab:MonoHiggs_yields}" <<endl;	
 cout << "\\end{center}" << endl;
 cout << "\\end{table}" << endl;
 
}
