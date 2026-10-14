#include "App.h"

App::App()
    :current_state(App_State::MAINMENU),
    game_data()
{}

int App::readInput() {
    int value;
    while (!(std::cin>>value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Введите число\n";
    }

    return value;
}

void App::handleMainMenu() {
    std::cout<<"---Главное меню---\n";
    std::cout<<"[1] Бюро Управления Контрактами\n";
    std::cout<<"[2] Разработка и Проектирование\n";
    std::cout<<"[3] Сборка\n";
    std::cout<<"[4] Полигон\n";
    std::cout<<"[5] Выход\n";

    int choice = readInput();

    switch (choice) {
        case 1:
            current_state = App_State::CONTRACTS;
            break;
        case 2:
            current_state = App_State::RANDD;
            break;
        case 3:
            current_state = App_State::ASSEMBLY;
            break;
        case 4:
            current_state = App_State::POLIGON;
            break;
        case 5:
            current_state = App_State::EXIT;
            break;
        default:
            std::cout<<"Недопустимое значение\n";
            break;
    }

}

void App::handleContracts() {
    std::cout << "---Бюро Управления Контрактами---\n";
    std::cout << "[1] - Принять контракт\n";
    std::cout << "[2] - Отклонить контракт\n";
    std::cout << "[3] - Выйти из БУК \n";

    std::cout<<"\nДоступные контракты\n";
    game_data.print_available_contracts();
    std::cout<<"\nАктивные контракты\n";
    game_data.print_active_contracts();
    int choice = readInput();


    switch (choice) {
        case 1: {
            std::cout<<"Введите номер контракта:\n";
            int id = readInput();
            game_data.accept_contract(id);
            break;
        }

        case 2: {
            std::cout<<"Введите номер контракта\n";
            int id = readInput();
            game_data.reject_contract(id);
            break;
        }

        case 3:
            current_state = App_State::MAINMENU;
            break;

        default:
            break;

    }
}

void App::handleRANDD() {
    std::cout << "---Разработка и Проектирования---\n";
    std::cout << "[1] - Разработать двигатель\n";
    std::cout << "[2] - Разработать полезную нагрузку\n";
    std::cout << "[3] - Склад \n";
    std::cout << "[4] - Выйти и центра Разработки и Проектирования\n";

    int choice = readInput();
    switch (choice) {
        case 1:
            game_data.addEngineToWarehouse();
            break;
        case 2:
            game_data.addPayloadToWarehouse();
            break;
        case 3:
            game_data.showWarehouse();
            break;
        case 4:
            current_state = App_State::MAINMENU;
            break;
        default:
            break;

    }

}




void App::run() {
    while (current_state != App_State::EXIT) {
        switch (current_state) {
            case App_State::MAINMENU: handleMainMenu(); break;
            case App_State::CONTRACTS: handleContracts(); break;
            case App_State::RANDD: handleRANDD(); break;
            default: break;
        }

    }

}