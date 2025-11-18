#include "Food.h"

Food::Food(int e, int x, int y, int r) : energy(e), coordinates{x, y}, rad(r) {}

int Food::getRadius() const {
    return rad;
}

int Food::getEnergy() const {
    return energy;
}

std::array<int, 2> Food::getCoordinates() const {
    return coordinates;
}

int Food::consumeEnergy() {
    if (energy > 0) {
        energy--;
        return 1;
    }
    return 0;
}

bool Food::is_energy() const {
    return energy > 0;
}