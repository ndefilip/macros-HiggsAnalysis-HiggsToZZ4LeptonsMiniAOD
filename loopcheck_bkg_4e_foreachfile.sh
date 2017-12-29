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

###### Data
n=0;
m=0;

name="DoubleElectron_Run2012D-16Jan2013-v2"
# name="DoubleMu_Run2012C_PromptReco_v2_190456-201678_add"

mkdir -p DataCards4e_${name}/

ls /lustre/cms/store/user/ndefilip/Data2012_Mor/${name}/roottree_leptons_*.root > tmplista_${name}.txt

cp bkg_input_all.txt bkg_input.txt
nlines=`wc -l tmplista_${name}.txt | awk '{print $1}'`;

for file in `cat tmplista_${name}.txt`;do

  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m

  rm -f DataCards4e_${name}/bkg_input_${n}.txt
  echo $file > DataCards4e_${name}/bkg_input_${n}.txt
  samplename=`cat DataCards4e_${name}/bkg_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat bkg_input.txt | tail -n $m >  bkg_input_tmp.txt
  mv  bkg_input_tmp.txt bkg_input.txt
  cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?RunReferenceAnalysis?RunReference4e_foreachfile?g" | sed "s?histodir?histos/histos4e_${name}_${n}?g" | sed "s?output?output_${name}_${n}?g" | sed "s?jobdir?jobs/jobs4e_${name}_${n}?g" | sed "s?bkg_input.txt?DataCards4e_${name}/bkg_input_${n}.txt?g" | sed "s?_log?_${name}_${n}_4e.log?g" > jobs4e/submit_ReferenceAnalysis_${name}_${n}_4e.sh
  ls jobs4e/submit_ReferenceAnalysis_${name}_${n}_4e.sh

 cd jobs4e
 qsub -q local submit_ReferenceAnalysis_${name}_${n}_4e.sh
 cd ..
done 

