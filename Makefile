HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif

HIPCC=$(HIP_PATH)/bin/hipcc

TARGET=hcc

SOURCES = vectoradd_hip.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE=./vectoradd_hip.exe

.PHONY: test


all: $(EXECUTABLE) test

CXXFLAGS =-g -mllvm -print-after-all -mllvm -debug-only=machine-scheduler 
CXXFLAGS = -mllvm -amdgpu-cluster-all=$(CLUSTERLDS)
CXXFLAGS = -DUFACTOR=$(UFACTOR) $(EXTRAMLLVM)
#-mllvm -misched=gcn-minreg 

CXX=$(HIPCC)


$(EXECUTABLE): $(OBJECTS) 
	$(HIPCC) $(OBJECTS) -o $@


test: $(EXECUTABLE)
	 rm -rf trace_dir
	 /opt/rocm/rocprofiler/bin/rpl_run.sh --obj-tracking on --stats -d trace_dir -i m2.xml -o profResult.csv $(EXECUTABLE)
	 #/opt/rocm/rocprofiler/bin/rpl_run.sh --obj-tracking on --stats -o statresult.csv $(EXECUTABLE)
#/opt/rocm/rocprofiler/bin/rpl_run.sh --obj-tracking on --stats 

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -f $(HIP_PATH)/src/*.o


