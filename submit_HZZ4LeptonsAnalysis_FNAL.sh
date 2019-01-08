#!/bin/bash


# mkdir -p /eos/uscms/store/user/`whoami`/80X/jobdir
# mkdir -p /eos/uscms/store/user/`whoami`/80X/histodir

workdir=${PWD}
echo "Running Mono-HtoZZto4Leptons Analysis with executables RunHZZ4LeptonsAnalysis"


if [ -d "$_CONDOR_SCRATCH_DIR/" ]; then
    workdir=`echo $_CONDOR_SCRATCH_DIR/`;
    cd ${workdir};
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=arch
scramv1 project CMSSW TARfile
cd TARfile     
tar -zxvf ../TARfile.tgz
rm ../TARfile.tgz
cd src
rm ../.SCRAM/arch/ProjectCache.db.gz
scramv1 b ProjectRename
eval `scramv1 runtime -sh`
cd ${workdir}

export LD_LIBRARY_PATH=${CMSSW_BASE}/src/ZZMatrixElement/MELA/data/$SCRAM_ARCH:$LD_LIBRARY_PATH

savedir=`echo root://cmseos.fnal.gov///store/user/\`whoami\`/80X/histodir`

echo "Path is" $PATH

echo "Working dir is $workdir"
echo "Saving dir is $savedir"

echo "Compiling the macros"
bash compilereference.sh 4mu

./RunReferenceAnalysis ./sig_input_h150.txt 1 ./bkg_input.txt 1 ./data_input.txt 1 site year mc >& ${workdir}/HZZ4LeptonsAnalysis_log

tar -zcvf ${workdir}/HZZ4LeptonsAnalysis_log.tgz ${workdir}/HZZ4LeptonsAnalysis_log

xrdcp --force  ${workdir}/HZZ4LeptonsAnalysis_log.tgz root://cmseos.fnal.gov///store/user/`whoami`/80X/jobdir/HZZ4LeptonsAnalysis_log.tgz

xrdcp --force ${workdir}/output.root    ${savedir}/.
xrdcp --force ${workdir}/output_bnn.txt ${savedir}/.
xrdcp --force ${workdir}/output_bnn.root ${savedir}/.
xrdcp --force ${workdir}/output_txt.txt ${savedir}/.
xrdcp --force ${workdir}/output_txt_vbf.txt ${savedir}/.


if [ -d "$_CONDOR_SCRATCH_DIR" ]; then
 rm -f ${workdir}/*
fi


