#!/bin/bash

if [ "$1" == "" ]; then
  if [ "$2" == "" ]; then
      if [ "$3" == "" ]; then
          echo "Please provide arguments to the script: site configuration, data type and MC type"
          echo "Usage bash loopcheck_bkg_2e2mu.sh <arg1> <arg2> <arg3>"
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

###### Data
n=0;
m=0;

mkdir jobs2e2mu;

echo "Reading data_input_2e2mu_$2_AN.txt file"

cp data_input_2e2mu_$2_AN.txt data_input.txt
nlines=`wc -l data_input_2e2mu_$2_AN.txt | awk '{print $1}'`;

while [ $n -lt ${nlines} ]; do
  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m
  rm -f DataCards2e2mu$2/data_input_${n}.txt
  cat data_input.txt | head -1 > DataCards2e2mu$2/data_input_${n}.txt
  samplename=`cat DataCards2e2mu$2/data_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat data_input.txt | tail -n $m >  data_input_tmp.txt
  mv  data_input_tmp.txt data_input.txt
  rm -f jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  if [ $1 = ${SCERN} ]; then
      cat submit_HZZ4LeptonsAnalysis_CERN.sh  | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu?g" | sed "s?histodir?histos2e2mu?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs2e2mu/?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_data?g" | sed "s?data_input.txt?DataCards2e2mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  elif  [ $1 = ${SFNAL} ]; then 
      cat submit_HZZ4LeptonsAnalysis_FNAL.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu?g" | sed "s?histodir?histos2e2mu?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_data?g" | sed "s?data_input.txt?DataCards2e2mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh
      cat condor_template.cfg  | sed "s?submit_HZZ4LeptonsAnalysis_FNAL?submit_ReferenceAnalysis_${samplename}_2e2mu?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_data?g" | sed "s?sig_input_h150.txt?DataCards2e2mu$2/data_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs2e2mu/condor_ReferenceAnalysis_${samplename}_2e2mu.cfg
  elif  [ $1 = ${SDESY} ]; then 
      cat submit_HZZ4LeptonsAnalysis_DESY.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu?g" | sed "s?histodir?histos2e2mu?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs2e2mu/?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_data?g" | sed "s?data_input.txt?DataCards2e2mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  else
      cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_data?g" | sed "s?data_input.txt?DataCards2e2mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  fi

  chmod u+xr jobs2e2mu/submit_ReferenceAnalysis_${samplename}_2e2mu.sh

  cd jobs2e2mu

  if [ $1 = ${SCERN} ]; then
      echo "Submitting jobs2e2mu via LSF at CERN"
      bsub -q 8nh submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  elif  [ $1 = ${SFNAL} ]; then
      echo "Submitting jobs2e2mu via CONDOR at FNAL"
      condor_submit condor_ReferenceAnalysis_${samplename}_2e2mu.cfg
  elif  [ $1 = ${SDESY} ]; then
      echo "Submitting jobs via SGE"
      qsub submit_ReferenceAnalysis_${samplename}_2e2mu.sh   
  else
      echo "Submitting jobs2e2mu via PBS"    
      qsub -q local submit_ReferenceAnalysis_${samplename}_2e2mu.sh
  fi
  cd ..
done 

