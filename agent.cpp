#include "agent.h"
#include <cmath>
#include <array>
#include "Food.h"
#include "base.h"

agent::agent(double x, double y, double spd, int rad)
    : speed(spd), radius(rad), energy(100), ame(0), direction(0.0), distA(0), distB(0) {
    coordinates[0] = x;
    coordinates[1] = y;
}

    std::array<double, 2> agent::getPosition() const {
    return coordinates;
}

    int agent::getEnergy() const {
        return energy;
}

    bool agent::isAlive() const {
        return energy > 0;
}
    int agent::getdistA(){
        return distA;
    }

    int agent::getdistB(){
        return distB;
    } 
    void agent::cheng_direction(agent& otheragent){
        direction = otheragent.direction;
    }
    bool agent::operator > (const agent& otheragent){
        return distA > otheragent.distA;
    }
    bool agent::agent_near(const agent& otheragent)
    {
        double f;
        f = sqrt(pow((coordinates[0] + otheragent.coordinates[0]), 2) + pow((coordinates[1] + otheragent.coordinates[1]), 2));
        return f <= 50.0;
    }
    void base_hear(Base& other) const
    {
        if (other.)
    }

    bool food_hear(Food& other) const{
        

    }

    void agent::Moovе(){
        coordinates[0] += speed * cos(direction);
        coordinates[1] += speed * cos(direction);
        speed = speed * ((rand() % 400 - 200) / 10000.0 + 1);
        direction = direction * ((rand() % 400 - 200) / 10000.0 + 1);
        energy-- ;
    }




    

    