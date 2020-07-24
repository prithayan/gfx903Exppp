#!/bin/bash
for (( c=1; c<=65; c*=2 ))
do  
     #echo "Cluster $c loads"
     export UFACTOR=$c
     rm -rf trace_dir
     export EXTRAMLLVM=""
     make clean; make
     cat  profResult.csv >> results/profResultFinalMaxOc.csv
     make
     cat  profResult.csv >> results/profResultFinalMaxOc.csv
     make
     cat  profResult.csv >> results/profResultFinalMaxOc.csv
     export EXTRAMLLVM="-mllvm -misched=gcn-minreg"
     make clean; make
     cat  profResult.csv >> results/profResultFinalMinReg.csv
     make
     cat  profResult.csv >> results/profResultFinalMinReg.csv
     make
     cat  profResult.csv >> results/profResultFinalMinReg.csv
     /opt/rocm/hip/bin/hipcc -DUFACTOR=${UFACTOR} -S   -c -o vectoradd_hip_maxO_U${c}.s vectoradd_hip.cpp
     /opt/rocm/hip/bin/hipcc -DUFACTOR=${UFACTOR} -S -mllvm -misched=gcn-minreg  -c -o vectoradd_hip_minR_U${c}.s vectoradd_hip.cpp
     #-mllvm -misched=gcn-minreg 
     cat results/profResultFinalMaxOc.csv
     cat results/profResultFinalMinReg.csv

done
