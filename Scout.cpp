#include "Scout.h"

Scout::Scout(double x, double y) : Agent(x, y) {
}

void Scout::interact(const Agent& other) {
    // Разведчик слушает соседа и обновляет знания о дистанции до БАЗЫ
    if (getDistB() > other.getDistB() + 50.0 ) {
        setDistB(other.getDistB() + 50.0);
    }
    
    // Разведчик слушает соседа и обновляет знания о дистанции до ЕДЫ
    if (getDistA() > other.getDistA() + 50.0) {
        setDistA(other.getDistA() + 50.0);
    }
    
    // ВАЖНО: Мы НЕ меняем direction. 
    // Разведчик бежит дальше по своим делам, просто запомнив цифры.
}