#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <iostream>
#include "Agent1.h"
#include "Scout.h"
#include "Worker.h"
#include "Food.h"
#include "base.h"

class Model {
private:
    double mapWidth;
    double mapHeight;
    
    std::vector<std::unique_ptr<Agent>> agents;
    std::vector<Food> foods;
    Base base;
    
    int totalEnergyCollected;
    int stepsCompleted;
    int agentsDied;
    int foodConsumed;

    void checkAgentInteractions();
    void checkFoodInteraction(); // Переименовано из checkFoodCollection
    void checkBaseDelivery();
    void handleBoundaries(Agent& agent);
    void removeDeadAgents();

public:
    Model(double width, double height);
    
    void initializeSimulation(int numScouts, int numWorkers, int numFood);
    void simulateStep();
    void simulate(int steps);
    
    void addScout(double x, double y);
    void addWorker(double x, double y);
    void addFood(int energy, double x, double y);
    
    void printStatistics() const;
    int getTotalEnergy() const { return totalEnergyCollected; }
    int getSteps() const { return stepsCompleted; }
    int getAliveAgents() const;
    int getRemainingFood() const { return foods.size(); }
    
    void displayMap() const;
};

#endif // MODEL_H