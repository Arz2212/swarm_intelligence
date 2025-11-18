#include "Agent1.h"
#include <cmath>
#include <cstdlib>
#include "Food.h"
#include "base.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Agent::Agent(double x, double y)
    : speed(10), radius(50), energy(1000), ame(0), direction(0.0), distA(0), distB(0) {
    coordinates[0] = x;
    coordinates[1] = y;
}

void Agent::operator = (Agent& other) {
    if (distB > other.distB){
        distB = other.distB + 50.0;
        if (ame == 1) {
            direction = other.direction;
        }
    }
    if (distA > other.distA){
        distA = other.distA + 50.0;
        if (ame == 0) {
            direction = other.direction;
        }
    }
}

bool Agent::isAlive() const {
    return energy > 0;
}

bool Agent::agent_near(const Agent& otheragent) const {
    double dx = coordinates[0] - otheragent.coordinates[0];
    double dy = coordinates[1] - otheragent.coordinates[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= 50.0;
}

bool Agent::base_near(const Base& otherBase) const {
    auto baseCoords = otherBase.getCoordinates();
    double dx = coordinates[0] - baseCoords[0];
    double dy = coordinates[1] - baseCoords[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= otherBase.getRadius();
}

bool Agent::food_near(const Food& otherFood) const {
    auto foodCoords = otherFood.getCoordinates();
    double dx = coordinates[0] - foodCoords[0];
    double dy = coordinates[1] - foodCoords[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= otherFood.getRadius();
}

void Agent::cheng_direction_and_ame(){
    if (direction > M_PI){
        direction = direction - M_PI;
    } else {
        direction = direction + M_PI;
    }
    ame = (ame + 1) % 2;
}

void Agent::moove() {
    coordinates[0] += speed * cos(direction);
    coordinates[1] += speed * sin(direction);
    
    speed = speed * ((rand() % 400 - 200) / 10000.0 + 1);
    direction = direction + ((rand() % 400 - 200) / 10000.0);
    
    energy--;
}