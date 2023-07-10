#include <sst/core/sst_config.h>
#include "memorySimulation.h"

memorySimulation::memorySimulation(SST::ComponentId_t id, SST::Params& params):
    SST::Component(id), repeats(0) {

    unsigned int mars_z = params.find<unsigned int>("marsagliaZ", 42);
    cycleNum = params.find<SST::Cycle_t>("cycleNum", 10000);

    this->rng = new SST::RNG::MarsagliaRNG(mars_z);
    // Just register a plain clock for this simple example
    registerClock("100MHz", new SST::Clock::Handler<memorySimulation>(this, &memorySimulation::generateNum));

    // Tell SST to wait until we authorize it to exit
    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();
} 

memorySimulation::~memorySimulation() {
    delete rng;
}

memorySimulation::setup() {
    output.verbose(CALL_INFO, 1, 0, "Component is being setup.\n");
}

memorySimulation::finish() {
    output.verbose(CALL_INFO, 1, 0, "Component is being finished.\n");
}

bool generateNum(SST::Cycle_t cycleCount) {
    uint32_t u32_rng =  rng->generateNextUInt32();

    if (cycleNum % 1000 == 0) {
        output.verbose(CALL_INFO, 1, 0, "Random Number: %d\n", u32_rng);
    }
    if (cycleCount > cycleNum) {
        primaryComponentOKToEndSim();
        return true;
    } else {
        return false;
    }
    return false;
}