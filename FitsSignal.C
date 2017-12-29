
//   gSystem->Load("libMinuit");
//   gSystem->Load("libRooFit");
  using namespace RooFit ;

// #include "TROOT.h"
// #include "TSystem.h"
// #include "TStyle.h"
// #include "TH1F.h"
// #include "TAxis.h"
// #include "TFile.h"
// #include "TTree.h"
// #include "TCanvas.h"
// #include "TPad.h"
// #include "TLine.h"
// #include "TObjArray.h"
// #include "TBranch.h"
// #include "TGraph.h"
// #include "TLatex.h"
// #include "TF1.h"
// #include "TH2D.h"
// #include "TLegend.h"

// // RooFit includes
// #include "RooRealVar.h"
// #include "RooArgSet.h"
// #include "RooArgList.h"
// #include "RooWorkspace.h"
// #include "RooAbsReal.h"
// #include "RooFitResult.h"
// #include "RooDataSet.h"
// #include "RooDataHist.h"
// #include "RooFFTConvPdf.h"
// #include "RooDataSet.h"
// #include "RooCBShape.h"
// #include "RooPlot.h"
#include "../VecbosApp/VecbosApp2/Math/src/HistogramTools.cc"
//#include "../VecbosApp/VecbosApp2/Math/include/HistogramTools.hh"

using namespace RooFit;
using namespace math;

void FitsSignal(std::string conf, int channel, std::string whichenergy);

void FitsSignal(std::string conf, int channel, std::string whichenergy){
    gSystem->Load("/cmshome/nicola/upgrade/CMSSW_6_1_1/lib/slc5_amd64_gcc472/libHiggsAnalysisCombinedLimit.so");
    gSystem->SetIncludePath("-I/cmshome/nicola/upgrade/VecbosApp/VecbosApp2/Math/include/");
    
    TPaveText *ll = new TPaveText(0.15, 0.95, 0.95, 0.99, "NDC");
    ll->SetTextSize(0.04);
    ll->SetTextFont(42);
    ll->SetFillColor(0);
    ll->SetBorderSize(0);
    ll->SetMargin(0.01);
    ll->SetTextAlign(12); // align left
    TString text = "CMS Simulation 2014";
    //TString text = "CMS";
    ll->AddText(0.01,0.6,text);
    cout << "Energy= " << whichenergy << endl;
    if (whichenergy.find("PhaseII")<100) {
      text = "#sqrt{s} = 14 TeV, Phase II - PU = 140" ;
      ll->AddText(0.5, 0.6, text);
    }
    else if (whichenergy.find("PhaseI")<100) {
      if (!(whichenergy.find("age1k")<100)) text = "#sqrt{s} = 14 TeV, Phase I - PU = 50";
      else text = "#sqrt{s} = 14 TeV, Phase I aged - PU = 140";
      ll->AddText(0.5, 0.6, text);
    }
    

    TString schannel;
    if      (channel == 1) schannel = "4mu";
    else if (channel == 2) schannel = "4e";
    else if (channel == 3) schannel = "2e2mu";
    else cout << "Not a valid channel: " << schannel << endl;

    cout << "schannel = " << schannel << endl;
    
    TFile *f;
    char filename[500];
    TString PUstring;
    if (whichenergy.find("PhaseII") < 100) PUstring="PU140";
    else if (whichenergy.find("PhaseI") < 100){
      if (! (whichenergy.find("age1k")<100)) PUstring="PU50";
      else PUstring="PU140";
    }

    //sprintf(filename,"%s_MassInV_H_%s_%s_%s.histo",conf.c_str(),schannel.Data(),PUstring.Data(),whichenergy.c_str());
    if (conf.find("Delphes")<20) sprintf(filename,"new/%s_MassInV_H_%s_%s_%s_muPOGeff_ptmin04.histo",conf.c_str(),schannel.Data(),whichenergy.c_str(),PUstring.Data());
    if (conf.find("FullSim")<20) {
      if (whichenergy.find("PhaseI") < 100 || whichenergy.find("Phase2") < 100) {
	if (whichenergy.find("ISO1") < 100 && channel==2) {
	  PUstring="PU140_ISO1_IP15";
	  whichenergy="PhaseI_age1k";
	}
	//sprintf(filename,"new/%s_MassInV_H_%s_%s_%s.histo",conf.c_str(),schannel.Data(),whichenergy.c_str(),PUstring.Data());    
	sprintf(filename,"/lustre/cms/store/user/defilip/HiggsAnalysisUpgrade/91X_LooseID/histos4mu_25ns/output_GluGluHToZZTo4L_M125_14TeV_powheg2_JHUgenV702_pythia8_PU200_miniAOD_puppi.root");
      }
    }
    
    cout << "Opening file= " << filename << endl;
    f = new TFile(filename);
    //TH1F *hh = (TH1F*)f->Get("HmassFit_notnorm");
    TH1F *hh = (TH1F*)f->Get("hM4l_7");
    if ( schannel=="4e"){
      if (!(whichenergy.find("age1k")<100)) hh->Rebin(8);
      else hh->Rebin(8);
    }
    
    if ( schannel=="4mu" || schannel=="2e2mu") hh->Rebin(2);

    double lowM,highM;
    if ( schannel=="4mu") {
      lowM=119.;
      highM=129.;
    }
    else if ( schannel=="4e") {
      lowM=110.5;
      highM=135.5;
    }
    else if ( schannel=="2e2mu"){
      lowM=114.;
      //lowM=116.;
      highM=133.5;
    }
    cout << "Ranges for the fit= " << schannel.Data() << " " << lowM << " " << highM << endl;
    RooRealVar f_mass4l("f_mass4l","f_mass4l",lowM,highM);    
    RooDataHist* hist = new RooDataHist("hist","hist",f_mass4l,Import(*hh)) ;
    hist->Print();

    
            
    //Theoretical signal model
    double masses[2]={125};
    RooRealVar MHStar("MHStar","MHStar",masses[0],0.,2000.);
    //MHStar.setConstant(true);
    RooRealVar Gamma_TOT("Gamma_TOT","Gamma_TOT",3,0.,700.);
    Gamma_TOT.setConstant(true);
    RooRealVar one("one","one",1.0);
    //one.setConstant(kTRUE);
    
    RooGenericPdf SignalTheor("SignalTheor","(@0)/( pow(pow(@0,2)-pow(@1,2),2) + pow(@0,2)*pow(@2,2) )",RooArgSet(f_mass4l,MHStar,Gamma_TOT));
    RooRelBWUFParam SignalTheorLM("signalTheorLM","signalTheorLM",f_mass4l,MHStar,Gamma_TOT);
    
    //Experimental resolution
    RooRealVar meanCB("meanCB","meanCB",0.,-25.,25.);
    RooRealVar sigmaCB("sigmaCB","sigmaCB",1.,0.,5.);
    RooRealVar sigmaCB_high("sigmaCB_high","sigmaCB_high",5.,0.,150.);
    RooRealVar alphaCB_1("alphaCB_1","alphaCB_1",2.,0.,50.);
    RooRealVar nCB_1("nCB_1","nCB_1",2.,-20.,20.);
    RooRealVar alphaCB_2("alphaCB_2","alphaCB_2",2.,0.,100.);
    RooRealVar nCB_2("nCB_2","nCB_2",2.,0.,10.);
    //nCB_2.setConstant(kTRUE);
    
    //Initialize to decent values
    float m = masses[0];
    sigmaCB.setVal(-4.56178+0.123209*m-0.00107193*m*m+4.5413e-06*m*m*m-8.19429e-09*m*m*m*m+4.75955e-12*m*m*m*m*m);
    
    RooDoubleCB massRes("massRes","Double Crystal Ball",f_mass4l,meanCB,sigmaCB,alphaCB_1,nCB_1,alphaCB_2,nCB_2);
    RooDoubleCB massResH("massResH","DCB Highmass",f_mass4l,meanCB,sigmaCB_high,alphaCB_1,nCB_1,alphaCB_2,nCB_2);
    
    //Convolute theoretical shape and resolution
    RooFFTConvPdf *sigPDF;
    sigPDF = new RooFFTConvPdf("sigPDF","sigPDF",f_mass4l,SignalTheorLM,massRes);
    sigPDF->setBufferFraction(0.2);
    
    RooPlot *xplot = f_mass4l.frame();
    xplot->SetTitle("");
    if (channel==1) xplot->SetXTitle("m_{4#mu} (GeV/c^{2})");
    if (channel==2) xplot->SetXTitle("m_{4e} (GeV/c^{2})");
    if (channel==3) xplot->SetXTitle("m_{2e2#mu} (GeV/c^{2})");
    
    TCanvas *canv = new TCanvas("canv","canv",1200,800);
    
    TLegend *leg0 = new TLegend(0.12,0.70,0.25,0.8,NULL,"brNDC");
    leg0->SetTextSize(0.03);
    leg0->SetLineColor(0);
    leg0->SetLineWidth(1);
    leg0->SetFillColor(kWhite);
    leg0->SetBorderSize(0);
    
    double mass,mean,sigma,a1,n1,a2,n2;
    TH1F* parameters;
    
    //Fit the shape
    RooFitResult *fitRes = sigPDF->fitTo(*hist,Save(1), SumW2Error(kTRUE),Range(lowM,highM));
    fitRes->Print("v");

    // Get the best fit paramters
    double mass,mean,sigma,a1,n1,a2,n2;
    mass=MHStar.getVal();
    mean=meanCB.getVal();
    sigma = sigmaCB.getVal();
    a1=alphaCB_1.getVal();
    n1=nCB_1.getVal();
    a2=alphaCB_2.getVal();
    n2=nCB_2.getVal();
    cout <<  mass << " " << mean << " " << sigma << " " << a1 << " " << n1 << " " << a2 << " " << n2 << endl;

    // Generate an histogram from the fitted function in order to get the effective resolution 
    RooDataSet *gendata = sigPDF->generate(f_mass4l,100000);
    TH1D *genh = (TH1D*) gendata->createHistogram("genh",f_mass4l,RooFit::Binning(100,lowM,highM));
    math::HistogramTools ht(genh);
    double rms = ht.effectiveSigma();
    cout << "RMS is " << rms << endl;    
    
    // Plot everything
    hist->plotOn(xplot,RooFit::Name("MC"));
    if (channel==1) leg0->AddEntry(xplot->findObject("MC"),"H#rightarrowZZ#rightarrow4#mu at m_{H} = 125 GeV/c^{2}", "P");
    if (channel==2) leg0->AddEntry(xplot->findObject("MC"),"H#rightarrowZZ#rightarrow4e at m_{H} = 125 GeV/c^{2}", "P");
    if (channel==3) leg0->AddEntry(xplot->findObject("MC"),"H#rightarrowZZ#rightarrow2e2#mu at m_{H} = 125 GeV/c^{2}", "P");
    //sigbkghist->plotOn(xplot,DrawOption("F"),FillColor(kCyan));
    
    sigPDF->plotOn(xplot,RooFit::Name("BestFit"));
    leg0->AddEntry(xplot->findObject("BestFit"),"Fit with dCB #otimes BW", "L");
    sigPDF->paramOn(xplot,hist,"",2,"NELU",0.74,0.9,0.9);
    xplot->getAttText()->SetTextSize(0.02);
    
    canv->cd();
    xplot->Draw();
    leg0->Draw("SAME");
    ll->Draw("SAME");
    //genh->Draw("LSAME");

    char pdf[200],png[200];
    sprintf(pdf,"BestFit_%s_%s_%s_%s.pdf", conf.c_str(),schannel.Data(),PUstring.Data(),whichenergy.c_str() );
    sprintf(png,"BestFit_%s_%s_%s_%s.png", conf.c_str(),schannel.Data(),PUstring.Data(),whichenergy.c_str() );
    canv->SaveAs(pdf);
    canv->SaveAs(png);


}


