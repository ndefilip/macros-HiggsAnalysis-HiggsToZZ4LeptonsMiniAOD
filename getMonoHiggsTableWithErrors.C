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
 
 // Signal Z'-2HDM
 TH1D *f4mu_Zp2HDM_MZp1200_MA0300   = (TH1D*)f4mu->Get("nEvent_4l_w_monoH_MZP1200");
 TH1D *f4e_Zp2HDM_MZp1200_MA0300    = (TH1D*)f4e->Get("nEvent_4l_w_monoH_MZP1200");
 TH1D *f2e2mu_Zp2HDM_MZp1200_MA0300 = (TH1D*)f2e2mu->Get("nEvent_4l_w_monoH_MZP1200");

 // Signal Z' baryonic 
 TH1D *f4mu_ZpBaryonic_MZp500_MChi1   = (TH1D*)f4mu->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");
 TH1D *f4e_ZpBaryonic_MZp500_MChi1    = (TH1D*)f4e->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");
 TH1D *f2e2mu_ZpBaryonic_MZp500_MChi1 = (TH1D*)f2e2mu->Get("nEvent_4l_w_ZpBaryonic_MZp500_MChi1");

 // Data
 TH1D *f4mu_totaldata   = (TH1D*)f4mu->Get("nEvent_4l_w_data");
 TH1D *f4e_totaldata    = (TH1D*)f4e->Get("nEvent_4l_w_data");
 TH1D *f2e2mu_totaldata = (TH1D*)f2e2mu->Get("nEvent_4l_w_data");

 ofstream output_file;
 output_file.open("MonoHiggsTableWithErrors.tex");

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

 sprintf(outformat,"$Z\\gamma*, ZZ$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_ZZ->GetBinContent(22), f4e_ZZ->GetBinError(22),
	 f4mu_ZZ->GetBinContent(22), f4mu_ZZ->GetBinError(22),
	 f2e2mu_ZZ->GetBinContent(22), f2e2mu_ZZ->GetBinError(22),
	 f4e_ZZ->GetBinContent(22)+f4mu_ZZ->GetBinContent(22)+f2e2mu_ZZ->GetBinContent(22),
	 sqrt(f4e_ZZ->GetBinError(22)*f4e_ZZ->GetBinError(22) + f4mu_ZZ->GetBinError(22)*f4mu_ZZ->GetBinError(22) + f2e2mu_ZZ->GetBinError(22)*f2e2mu_ZZ->GetBinError(22) ) 
	 );
 output_file << outformat <<endl;

 sprintf(outformat,"$t \\bar{t} V$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_TTV->GetBinContent(22), f4e_TTV->GetBinError(22),
	 f4mu_TTV->GetBinContent(22), f4mu_TTV->GetBinError(22),
	 f2e2mu_TTV->GetBinContent(22), f2e2mu_TTV->GetBinError(22),
	 f4e_TTV->GetBinContent(22)+f4mu_TTV->GetBinContent(22)+f2e2mu_TTV->GetBinContent(22),
	 sqrt(f4e_TTV->GetBinError(22)*f4e_TTV->GetBinError(22) + f4mu_TTV->GetBinError(22)*f4mu_TTV->GetBinError(22) + f2e2mu_TTV->GetBinError(22)*f2e2mu_TTV->GetBinError(22) ) 
	 );
 output_file << outformat <<endl;

 sprintf(outformat,"$VVV$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_VVV->GetBinContent(22), f4e_VVV->GetBinError(22),
	 f4mu_VVV->GetBinContent(22), f4mu_VVV->GetBinError(22),
	 f2e2mu_VVV->GetBinContent(22), f2e2mu_VVV->GetBinError(22),
	 f4e_VVV->GetBinContent(22)+f4mu_VVV->GetBinContent(22)+f2e2mu_VVV->GetBinContent(22),
	 sqrt(f4e_VVV->GetBinError(22)*f4e_VVV->GetBinError(22) + f4mu_VVV->GetBinError(22)*f4mu_VVV->GetBinError(22) + f2e2mu_VVV->GetBinError(22)*f2e2mu_VVV->GetBinError(22) ) 
	 );
 output_file << outformat <<endl;

 
 float ZX_4e=2.99;    
 float ZX_4e_err=2.18;// float ZX_4e_err=ZX_4e*0.43;
 float ZX_4mu=4.67;   
 float ZX_4mu_err=2.72;// float ZX_4mu_err=ZX_4mu*0.36;
 float ZX_2e2mu=8.54; 
 float ZX_2e2mu_err=3.59;// float ZX_2e2mu_err=ZX_2e2mu*0.40;

 sprintf(outformat,"$Z+X$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\",
	 ZX_4e, ZX_4e_err,
	 ZX_4mu, ZX_4mu_err,
	 ZX_2e2mu, ZX_2e2mu_err,
	 ZX_4e+ZX_4mu+ZX_2e2mu, sqrt( ZX_4e_err*ZX_4e_err+ZX_4mu_err*ZX_4mu_err+ZX_2e2mu_err*ZX_2e2mu_err)
	 );
 output_file << outformat <<endl;
 
 sprintf(outformat,"SM Higgs ($m_{H}=125$ GeV)) & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 f4e_totSM_H->GetBinContent(22), f4e_totSM_H->GetBinError(22),
	 f4mu_totSM_H->GetBinContent(22), f4mu_totSM_H->GetBinError(22),
	 f2e2mu_totSM_H->GetBinContent(22), f2e2mu_totSM_H->GetBinError(22),
	 f4e_totSM_H->GetBinContent(22)+f4mu_totSM_H->GetBinContent(22)+f2e2mu_totSM_H->GetBinContent(22),
	 sqrt(f4e_totSM_H->GetBinError(22)*f4e_totSM_H->GetBinError(22) + f4mu_totSM_H->GetBinError(22)*f4mu_totSM_H->GetBinError(22) + f2e2mu_totSM_H->GetBinError(22)*f2e2mu_totSM_H->GetBinError(22) ) 
	 );
 output_file << outformat <<endl;
 
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

 output_file << "\\hline" << endl;
 sprintf(outformat,"Sum of bkgs & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
	 sumbkg_4e,    sumbkg_4e_err,
	 sumbkg_4mu,   sumbkg_4mu_err,
	 sumbkg_2e2mu, sumbkg_2e2mu_err, 
	 sumbkg_4l,sumbkg_4l_err	 
	 );
 output_file << outformat <<endl;

 output_file << "\\hline" << endl;
 sprintf(outformat,"Signal: Z'-2HDM ($m_{Z'}=1200$ GeV, $m_{A_{0}}=300$ GeV)  & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
         f4e_Zp2HDM_MZp1200_MA0300->GetBinContent(22), f4e_Zp2HDM_MZp1200_MA0300->GetBinError(22),
         f4mu_Zp2HDM_MZp1200_MA0300->GetBinContent(22), f4mu_Zp2HDM_MZp1200_MA0300->GetBinError(22),
         f2e2mu_Zp2HDM_MZp1200_MA0300->GetBinContent(22), f2e2mu_Zp2HDM_MZp1200_MA0300->GetBinError(22),
         f4e_Zp2HDM_MZp1200_MA0300->GetBinContent(22)+f4mu_Zp2HDM_MZp1200_MA0300->GetBinContent(22)+f2e2mu_Zp2HDM_MZp1200_MA0300->GetBinContent(22),
         sqrt(
              f4e_Zp2HDM_MZp1200_MA0300->GetBinError(22)*f4e_Zp2HDM_MZp1200_MA0300->GetBinError(22)+
              f4mu_Zp2HDM_MZp1200_MA0300->GetBinError(22)*f4mu_Zp2HDM_MZp1200_MA0300->GetBinError(22)+
              f2e2mu_Zp2HDM_MZp1200_MA0300->GetBinError(22)*f2e2mu_Zp2HDM_MZp1200_MA0300->GetBinError(22)
              )

         );
 output_file << outformat <<endl;
 //output_file << "\\hline" << endl;

 sprintf(outformat,"Signal: Z'-Baryonic ($m_{Z'_{B}}=500$ GeV, $m_\\chi=1$ GeV)  & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  & %.2f $\\pm$ %.2f \\\\",
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
 output_file << outformat <<endl;

 output_file << "\\hline" << endl; 
 sprintf(outformat,"Observed & %d & %d & %d & %d \\\\",
	 int(f4e_totaldata->GetBinContent(22)),
	 int(f4mu_totaldata->GetBinContent(22)),
	 int(f2e2mu_totaldata->GetBinContent(22)),
	 int(f4e_totaldata->GetBinContent(22)+f4mu_totaldata->GetBinContent(22)+f2e2mu_totaldata->GetBinContent(22))
	 );
 output_file << outformat <<endl;
 
 output_file << "\\hline \\hline" << endl;
 output_file << "\\end{tabular}" << endl;
 output_file << "}" << endl;
 output_file << "\\caption{Number of expected background and signal events and number of observed candidates, after pplying the full mono-Higgs selection; only statistical errors are quoted.}" << endl;

 output_file << "\\label{tab:MonoHiggs_yields}" <<endl;	
 output_file << "\\end{center}" << endl;
 output_file << "\\end{table}" << endl;

 output_file << "\\end{document}" << endl;

 output_file.close();

 system("pdflatex MonoHiggsTableWithErrors.tex");
 system("pdftopng MonoHiggsTableWithErrors.pdf MonoHiggsTableWithErrors");
 
}
