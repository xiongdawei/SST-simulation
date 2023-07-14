#ifndef _BASICEVENT_H
#define _BASICEVENT_H

#include <sst/core/event.h>
#include <vector>
#include <random>

class cpuEvent : public SST::Event
{
public:
    cpuEvent() {};
    cpuEvent(int vec_len) {
        std::cout << "Do I be here" << std::endl;
        last = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 10);
        for (int i = 0; i < vec_len; i++) {
            data.push_back(dis(gen));
        }
        last = false;
    };
    std::vector<char> payload;
    std::vector<int> data;
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
        std::cout << "\n" << std::endl;
    };

    ImplementSerializable(cpuEvent);
};

#endif 
