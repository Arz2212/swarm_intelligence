#include "Scout.h"

Scout::Scout(double x, double y) : Agent(x, y) {
}

void Scout::operator=(Agent& other) {
    // Разведчик увеличивает дальность, но не меняет направление
    if (getDistB() > other.getDistB() + 50 ) {
        setDistB(other.getDistB() + 50.0);
    }
    
    if (getDistA() > other.getDistA() + 50) {
        setDistA(other.getDistA() + 50.0);
    }
}