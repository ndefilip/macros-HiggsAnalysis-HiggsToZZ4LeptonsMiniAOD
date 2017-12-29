#!/bin/bash

if [ "$1" == "" ]; then
  if [ "$2" == "" ]; then
      if [ "$3" == "" ]; then
	  echo "Please provide arguments to the script: site configuration, data type and MC type"
	  echo "Usage bash loopcheck_data_2e2mu.sh <arg1> <arg2> <arg3>"
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

name="DoubleElectron_Run2012C-22Jan2013-v1"


mkdir -p DataCards2e2mu_${name}/

rm -f  tmplista_${name}.txt
ls /lustre/cms/store/user/defilip/localjobs/Data2012_step1_paper_${name}/histodir/roottree_leptons_*.root > tmplista_${name}.txt
# ls /lustre/cms/store/user/jpb/Data2012_Moriond/${name}/roottree_leptons_*.root > tmplista_${name}.txt

# cp data_input_all.txt data_input.txt
nlines=`wc -l tmplista_${name}.txt | awk '{print $1}'`;

for file in `cat tmplista_${name}.txt`;do

  (( n = n + 1 ))
  (( m = ${nlines} - n ))
  echo $n $m

  rm -f DataCards2e2mu_${name}/data_input_${n}.txt
  echo $file > DataCards2e2mu_${name}/data_input_${n}.txt
  samplename=`cat DataCards2e2mu_${name}/data_input_${n}.txt | awk '{print $1}'`
  echo $samplename
  cat data_input.txt | tail -n $m >  data_input_tmp.txt
  mv  data_input_tmp.txt data_input.txt
  cat submit_HZZ4LeptonsAnalysis.sh | sed "s?mc?$3?g" |sed "s?year?$2?g" | sed "s?HZZ4LeptonsAnalysis?RunReferenceAnalysis?g" | sed "s?jobdir?jobs/jobs2e2mu_${name}_${n}?g" | sed "s?histodir?histos/histos2e2mu_${name}_${n}?g" | sed "s?RunReferenceAnalysis?RunReference2e2mu_foreachfile?g" | sed "s?data_input.txt?DataCards2e2mu_${name}/data_input_${n}.txt?g" | sed "s?_log?_${name}_${n}_2e2mu.log?g" > jobs2e2mu/submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh

  ls jobs2e2mu/submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh

 cd jobs2e2mu
 qsub -q local submit_ReferenceAnalysis_${name}_${n}_2e2mu.sh
 cd ..
done 

