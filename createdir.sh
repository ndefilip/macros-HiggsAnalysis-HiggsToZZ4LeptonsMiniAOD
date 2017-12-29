#!/bin/bash

if [ "$1" == "" ]; then
          echo "Usage bash createdir.sh <arg1>"
          exit
fi



echo "$1 configuration";

SCERN="CERN";
SFNAL="FNAL";
SDESY="DESY";


mkdir -p plots
mkdir -p SigCards2e2muFall11 SigCards4eFall11 SigCards4muFall11
mkdir -p BkgCards2e2muFall11 BkgCards4eFall11 BkgCards4muFall11  
mkdir -p SigCards2e2muSummer12 SigCards4eSummer12 SigCards4muSummer12
mkdir -p BkgCards2e2muSummer12 BkgCards4eSummer12 BkgCards4muSummer12  
mkdir -p DataCards2e2mu2011 DataCards4e2011 DataCards4mu2011
mkdir -p DataCards2e2mu2012 DataCards4e2012 DataCards4mu2012

mkdir -p jobs2e2mu jobs4mu jobs4e

if [ $1 = ${SFNAL} ]; then
 path="/uscms/home/`whoami`/nobackup/";
elif [ $1 = ${SDESY} ]; then
 path="/nfs/dust/test/cmsdas/`whoami`/";
elif [ $1 = ${SCERN} ]; then
 path=`echo ${PWD}`;
else 
 path=`echo ${PWD}`;
fi

# echo $path

# tar -zxvf histos4mu_2011.tgz   -C ${path}
# tar -zxvf histos4e_2011.tgz    -C ${path}
# tar -zxvf histos2e2mu_2011.tgz -C ${path}
