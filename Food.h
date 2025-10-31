#ifndef FOOD_H
#define FOOD_H

#include <array>

class Food {
private:
    int energy;
    std::array<int, 2> coordinates; // x, y
    int rad;

public:
    Food(int e, int x, int y, int r);

    int getRaius() const;
    int getEnergy() const; // возврат количества энергии
    int consumeEnergy();  // уменьшает энергию на 1 и возвращает 1 (если >0) или 0 (если ==0)
    bool is_energy() const; // проверка осталась ли еда 
    std::array<int, 2> getCoordinates() const; // возврат координат 
};

#endif // FOOD_H