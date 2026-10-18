#include "Payload.h"

#include "Engine.h"

Payload::Payload():
    Part(next_id++, "", 0, 0, 0, 0), payload_mass(0){}

Payload::Payload(std::string name, double mass, double length, double diameter, double cost,double payload_mass):
    Part(next_id++, std::move(name), mass, length, diameter, cost), payload_mass(payload_mass){}

void Payload::showInfo() {
    std::cout<<"\""<<" ID: "<<id<<"\n";
    std::cout<<"Масса полезной нагрузки: "<<payload_mass<<"кг\n";
    std::cout<<"Диаметр: "<<diameter<<"м\n";
    std::cout<<"Длина: "<<length<<"м\n";
    std::cout<<"Цена: "<<cost<<"$\n";
}

void Payload::createPart() {
    std::cout<<"\n---Проектирование полезной нагрузки---\n";
    std::cout<<"Введите массу полезной нагрузки: \n";
    payload_mass = readInput();

    std::cout<<"Введите длину (м): \n";
    length = readInput();
    std::cout<<"Введите диаметр(м): \n";
    diameter = readInput();

}

double Payload::calculateCost() {
    cost = payload_mass * 15.0;
    return cost;
}

double Payload::calculateProductionDays() {
    double production_days = 1 + (payload_mass / 15);
    return production_days;
}

int Payload::getId() {
    return id;
}

int Payload::next_id = 1;