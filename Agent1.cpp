#include "Agent1.h"
#include <cmath>
#include <array>
#include "Food.h"
#include "base.h"

Agent::Agent(double x, double y)
    : speed(10), radius(50), energy(1000), ame(0), direction(0.0), distA(0), distB(0) {
    coordinates[0] = x;
    coordinates[1] = y;
}

void Agent::operator = (Agent& other)
{
    if (distB > other.distB){
        distB = other.distB;
        if (ame == 1) {
            direction = other.direction;
        }
    }
    if (distA > other.distA){
        distA = other.distA;
        if (ame == 0) {
            direction = other.direction;
        }
    }

}
bool Agent::isAlive() const {
    return energy > 0;
}
bool Agent::agent_near(const Agent& otheragent) const
{
    double f;
    f = sqrt(pow((coordinates[0] + otheragent.coordinates[0]), 2) + pow((coordinates[1] + otheragent.coordinates[1]), 2));
    return f <= 50.0;
}

bool Agent::base_near(const Base& otherBase) const
{
    double f;
    f = sqrt(pow((coordinates[0] + otherBase.coordinates[0]), 2) + pow((coordinates[1] + otherBase.coordinates[1]), 2));
    return f <= otherBase.rad;
}

bool Agent::food_near(const Food& otherFood) const
{
    double f;
    f = sqrt(pow((coordinates[0] + otherFood.coordinates[0]), 2) + pow((coordinates[1] + otherFood.coordinates[1]), 2));
    return f <= otherFood.rad;
}
void Agent::cheng_direction_and_ame(){
    if (direction > M_PI){
    direction = direction + M_PI;
    }
    else
    {
    direction = direction - M_PI;
    }
    ame = (ame +1) % 2;
}

void Agent::moove()
{
    coordinates[0] += speed * cos(direction);
    coordinates[1] += speed * sin(direction);
    speed = speed * ((rand() % 400 - 200) / 10000.0 + 1);
    direction = direction * ((rand() % 400 - 200) / 10000.0 + 1);
    energy--;
}



