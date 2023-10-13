#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/rng/marsaglia.h>
#include <sst/core/interfaces/simpleNetwork.h>

#include <algorithm>

class cpuSimulation : public SST::Component
{
public:


    SST_ELI_REGISTER_COMPONENT(
        cpuSimulation,                       // Component class
        "cpuSimulation",         // Component library (for Python/library lookup)
        "cpuPC",                     // Component name (for Python/library lookup)
        SST_ELI_ELEMENT_VERSION(1,0,0), // Version of the component (not related to SST version)
        "A Simple CPU Simulation for testing port control",        // Description
        COMPONENT_CATEGORY_PROCESSOR    // Category
    )

    SST_ELI_DOCUMENT_PARAMS(
        { "eventsToSend", "How many events this component should send.", NULL},
        { "eventSize",    "Payload size for each event, in bytes.", "16"},
        { "ShowRes",      "Show the result of the vector sum", 0}
    )

    SST_ELI_DOCUMENT_PORTS(
        {"top_port",     "Link to top component",   {" cpuEvent "} },
        {"bottom_port",  "Link to bottom component",{" cpuEvent "} },
        {"left_port",    "Link to left component",  {" cpuEvent "} },
		{"right_port",   "Link to right component", {" cpuEvent "} },
        {"rtr", "Port that hooks up to router.", {" cpuEvent "}},
	)
    
    SST_ELI_DOCUMENT_STATISTICS( )

    SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS(
        {"networkIF", "Network interface", "SST::Interfaces::SimpleNetwork"}
     )

    cpuSimulation(SST::ComponentId_t id, SST::Params& params);
    ~cpuSimulation();
    void showVectorSum();
    SST::ComponentId_t ID;

private:

    void handleEvent(SST::Event *ev);
    virtual bool clockTic(SST::Cycle_t);

    int eventsToSend;
    int eventSize;
    bool lastEventReceived;
    bool ShowRes;
    bool propogate = false;

    SST::Output* out;

    SST::Link* top_link;git
    SST::Link* bottom_link;
    SST::Link* left_link;
	SST::Link* right_link;
    SST::Interfaces::SimpleNetwork *link_control;
 
};