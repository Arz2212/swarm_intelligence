#ifndef SCOUT_H
#define SCOUT_H

#include "Agent1.h"

class Scout : public Agent {
public:
    Scout(double x, double y);
    
    // Заменили operator= на interact
    // const Agent& other — потому что мы только читаем данные соседа
    void interact(const Agent& other) override;
};

#endif // SCOUT_H