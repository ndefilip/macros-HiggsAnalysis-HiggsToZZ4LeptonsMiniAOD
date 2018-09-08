#!/usr/bin/env python
# -----------------------------------------------------------------------------
#  File:        readreducedntuple.py
#  Usage:       python readreducedntuple.py --channel 4mu
# -----------------------------------------------------------------------------
from ROOT import *
import numpy as np
import math
import argparse
import os

# Convert ROOT TNtuple data structure to Python arrays
def get_data(f):
  f = TFile.Open(f)
  t = f.Get("HZZ4LeptonsAnalysisReduced")

  print t.GetEntries()

  target = []
  weight = [] 

  lept1_pt = [] 
  lept1_eta = [] 
  lept1_phi = [] 
  lept1_charge = [] 
  lept1_pfx = [] 
  lept1_sip = [] 
  lept1_pdgid = []

  lept2_pt = [] 
  lept2_eta = [] 
  lept2_phi = [] 
  lept2_charge = [] 
  lept2_pfx = [] 
  lept2_sip = [] 
  lept2_pdgid = []

  lept3_pt = [] 
  lept3_eta = [] 
  lept3_phi = [] 
  lept3_charge = [] 
  lept3_pfx = [] 
  lept3_sip = [] 
  lept3_pdgid = []

  lept4_pt = [] 
  lept4_eta = [] 
  lept4_phi = [] 
  lept4_charge = [] 
  lept4_pfx = [] 
  lept4_sip = [] 
  lept4_pdgid = []

  Z1mass = [] 
  Z2mass = [] 
  angle_costhetastar = [] 
  angle_costheta1 = [] 
  angle_costheta2 = [] 
  angle_phi = [] 
  angle_phistar1 = [] 
  eta4l = [] 
  pt4l = [] 
  mass4l = [] 
  mass4lErr = [] 
  njets_pass = [] 
  deltajj = [] 
  massjj = [] 
  D_jet = [] 
  jet1_pt = [] 
  jet1_eta = [] 
  jet1_phi = [] 
  jet1_e = [] 
  jet2_pt = [] 
  jet2_eta = [] 
  jet2_phi = [] 
  jet2_e = [] 
  jet1_highpt_pt = [] 
  jet1_highpt_eta = [] 
  jet1_highpt_phi = [] 
  jet1_highpt_e = [] 
  jet2_highpt_pt = [] 
  jet2_highpt_eta = [] 
  jet2_highpt_phi = [] 
  jet2_highpt_e = [] 
  jet3_highpt_pt = [] 
  jet3_highpt_eta = [] 
  jet3_highpt_phi = [] 
  jet3_highpt_e = []

  pfmet = []
  Ngood = []
  Nbjets = []
  mT = []
  dphi = []
  D_bkg_kin = []
  D_bkg = [] 
  D_gg = []
  D_g4 = []
  Djet_VAJHU = []
  category = []
  
  for evt in t:
    #print evt.f_weight

    target.append(1)
    # target.append(0)
    weight.append(evt.f_weight)

    lept1_pt.append(evt.f_lept1_pt) 
    lept1_eta.append(evt.f_lept1_eta) 
    lept1_phi.append(evt.f_lept1_phi) 
    lept1_charge.append(evt.f_lept1_charge) 
    lept1_pfx.append(evt.f_lept1_pfx) 
    lept1_sip.append(evt.f_lept1_sip) 
    lept1_pdgid.append(evt.f_lept1_pdgid)

    lept2_pt.append(evt.f_lept2_pt) 
    lept2_eta.append(evt.f_lept2_eta) 
    lept2_phi.append(evt.f_lept2_phi) 
    lept2_charge.append(evt.f_lept2_charge) 
    lept2_pfx.append(evt.f_lept2_pfx) 
    lept2_sip.append(evt.f_lept2_sip) 
    lept2_pdgid.append(evt.f_lept2_pdgid)

    lept3_pt.append(evt.f_lept3_pt) 
    lept3_eta.append(evt.f_lept3_eta) 
    lept3_phi.append(evt.f_lept3_phi) 
    lept3_charge.append(evt.f_lept3_charge) 
    lept3_pfx.append(evt.f_lept3_pfx) 
    lept3_sip.append(evt.f_lept3_sip) 
    lept3_pdgid.append(evt.f_lept3_pdgid)

    lept4_pt.append(evt.f_lept4_pt) 
    lept4_eta.append(evt.f_lept4_eta) 
    lept4_phi.append(evt.f_lept4_phi) 
    lept4_charge.append(evt.f_lept4_charge) 
    lept4_pfx.append(evt.f_lept4_pfx) 
    lept4_sip.append(evt.f_lept4_sip) 
    lept4_pdgid.append(evt.f_lept4_pdgid)

    Z1mass.append(evt.f_Z1mass) 
    Z2mass.append(evt.f_Z2mass)
    
    angle_costhetastar.append(evt.f_angle_costhetastar) 
    angle_costheta1.append(evt.f_angle_costheta1)
    angle_costheta2.append(evt.f_angle_costheta2) 
    angle_phi.append(evt.f_angle_phi) 
    angle_phistar1.append(evt.f_angle_phistar1) 
    eta4l.append(evt.f_eta4l) 
    pt4l.append(evt.f_pt4l) 
    mass4l.append(evt.f_mass4l) 
    mass4lErr.append(evt.f_mass4lErr) 
    njets_pass.append(evt.f_njets_pass) 
    deltajj.append(evt.f_deltajj) 
    massjj.append(evt.f_massjj) 
    D_jet.append(evt.f_D_jet) 

    jet1_pt.append(evt.f_jet1_pt) 
    jet1_eta.append(evt.f_jet1_eta) 
    jet1_phi.append(evt.f_jet1_phi) 
    jet1_e.append(evt.f_jet1_e) 
    jet2_pt.append(evt.f_jet2_pt) 
    jet2_eta.append(evt.f_jet2_eta) 
    jet2_phi.append(evt.f_jet2_phi) 
    jet2_e.append(evt.f_jet2_e)
    
    jet1_highpt_pt.append(evt.f_jet1_highpt_pt) 
    jet1_highpt_eta.append(evt.f_jet1_highpt_eta) 
    jet1_highpt_phi.append(evt.f_jet1_highpt_phi) 
    jet1_highpt_e.append(evt.f_jet1_highpt_e) 
    
    jet2_highpt_pt.append(evt.f_jet2_highpt_pt) 
    jet2_highpt_eta.append(evt.f_jet2_highpt_eta) 
    jet2_highpt_phi.append(evt.f_jet2_highpt_phi) 
    jet2_highpt_e.append(evt.f_jet2_highpt_e) 
    
    jet3_highpt_pt.append(evt.f_jet3_highpt_pt) 
    jet3_highpt_eta.append(evt.f_jet3_highpt_eta) 
    jet3_highpt_phi.append(evt.f_jet3_highpt_phi) 
    jet3_highpt_e.append(evt.f_jet3_highpt_e) 
    
    pfmet.append(evt.f_pfmet)
    Ngood.append(evt.f_Ngood)
    Nbjets.append(evt.f_Nbjets)
    
    mT.append(evt.f_mT)
    dphi.append(evt.f_dphi)
    D_bkg_kin.append(evt.f_D_bkg_kin)    
    D_bkg.append(evt.f_D_bkg)
    D_gg.append(evt.f_D_gg)
    D_g4.append(evt.f_D_g4)
    Djet_VAJHU.append(evt.f_Djet_VAJHU)

    category.append(evt.f_category)

  f.Close()
  return (target,weight,lept1_pt,lept1_eta,lept1_phi,lept1_charge,lept1_pfx,lept1_sip,lept1_pdgid,lept2_pt,lept2_eta,lept2_phi,lept2_charge,lept2_pfx,lept2_sip,lept2_pdgid,lept3_pt,lept3_eta,lept3_phi,lept3_charge,lept3_pfx,lept3_sip,lept3_pdgid,lept4_pt,lept4_eta,lept4_phi,lept4_charge,lept4_pfx,lept4_sip,lept4_pdgid,Z1mass,Z2mass,angle_costhetastar,angle_costheta1,angle_costheta2,angle_phi,angle_phistar1,eta4l,pt4l,mass4l,mass4lErr,njets_pass,deltajj,massjj,D_jet,jet1_pt,jet1_eta,jet1_phi,jet1_e,jet2_pt,jet2_eta,jet2_phi,jet2_e,jet1_highpt_pt,jet1_highpt_eta,jet1_highpt_phi,jet1_highpt_e,jet2_highpt_pt,jet2_highpt_eta,jet2_highpt_phi,jet2_highpt_e,jet3_highpt_pt,jet3_highpt_eta,jet3_highpt_phi,jet3_highpt_e,pfmet,Ngood,Nbjets,mT,dphi,D_bkg_kin,D_bkg,D_gg,D_g4,Djet_VAJHU)

if __name__ == "__main__":
 
  # Parse command line arguments
  parser = argparse.ArgumentParser()
  parser.add_argument('--channel', required=True, help='Decay channel: 4mu, 4e, or 2e2mu')
  args = parser.parse_args()

  # Read in list of data and simulation files
  flist = map(lambda x: x.split()[-1], open('filelist_' + args.channel + '_2016_Spring16_AN_Bari_miniaod_HHanalysis.txt').readlines()) 
  #flist = map(lambda x: x.split()[-1], open('listHHsignal_' + args.channel + '.txt').readlines())
  # flist = map(lambda x: x.split()[-1], open('test4mu_13TeV.txt').readlines())

  os.mkdir('histos'+ args.channel +'_25ns_bnn')

  # Book histograms for shape analysis
  #m4l = TH1F("m4l","m4l",1000,0.,1000.)
  #m4l.Sumw2()

  # Loop through input files, testing machine learning algorithm and applying signal region selection

  for f in flist:
      
    print f

    if 'ZX' in f: 
      continue
    if 'Final_Estimation' in f: 
      continue
      
    # Get Data
    target,weight,lept1_pt,lept1_eta,lept1_phi,lept1_charge,lept1_pfx,lept1_sip,lept1_pdgid,lept2_pt,lept2_eta,lept2_phi,lept2_charge,lept2_pfx,lept2_sip,lept2_pdgid,lept3_pt,lept3_eta,lept3_phi,lept3_charge,lept3_pfx,lept3_sip,lept3_pdgid,lept4_pt,lept4_eta,lept4_phi,lept4_charge,lept4_pfx,lept4_sip,lept4_pdgid,Z1mass,Z2mass,angle_costhetastar,angle_costheta1,angle_costheta2,angle_phi,angle_phistar1,eta4l,pt4l,mass4l,mass4lErr,njets_pass,deltajj,massjj,D_jet,jet1_pt,jet1_eta,jet1_phi,jet1_e,jet2_pt,jet2_eta,jet2_phi,jet2_e,jet1_highpt_pt,jet1_highpt_eta,jet1_highpt_phi,jet1_highpt_e,jet2_highpt_pt,jet2_highpt_eta,jet2_highpt_phi,jet2_highpt_e,jet3_highpt_pt,jet3_highpt_eta,jet3_highpt_phi,jet3_highpt_e,pfmet,Ngood,Nbjets,mT,dphi,D_bkg_kin,D_bkg,D_gg,D_g4,Djet_VAJHU = get_data(f)
    
    basefile='histos' + args.channel + '_25ns_bnn/' + os.path.basename(f)
    bnnfile=basefile.replace(".root","_bnn.txt")
    print bnnfile
    bnn = open(bnnfile,'w') 

    bnn.write('target weight lept1_pt lept1_eta lept1_phi lept1_charge lept1_pfx lept1_sip lept1_pdgid lept2_pt lept2_eta lept2_phi lept2_charge lept2_pfx lept2_sip lept2_pdgid lept3_pt lept3_eta lept3_phi lept3_charge lept3_pfx lept3_sip lept3_pdgid lept4_pt lept4_eta lept4_phi lept4_charge lept4_pfx lept4_sip lept4_pdgid Z1mass Z2mass angle_costhetastar angle_costheta1 angle_costheta2 angle_phi angle_phistar1 eta4l pt4l mass4l mass4lErr njets_pass deltajj massjj D_jet jet1_pt jet1_eta jet1_phi jet1_e jet2_pt jet2_eta jet2_phi jet2_e jet1_highpt_pt jet1_highpt_eta jet1_highpt_phi jet1_highpt_e jet2_highpt_pt jet2_highpt_eta jet2_highpt_phi jet2_highpt_e jet3_highpt_pt jet3_highpt_eta jet3_highpt_phi jet3_highpt_e pfmet Ngood Nbjets mT dphi D_bkg_kin D_bkg D_gg D_g4 Djet_VAJHU' + ' \n')

    # Apply selection, filling histograms before and after
    for i in range(0, len(weight)):
      #print "Weight is =", weight[i]
      #if njets_pass[i] < 2: continue
      #if abs(mass4l[i] - 125.) > 10.: continue
      #if Nbjets < 1: continue

      # m4l.Fill(mass4l[i], weight[i])

      bnn.write(repr(target[i]) + " " + 
                repr(weight[i]) + " " +
                repr(lept1_pt[i]) + " " + 
                repr(lept1_eta[i]) + " " + 
                repr(lept1_phi[i]) + " " + 
                repr(lept1_charge[i]) + " " + 
                repr(lept1_pfx[i]) + " " + 
                repr(lept1_sip[i]) + " " + 
                repr(lept1_pdgid[i]) + " " +
                repr(lept2_pt[i]) + " " + 
                repr(lept2_eta[i]) + " " + 
                repr(lept2_phi[i]) + " " + 
                repr(lept2_charge[i]) + " " + 
                repr(lept2_pfx[i]) + " " + 
                repr(lept2_sip[i]) + " " + 
                repr(lept2_pdgid[i]) + " " +                
                repr(lept3_pt[i]) + " " + 
                repr(lept3_eta[i]) + " " + 
                repr(lept3_phi[i]) + " " + 
                repr(lept3_charge[i]) + " " + 
                repr(lept3_pfx[i]) + " " + 
                repr(lept3_sip[i]) + " " + 
                repr(lept3_pdgid[i]) + " " +                
                repr(lept4_pt[i]) + " " + 
                repr(lept4_eta[i]) + " " + 
                repr(lept4_phi[i]) + " " + 
                repr(lept4_charge[i]) + " " + 
                repr(lept4_pfx[i]) + " " + 
                repr(lept4_sip[i]) + " " + 
                repr(lept4_pdgid[i]) + " " +
                repr(Z1mass[i]) + " " + 
                repr(Z2mass[i]) + " " + 
                repr(angle_costhetastar[i]) + " " + 
                repr(angle_costheta1[i]) + " " + 
                repr(angle_costheta2[i]) + " " + 
                repr(angle_phi[i]) + " " + 
                repr(angle_phistar1[i]) + " " + 
                repr(eta4l[i]) + " " + 
                repr(pt4l[i]) + " " + 
                repr(mass4l[i]) + " " + 
                repr(mass4lErr[i]) + " " + 
                repr(njets_pass[i]) + " " + 
                repr(deltajj[i]) + " " + 
                repr(massjj[i]) + " " + 
                repr(D_jet[i]) + " " + 
                repr(jet1_pt[i]) + " " + 
                repr(jet1_eta[i]) + " " + 
                repr(jet1_phi[i]) + " " + 
                repr(jet1_e[i]) + " " + 
                repr(jet2_pt[i]) + " " + 
                repr(jet2_eta[i]) + " " + 
                repr(jet2_phi[i]) + " " + 
                repr(jet2_e[i]) + " " + 
                repr(jet1_highpt_pt[i]) + " " + 
                repr(jet1_highpt_eta[i]) + " " + 
                repr(jet1_highpt_phi[i]) + " " + 
                repr(jet1_highpt_e[i]) + " " + 
                repr(jet2_highpt_pt[i]) + " " + 
                repr(jet2_highpt_eta[i]) + " " + 
                repr(jet2_highpt_phi[i]) + " " + 
                repr(jet2_highpt_e[i]) + " " + 
                repr(jet3_highpt_pt[i]) + " " + 
                repr(jet3_highpt_eta[i]) + " " + 
                repr(jet3_highpt_phi[i]) + " " + 
                repr(jet3_highpt_e[i]) + " " +
                repr(pfmet[i]) + " " +
                repr(Ngood[i]) + " " +
                repr(Nbjets[i]) + " " +
                repr(mT[i]) + " " +
                repr(dphi[i]) + " " +
                repr(D_bkg_kin[i]) + " " +
                repr(D_bkg[i]) + " " + 
                repr(D_gg[i]) + " " +
                repr(D_g4[i]) + " " +
                repr(Djet_VAJHU[i]) +                
                ' \n')

    bnn.close()
   
    
    # Write shape histogram to file for Monte Carlo samples
    #fs = TFile('HHselection_' + args.channel + '.root', 'UPDATE')
    #m4l.Write("mass4l")
