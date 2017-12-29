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

###### Data
n=0;
m=0;

mkdir jobs4e;

echo "Reading data_input_4e_$2_AN.txt file"

cp data_input_4e_$2_AN.txt data_input.txt
nlines=`wc -l data_input_4e_$2_AN.txt | awk '{print $1}'`;

while [ $n -lt ${nlines} ]; do
  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m
  rm -f DataCards4e$2/data_input_${n}.txt
  cat data_input.txt | head -1 > DataCards4e$2/data_input_${n}.txt
  samplename=`cat DataCards4e$2/data_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat data_input.txt | tail -n $m >  data_input_tmp.txt
  mv  data_input_tmp.txt data_input.txt
  rm -f jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh
  if [ $1 = ${SCERN} ]; then
      cat submit_HZZ4LeptonsAnalysis_CERN.sh  | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e?g" | sed "s?histodir?histos4e?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs4e/?g" | sed "s?RunReferenceAnalysis?RunReference4e_data?g" | sed "s?data_input.txt?DataCards4e$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh
  elif  [ $1 = ${SFNAL} ]; then 
      cat submit_HZZ4LeptonsAnalysis_FNAL.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e?g" | sed "s?histodir?histos4e?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_data?g" | sed "s?data_input.txt?DataCards4e$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh
      cat condor_template.cfg  | sed "s?submit_HZZ4LeptonsAnalysis_FNAL?submit_ReferenceAnalysis_${samplename}_4e?g" | sed "s?RunReferenceAnalysis?RunReference4e_data?g" | sed "s?sig_input_h150.txt?DataCards4e$2/data_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs4e/condor_ReferenceAnalysis_${samplename}_4e.cfg
  elif  [ $1 = ${SDESY} ]; then 
      cat submit_HZZ4LeptonsAnalysis_DESY.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e?g" | sed "s?histodir?histos4e?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs4e/?g" | sed "s?RunReferenceAnalysis?RunReference4e_data?g" | sed "s?data_input.txt?DataCards4e$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh
  else
      cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4e_25ns?g" | sed "s?histodir?histos4e_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4e_data?g" | sed "s?data_input.txt?DataCards4e$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh

  fi

  chmod u+xr jobs4e/submit_ReferenceAnalysis_${samplename}_4e.sh

  cd jobs4e

  if [ $1 = ${SCERN} ]; then
      echo "Submitting jobs4e via LSF at CERN"
      bsub -q 8nh submit_ReferenceAnalysis_${samplename}_4e.sh
  elif  [ $1 = ${SFNAL} ]; then
      echo "Submitting jobs4e via CONDOR at FNAL"
      condor_submit condor_ReferenceAnalysis_${samplename}_4e.cfg
  elif  [ $1 = ${SDESY} ]; then
      echo "Submitting jobs via SGE"
      qsub submit_ReferenceAnalysis_${samplename}_4e.sh   
  else
      echo "Submitting jobs4e via PBS"    
      qsub -q local submit_ReferenceAnalysis_${samplename}_4e.sh
  fi
  cd ..
done 

