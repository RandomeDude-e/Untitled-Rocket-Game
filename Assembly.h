#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

#include "Engine.h"
#include "Payload.h"
#include "Rocket.h"

class Assembly {
private:
    std::vector<std::unique_ptr<Engine>> selected_engine;
    std::vector<std::unique_ptr<Payload>> selected_payload;
public:
    void addEngine(int ID, std::vector<std::unique_ptr<Engine>>& engines);
    void addPayload(int ID, std::vector<std::unique_ptr<Payload>>& payloads);
    void clear();

    std::optional<Rocket> buildRocket();
};