
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

 ofstream output_file;
 output_file.open("SMHiggsTableWithErrors.tex");


 output_file << "\\documentclass[a4paper,10pt]{article}" << endl;
 output_file << "\\usepackage[pdftex]{graphicx}" << endl;
 output_file << "\\usepackage{caption}" << endl;
 output_file << "\\usepackage{amsmath}" << endl;
 output_file << "\\usepackage{multirow}" << endl;
 
 output_file << "\\begin{document} " << endl;

 output_file << "\\begin{table}[htbH]" << endl;
 output_file << "\\begin{center}" << endl;
 output_file << "\\resizebox{\\textwidth}{!}{% " << endl;
 output_file << "\\begin{tabular}{l|c|c|c|c}" << endl;
 output_file << "\\hline \\hline" << endl;
 output_file << "{\\textbf{Channel}} & {\\textbf{$4e$}} & {\\textbf{$4\\mu$}} & {\\textbf{$2e2\\mu$}} & {\\textbf{$4l$}} \\\\ " << endl;
 output_file << "\\hline" << endl;

 Char_t outformat[20000];

 sprintf(outformat,"$q \\bar{q}\\rightarrow ZZ$ & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
	 f4e_qqZZ->GetBinContent(15), f4e_qqZZ->GetBinError(15),
	 f4mu_qqZZ->GetBinContent(15), f4mu_qqZZ->GetBinError(15),
	 f2e2mu_qqZZ->GetBinContent(15), f2e2mu_qqZZ->GetBinError(15),
	 f4e_qqZZ->GetBinContent(15)+f4mu_qqZZ->GetBinContent(15)+f2e2mu_qqZZ->GetBinContent(15),
	 sqrt(f4e_qqZZ->GetBinError(15)*f4e_qqZZ->GetBinError(15) + f4mu_qqZZ->GetBinError(15)*f4mu_qqZZ->GetBinError(15) + f2e2mu_qqZZ->GetBinError(15)*f2e2mu_qqZZ->GetBinError(15) ) 
	 );
 output_file << outformat <<endl;
 
 sprintf(outformat,"$gg\\rightarrow ZZ$ & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
	 f4e_ggZZ->GetBinContent(15), f4e_ggZZ->GetBinError(15),
	 f4mu_ggZZ->GetBinContent(15), f4mu_ggZZ->GetBinError(15),
	 f2e2mu_ggZZ->GetBinContent(15), f2e2mu_ggZZ->GetBinError(15),
	 f4e_ggZZ->GetBinContent(15)+f4mu_ggZZ->GetBinContent(15)+f2e2mu_ggZZ->GetBinContent(15),
	 sqrt(f4e_ggZZ->GetBinError(15)*f4e_ggZZ->GetBinError(15) + f4mu_ggZZ->GetBinError(15)*f4mu_ggZZ->GetBinError(15) + f2e2mu_ggZZ->GetBinError(15)*f2e2mu_ggZZ->GetBinError(15) ) 
	 );
 output_file << outformat <<endl;

 float ZX_4e=28.59;
 float ZX_4e_err=12.39; // float ZX_4e_err=ZX_4e*0.43;
 float ZX_4mu=29.88;
 float ZX_4mu_err=10.84; // float ZX_4mu_err=ZX_4mu*0.36;
 float ZX_2e2mu=61.32;
 float ZX_2e2mu_err=17.84; // float ZX_2e2mu_err=ZX_2e2mu*0.40;


 //output_file << "ZZ 4e" << f4e_ZZ->GetBinContent(15) << " " << f4e_ZZ->GetBinError(15) << endl;
 float sumbkg_4e    = f4e_ZZ->GetBinContent(15)+ZX_4e;  float sumbkg_4e_err=sqrt(f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err);
 float sumbkg_4mu   = f4mu_ZZ->GetBinContent(15)+ZX_4mu; float sumbkg_4mu_err=sqrt(f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err);
 float sumbkg_2e2mu = f2e2mu_ZZ->GetBinContent(15)+ZX_2e2mu; float sumbkg_2e2mu_err=sqrt(f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err);
 float sumbkg_4l    = sumbkg_4e+sumbkg_4mu+sumbkg_2e2mu;  
 float sumbkg_4l_err=sqrt(
	      (f4e_ZZ->GetBinError(15)*f4e_ZZ->GetBinError(15)+ZX_4e_err*ZX_4e_err)+
	      (f4mu_ZZ->GetBinError(15)*f4mu_ZZ->GetBinError(15)+ZX_4mu_err*ZX_4mu_err)+
	      (f2e2mu_ZZ->GetBinError(15)*f2e2mu_ZZ->GetBinError(15)+ZX_2e2mu_err*ZX_2e2mu_err)
			  );

 sprintf(outformat,"$Z+X$ & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f \\\\",
	 ZX_4e, ZX_4e_err,
	 ZX_4mu, ZX_4mu_err,
	 ZX_2e2mu, ZX_2e2mu_err,
	 ZX_4e+ZX_4mu+ZX_2e2mu, sqrt( ZX_4e_err*ZX_4e_err+ZX_4mu_err*ZX_4mu_err+ZX_2e2mu_err*ZX_2e2mu_err)
	 );
 output_file << outformat <<endl;

 // sprintf(outformat,"Sum of bkgs & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
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
 // output_file << outformat <<endl;

 sprintf(outformat,"Sum of bkgs & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
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
 output_file << outformat <<endl;

 sprintf(outformat,"SM Higgs ($m_{H}=125$ GeV)) & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
	 f4e_totSM_H->GetBinContent(15), f4e_totSM_H->GetBinError(15),
	 f4mu_totSM_H->GetBinContent(15), f4mu_totSM_H->GetBinError(15),
	 f2e2mu_totSM_H->GetBinContent(15), f2e2mu_totSM_H->GetBinError(15),
	 f4e_totSM_H->GetBinContent(15)+f4mu_totSM_H->GetBinContent(15)+f2e2mu_totSM_H->GetBinContent(15),
	 sqrt(f4e_totSM_H->GetBinError(15)*f4e_totSM_H->GetBinError(15) + f4mu_totSM_H->GetBinError(15)*f4mu_totSM_H->GetBinError(15) + f2e2mu_totSM_H->GetBinError(15)*f2e2mu_totSM_H->GetBinError(15) ) 
	 );
 output_file << outformat <<endl;

 float H_sumbkg_4e    = sumbkg_4e+f4e_totSM_H->GetBinContent(15);
 float H_sumbkg_4mu   = sumbkg_4mu+f4mu_totSM_H->GetBinContent(15);
 float H_sumbkg_2e2mu = sumbkg_2e2mu+f2e2mu_totSM_H->GetBinContent(15);
 float H_sumbkg_4l    = H_sumbkg_4e+H_sumbkg_4mu+H_sumbkg_2e2mu;

 output_file << "\\hline " << endl;
 sprintf(outformat,"Total expected & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f  & %.1f $\\pm$ %.1f \\\\",
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
 output_file << outformat <<endl;

 output_file << "\\hline" << endl; 
 sprintf(outformat,"Observed & %d & %d & %d & %d \\\\",
	 int(f4e_totaldata->GetBinContent(15)),
	 int(f4mu_totaldata->GetBinContent(15)),
	 int(f2e2mu_totaldata->GetBinContent(15)),
	 int(f4e_totaldata->GetBinContent(15)+f4mu_totaldata->GetBinContent(15)+f2e2mu_totaldata->GetBinContent(15))
	 );
 output_file << outformat <<endl;
 
 output_file << "\\hline \\hline" << endl;
 output_file << "\\end{tabular}" << endl;
 output_file << "}" << endl;
 output_file << "\\caption{Number of estimated background and signal events and number of observed candidates, after the SM Higgs selection, in the mass range $m_{4l}>$ 70 GeV. SM Higgs signal and ZZ background are estimated from Monte Carlo simulation, while Z+X is estimated from data; only statistical errors are quoted.}" << endl;

 output_file << "\\label{tab:SMHiggs_yields}" <<endl;	
 output_file << "\\end{center}" << endl;
 output_file << "\\end{table}" << endl;

 output_file << "\\end{document}" << endl;

 output_file.close();

 system("pdflatex SMHiggsTableWithErrors.tex");
 system("pdftopng SMHiggsTableWithErrors.pdf SMHiggsTableWithErrors");
}
