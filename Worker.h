#ifndef WORKER_H
#define WORKER_H

#include "Agent1.h"
#include "Food.h"
#include "base.h"

class Worker : public Agent {
private:
    int carriedEnergy;

public:
    Worker(double x, double y);
    
    void moove() override;
    void collectFood(Food& food);
    void deliverToBase(Base& base);
    int getCarriedEnergy() const;
    void resetCarriedEnergy();
};

#endif // WORKER_H