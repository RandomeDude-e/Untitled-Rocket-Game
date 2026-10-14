#include "GameData.h"


GameData::GameData():
    money(7500), player_rep(0), current_day(1){
        init_contracts();
}

void GameData::init_contracts() {
    while (available_contracts.size() < 3) {
        available_contracts.push_back(Contracts::generateContract(player_rep));

    }
}

void GameData::accept_contract(int ID) {

    if (active_contracts.size()>=3) {
        std::cout <<"Лимит превышен!\n";
        return;
    }
    int target = -1;

    for (int i = 0; i <available_contracts.size(); i++) {
        if (available_contracts[i].getId() ==  ID) {
            target = i;
            break;
        }
    }

    if (ID<=0 || target == -1) {
        std::cout<<"Контракта с таким номером не существует\n";
        return;
    }

    available_contracts[target].setIsActive(true);
    money += available_contracts[target].getAdvance();

    active_contracts.push_back(std::move(available_contracts[target]));
    available_contracts.erase(available_contracts.begin() + target);
    init_contracts();


}

void GameData::reject_contract(int ID) {
    int target = -1;
    for (int i = 0; i<active_contracts.size(); i++) {
        if (active_contracts[i].getId() == ID) {
            target = i;
            break;

        }
    }
    if (ID<=0 || target == -1) {
        std::cout<<"Контракта с таким номером не существует\n";
        return;
    }


    active_contracts[target].setIsFailed(true);
    active_contracts[target].setIsActive(false);
    money -= active_contracts[target].getPenalty();
    player_rep-=active_contracts[target].getRepFailure();

    active_contracts.erase(active_contracts.begin() + target);
}

void GameData::print_available_contracts() const{
    for (const auto& contract : available_contracts) {
        std::cout<<"\n=================================================================\n";
        std::cout<<"Контракт # "<<contract.getId()<<" "<< contract.getTitle()<<"\n";
        std::cout<<contract.getDescription()<<"\n";
        std::cout<<"Награда: "<<contract.getPayment()<<"\n";
        std::cout<<"Аванс: "<<contract.getAdvance()<<"\n";
        std::cout<<"Репутация при завершении: "<<contract.getRepSuccess()<<"\n";
        std::cout<<"Репутация при провале ИЛИ отказе: "<<contract.getRepFailure()<<"\n";
        std::cout<<"Штраф при провале ИЛИ отказе: "<<contract.getPenalty()<<"\n";
        std::cout<<"Дедлайн: "<<contract.getDeadline()<<" дней\n";

    }
    std::cout<<"\n=================================================================\n";
}

void GameData::print_active_contracts() const{
    for (const auto& contract : active_contracts) {
        std::cout<<"\n=================================================================\n";
        std::cout<<"Контракт # "<<contract.getId()<<" "<<contract.getTitle()<<"\n";
        std::cout<<contract.getDescription()<<"\n";
        std::cout<<"Дедлайн: "<<contract.getDeadline()<<" дней\n";
    }
    std::cout<<"\n=================================================================\n";
}

void GameData::addEngineToWarehouse() {
    auto new_engine = std::make_unique<Engine>();
    new_engine->createPart();
    double engine_cost = new_engine->calculateCost();

    std::cout << "Стоимость создания: " << engine_cost << "$\n";
    new_engine->showInfo();
    std::cout << "[1] - Создать\n";
    std::cout << "[2] - Уничтожить\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        if (money >= engine_cost) {
            money -= engine_cost;
            current_day += new_engine->calculateProductionDays();
            parts.push_back(std::move(new_engine));
            std::cout << "Двигатель успешно добавлен на склад!\n";
        } else {
            std::cout << "Недостаточно средств\n";
        }
    } else if (choice == 2) {
        std::cout << "Двигатель уничтожен\n";
    } else {
        std::cout << "Неверный выбор\n";
    }
}

void GameData::addPayloadToWarehouse() {
    auto new_payload = std::make_unique<Payload>();
    new_payload->createPart();
    double payload_cost = new_payload->calculateCost();

    std::cout << "Стоимость создания: " << payload_cost << "$\n";
    new_payload->showInfo();
    std::cout << "[1] - Создать\n";
    std::cout << "[2] - Уничтожить\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        if (money >= payload_cost) {
            money -= payload_cost;
            current_day += new_payload->calculateProductionDays();
            parts.push_back(std::move(new_payload));
            std::cout << "Деталь успешно добавлена на склад!\n";
        } else {
            std::cout << "Недостаточно средств\n";
        }
    } else if (choice == 2) {
        std::cout << "Полезная нагрузка уничтожена\n";
    } else {
        std::cout << "Неверный выбор\n";
    }
}

void GameData::showWarehouse() const{
    std::cout<<"\n---Склад Деталей---\n";
    if (parts.empty()) std::cout<<"Склад пуст\n";
    for (const auto& part : parts) {
        part->showInfo();
    }
}
