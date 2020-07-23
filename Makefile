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

CXX=$(HIPCC)


$(EXECUTABLE): $(OBJECTS) 
	$(HIPCC) $(OBJECTS) -o $@


test: $(EXECUTABLE)
	/opt/rocm/rocprofiler/bin/rpl_run.sh --obj-tracking on --stats -i m2.xml -o profResult.csv $(EXECUTABLE)


clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -f $(HIP_PATH)/src/*.o


