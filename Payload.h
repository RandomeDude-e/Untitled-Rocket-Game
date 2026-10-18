#pragma once
#include "Part.h"

class Payload : public Part {
private:
    static int next_id;
    double payload_mass;
public:
    Payload();
    Payload(std::string name, double mass,double length, double diameter, double cost, double payload_mass);

    void showInfo() override;
    void createPart() override;
    double calculateCost() override;
    double calculateProductionDays() override;
    int getId() override;
};