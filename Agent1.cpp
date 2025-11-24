#include "Agent1.h"
#include <cmath>
#include <cstdlib>
#include "Food.h"
#include "base.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Agent::Agent(double x, double y)
    : speed(10.0), radius(100), energy(100000), ame(rand() %2), direction(rand() % 400/ 100), distA(100000), distB(100000), 
      deafTimer(0) {
    coordinates[0] = x;
    coordinates[1] = y;
}


void Agent::interact(const Agent& other) {
    // 1. Если агент "глухой" (таймер > 0), он игнорирует всех
    if (deafTimer > 0) return; 

    bool updated = false; // Флаг: узнали ли мы что-то полезное?

    // --- Логика для БАЗЫ ---
    if (distB > other.distB + 50.0) {
        distB = other.distB + 50.0;
        
        if (ame == 1) { // Если ищем базу
            double dy = other.coordinates[1] - coordinates[1];
            double dx = other.coordinates[0] - coordinates[0];
            direction = atan2(dy, dx);
        }
        updated = true; // Мы обновили информацию
    }

    // --- Логика для ЕДЫ ---
    if (distA > other.distA + 50.0) {
        distA = other.distA + 50.0;
        
        if (ame == 0) { // Если ищем еду
            double dy = other.coordinates[1] - coordinates[1];
            double dx = other.coordinates[0] - coordinates[0];
            direction = atan2(dy, dx);
        }
        updated = true; // Мы обновили информацию
    }

    // 2. Если информация обновилась, включаем "глухоту" на 5 ходов
    if (updated) {
        deafTimer = 0;
    }
}
// проверка жив ли агент 
bool Agent::isAlive() const {
    return energy > 0;
}
// проверка агента рядом 
bool Agent::agent_near(const Agent& otheragent) const {
    double dx = coordinates[0] - otheragent.coordinates[0];
    double dy = coordinates[1] - otheragent.coordinates[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= 50.0;

}
// проверка базы рядом
bool Agent::base_near(const Base& otherBase) const {
    auto baseCoords = otherBase.getCoordinates();
    double dx = coordinates[0] - baseCoords[0];
    double dy = coordinates[1] - baseCoords[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= otherBase.getRadius();
}
// проверка еды рядом 
bool Agent::food_near(const Food& otherFood) const {
    auto foodCoords = otherFood.getCoordinates();
    double dx = coordinates[0] - foodCoords[0];
    double dy = coordinates[1] - foodCoords[1];
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= otherFood.getRadius();
}
// развернуться на 180 градусов
void Agent::cheng_direction(){
    if (direction > M_PI){
        direction = direction - M_PI;
    } else {
        direction = direction + M_PI;
    }
}
// поменять цель 
void Agent::cheng_ame(){
    ame = ( ame + 1 ) % 2;
}
// движение
void Agent::moove() {
    if (deafTimer > 0) {
        deafTimer--;
    }
    coordinates[0] += speed * cos(direction);
    coordinates[1] += speed * sin(direction);
    
    speed = speed * ((rand() % 400 - 200) / 10000.0 + 1);
    direction = direction + ((rand() % 400 - 200) / 10000.0);
    distA += speed;
    distB += speed;
    
    energy--;
}
