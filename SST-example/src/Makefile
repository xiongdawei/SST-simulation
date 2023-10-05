CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)

all: libcpuSimulation.so  trafficgen.so install

libcpuSimulation.so: cpuSimulation.cc cpuEvent.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

trafficgen.so: trafficGenerator.cc trafficGenerator.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

# liblinkSimulation.so: linkSimulation.cc cpuEvent.h
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

install:
	sst-register cpuSimulation cpuSimulation_LIBDIR=$(CURDIR)
	sst-register SST_ELEMENT_SOURCE cpuSimulation=$(CURDIR)
	sst-register SST_ELEMENT_TESTS  cpuSimulation=$(CURDIR)/../tests
	sst-register trafficgen trafficgen_LIBDIR=$(CURDIR)
	sst-register SST_ELEMENT_SOURCE trafficgen=$(CURDIR)
	sst-register SST_ELEMENT_TESTS  trafficgen=$(CURDIR)/../tests

.PHONY:
	clean install make all

clean:
	rm -f *.so
