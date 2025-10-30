#include "agent.h"
#include <cmath>


agent::agent(int x, int y, double spd, int rad) 
    : speed(spd), radius(rad), energy(100) {
    coordinates[0] = x;
    coordinates[1] = y;
    direction = 0.0;
    ame = 0;
    distA = 0;
    distB = 0;}

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
    void agent::cheng_direction(agent& otheragent){
        direction = otheragent.direction
    }
    bool agent::operator > (const agent& otheragent){
        return distA > otheragent.distA
    }



{
    
}
    