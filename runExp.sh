#!/bin/bash
for (( c=1; c<=10; c++ ))
do  
     #echo "Cluster $c loads"
     export CLUSTERLDS=$c
     make clean; make
     cat  profResult.csv >> results/profResultFinal2.csv
     csvtool readable results/profResultFinal.csv
     /home/prithayan/work/AMD/rocm/hip//bin/hipcc -mllvm -amdgpu-cluster-all=${c}  -S  -c -o  coalL1_nomod_cluster_${CLUSTERLDS}.s  vectoradd_hip.cpp 

done
