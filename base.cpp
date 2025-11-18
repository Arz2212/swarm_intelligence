#include "base.h"

Base::Base(int e, int x, int y, int r) : energy(e), coordinates{x, y}, rad(r) {}

int Base::getRadius() const {
    return rad;
}

int Base::getEnergy() const {
    return energy;
}

std::array<int, 2> Base::getCoordinates() const {
    return coordinates;
}

int Base::create() {
    energy--;
    if (energy < 0)
        energy = 0;
    return energy > 0 ? 1 : 0;
}

bool Base::is_energy() const {
    return energy > 0;
}

void Base::receiveEnergy(int amount) {
    energy += amount;
}