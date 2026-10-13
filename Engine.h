#pragma once
#include "Part.h"


class Engine : public Part {
private:
    const double P_ATM = 101325.0;
    const double R_UNIV = 8314.46;

    static int next_id;
    double thrust;
    double fuel_mass;
    double dry_mass;
    double density;
    double fuel_volume;
    double length;
    double thickness;
    double diameter;
    double inner_diameter; //BATES
    double mass_flow;
    double specific_impulse;
    double exhaust_velocity;
    double Dt;
    double De;
    double At;
    double Ae;
    double expansion_ratio;// Ae/A*
    double p1; //pressure inside combustion chamber
    double p2; //pressure in nozzle exit
    double p3;
    double time;
    double burn_rate;
    double burn_area;
    std::string fuel_type;

    double gamma; //adiabatic coefficient
    double molar_mass;
    double T;
    double n;//n exponent
    double characteristic_velocity; // exhaust velocity but without geometry
public:
    Engine();
    Engine(double thrust, double fuel_mass, double dry_mass,double density, double fuel_volume, double length, double thickness, double diameter,
        double inner_diameter,double mass_flow, double specific_impulse,
        double exhaust_velocity, double Dt, double De,double At, double Ae, double expansion_ratio, double p1, double p2,double p3, double time, double burn_rate, double burn_area, std::string fuel_type,
        double gamma, double molar_mass, double T, double n, double characteristic_velocity);

    void showInfo() override ;
    void calculateParameters() override ;
    void createPart() override ;

};