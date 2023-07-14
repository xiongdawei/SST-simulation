#include <sst/core/sst_config.h>

#include "cpuSimulation.h"
#include "cpuEvent.h"

cpuSimulation::cpuSimulation(SST::ComponentId_t id, SST::Params& params) : Component(id) {

    out = new SST::Output("", 1, 0, SST::Output::STDOUT);
    bool found;
    eventsToSend = params.find<int64_t>("eventsToSend", 0, found);
    if (!found) {
        out->fatal(CALL_INFO, -1, "Error in %s: the input did not specify 'eventsToSend' parameter\n", getName().c_str());
    }
    eventSize = params.find<int64_t>("eventSize", 16);

    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();

    top_link = configureLink("top_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
    bottom_link = configureLink("bottom_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
    left_link = configureLink("left_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
	right_link = configureLink("right_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));

    sst_assert(top_link, CALL_INFO, -1, "Error in %s: Top Link configuration failed\n", getName().c_str());
    sst_assert(bottom_link, CALL_INFO, -1, "Error in %s: Bottom Link configuration failed\n", getName().c_str()
    sst_assert(left_link, CALL_INFO, -1, "Error in %s: Left Link configuration failed\n", getName().c_str());
	sst_assert(right_link, CALL_INFO, -1, "Error in %s: Right Link configuration failed\n", getName().c_str());

    registerClock("1GHz", new SST::Clock::Handler<cpuSimulation>(this, &cpuSimulation::clockTic));

    lastEventReceived = false;
}

cpuSimulation::~cpuSimulation()
{
	out->verbose(CALL_INFO, 1, 0, "Component is being destroyed.\n");
    //delete out;
}

void cpuSimulation::handleEvent(SST::Event *ev)
{
    cpuEvent *event = dynamic_cast<cpuEvent*>(ev);
	out->verbose(CALL_INFO, 1, 0, "Received Event with data%lu First data is %d\n", event->payload.size(), event->data[0]);
    event->showData();
    if (event) {
        volatile int sum = 0; 
        for (std::vector<char>::iterator i = event->payload.begin();
             i != event->payload.end(); ++i) {
            sum += *i;
        }
        if (event->last) {
            lastEventReceived = true;
        }
        //delete event;
    } else {
        out->fatal(CALL_INFO, -1, "Error! Bad Event Type received by %s!\n", getName().c_str());
    }
}

bool cpuSimulation::clockTic(SST::Cycle_t cycleCount)
{
    if (eventsToSend > 0) {
        cpuEvent *event = new cpuEvent(10);
        out->verbose(CALL_INFO, 1, 0, "Ababababab");
        for (int i = 0; i < eventSize; i++) {
            event->payload.push_back(1);
        }
        if (eventsToSend == 1) {
            event->last = true;
        }
        eventsToSend--;
        left_link->send(event);
	    right_link->send(event);
        top_link->send(event);
        bottom_link->send(event);
    }

    if (eventsToSend == 0 && lastEventReceived == true) { 
        primaryComponentOKToEndSim(); 
        return true;
    }

    return false;
}
