#include <sst/core/sst_config.h>
#include <vector>
#include <random>
#include "cpuEvent.h"

cpuEvent::cpuEvent() {
    std::cout << "Do I be here" << std::endl;
    last = false;
}

cpuEvent::cpuEvent(int vec_len) {
    std::cout << "Do I be here" << std::endl;
    last = false;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10);
    for (int i = 0; i < vec_len; i++) {
        data.push_back(dis(gen));
    }
    last = false;
}

cpuEvent::showData() {
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n" << std::endl;
}