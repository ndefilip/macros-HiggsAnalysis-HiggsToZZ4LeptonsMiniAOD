#!/bin/bash

rm -f att.txt

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
