#!/bin/bash

rm -f att.txt

for file in `ls -trd1 jobs4mu/*.sh.* | head -500`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs4e/*.sh.* | head -500`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs2e2mu/*.sh.* | head -500`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt


for file in `ls -trd1 jobs4mu/sleep* | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs4e/sleep* | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs2e2mu/sleep* | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt


for file in `ls -trd1 jobs4mu/*.log | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs4e/*.log | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt

for file in `ls -trd1 jobs2e2mu/*.log | head -200`; do
 echo $file
 echo "rm -f $file" >> att.txt
done

bash att.txt
