#ifndef FOOD_H
#define FOOD_H

#include <array>

class Food {
private:
    int energy;
    std::array<int, 2> coordinates;
    int rad;

public:
    Food(int e, int x, int y, int r);

    int getRadius() const;
    int getEnergy() const;
    std::array<int, 2> getCoordinates() const;
    
    int consumeEnergy();
    bool is_energy() const;
};

#endif // FOOD_H