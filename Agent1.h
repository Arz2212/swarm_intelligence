#ifndef AGENT_H
#define AGENT_H
#include <array>

class Agent
{
private:
    std::array<double, 2> coordinates;
    int ame; 
    double distA;
    double distB;
    int radius;
    double speed;
    int energy;
    double direction;
public:
    Agent(double x, double y);

    virtual ~Agent() = default;

    void operator = (Agent& other);

    bool isAlive() const;
    bool agent_near(Agent& other) const;
    bool base_near(Base& other) const;
    bool food_near(Food& other) const;

    void cheng_direction_and_ame();
    void moove();
}


#endif // AGENT_H