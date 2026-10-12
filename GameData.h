#pragma once
#include <vector>
#include <iostream>

#include "Contracts.h"

class GameData {
private:
    double money;
    double player_rep;
    std::vector<Contracts> available_contracts;
    std::vector<Contracts> active_contracts;


public:
    GameData();
    void init_contracts();
    void accept_contract(int ID);
    void reject_contract(int ID);
    void print_available_contracts() const;
    void print_active_contracts() const;
};