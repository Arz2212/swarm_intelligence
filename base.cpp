#include "base.h"

Base::Base(int e, int x, int y) : energy(e), coordinates{x, y} {}

int Base::getEnergy() const {
    return energy;
}

int Base::create() {
    energy -= 1;
    if (energy < 0)
        energy = 0;
    return energy > 0 ? 1 : 0;
}

bool Base::is_energy() const {
    return energy == 0;
}

std::array<int, 2> Base::getCoordinates() const {
    return coordinates;
}