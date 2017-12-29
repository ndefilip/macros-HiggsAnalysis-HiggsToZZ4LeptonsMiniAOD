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
SBARI="BARI";

###### Signal

n=0;
m=0;

mkdir -p jobs2e2mu

echo "Reading sig_input_$3_AN.txt file"

cp sig_input_$3_AN.txt sig_input.txt
nlines=`wc -l sig_input.txt | awk '{print $1}'`;

mkdir -p SigCards2e2mu$3

while [ $n -lt ${nlines} ]; do
    (( n = n + 1 ))
    (( m = ${nlines} - n ))
    echo $n $m
    rm -f SigCards2e2mu$3/sig_input_${n}.txt
    cat sig_input.txt | head -1 > SigCards2e2mu$3/sig_input_${n}.txt
    samplename=`cat SigCards2e2mu$3/sig_input_${n}.txt | awk '{print $1}'`
    cat sig_input.txt | tail -n $m >  sig_input_tmp.txt
    mv  sig_input_tmp.txt sig_input.txt
    echo $samplename
    rm -f jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh	

    if [ $1 = ${SCERN} ]; then
     cat submit_HZZ4LeptonsAnalysis_CERN.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
    elif  [ $1 = ${SFNAL} ]; then 
     cat submit_HZZ4LeptonsAnalysis_FNAL.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
     cat condor_template.cfg  | sed "s?submit_HZZ4LeptonsAnalysis_FNAL?submit_ReferenceAnalysis_sig_${samplename}_2e2mu?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs2e2mu/condor_ReferenceAnalysis_sig_${samplename}_2e2mu.cfg
    elif  [ $1 = ${SDESY} ]; then
     cat submit_HZZ4LeptonsAnalysis_DESY.sh | sed "s?site?$1?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
    elif  [ $1 = ${SBARI} ]; then
	cat submit_HZZ4LeptonsAnalysis_BARI.sh | sed "s?CMSSW_BASE_DIR?${CMSSW_BASE}?g" | sed "s?path?$PATH?g"  | sed "s?lib:?$LD_LIBRARY_PATH:?g" | sed "s?4mu?2e2mu?g" | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
	cat condor_template.cfg  | sed "s?4mu?2e2mu?g" | sed "s?submit_HZZ4LeptonsAnalysis_BARI?submit_ReferenceAnalysis_sig_${samplename}_2e2mu?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?mail?`whoami`?g" > jobs2e2mu/condor_ReferenceAnalysis_sig_${samplename}_2e2mu.cfg      
    else 
     cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs2e2mu_25ns?g" | sed "s?histodir?histos2e2mu_25ns?g" | sed "s?output?output_${samplename}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_signal?g" | sed "s?sig_input_h150.txt?SigCards2e2mu$3/sig_input_${n}.txt?g" | sed "s?_log?_${samplename}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
    fi

    chmod u+xr  jobs2e2mu/submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh

    cd jobs2e2mu
    
    if [ $1 = ${SCERN} ]; then
       echo "Submitting jobs via LSF at CERN"
       bsub -q 8nh  submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
    elif  [ $1 = ${SFNAL} ]; then
       echo "Submitting jobs via CONDOR at FNAL"
       condor_submit  condor_ReferenceAnalysis_sig_${samplename}_2e2mu.cfg
    elif  [ $1 = ${SDESY} ]; then
       echo "Submitting jobs via SGE"
       qsub submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh   
    elif  [ $1 = ${SBARI} ]; then
       echo "Submitting jobs via CONDOR at BARI"
       # condor_submit -name ettore  condor_ReferenceAnalysis_sig_${samplename}_2e2mu.cfg
    else
       echo "Submitting jobs via PBS"
       qsub -q local submit_ReferenceAnalysis_sig_${samplename}_2e2mu.sh
    fi 
    cd ..
done 

