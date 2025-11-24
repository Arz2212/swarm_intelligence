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
    void checkFoodInteraction();  
    void checkBaseDelivery(); // проверка доставки до базы
    void handleBoundaries(Agent& agent); // проверка сталкновений с базой 
    void removeDeadAgents(); // удаление мертвых агентов

public:
    Model(double width, double height);
    
    void initializeSimulation(int numScouts, int numWorkers, int numFood); // запуск симуляции 
    void simulateStep(); // симуляция шага шага
    void simulate(int steps); // симуляция количества шагов
    
    void addScout(double x, double y); // добавить разведчика
    void addWorker(double x, double y); // добавить рабочего пока основной агент 
    void addFood(int energy, double x, double y); // добавить еду
    
    int getTotalEnergy() const { return totalEnergyCollected; } // общее собранное энергии 
    int getSteps() const { return stepsCompleted; } // шаг
    int getAliveAgents() const; // живые агентв
    int getRemainingFood() const { return foods.size(); } // оставшаяся еда
    
    void displayMap() const; // карта
};

#endif // MODEL_H