#!/bin/bash

username=`whoami`

mkdir -p /nfs/dust/cms/group/cmsdas2018/users/${username}/jobdir
mkdir -p /nfs/dust/cms/group/cmsdas2018/users/${username}/histodir

echo "Running HtoZZto4Leptons Analysis with executables RunHZZ4LeptonsAnalysis"
source /cvmfs/cms.cern.ch/cmsset_default.sh

export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH
export PATH=path:$PATH


export CMSSW_BASE=CMSSW_BASE_DIR
melalibdir=${CMSSW_BASE}/lib/slc6_amd64_gcc493/
export LD_LIBRARY_PATH=${melalibdir}:$LD_LIBRARY_PATH

if [ -d "$_CONDOR_SCRATCH_DIR" ]; then
    workdir=`echo $_CONDOR_SCRATCH_DIR`;
    cd ${workdir};
else 
    workdir=`echo $PWD`;
    cd ${workdir};
fi

savedir=`echo /nfs/dust/cms/group/cmsdas2018/users/${username}/histodir`

echo "Working dir is $workdir"
#echo "Executable dir is $exedir"
echo "Saving dir is $savedir"

echo "Compiling the macros"
bash compilereference.sh 4mu


./RunReferenceAnalysis ./sig_input_h150.txt 1 ./bkg_input.txt 1 ./data_input.txt 1 site year mc >& ${workdir}/HZZ4LeptonsAnalysis_log

tar -zcvf ${workdir}/HZZ4LeptonsAnalysis_log.tgz ${workdir}/HZZ4LeptonsAnalysis_log

cp -f ${workdir}/HZZ4LeptonsAnalysis_log.tgz /nfs/dust/cms/group/cmsdas2018/users/${username}/jobdir

mv ${workdir}/output.root    ${savedir}/.
mv ${workdir}/output_bnn.txt ${savedir}/.
mv ${workdir}/output_bnn.root ${savedir}/.
mv ${workdir}/output_txt.txt ${savedir}/.
mv ${workdir}/output_txt_vbf.txt ${savedir}/.

if [ -d "$_CONDOR_SCRATCH_DIR" ]; then
 rm -f $_CONDOR_SCRATCH_DIR/*
fi
