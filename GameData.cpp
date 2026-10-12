#include "GameData.h"

GameData::GameData():
    money(2500), player_rep(0) {
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
