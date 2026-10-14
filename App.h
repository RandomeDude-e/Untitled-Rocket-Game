#pragma once
#include <iostream>
#include "GameData.h"
#include "Part.h"
#include "Engine.h"
#include "Payload.h"

enum class App_State {
    MAINMENU,
    CONTRACTS,
    RANDD,
    ASSEMBLY,
    POLIGON,
    EXIT
};

class App {
private:
    App_State current_state;
    GameData game_data;

    static int readInput();

    void handleMainMenu();
    void handleContracts();
    void handleRANDD();


public:

    void run();
    App();
};