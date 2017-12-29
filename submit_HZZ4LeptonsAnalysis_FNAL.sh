#!/bin/bash


mkdir -p /eos/uscms/store/user/ndefilip/80X/jobdir
mkdir -p /eos/uscms/store/user/ndefilip/80X/histodir

workdir=${PWD}
echo "Running Mono-HtoZZto4Leptons Analysis with executables RunHZZ4LeptonsAnalysis"


source /cvmfs/cms.cern.ch/cmsset_default.sh 
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH

export PATH=path:$PATH

export CMSSW_BASE=CMSSW_BASE_DIR
export CMSSW_SEARCH_PATH=CMSSW_SEARCH_PATH_DIR

melalibdir=${CMSSW_BASE}/lib/slc6_amd64_gcc530/
export LD_LIBRARY_PATH=${melalibdir}:$LD_LIBRARY_PATH

if [ -d "$_CONDOR_SCRATCH_DIR/" ]; then
    workdir=`echo $_CONDOR_SCRATCH_DIR/`;
    cd ${workdir};
fi

savedir=`echo root://cmseos.fnal.gov///store/user/ndefilip/80X/histodir`

echo "Path is" $PATH
echo "Search Path is" $CMSSW_SEARCH_PATH

echo "Working dir is $workdir"
echo "Saving dir is $savedir"

echo "Compiling the macros"
bash compilereference.sh 4mu

./RunReferenceAnalysis ./sig_input_h150.txt 1 ./bkg_input.txt 1 ./data_input.txt 1 site year mc >& ${workdir}/HZZ4LeptonsAnalysis_log

xrdcp --force ${workdir}/HZZ4LeptonsAnalysis_log root://cmseos.fnal.gov///store/user/ndefilip/80X/jobdir/HZZ4LeptonsAnalysis_log

xrdcp --force ${workdir}/output.root    ${savedir}/.
xrdcp --force ${workdir}/output_bnn.txt ${savedir}/.
xrdcp --force ${workdir}/output_bnn.root ${savedir}/.
xrdcp --force ${workdir}/output_txt.txt ${savedir}/.
xrdcp --force ${workdir}/output_txt_vbf.txt ${savedir}/.


if [ -d "$_CONDOR_SCRATCH_DIR" ]; then
 rm -f ${workdir}/*
fi


