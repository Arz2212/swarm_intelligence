#include "food.h"

Food::Food(int e, int x, int y) : energy(e), coordinates{x, y} {}

int Food::getEnergy() const {
    return energy;
}

int Food::consumeEnergy() {
    energy -= 1;
    if (energy < 0)
        energy = 0;
    return energy > 0 ? 1 : 0;
}

bool Food::is_energy() const {
    return energy == 0;
}

std::array<int, 2> Food::getCoordinates() const {
    return coordinates;
}