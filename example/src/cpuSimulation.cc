// Copyright 2009-2023 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2023, NTESS
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include <sst/core/sst_config.h>
#include "cpuSimulation.h"

cpuSimulation::cpuSimulation( SST::ComponentId_t id, SST::Params& params ) :
	SST::Component(id), repeats(0) {

	output.init("cpuSimulation" + getName() + "-> ", 1, 0, SST::Output::STDOUT);

	printFreq  = params.find<SST::Cycle_t>("printFrequency", 5);
	maxRepeats = params.find<SST::Cycle_t>("repeats", 10);

	if( ! (printFreq > 0) ) {
		output.fatal(CALL_INFO, -1, "Error: printFrequency must be greater than zero.\n");
	}

	output.verbose(CALL_INFO, 1, 0, "Config: maxRepeats=%" PRIu64 ", printFreq=%" PRIu64 "\n",
		static_cast<uint64_t>(maxRepeats), static_cast<uint64_t>(printFreq));

	// Just register a plain clock for this simple example
    	registerClock("100MHz", new SST::Clock::Handler<cpuSimulation>(this, &cpuSimulation::clockTick));

	// Tell SST to wait until we authorize it to exit
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
		int res = this->vectorAdd(1, 2);
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