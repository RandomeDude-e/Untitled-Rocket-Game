#pragma once
#include <vector>
#include <iostream>
#include <memory>

#include "Contracts.h"
#include "Part.h"
#include "Engine.h"
#include "Payload.h"

class GameData {
private:
    double money;
    double player_rep;
    double current_day;
    std::vector<Contracts> available_contracts;
    std::vector<Contracts> active_contracts;

    std::vector<std::unique_ptr<Part>> parts; // warehouse


public:
    GameData();
    void init_contracts();
    void accept_contract(int ID);
    void reject_contract(int ID);
    void print_available_contracts() const;
    void print_active_contracts() const;

    void addEngineToWarehouse();
    void addPayloadToWarehouse();
    void showWarehouse() const;

};