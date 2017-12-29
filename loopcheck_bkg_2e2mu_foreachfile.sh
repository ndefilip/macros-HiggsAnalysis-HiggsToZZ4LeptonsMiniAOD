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

###### Data
n=0;
m=0;

name="MuEG_Run2012C_PromptReco_v2_190456-201678_add"
# name="DoubleMu_Run2012C_PromptReco_v2_190456-201678_add"

mkdir -p DataCards2e2mu_${name}/

ls /lustre/cms/store/user/ndefilip/Data2012_postICHEP/${name}/roottree_leptons_*.root > tmplista_${name}.txt

cp bkg_input_all.txt bkg_input.txt
nlines=`wc -l tmplista_${name}.txt | awk '{print $1}'`;

for file in `cat tmplista_${name}.txt`;do

  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m

  rm -f DataCards2e2mu_${name}/bkg_input_${n}.txt
  echo $file > DataCards2e2mu_${name}/bkg_input_${n}.txt
  samplename=`cat DataCards2e2mu_${name}/bkg_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat bkg_input.txt | tail -n $m >  bkg_input_tmp.txt
  mv  bkg_input_tmp.txt bkg_input.txt
  cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_foreachfile?g" | sed "s?histodir?histos/histos2e2mu_${name}_${n}?g" | sed "s?output?output_${name}_${n}?g" | sed "s?jobdir?jobs/jobs2e2mu_${name}_${n}?g" | sed "s?bkg_input.txt?DataCards2e2mu_${name}/bkg_input_${n}.txt?g" | sed "s?_log?_${name}_${n}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh
  ls jobs2e2mu/submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh

 cd jobs2e2mu
 qsub -q local submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh
 cd ..
done 

