#include "Worker.h"

Worker::Worker(double x, double y) : Agent(x, y), carriedEnergy(0) {
    // Создание рабочего 
}

void Worker::moove() {
    Agent::moove();
}

void Worker::collectFood(Food& food) {
    if (food_near(food)){
        cheng_direction();
        distA = 0;
    } 
    if (food_near(food) && food.is_energy() && ame == 0) {
        int gained = food.consumeEnergy();
        carriedEnergy += gained;
        cheng_ame();
    }
}

void Worker::deliverToBase(Base& base) {
    if (base_near(base)){
        cheng_direction();
        distB = 0;
    } 
    if (base_near(base) && ame == 1) {
        resetCarriedEnergy();
        cheng_ame();
    }
}

int Worker::getCarriedEnergy() const {
    return carriedEnergy;
}

void Worker::resetCarriedEnergy() {
    carriedEnergy = 0;
}