#ifndef SCOUT_H
#define SCOUT_H

#include "Agent1.h"

class Scout : public Agent {
public:
    Scout(double x, double y);
    void operator=(Agent& other) override;
};

#endif // SCOUT_H