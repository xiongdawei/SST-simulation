#include <sst/core/sst_config.h>
#include "cpuSimulation.h"

cpuSimulation::cpuSimulation( SST::ComponentId_t id, SST::Params& params ) :
	SST::Component(id), repeats(0) {

	output.init("cpuSimulation" + getName() + "-> ", 1, 0, SST::Output::STDOUT);

	printFreq  = params.find<SST::Cycle_t>("printFrequency", 5);
	maxRepeats = params.find<SST::Cycle_t>("repeats", 10);
	rng =  new SST::RNG::MarsagliaRNG(23, 32);

	if( ! (printFreq > 0) ) {
		output.fatal(CALL_INFO, -1, "Error: printFrequency must be greater than zero.\n");
	}

	output.verbose(CALL_INFO, 1, 0, "Config: maxRepeats=%" PRIu64 ", printFreq=%" PRIu64 "\n",
		static_cast<uint64_t>(maxRepeats), static_cast<uint64_t>(printFreq));

    	registerClock("1GHz", new SST::Clock::Handler<cpuSimulation>(this, &cpuSimulation::clockTick));


    	registerAsPrimaryComponent();
    	primaryComponentDoNotEndSim();
}

cpuSimulation::~cpuSimulation() {

}

void cpuSimulation::setup() {
	output.verbose(CALL_INFO, 1, 0, "Component is being setup.\n");
}

void cpuSimulation::finish() {
	output.verbose(CALL_INFO, 1, 0, "Component is being finished.\n");
}

bool cpuSimulation::clockTick( SST::Cycle_t currentCycle) {

	if( currentCycle % printFreq == 0 ) {
		int res = this->vectorAdd(rng->generateNextUInt32(), rng->generateNextUInt32());
		output.verbose(CALL_INFO, 1, 0, "Hello World!\n");
		output.verbose(CALL_INFO, 1, 0, "Vector Add Result: %d\n", res);
	}

	repeats++;

	if( repeats == maxRepeats ) {
		primaryComponentOKToEndSim();
		return true;
	} else {
		return false;
	}
}

int cpuSimulation::vectorAdd(int a, int b) {
	return a + b;
}