#!/bin/bash


# for file in `ls /lustre/cms/store/user/dburns/MonoHiggs/Spring16_merged/*Baryon*`; do
for file in `ls /lustre/cms/store/user/gminiell/MonoHiggs/Moriond17_merged/*WJet*`; do
#for file in ` ls /lustre/cms/store/user/gminiell/Data2016/DoubleMuon/DoubleMuon_Run2016C-23Sep2016-v1_part3_3/161218_212912/*/roottree_leptons_*.root `; do
# for file in `ls /lustre/cms/store/user/gminiell/MonoHiggs/Data2016_MonoHiggs_13TeV_merged/*`; do

echo $file
cat checkentries.C | sed "s?filename?${file}?g" > tmp.C
g++ -I $ROOTSYS/include tmp.C `root-config --glibs` `root-config --libs` `root-config --cflags` -o checkentries
./checkentries

done

