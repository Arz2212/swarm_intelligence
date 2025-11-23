#include "Agent1.h"
#include <cmath>
#include <cstdlib>
#include "Food.h"
#include "base.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Agent::Agent(double x, double y)
    : speed(10.0), radius(100), energy(1000), ame(1), direction(rand() % 400/ 100), distA(100000), distB(100000) {
    coordinates[0] = x;
    coordinates[1] = y;
}

void Agent::operator = (Agent& other) {
    if (distB > other.distB + 50.0 ){
        distB = other.distB + 50.0;
        if (ame == 1) {
            direction = atan((other.coordinates[1]- coordinates[1])/(other.coordinates[0]- coordinates[0]));
        }
    }
    if (distA > other.distA + 50.0){
        distA = other.distA + 50.0;
        if (ame == 0) {
            direction = atan((other.coordinates[1]- coordinates[1])/(other.coordinates[0]- coordinates[0]));
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

void Agent::cheng_direction(){
    if (direction > M_PI){
        direction = direction - M_PI;
    } else {
        direction = direction + M_PI;
    }
}
void Agent::cheng_ame(){
    ame = ( ame + 1 ) % 2;
}

void Agent::moove() {
    coordinates[0] += speed * cos(direction);
    coordinates[1] += speed * sin(direction);
    
    // speed = speed * ((rand() % 400 - 200) / 10000.0 + 1);
    // direction = direction + ((rand() % 400 - 200) / 10000.0);
    distA += speed;
    distB += speed;
    
    energy--;
}
