#include "Assembly.h"

void Assembly::addEngine(int ID,std::vector<std::unique_ptr<Engine>> engines) {
    for (auto it =engines.begin(); it != engines.end();++it) {
        if ((*it)->getId() == ID) {
            selected_engine.push_back(std::move(*it));
            engines.erase(it);
        }else {
            std::cout <<"Детали с таким ID нет\n";
        }
    }
}

void Assembly::addPayload(int ID, std::vector<std::unique_ptr<Payload>> payloads) {
    for (auto it = payloads.begin(); it!=payloads.end();++it) {
        if ((*it)->getId() == ID) {
            selected_payload.push_back(std::move(*it));
            payloads.erase(it);
        }else {
            std::cout <<"Детали с таким ID нет\n";
        }
    }
}

void Assembly::clear() {
    selected_engine.clear();
    selected_payload.clear();
}