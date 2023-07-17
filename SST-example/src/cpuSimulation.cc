#include <sst/core/sst_config.h>
#include <algorithm>

#include "cpuSimulation.h"
#include "cpuEvent.h"

cpuSimulation::cpuSimulation(SST::ComponentId_t id, SST::Params& params) : Component(id) {

    out = new SST::Output("", 1, 0, SST::Output::STDOUT);
    ID = id;
    out->verbose(CALL_INFO, 1, 0, "The Component ID is %llu\n", ID);
    bool found;
    eventsToSend = params.find<int64_t>("eventsToSend", 0, found);
    ShowRes = params.find<int>("ShowRes", 0);
    if (!found) {
        out->fatal(CALL_INFO, -1, "Error in %s: the input did not specify 'eventsToSend' parameter\n", getName().c_str());
    }
    
    eventSize = params.find<int64_t>("eventSize", 16);

    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();
    if (isPortConnected("top_port")) {
        top_link = configureLink("top_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
        sst_assert(top_link,    CALL_INFO, -1, "Error in %s: Top Link configuration failed\n", getName().c_str());
    }
    if (isPortConnected("bottom_port")) {
        bottom_link = configureLink("bottom_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
        sst_assert(bottom_link, CALL_INFO, -1, "Error in %s: Bottom Link configuration failed\n", getName().c_str());
    }
    if (isPortConnected("left_port")) {
        left_link = configureLink("left_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
        sst_assert(left_link,   CALL_INFO, -1, "Error in %s: Left Link configuration failed\n", getName().c_str());
    }
    if (isPortConnected("right_port")) {
        right_link = configureLink("right_port", new SST::Event::Handler<cpuSimulation>(this, &cpuSimulation::handleEvent));
        sst_assert(right_link,  CALL_INFO, -1, "Error in %s: Right Link configuration failed\n", getName().c_str());
    }
    registerClock("1GHz", new SST::Clock::Handler<cpuSimulation>(this, &cpuSimulation::clockTic));
    lastEventReceived = false;
}

cpuSimulation::~cpuSimulation()
{

    int max_size = std::max(std::max(top_data.size(), bottom_data.size()), std::max(left_data.size(), right_data.size()));
    for (int i = 0; i < max_size; i++) {
        std::vector<int> temp;
        for (int j = 0; j < eventSize; ++j) {
            int temp_data = 0;
            if (top_data.size() > i) {
                temp_data += top_data[i][j];
            } 
            if (bottom_data.size() > i) {
                temp_data += bottom_data[i][j];
            }
            if (left_data.size() > i) {
                temp_data += left_data[i][j];
            }
            if (right_data.size() > i) {
                temp_data += right_data[i][j];
            }
            temp.push_back(temp_data);
        }
        vector_sum.push_back(temp);
    }
    if (ShowRes == 1) {
        showVectorSum();
    }
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
        switch (event->dir) {
            case TOP:
                top_data.push_back(event->data);
                out->verbose(CALL_INFO, 1, 0, "-----|||||------\n");
                break;
            case BOTTOM:
                bottom_data.push_back(event->data);
                break;
            case LEFT:
                left_data.push_back(event->data);
                break;
            case RIGHT:       
                right_data.push_back(event->data);
                break;
        }

    } else {
        out->fatal(CALL_INFO, -1, "Error! Bad Event Type received by %s!\n", getName().c_str());
    }
}

bool cpuSimulation::clockTic(SST::Cycle_t cycleCount)
{
    if (eventsToSend > 0) {
        cpuEvent *event_to_top = new cpuEvent(eventSize, ID, BOTTOM);
        cpuEvent *event_to_bottom = new cpuEvent(eventSize, ID, TOP);
        cpuEvent *event_to_left = new cpuEvent(eventSize, ID, RIGHT);
        cpuEvent *event_to_right = new cpuEvent(eventSize, ID, LEFT);
        for (int i = 0; i < eventSize; i++) {
            event_to_top->payload.push_back(1);
            event_to_bottom->payload.push_back(1);
            event_to_left->payload.push_back(1);
            event_to_right->payload.push_back(1);
        }
        if (eventsToSend == 1) {
            event_to_top->last = true;
            event_to_bottom->last = true;
            event_to_left->last = true;
            event_to_right->last = true;
        }
        eventsToSend--;
        if (isPortConnected("top_port")) {
            top_link->send(event_to_top);
        }
        if (isPortConnected("bottom_port")) {
            bottom_link->send(event_to_bottom);
        }
        if (isPortConnected("left_port")) {
            left_link->send(event_to_left);
        }
        if (isPortConnected("right_port")) {
            right_link->send(event_to_right);
        }
    }
    if (ShowRes == 1) {
        out->verbose(CALL_INFO, 1, 0, "Clock Ticks: %lld\n", cycleCount);
        if (bottom_data.size() > 0) {
            for (int i = 0; i < bottom_data.size(); ++i) {
                for (int j = 0; j < eventSize; ++j) {
                    out->verbose(CALL_INFO, 1, 0, "Bottom data %d\n",bottom_data[i][j]);
                }   
            } 
        } else {
            out->verbose(CALL_INFO, 1, 0, "Bottom data is empty\n");
        }    
    }
    if (eventsToSend == 0 && lastEventReceived == true) { 
        primaryComponentOKToEndSim(); 
        return true;
    }

    return false;
}

void cpuSimulation::showVectorSum() {
    std::cout << "Data from top: " << std::endl;
    for (int i = 0; i < top_data.size(); ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < eventSize; ++j) {
            std::cout << top_data[i][j] << " | ";
        }
    }
    std::cout << "\n" << std::endl;
    std::cout << "Data from bottom: " << std::endl;
    for (int i = 0; i < bottom_data.size(); ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < eventSize; ++j) {
            std::cout << bottom_data[i][j] << " | ";
        }
    }
    std::cout << "\n" << std::endl;
    std::cout << "Data from left: " << std::endl;
    for (int i = 0; i < left_data.size(); ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < eventSize; ++j) {
            std::cout << left_data[i][j] << " | ";
        }
    }
    std::cout << "\n" << std::endl;
    std::cout << "Data from right: " << std::endl;
    for (int i = 0; i < right_data.size(); ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < eventSize; ++j) {
            std::cout << right_data[i][j] << " | ";
        }
    }
    std::cout << "\n" << std::endl;
    std::cout << "The vector sum is: " << std::endl;
    for (int i = 0; i < vector_sum.size(); i++) {
        for (int j = 0; j < eventSize; j++) {
            std::cout << vector_sum[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}