#ifndef _SIMPLE_EXTERNAL_ELEMENT_H
#define _SIMPLE_EXTERNAL_ELEMENT_H

#include <sst/core/component.h>
#include <sst/core/eli/elementinfo.h>

class memorySimulation : public SST::Component {

public:
    memorySimulation(SST::ComponentId_t id, SST::Params& params);
    ~memorySimulation();

    void setup();
    void finish();

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
        {"vecB", "Vector B", "0"}
    )

private:
    SST::Output output;
}
