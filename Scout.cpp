#include "Scout.h"

Scout::Scout(double x, double y) : Agent(x, y) {
    // Создание разведчика без вывода в консоль
}

void Scout::operator=(Agent& other) {
    // Разведчик увеличивает дальность, но не меняет направление
    if (getDistB() > other.getDistB()) {
        setDistB(other.getDistB() + 50.0);
        // Направление не меняется - особенность разведчика
    }
    
    if (getDistA() > other.getDistA()) {
        setDistA(other.getDistA() + 50.0);
        // Направление не меняется - особенность разведчика
    }
}