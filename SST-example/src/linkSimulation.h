#ifndef _BASICLINKS_H
#define _BASICLINKS_H

/*
 * Summary: This example demonstrates different ways creating ports and managing links.
 *
 * Concepts covered:
 *  - Event handlers
 *  - Polling links
 *  - Optional ports
 *  - Vector ports
 *  - Statistics
 *
 * Description
 *  The component has two ports and one port vector. The 'port_handler' port uses an Event handler 
 *  to manage event arrival. The 'port_polled' port is polled using a clock function. The 
 *  'port_vector%d' vector of ports is a set of ports named port_vector0, port_vector1, etc. These 
 *  ports are handled using an Event handler like the 'port_handler' port.
 *  The component also has a statistic for each port that counts the number of bytes received on the port.
 *  All ports expect events of type 'simpleElementExample::basicEvent', which include 
 *
 * Simulation
 *  The component configures each link and creates a clock so that it can poll the polled port. It
 *  1. Event sizes are randomly selected between 0 and eventSize for each event
 *  2. The component uses a Statistic to count the number of payload bytes it received
 *
 *
 */

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/rng/marsaglia.h>
#include "cpuEvent.h"

class basicLinks : public SST::Component
{
public:

/*
 *  SST Registration macros register Components with the SST Core and 
 *  document their parameters, ports, etc.
 *  SST_ELI_REGISTER_COMPONENT is required, the documentation macros
 *  are only required if relevant
 */
    // REGISTER THIS COMPONENT INTO THE ELEMENT LIBRARY
    SST_ELI_REGISTER_COMPONENT(
        basicLinks,                         // Component class
        "cpuSimulation",             // Component library (for Python/library lookup)
        "basicLinks",                       // Component name (for Python/library lookup)
        SST_ELI_ELEMENT_VERSION(1,0,0),     // Version of the component (not related to SST version)
        "Basic: managing links example",    // Description
        COMPONENT_CATEGORY_UNCATEGORIZED    // Category
    )

    // Document the parameters that this component accepts
    // { "parameter_name", "description", "default value or NULL if required" }
    SST_ELI_DOCUMENT_PARAMS(
        { "eventsToSend", "How many events this component should send.", NULL},
        { "eventSize",    "Payload size for each event, in bytes.", "16"}
    )

    // Document the ports that this component has
    // {"Port name", "Description", { "list of event types that the port can handle"} }
    SST_ELI_DOCUMENT_PORTS(
        {"port_handler",    "Link to another component. This port uses an event handler to capture incoming events.", { "simpleElementExample.basicEvent", ""} },
        {"port_polled",     "Link to another component. This port uses polling to capture incoming events.", { "simpleElementExample.basicEvent", ""} },
        {"port_vector%(portnum)d", "Link(s) to another component. These ports demonstrate creating a vector of ports from one port name. Connect port_vector0, port_vector1, etc.", {"simpleElementExample.basicEvent"} },
    )
    
    // Document the statistics that this component provides
    // { "statistic_name", "description", "units", enable_level }
    SST_ELI_DOCUMENT_STATISTICS( 
        {"EventSize_PortHandler", "Records the payload size of each event received on the port_handler port", "bytes", 1},
        {"EventSize_PortPolled", "Records the payload size of each event received on the port_polled port", "bytes", 1},
        {"EventSize_PortVector", "Records the payload size of each event received on the port_vector port(s)", "bytes", 1},
    )

    // Optional since there is nothing to document - see SubComponent examples for more info
    SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS( )

// Class members

    // Constructor. Components receive a unique ID and the set of parameters that were assigned in the Python input.
    basicLinks(SST::ComponentId_t id, SST::Params& params);
    
    // Destructor
    ~basicLinks();
    int vecAdd(int a, int b);

private:
    // Event handler, called when an event is received on the handler link
    void handleEvent(SST::Event *ev);

    // Event handler, called when an event is received on one of link vector elements
    void handleEventWithID(SST::Event *ev, int linknum);

    // Clock handler, called on each clock cycle
    virtual bool clockTic(SST::Cycle_t);

    // Parameters
    int64_t eventsToSend;
    int eventSize;
    int lastEventReceived;

    // Random number generator
    SST::RNG::MarsagliaRNG* rng;

    // SST Output object, for printing, error messages, etc.
    SST::Output* out;

    // Links
    SST::Link* linkHandler;
    SST::Link* linkPolled;
    std::vector<SST::Link*> linkVector;
    
    // Statistics
    Statistic<uint64_t>* stat_portHandler;
    Statistic<uint64_t>* stat_portPolled;
    std::vector<Statistic<uint64_t>*> stat_portVector;

};

#endif 
