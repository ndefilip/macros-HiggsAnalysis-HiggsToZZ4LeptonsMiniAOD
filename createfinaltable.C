{

  float yields4mu7TeV[9],yields4e7TeV[9],yields2e2mu7TeV[9];
  float eryields4mu7TeV[9],eryields4e7TeV[9],eryields2e2mu7TeV[9];
  float yields4mu8TeV[9],yields4e8TeV[9],yields2e2mu8TeV[9];
  float eryields4mu8TeV[9],eryields4e8TeV[9],eryields2e2mu8TeV[9];
  string process;

  vector<std::string> yieldslist7TeV,yieldslist8TeV;
  yieldslist7TeV.push_back("plots/yields_4#mu_7TeV.txt");
  yieldslist7TeV.push_back("plots/yields_4e_7TeV.txt");
  yieldslist7TeV.push_back("plots/yields_2e2#mu_7TeV.txt");

  yieldslist8TeV.push_back("plots/yields_4#mu_8TeV.txt");
  yieldslist8TeV.push_back("plots/yields_4e_8TeV.txt");
  yieldslist8TeV.push_back("plots/yields_2e2#mu_8TeV.txt");

  for (vector<string>::iterator i=yieldslist7TeV.begin();i<yieldslist7TeV.end();i++){
    cout <<"Reading file " << i->c_str() << endl;
    std::ifstream ifs(i->c_str());
    int j=0;
    while( ifs.good() && j<9) {
      if (i==yieldslist7TeV.begin()) {
	ifs >> process >> yields4mu7TeV[j] >> process >> eryields4mu7TeV[j];
	cout << "Reading " << j << " " << yields4mu7TeV[j]  << " " << eryields4mu7TeV[j] <<endl;
      }
      else if (i==yieldslist7TeV.end()-1) {
	ifs >> process >> yields2e2mu7TeV[j] >> process >> eryields2e2mu7TeV[j];
	cout << "Reading " << j << " " << yields2e2mu7TeV[j]  << " " << eryields2e2mu7TeV[j] <<endl;
      }
      else {
	ifs >> process >> yields4e7TeV[j] >> process >> eryields4e7TeV[j];
	cout << "Reading " << j << " " << yields4e7TeV[j]  << " " << eryields4e7TeV[j] <<endl;
      }
      j++;
    }
  }

  cout << "Yields: " << yields4mu7TeV[0] << " " << yields4e7TeV[0] << " " << yields2e2mu7TeV[0] << endl;

  for (vector<string>::iterator i=yieldslist8TeV.begin();i<yieldslist8TeV.end();i++){
    cout <<"Reading file " << i->c_str() << endl;
    std::ifstream ifs(i->c_str());
    int j=0;
    while( ifs.good() && j<9) {
      if (i==yieldslist8TeV.begin()) {
        ifs >> process >> yields4mu8TeV[j] >> process >> eryields4mu8TeV[j];
        cout << "Reading " << j << " " << yields4mu8TeV[j]  << " " << eryields4mu8TeV[j] <<endl;
      }
      else if (i==yieldslist8TeV.end()-1) {
	ifs >> process >> yields2e2mu8TeV[j] >> process >> eryields2e2mu8TeV[j];
	cout << "Reading " << j << " " << yields2e2mu8TeV[j]  << " " << eryields2e2mu8TeV[j] <<endl;
      }
      else {
	ifs >> process >> yields4e8TeV[j] >> process >> eryields4e8TeV[j];
	cout << "Reading " << j << " " << yields4e8TeV[j]  << " " << eryields4e8TeV[j] <<endl;
      }
      j++;
    }
  }
  cout << "Yields: " << yields4mu8TeV[0] << " " << yields4e8TeV[0] << " " << yields2e2mu8TeV[0] << endl;

  float yields4muRunI[9],yields4eRunI[9],yields2e2muRunI[9];
  float eryields4muRunI[9],eryields4eRunI[9],eryields2e2muRunI[9];

  for (int ii=0;ii<9;ii++){
    yields4muRunI[ii]=yields4mu7TeV[ii]+yields4mu8TeV[ii];
    yields4eRunI[ii]=yields4e7TeV[ii]+yields4e8TeV[ii];
    yields2e2muRunI[ii]=yields2e2mu7TeV[ii]+yields2e2mu8TeV[ii];

    eryields4muRunI[ii]=sqrt(pow(eryields4mu7TeV[ii],2)+pow(eryields4mu8TeV[ii],2));
    eryields4eRunI[ii]=sqrt(pow(eryields4e7TeV[ii],2)+pow(eryields4e8TeV[ii],2));
    eryields2e2muRunI[ii]=sqrt(pow(eryields2e2mu7TeV[ii],2)+pow(eryields2e2mu8TeV[ii],2));
  }


  Char_t tableOUT[500];
  sprintf(tableOUT,"finaltable_m4l_100_1000_RunI.tex");
  cout << "Opening a table file " << tableOUT << endl;
  ofstream output;
  output.open(tableOUT);

  char outputstring[20000];

  output << "\\documentclass[a4paper,10pt]{article}" << endl;
  output << "\\usepackage[pdftex]{graphicx}" << endl;
  output << "\\usepackage{caption}" << endl;
  output << "\\usepackage{amsmath}" << endl;
  output << "\\usepackage{multirow}" << endl;
  output << " " << endl;    
  output << "\\begin{document}" << endl;
  output << " " << endl;
  output << "\\begin{table}" << endl;
  output << "\\caption{The number of estimated background and signal events and number of observed candidates, after final inclusive selection, in the full measurement range 100 $< \\, m_{4l} \\, <$ 1000 GeV. Signal and ZZ background are estimated from Monte Carlo simulation, while Z+X is estimated from data}" << endl;

  output << "\\begin{center}" << endl;
  output << "\\label{tab:EventYields}" << endl;
  output << "\\begin{tabular}{l|c|c|c}" << endl;
  output << "\\hline \\hline" << endl;
  output << "{\\textbf{Channel}} & {\\textbf{$4e$}} & {\\textbf{$4\\mu$}} & {\\textbf{$2e2\\mu$}} \\\\ " << endl;
  output << "\\hline \\hline" << endl;

  // 7 TeV
  output << "\\multicolumn{4}{c}{$\\mathrm{5.05 \\, fb^{-1} \\, @ \\, 7 \\, TeV}$}  \\\\ " << endl;
  output << "\\hline" << endl;

  sprintf(outputstring,"ZZ background & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
	  yields4e7TeV[2], eryields4e7TeV[2],
	  yields4mu7TeV[2], eryields4mu7TeV[2],
	  yields2e2mu7TeV[2], eryields2e2mu7TeV[2]);
  output << outputstring << endl;


  sprintf(outputstring,"Z + X & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e7TeV[1], eryields4e7TeV[1],
          yields4mu7TeV[1], eryields4mu7TeV[1],
          yields2e2mu7TeV[1], eryields2e2mu7TeV[1]);
  output << outputstring << endl;


  output << "\\hline" << endl;

  sprintf(outputstring,"All background expected & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e7TeV[2] +yields4e7TeV[1], sqrt(pow(eryields4e7TeV[1],2)+pow(eryields4e7TeV[2],2)),
          yields4mu7TeV[2]+yields4mu7TeV[1], sqrt(pow(eryields4mu7TeV[1],2)+pow(eryields4mu7TeV[2],2)),
          yields2e2mu7TeV[2]+yields2e2mu7TeV[1], sqrt(pow(eryields2e2mu7TeV[1],2)+pow(eryields2e2mu7TeV[2],2))
          );
  output << outputstring << endl;


  output << "\\hline" << endl;

  sprintf(outputstring,"$m_H$ = 500 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e7TeV[7], eryields4e7TeV[7],
          yields4mu7TeV[7], eryields4mu7TeV[7],
          yields2e2mu7TeV[7], eryields2e2mu7TeV[7]);
  output << outputstring << endl;

  sprintf(outputstring,"$m_H$ = 800 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e7TeV[8], eryields4e7TeV[8],
          yields4mu7TeV[8], eryields4mu7TeV[8],
          yields2e2mu7TeV[8], eryields2e2mu7TeV[8]);
  output << outputstring << endl;

  output << "\\hline" << endl;
  sprintf(outputstring,"Observed & %f & %f & %f \\\\",yields4e7TeV[0],yields4mu7TeV[0],yields2e2mu7TeV[0]);
  output << outputstring << endl;
  output << "\\hline \\hline" << endl;

  // 8 TeV
  output << "\\multicolumn{4}{c}{$\\mathrm{19.71 \\, fb^{-1} \\, @ \\, 8 \\, TeV}$}  \\\\ " << endl;
  output << "\\hline" << endl;

  sprintf(outputstring,"ZZ background & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e8TeV[2], eryields4e8TeV[2],
          yields4mu8TeV[2], eryields4mu8TeV[2],
          yields2e2mu8TeV[2], eryields2e2mu8TeV[2]);
  output << outputstring << endl;

  sprintf(outputstring,"Z + X & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e8TeV[1], eryields4e8TeV[1],
          yields4mu8TeV[1], eryields4mu8TeV[1],
          yields2e2mu8TeV[1], eryields2e2mu8TeV[1]);
  output << outputstring << endl;

  output << "\\hline" << endl;

  sprintf(outputstring,"All background expected & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e8TeV[2]  + yields4e8TeV[1], sqrt(pow(eryields4e8TeV[1],2)+pow(eryields4e8TeV[2],2)),
          yields4mu8TeV[2] + yields4mu8TeV[1], sqrt(pow(eryields4mu8TeV[1],2)+pow(eryields4mu8TeV[2],2)),
          yields2e2mu8TeV[2] + yields2e2mu8TeV[1], sqrt(pow(eryields2e2mu8TeV[1],2)+pow(eryields2e2mu8TeV[2],2))
	  );
  output << outputstring << endl;

  output << "\\hline" << endl;

  sprintf(outputstring,"$m_H$ = 500 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e8TeV[7], eryields4e8TeV[7],
          yields4mu8TeV[7], eryields4mu8TeV[7],
          yields2e2mu8TeV[7], eryields2e2mu8TeV[7]);
  output << outputstring << endl;

  sprintf(outputstring,"$m_H$ = 800 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4e8TeV[8], eryields4e8TeV[8],
          yields4mu8TeV[8], eryields4mu8TeV[8],
          yields2e2mu8TeV[8], eryields2e2mu8TeV[8]);
  output << outputstring << endl;


  output << "\\hline" << endl;
  sprintf(outputstring,"Observed & %f & %f & %f \\\\",yields4e8TeV[0],yields4mu8TeV[0],yields2e2mu8TeV[0]);
  output << outputstring << endl;
  output << "\\hline \\hline" << endl;

  // 7 + 8 TeV
  output << "\\multicolumn{4}{c}{$\\mathrm{5.05 \\, fb^{-1} \\, @ \\, 7 \\, TeV}$ and $\\mathrm{19.71 \\, fb^{-1} \\, @ \\, 8 \\, TeV}$}  \\\\" << endl;
  output << "\\hline" << endl;

  sprintf(outputstring,"ZZ background & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4eRunI[2], eryields4eRunI[2],
          yields4muRunI[2], eryields4muRunI[2],
          yields2e2muRunI[2], eryields2e2muRunI[2]);
  output << outputstring << endl;

  sprintf(outputstring,"Z + X & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4eRunI[1], eryields4eRunI[1],
          yields4muRunI[1], eryields4muRunI[1],
          yields2e2muRunI[1], eryields2e2muRunI[1]);
  output << outputstring << endl;


  output << "\\hline" << endl;

  sprintf(outputstring,"All background expected & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4eRunI[2]  + yields4eRunI[1], sqrt(pow(eryields4eRunI[1],2)+pow(eryields4eRunI[2],2)),
          yields4muRunI[2] + yields4muRunI[1], sqrt(pow(eryields4muRunI[1],2)+pow(eryields4muRunI[2],2)),
          yields2e2muRunI[2] + yields2e2muRunI[1], sqrt(pow(eryields2e2muRunI[1],2)+pow(eryields2e2muRunI[2],2))
          );
  output << outputstring << endl;


  output << "\\hline" << endl;

  sprintf(outputstring,"$m_H$ = 500 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4eRunI[7], eryields4eRunI[7],
          yields4muRunI[7], eryields4muRunI[7],
          yields2e2muRunI[7], eryields2e2muRunI[7]);
  output << outputstring << endl;

  sprintf(outputstring,"$m_H$ = 800 GeV & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f \\\\",
          yields4eRunI[8], eryields4eRunI[8],
          yields4muRunI[8], eryields4muRunI[8],
          yields2e2muRunI[8], eryields2e2muRunI[8]);
  output << outputstring << endl;

  output << "\\hline" << endl;

  sprintf(outputstring,"Observed & %f & %f & %f \\\\",yields4eRunI[0],yields4muRunI[0],yields2e2muRunI[0]); 
  output << outputstring << endl;

  output << "\\hline \\hline" << endl;
  output << "\\end{tabular}" << endl;
  output << "\\end{center}" << endl;
  output << "\\end{table}" << endl;
  output << "%============" << endl;
  
  output << " " <<endl;
  output << "\\end{document}" << endl;

  output.close();


}
