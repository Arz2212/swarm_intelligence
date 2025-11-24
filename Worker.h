#ifndef WORKER_H
#define WORKER_H

#include "Agent1.h"
#include "Food.h"
#include "base.h"

class Worker : public Agent {
private:
    int carriedEnergy; // количество переносимой энергии 

public:
    Worker(double x, double y);
    
    void moove() override;
    void collectFood(Food& food); // забирает еду
    void deliverToBase(Base& base); // доставляет еду
    int getCarriedEnergy() const; // сколько еды осталось 
    void resetCarriedEnergy(); // перещзагрузка
};

#endif // WORKER_H