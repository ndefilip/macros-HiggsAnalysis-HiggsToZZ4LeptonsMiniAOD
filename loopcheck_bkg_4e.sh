#!/bin/bash

if [ "$1" == "" ]; then
  if [ "$2" == "" ]; then
      if [ "$3" == "" ]; then
          echo "Please provide arguments to the script: site configuration, data type and MC type"
          echo "Usage bash loopcheck_bkg_4e.sh <arg1> <arg2> <arg3>"
          exit
      fi
  fi
fi



echo "$1 configuration";
echo "$2 data"
echo "$3 simulation"

SCERN="CERN";
SFNAL="FNAL";
SDESY="DESY";


###### Background
n=0;
m=0;

mkdir -p jobs4e;

echo "Reading bkg_input_$3_AN.txt file"

cp -f bkg_input_$3_AN.txt bkg_input.txt
nlines=`wc -l bkg_input_$3_AN.txt | awk '{print $1}'`;

mkdir -p BkgCards4e$3;

while [ $n -lt ${nlines} ]; do
  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m
  rm -f BkgCards4e$3/bkg_input_${n}.txt
  cat bkg_input.txt | head -1 > BkgCards4e$3/bkg_input_${n}.txt
  samplename=`cat BkgCards4e$3/bkg_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat bkg_input.txt | tail -n $m >  bkg_input_tmp.txt
  mv  bkg_input_tmp.txt bkg_input.txt
  rm -f jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
  if [ $1 = ${SCERN} ]; then
      cat submit_HZZ4LeptonsAnalysis_CERN.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e_25ns?g" | sed "s?histodir?histos4e_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_bkg?g" | sed "s?bkg_input.txt?BkgCards4e$3/bkg_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
  elif  [ $1 = ${SFNAL} ]; then 
      cat submit_HZZ4LeptonsAnalysis_FNAL.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e_25ns?g" | sed "s?histodir?histos4e_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_bkg?g" | sed "s?bkg_input.txt?BkgCards4e$3/bkg_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
      cat condor_template.cfg  | sed "s?submit_HZZ4LeptonsAnalysis_FNAL?submit_ReferenceAnalysis_bkg_${samplename}_4e?g" | sed "s?RunReferenceAnalysis?RunReference4e_bkg?g" | sed "s?sig_input_h150.txt?BkgCards4e$3/bkg_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs4e/condor_ReferenceAnalysis_bkg_${samplename}_4e.cfg      
  elif  [ $1 = ${SDESY} ]; then
     cat submit_HZZ4LeptonsAnalysis_DESY.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e_25ns?g" | sed "s?histodir?histos4e_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_bkg?g" | sed "s?bkg_input.txt?BkgCards4e$3/bkg_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
  else
      cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis_bkg?g" | sed "s?jobdir?jobs4e_25ns?g" | sed "s?histodir?histos4e_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_bkg?g" | sed "s?bkg_input.txt?BkgCards4e$3/bkg_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh

  fi

  chmod u+xr jobs4e/submit_ReferenceAnalysis_bkg_${samplename}_4e.sh

  cd jobs4e

  if [ $1 = ${SCERN} ]; then
      echo "Submitting jobs via LSF at CERN"
      bsub -q 8nh  submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
  elif  [ $1 = ${SFNAL} ]; then
      echo "Submitting jobs via CONDOR at FNAL"
      condor_submit  condor_ReferenceAnalysis_bkg_${samplename}_4e.cfg
  elif  [ $1 = ${SDESY} ]; then
      echo "Submitting jobs via SGE"
      qsub submit_ReferenceAnalysis_bkg_${samplename}_4e.sh   
  else
      echo "Submitting jobs via PBS"    
      qsub -q local submit_ReferenceAnalysis_bkg_${samplename}_4e.sh
  fi
  cd ..
done 

