#ifndef AGENT_H
#define AGENT_H

#include <array>

class Base;
class Food;

class Agent
{
protected:
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

    virtual void operator = (Agent& other);

    bool isAlive() const;
    bool agent_near(const Agent& other) const;
    bool base_near(const Base& other) const;
    bool food_near(const Food& other) const;

    void cheng_direction_and_ame();
    virtual void moove();
    
    std::array<double, 2> getCoordinates() const { return coordinates; }
    double getDirection() const { return direction; }
    int getEnergy() const { return energy; }
    void setEnergy(int e) { energy = e; }
    double getSpeed() const { return speed; }
    void setSpeed(double s) { speed = s; }
    void setCoordinates(double x, double y) { coordinates[0] = x; coordinates[1] = y; }
    
    double getDistA() const { return distA; }
    double getDistB() const { return distB; }
    int getAme() const { return ame; }
    void setDistA(double d) { distA = d; }
    void setDistB(double d) { distB = d; }
    void setDirection(double d) { direction = d; }
};

#endif // AGENT_H