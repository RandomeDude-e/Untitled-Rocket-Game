#include "Part.h"

Part::Part():
    id(0), name(" "), mass(0), cost(0)
{}

Part::Part(int id, std::string name, double mass, double cost) :
    id(id), name{std::move(name)}, mass(mass), cost(cost){}

int Part::readInput() {
        int value;
        while (!(std::cin>>value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Введите число\n";
        }

        return value;
}
