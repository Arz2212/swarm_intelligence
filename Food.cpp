#include "food.h"

Food::Food(int e, int x, int y, int r) : energy(e), coordinates{x, y}, rad(r){}

int Food::getEnergy() const {
    return energy;
}
int Food::getRaius() const{
    return rad;
}

int Food::consumeEnergy() {
    energy--;
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