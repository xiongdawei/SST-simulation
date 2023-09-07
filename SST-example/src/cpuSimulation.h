#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/rng/marsaglia.h>
#include <sst/core/event.h>
#include <sst/core/output.h>
#include <sst/core/timeConverter.h>
#include <sst/core/interfaces/simpleNetwork.h>
#include <algorithm>

class cpuSimulation : public SST::Component
{
public:

    SST_ELI_REGISTER_COMPONENT(
        cpuSimulation,                       // Component class
        "cpuSimulation",         // Component library (for Python/library lookup)
        "cpu",                     // Component name (for Python/library lookup)
        SST_ELI_ELEMENT_VERSION(1,0,0), // Version of the component (not related to SST version)
        "A Simple CPU Simulation",        // Description
        COMPONENT_CATEGORY_PROCESSOR    // Category
    )

    SST_ELI_DOCUMENT_PARAMS(
        {"eventsToSend",     "How many events this component should send.", NULL},
        {"eventSize",        "Payload size for each event, in bytes.", "16"},
        {"ShowRes",          "Show the result of the vector sum", 0},
        {"link_bw",          "Bandwidth of the router link specified in either b/s or B/s (can include SI prefix)."},
        {"packet_size",      "Packet size specified in either b or B (can include SI prefix)."},
        {"packets_to_send",  "Number of packets to send in the test."},
        {"linkcontrol",      "SimpleNetwork class to use to talk to network."},
        {"id",        "Network ID of endpoint."},
        {"num_peers", "Total number of endpoints in network."},
    )

    SST_ELI_DOCUMENT_PORTS(
        {"top_port",     "Link to top component",   {" cpuEvent "} },
        {"bottom_port",  "Link to bottom component",{" cpuEvent "} },
        {"left_port",    "Link to left component",  {" cpuEvent "} },
		{"right_port",   "Link to right component", {" cpuEvent "} }
	)
    
    SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS(
        {"networkIF", "Network interface", "SST::Interfaces::SimpleNetwork" }
    )

    SST_ELI_DOCUMENT_STATISTICS( )

    cpuSimulation(SST::ComponentId_t id, SST::Params& params);
    ~cpuSimulation();
    void showVectorSum();
    SST::ComponentId_t ID;
    void init(unsigned int phase);
    void setup();
    void finish();
    std::vector<int> src;
    std::vector<int> dest;
    std::vector<SST::UnitAlgebra> delays;

private:
    void handleEvent(SST::Event *ev);
    // bool send_handler(int vn);
    // bool recv_handler(int vn);
    virtual bool clockTic(SST::Cycle_t);
    bool clock_handler(SST::Cycle_t cycle);

    bool handle_event(int vn);

    int eventsToSend;
    int eventSize;
    int num_peers;
    bool sending;
    bool initialized;
    bool lastEventReceived;
    bool ShowRes;
    bool propogate = false;

    SST::Interfaces::SimpleNetwork* link_control;
    SST::Link* self_link;
    SST::Link* report_timing;

    void start(SST::Event* ev);

    SST::Output* out;
    SST::Link* top_link;
    SST::Link* bottom_link;
    SST::Link* left_link;
	SST::Link* right_link;
    std::vector<SST::Link*> vector_link;
    std::vector<std::vector<int>> top_data;
    std::vector<std::vector<int>> bottom_data;
    std::vector<std::vector<int>> left_data;
    std::vector<std::vector<int>> right_data;  
    std::vector<std::vector<int>> vector_sum;  
};