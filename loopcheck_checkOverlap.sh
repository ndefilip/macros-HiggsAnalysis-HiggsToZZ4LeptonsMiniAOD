#!/bin/bash

if [ "$1" == "" ]; then
  if [ "$2" == "" ]; then
          echo "Please provide arguments to the script: site configuration, data type and MC type"
          echo "Usage bash loopcheck_checkOverlap.sh <arg1> <arg2>"
          exit
  fi
fi


echo "$1 configuration";
echo "$2 data"

SCERN="CERN";
SFNAL="FNAL";

mkdir -p jobs
cat submit_checkOverlap.sh | sed "s?site?$1?g" | sed "s?year?$2?g" > jobs/submit_checkOverlap_$1_$2.sh

cd jobs; qsub -q local submit_checkOverlap_$1_$2.sh; cd ..;
