#ifndef _SIMPLE_EXTERNAL_ELEMENT_H
#define _SIMPLE_EXTERNAL_ELEMENT_H

#include <sst/core/component.h>
#include <sst/core/eli/elementinfo.h>
#include <sst/core/rng/marsaglia.h>
#include <sst/core/link.h>

class memorySimulation : public SST::Component {

public:
    memorySimulation(SST::ComponentId_t id, SST::Params& params);
    ~memorySimulation();

    void setup();
    void finish();

    bool clockTick(SST::Cycle_t currentCycle);
    bool generateNum(SST::Cycle_t currentCycle);

    SST_ELI_REGISTER_COMPONENT(
        memorySimulation,
        "memorySimulation",
        "memorySimulation",
        SST_ELI_ELEMENT_VERSION(1, 0, 0),
        "A Simulation of Memory for SST",
        COMPONENT_CATEGORY_PROCESSOR
    )

    SST_ELI_DOCUMENT_PARAMS(
        {"vecA", "Vector A", "0"},
        {"vecB", "Vector B", "0"},
        {"marsagliaZ", "Number of clock cycles to run for", "10000"}
    )

    SST_ELI_DOCUMENT_PORTS( );

    SST_EFI_DOCUMENT_STATISTICS( );

private:
    SST::Output output;
    uint64_t cycleNum;
    SST::RNG::MarsagliaRNG* rng;
    int vecA;
    int vecB;


}
