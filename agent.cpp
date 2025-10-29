#include "agent.h"
#include <cmath>


agent::agent(int x, int y, double spd, int rad) 
    : speed(spd), radius(rad), energy(100) {
        coordinates[0] = x;
    coordinates[1] = y;
    direction = 0.0;
    ame = 0;
    distA = 0;
    distB = 100000000;}

    std::array<int, 2> agent::getPosition() const {
    return coordinates;
}

    int agent::getEnergy() const {
        return energy;
}

    bool agent::isAlive() const {
        return energy > 0;
}
    int agent::getdistA(){
        return distA
    }

    int agent::getdistB(){
        return distB
    } 
void agent::agent_near(const std::vector<std::shared_ptr<Unit>>& all_units)
{
    for (const auto& other_unit : all_units) {
        // Пропускаем проверку с самим собой
        if (other_unit.get() != this) {
            double distance = distanceTo(*other_unit);
            if (distance < 50.0) {
                std::cout << "Юнит " << id << " (" << x << ", " << y 
                          << ") обнаружил соседа на расстоянии " << distance << std::endl;
                exchangeBaseInfo(*other_unit);
                                    std::cout << std::endl;
                }
            }
        }
    }
}
    