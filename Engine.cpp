#include "Part.h"
#include "Engine.h"

#include <cmath>

Engine::Engine():
    Part(), thrust(0), fuel_mass(0), dry_mass(0), density(0), fuel_volume(0), length(0), thickness(0), diameter(0), inner_diameter(0), mass_flow(0), specific_impulse(0), exhaust_velocity(0),
    Dt(0), De(0), At(0),Ae(0),expansion_ratio(0), p1(0), p2(0), p3(0), time(0), burn_rate(0), burn_area(0), fuel_type(" "),
    gamma(0), molar_mass(0), T(0), n(0), characteristic_velocity(0){}

Engine::Engine(double thrust, double fuel_mass, double dry_mass, double density, double fuel_volume, double length, double thickness, double diameter,
        double inner_diameter, double mass_flow, double specific_impuls,
        double exhaust_velocity, double Dt, double De,double At, double Ae, double expansion_ratio, double p1, double p2, double p3, double time, double burn_rate, double burn_area, std::string fuel_type,
        double gamma, double molar_mass, double T, double n, double characteristic_velocity):
    Part(next_id++, std::move(name), mass, cost),
    thrust(thrust), fuel_mass(fuel_mass), dry_mass(dry_mass), density(density), fuel_volume(fuel_volume), length(length),
    thickness(thickness), diameter(diameter), inner_diameter(inner_diameter), mass_flow(mass_flow), specific_impulse(specific_impuls),
    exhaust_velocity(exhaust_velocity), Dt(Dt), De(De), At(At), Ae(Ae),expansion_ratio(expansion_ratio),
    p1(p1), p2(p2), p3(p3), time(time), burn_rate(burn_rate),burn_area(burn_area), fuel_type {std::move(fuel_type)},
    gamma(0), molar_mass(0), T(0), n(0), characteristic_velocity(0){}

void Engine::showInfo() {
    std::cout<<"Двигатель "<<"\"" + name + "\""<<" ID: "<<id<<"\n";
    std::cout<<"Тяга: "<<thrust<<"N\n";
    std::cout<<"Время работы: "<<time<<" с\n";
    std::cout<<"Удельный импульс: "<<specific_impulse<< " с\n";
    std::cout<<"Масса Полная: "<<mass<< "кг\n";
    std::cout<<"Масса сухая: "<<dry_mass<< "кг\n";
    std::cout<<"Масса топлива : "<<fuel_mass<< "кг\n";
}

void Engine::calculateParameters() {
    fuel_volume = (3.14 / 4.0) * (diameter * diameter - inner_diameter * inner_diameter) * length;
    fuel_mass = density * fuel_volume;
    dry_mass = thickness * 2770.0; // density for aluminium composite
    mass = dry_mass + fuel_mass;
    Ae = (3.14 / 4.0) * (De * De);
    At = (3.14 / 4.0) * (Dt * Dt);
    expansion_ratio = Ae / At;
    burn_area = 3.14 * inner_diameter * length;
    mass_flow = density * burn_rate * burn_area;
    time = fuel_mass / mass_flow;

    double gamma_term = (gamma + 1.0) / (2.0 * (gamma - 1.0));
    double Gamma_complex = sqrt(gamma) * pow(2.0 / (gamma + 1.0), gamma_term);
    characteristic_velocity = sqrt((R_UNIV * T) / molar_mass) / Gamma_complex;
    double mass_generation_factor = density * burn_rate * burn_area * characteristic_velocity;
    p1 = pow(mass_generation_factor / At, 1.0 / (1.0 - n));
    p3 = P_ATM;
    p2 = p1 / pow(expansion_ratio, gamma); // Или pow(Ae / At, gamma)

    thrust = (exhaust_velocity * mass_flow) + ((p2 - p3) * Ae);
    specific_impulse = thrust / (mass_flow * 9.8066);


}

void Engine::createPart() {
    std::cout<<"\n---Проектирование двигателя---\n";
    std::cout<<"Введите название двигателя: \n";
    std::getline(std::cin,name);

    std::cout<<"Введите длину (м): \n";
    length = readInput();
    std::cout<<"Введите толщину (м): \n";
    thickness = readInput();
    do {
        std::cout<<"Введите диаметр топливной шашки(м): \n";
        diameter = readInput();
        if (diameter <=0) std::cout<<"Диаметр не может быть меньше нуля\n";
    }while (diameter  <= 0);

    do {
        std::cout<<"Введите внутрений диаметр топливной шашки (м): \n";
        inner_diameter = readInput();
        if (inner_diameter<=0 || inner_diameter >= diameter) std::cout<<"Внутрений диаметр не может быть больше внешнего диаметра\n";
    }while (inner_diameter <= 0 || inner_diameter >= diameter) ;


    std::cout<<"Введите тип топлива [1] - Дымный порох, [2] - Сорбитова карамель [3] - Алюминий-Перхлоратовое горючее\n";
    int choice = readInput();
    switch (choice) {
        case 1:
            fuel_type = "Дымный порох";
            density = 1650;
            exhaust_velocity = 800;
            p1 = 2.0e6;
            burn_rate = 0.012;
            T = 1800.0;
            molar_mass= 32.0;
            gamma = 1.25;
            n = 0.5;
            break;
        case 2:
            fuel_type = "Сорбитова карамель";
            density = 1780;
            exhaust_velocity = 1750;
            p1 = 4.0e6;
            burn_rate = 0.006;
            T = 1700.0;
            molar_mass = 26.5;
            gamma = 1.135;
            n = 0.3;
            break;
        case 3:
            fuel_type = "Перхлоратно-алюминиевое горючее\n";
            density = 1770;
            exhaust_velocity = 2450;
            p1 = 6.0e6;
            burn_rate =  0.008;
            T = 2800.0;
            molar_mass = 24.0;
            gamma = 1.22;
            n = 0.35;
            break;
        default:
            break;
    }

    do {
        std::cout<<"Введите сужение сопла (м): \n";
         Dt= readInput();
        if (Dt <= 0 || Dt >= diameter) std::cout<<"Сужение сопла не может быть больше диаметра шашки\n";
    }while (Dt <= 0 || Dt >= diameter);

    do {
        std::cout<<"Введите расшырение сопла (м): \n";
        De = readInput();
        if (De <=0 || De <= Dt || De >= diameter) std::cout<<"Расширение сопла не может быть меньше сужение сопла ИЛИ больше диаметра шашки\n";
    }while (De <=0 || De <= Dt || De >= diameter);

    calculateParameters();
}

int Engine::next_id = 1;