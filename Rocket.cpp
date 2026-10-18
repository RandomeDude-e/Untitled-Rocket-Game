#include "Rocket.h"

Rocket::Rocket():
    mass(0), thrust(0), burn_time(0) {}

Rocket::Rocket(double mass, double thrust, double burn_time):
    mass(mass),thrust(thrust), burn_time(burn_time) {}

void Rocket::update(double dt){}