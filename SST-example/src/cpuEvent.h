#ifndef _BASICEVENT_H
#define _BASICEVENT_H

#include <sst/core/event.h>
#include <vector>
#include <random>

enum Direction {TOP, BOTTOM, LEFT, RIGHT};

class cpuEvent : public SST::Event
{
public:
    cpuEvent() {};
    cpuEvent(int vec_len, SST::ComponentId_t id, Direction dir_) {
        last = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 10);
        for (int i = 0; i < vec_len; i++) {
            data.push_back(dis(gen));
        }
        last = false;
        org_id = id;
        dir = dir_;
    };
    std::vector<char> payload;
    std::vector<int> data;
    SST::ComponentId_t org_id;
    Direction dir;
    bool last;
    void serialize_order(SST::Core::Serialization::serializer &ser)  override {
        Event::serialize_order(ser);
        ser & payload;
        ser & last;
    }
    void showData() {
        for (int i = 0; i < data.size(); i++) {
            std::cout << data[i] << " ";
        }
        std::cout << "Data Coming from: " << org_id << "\n" << std::endl;
    };

    ImplementSerializable(cpuEvent);
};

#endif 
