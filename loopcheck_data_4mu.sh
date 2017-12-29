
#!/bin/bash

if [ "$1" == "" ]; then
  if [ "$2" == "" ]; then
      if [ "$3" == "" ]; then
          echo "Please provide arguments to the script: site configuration, data type and MC type"
          echo "Usage bash loopcheck_bkg_4mu.sh <arg1> <arg2> <arg3>"
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

mkdir -p jobs4mu;

echo "Reading data_input_4mu_$2_AN.txt file"

cp data_input_4mu_$2_AN.txt data_input.txt
nlines=`wc -l data_input_4mu_$2_AN.txt | awk '{print $1}'`;
echo "Number of files is " $nlines

while [ $n -lt ${nlines} ]; do
  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m
  mkdir -p  DataCards4mu$2
  rm -f DataCards4mu$2/data_input_${n}.txt
  cat data_input.txt | head -1 > DataCards4mu$2/data_input_${n}.txt
  samplename=`cat DataCards4mu$2/data_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat data_input.txt | tail -n $m >  data_input_tmp.txt
  mv  data_input_tmp.txt data_input.txt
  rm -f jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh
  if [ $1 = ${SCERN} ]; then
     cat submit_HZZ4LeptonsAnalysis_CERN.sh  | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4mu?g" | sed "s?histodir?histos4mu?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs4mu/?g" | sed "s?RunReferenceAnalysis?RunReference4mu_data?g" | sed "s?data_input.txt?DataCards4mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4mu.log?g" > jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh
  elif  [ $1 = ${SFNAL} ]; then 
      cat submit_HZZ4LeptonsAnalysis_FNAL.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4mu?g" | sed "s?histodir?histos4mu?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4mu_data?g" | sed "s?data_input.txt?DataCards4mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4mu.log?g" > jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh
      cat condor_template.cfg  | sed "s?submit_HZZ4LeptonsAnalysis_FNAL?submit_ReferenceAnalysis_${samplename}_4mu?g" | sed "s?RunReferenceAnalysis?RunReference4mu_data?g" | sed "s?sig_input_h150.txt?DataCards4mu$2/data_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs4mu/condor_ReferenceAnalysis_${samplename}_4mu.cfg
  elif  [ $1 = ${SDESY} ]; then 
      cat submit_HZZ4LeptonsAnalysis_DESY.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4mu?g" | sed "s?histodir?histos4mu?g" | sed "s?output?output_${samplename}?g" | sed "s?jobs/?jobs4mu/?g" | sed "s?RunReferenceAnalysis?RunReference4mu_data?g" | sed "s?data_input.txt?DataCards4mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4mu.log?g" > jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh
  else
      cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs4mu_25ns?g" | sed "s?histodir?histos4mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference4mu_data?g" | sed "s?data_input.txt?DataCards4mu$2/data_input_${n}.txt?g" | sed "s?_log?_${samplename}_4mu.log?g" > jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh
  fi

  chmod u+xr jobs4mu/submit_ReferenceAnalysis_${samplename}_4mu.sh

  cd jobs4mu

  if [ $1 = ${SCERN} ]; then
      echo "Submitting jobs4mu via LSF at CERN"
      bsub -q 8nh submit_ReferenceAnalysis_${samplename}_4mu.sh
  elif  [ $1 = ${SFNAL} ]; then
      echo "Submitting jobs4mu via CONDOR at FNAL"
      condor_submit condor_ReferenceAnalysis_${samplename}_4mu.cfg
  elif  [ $1 = ${SDESY} ]; then
      echo "Submitting jobs via SGE"
      qsub submit_ReferenceAnalysis_${samplename}_4mu.sh   
  else
      echo "Submitting jobs4mu via PBS"    
      qsub -q local submit_ReferenceAnalysis_${samplename}_4mu.sh
  fi
  cd ..
done 

