#pragma once
#include <string>
#include <iostream>
#include <limits>

class Part {
protected:
    int id;

    std::string name;
    double mass;
    double cost;

public:
    Part();
    Part(int id, std::string name, double mass, double cost);
    virtual double readInput();
    virtual void showInfo() = 0;
    virtual void calculateParameters() = 0;
    virtual void createPart() = 0;
    virtual ~Part() = default;
};