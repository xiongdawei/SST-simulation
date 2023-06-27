CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)

all: libcpuSimulation.so install

libcpuSimulation.so: cpuSimulation.cc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

install:
	sst-register cpuSimulation cpuSimulation_LIBDIR=$(CURDIR)
	sst-register SST_ELEMENT_SOURCE cpuSimulation=$(CURDIR)
	sst-register SST_ELEMENT_TESTS  cpuSimulation=$(CURDIR)/../tests

.PHONY: all install clean

clean:
	rm -f *.o libcpuSimulation.so

