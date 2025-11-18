#include "Worker.h"

Worker::Worker(double x, double y) : Agent(x, y), carriedEnergy(0) {
    // Создание рабочего без вывода в консоль
}

void Worker::moove() {
    // Рабочий двигается как обычный агент
    Agent::moove();
}

void Worker::collectFood(Food& food) {
    if (food_near(food) && food.is_energy()) {
        int gained = food.consumeEnergy();
        carriedEnergy += gained;
    }
}

void Worker::deliverToBase(Base& base) {
    if (base_near(base) && carriedEnergy > 0) {
        base.receiveEnergy(carriedEnergy);
        resetCarriedEnergy();
    }
}

int Worker::getCarriedEnergy() const {
    return carriedEnergy;
}

void Worker::resetCarriedEnergy() {
    carriedEnergy = 0;
}