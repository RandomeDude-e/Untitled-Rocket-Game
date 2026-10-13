#include "Part.h"
#include "Engine.h"
#include <cmath>

Engine::Engine():
    Part(next_id++, "", 0, 0), thrust(0), fuel_mass(0), dry_mass(0), density(0), fuel_volume(0), length(0), thickness(0), diameter(0), inner_diameter(0), mass_flow(0), specific_impulse(0), exhaust_velocity(0),
    Dt(0), De(0), At(0),Ae(0),expansion_ratio(0), p1(0), p2(0), p3(0), time(0), burn_rate(0), burn_area(0), fuel_type(" "),
    gamma(0), molar_mass(0), T(0), n(0), characteristic_velocity(0){}

Engine::Engine(double thrust, double fuel_mass, double dry_mass, double density, double fuel_volume, double length, double thickness, double diameter,
        double inner_diameter,double mass_flow, double specific_impulse,
        double exhaust_velocity, double Dt, double De,double At, double Ae, double expansion_ratio, double p1, double p2,double p3, double time, double burn_rate, double burn_area, std::string fuel_type,
        double gamma, double molar_mass, double T, double n, double characteristic_velocity):
    Part(next_id++, std::move(name), mass, cost),
    thrust(thrust), fuel_mass(fuel_mass), dry_mass(dry_mass), density(density), fuel_volume(fuel_volume), length(length),
    thickness(thickness), diameter(diameter), inner_diameter(inner_diameter), mass_flow(mass_flow), specific_impulse(specific_impulse),
    exhaust_velocity(exhaust_velocity), Dt(Dt), De(De), At(At), Ae(Ae),expansion_ratio(expansion_ratio),
    p1(p1), p2(p2), p3(p3), time(time), burn_rate(burn_rate),burn_area(burn_area), fuel_type {std::move(fuel_type)},
    gamma(gamma), molar_mass(molar_mass), T(T), n(n), characteristic_velocity(characteristic_velocity){}

void Engine::showInfo() {
    std::cout<<"Двигатель "<<"\"" + name + "\""<<" ID: "<<id<<"\n";
    std::cout<<"Тяга: "<<thrust<<"N\n";
    std::cout<<"Время работы: "<<time<<" с\n";
    std::cout<<"Удельный импульс: "<<specific_impulse<< " с\n";
    std::cout<<"Масса Полная: "<<mass<< "кг\n";
    std::cout<<"Масса сухая: "<<dry_mass<< "кг\n";
    std::cout<<"Масса топлива : "<<fuel_mass<< "кг\n";
    std::cout<<"Давление в камере згорания: "<<p1<<"Па\n";
}

void Engine::calculateParameters() {
    fuel_volume = (3.14 / 4.0) * (diameter * diameter - inner_diameter * inner_diameter) * length;
    fuel_mass = density * fuel_volume;
    double shell_surface = 3.14 * diameter * length;
    dry_mass = shell_surface * thickness * 2770.0;
    mass = dry_mass + fuel_mass;
    Ae = (3.14 / 4.0) * (De * De);
    At = (3.14 / 4.0) * (Dt * Dt);
    expansion_ratio = Ae / At;
    burn_area = 3.14 * inner_diameter * length;

    double gamma_term = (gamma + 1.0) / (2.0 * (gamma - 1.0));
    double Gamma_complex = std::sqrt(gamma) * std::pow(2.0 / (gamma + 1.0), gamma_term);
    characteristic_velocity = std::sqrt((R_UNIV * T) / molar_mass) / Gamma_complex;

    double P_ref = 3.0e6;
    double a_coefficient = burn_rate / std::pow(P_ref, n);
    double mass_generation_factor = density * a_coefficient * burn_area * characteristic_velocity;
    p1 = std::pow(mass_generation_factor / At, 1.0 / (1.0 - n));
    if (p1 < 100000.0) p1 = 100000.0;
    double current_burn_rate = a_coefficient * std::pow(p1, n);
    mass_flow = density * current_burn_rate * burn_area;
    if (mass_flow > 0) {
        time = fuel_mass / mass_flow;
    } else {
        time = 0;
    }

    p3 = P_ATM;
    p2 = p1 / std::pow(expansion_ratio, gamma);
    double pressure_ratio_term = (gamma - 1.0) / gamma;
    exhaust_velocity = std::sqrt((2.0 * R_UNIV * T / (gamma - 1.0) / molar_mass) *
                       (1.0 - std::pow(p2 / p1, pressure_ratio_term)));
    thrust = (exhaust_velocity * mass_flow) + ((p2 - p3) * Ae);

    if (mass_flow > 0) {
        specific_impulse = thrust / (mass_flow * 9.8066);
    } else {
        specific_impulse = 0;
    }
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
    } while (diameter <= 0);

    do {
        std::cout<<"Введите внутрений диаметр топливной шашки (м): \n";
        inner_diameter = readInput();
        if (inner_diameter <= 0 || inner_diameter >= diameter) std::cout<<"Внутрений диаметр не может быть больше внешнего диаметра\n";
    } while (inner_diameter <= 0 || inner_diameter >= diameter);


    std::cout<<"Введите тип топлива [1] - Дымный порох, [2] - Сорбитова карамель [3] - Алюминий-Перхлоратовое горючее\n";
    int choice = readInput();
    switch (choice) {
        case 1:
            fuel_type = "Дымный порох";
            density = 1650;
            burn_rate = 0.012;
            T = 1800.0;
            molar_mass = 32.0;
            gamma = 1.25;
            n = 0.5;
            break;
        case 2:
            fuel_type = "Сорбитова карамель";
            density = 1780;
            burn_rate = 0.006;
            T = 1700.0;
            molar_mass = 26.5;
            gamma = 1.135;
            n = 0.3;
            break;
        case 3:
            fuel_type = "Перхлоратно-алюминиевое горючее";
            density = 1770;
            burn_rate = 0.008;
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
        Dt = readInput();
        if (Dt <= 0 || Dt >= diameter) std::cout<<"Сужение сопла не может быть больше диаметра шашки\n";
    } while (Dt <= 0 || Dt >= diameter);

    do {
        std::cout<<"Введите расшырение сопла (м): \n";
        De = readInput();
        if (De <= 0 || De <= Dt) std::cout<<"Расширение сопла не может быть меньше сужение сопла ИЛИ больше диаметра шашки\n";
    } while (De <= 0 || De <= Dt);

    calculateParameters();

}

int Engine::next_id = 1;