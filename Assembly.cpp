#include "Assembly.h"

void Assembly::addEngine(int ID,std::vector<std::unique_ptr<Engine>>& engines) {
    bool found = false;
    for (auto it =engines.begin(); it != engines.end();++it) {
        if ((*it)->getId() == ID) {
            selected_engine.push_back(std::move(*it));
            engines.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Детали с таким ID нет на складе\n";
    }
}


void Assembly::addPayload(int ID, std::vector<std::unique_ptr<Payload>>& payloads) {
    bool found = false;
    for (auto it = payloads.begin(); it!=payloads.end();++it) {
        if ((*it)->getId() == ID) {
            selected_payload.push_back(std::move(*it));
            payloads.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Детали с таким ID нет на складе\n";
    }
}


void Assembly::clear() {
    selected_engine.clear();
    selected_payload.clear();
}

std::optional<Rocket> Assembly::buildRocket() {
    if (selected_engine.empty() && selected_payload.empty()) {
        std::cout<<"Цех пуст.\n";
        return std::nullopt;
    }
    double target = 0.0;

    double total_mass = 0.0;
    double total_thrust = 0.0;
    double burn_time = 0.0;

    for (const auto& engine : selected_engine) {
        target = engine->getDiameter();
        total_mass += engine->getMass();
        total_thrust += engine->getThrust();
        burn_time += engine->getBurnTime();
    }

    for (const auto& payload : selected_payload) {
        if (payload->getDiameter() != target) {
            std::cout<<"Диаметр не совпадает с базовым\n";
            return std::nullopt;
        }else {
            total_mass += payload->getMass();
        }
    }


    clear();
    return Rocket{total_mass, total_thrust, burn_time};
}