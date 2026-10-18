#pragma once

class Rocket {
private:
    double mass;
    double thrust;
    double burn_time;

public:
    Rocket();
    Rocket(double mass, double thrust, double burn_time);

    void update(double dt);
};