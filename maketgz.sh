rm -f histos4mu_25ns/*
rm -f histos4e_25ns/*
rm -f histos2e2mu_25ns/*

cat filelist_4mu_2016_Spring16_AN_Bari_miniaod.txt | awk '{print "cp -f "$1" histos4mu_25ns/."}' > a4mu.txt
bash a4mu.txt
cp filelist_4mu_2016_Spring16_AN_Bari_miniaod.txt histos4mu_25ns/.
tar -zcvf histos4mu_25ns_2016_miniaod.tgz histos4mu_25ns

cat filelist_4e_2016_Spring16_AN_Bari_miniaod.txt | awk '{print "cp -f "$1" histos4e_25ns/."}' > a4e.txt
bash a4e.txt
cp filelist_4e_2016_Spring16_AN_Bari_miniaod.txt histos4e_25ns/.
tar -zcvf histos4e_25ns_2016_miniaod.tgz histos4e_25ns

cat filelist_2e2mu_2016_Spring16_AN_Bari_miniaod.txt | awk '{print "cp -f "$1" histos2e2mu_25ns/."}' > a2e2mu.txt
bash a2e2mu.txt
cp filelist_2e2mu_2016_Spring16_AN_Bari_miniaod.txt histos2e2mu_25ns/.
tar -zcvf histos2e2mu_25ns_2016_miniaod.tgz histos2e2mu_25ns
