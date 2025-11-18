#include "Model.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Model::Model(double width, double height) 
    : mapWidth(width), mapHeight(height), 
      base(1000, width/2, height/2, 100),
      totalEnergyCollected(0), stepsCompleted(0), 
      agentsDied(0), foodConsumed(0) {
    std::srand(std::time(0));
}

void Model::initializeSimulation(int numScouts, int numWorkers, int numFood) {
    std::cout << "Initializing simulation with " << numScouts << " scouts, " 
              << numWorkers << " workers, and " << numFood << " food sources" << std::endl;
    
    for (int i = 0; i < numScouts; ++i) {
        double x = (std::rand() % static_cast<int>(mapWidth));
        double y = (std::rand() % static_cast<int>(mapHeight));
        addScout(x, y);
    }
    
    for (int i = 0; i < numWorkers; ++i) {
        double x = (std::rand() % static_cast<int>(mapWidth));
        double y = (std::rand() % static_cast<int>(mapHeight));
        addWorker(x, y);
    }
    
    for (int i = 0; i < numFood; ++i) {
        double x = (std::rand() % static_cast<int>(mapWidth));
        double y = (std::rand() % static_cast<int>(mapHeight));
        addFood(10 + std::rand() % 20, x, y);
    }
    
    std::cout << "Simulation initialized successfully" << std::endl;
}

void Model::simulateStep() {
    for (auto& agent : agents) {
        if (agent->isAlive()) {
            agent->moove();
            handleBoundaries(*agent);
        }
    }
    
    checkAgentInteractions();
    checkFoodInteraction();
    checkBaseDelivery();
    removeDeadAgents();
    
    stepsCompleted++;
}

void Model::simulate(int steps) {
    std::cout << "Starting simulation for " << steps << " steps..." << std::endl;
    
    for (int i = 0; i < steps; ++i) {
        simulateStep();
        
        if (i % 100 == 0) {
            std::cout << "Step " << i << "/" << steps << std::endl;
            printStatistics();
        }
    }
    
    std::cout << "Simulation completed after " << steps << " steps" << std::endl;
}

void Model::addScout(double x, double y) {
    agents.push_back(std::unique_ptr<Scout>(new Scout(x, y)));
}

void Model::addWorker(double x, double y) {
    agents.push_back(std::unique_ptr<Worker>(new Worker(x, y)));
}

void Model::addFood(int energy, double x, double y) {
    foods.emplace_back(energy, x, y, 15);
}

void Model::checkAgentInteractions() {
    for (size_t i = 0; i < agents.size(); ++i) {
        if (!agents[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < agents.size(); ++j) {
            if (!agents[j]->isAlive()) continue;
            
            if (agents[i]->agent_near(*agents[j])) {
                *agents[i] = *agents[j];
                *agents[j] = *agents[i];
            }
        }
    }
}

// Исправленный метод - используем cheng_direction_and_ame для разворота
void Model::checkFoodInteraction() {
    for (auto& agent : agents) {
        if (!agent->isAlive()) continue;
        
        for (auto& food : foods) {
            if (food.is_energy() && agent->food_near(food)) {
                // Все агенты разворачиваются при встрече с едой
                agent->cheng_direction_and_ame();
                
                // Если агент - рабочий, то он также собирает энергию
                Worker* worker = dynamic_cast<Worker*>(agent.get());
                if (worker) {
                    worker->collectFood(food);
                    if (!food.is_energy()) {
                        foodConsumed++;
                    }
                }
                
                break; // Обрабатываем только одну еду за шаг
            }
        }
    }
}

void Model::checkBaseDelivery() {
    for (auto& agent : agents) {
        if (!agent->isAlive()) continue;
        
        Worker* worker = dynamic_cast<Worker*>(agent.get());
        if (worker && agent->base_near(base)) {
            int delivered = worker->getCarriedEnergy();
            if (delivered > 0) {
                base.receiveEnergy(delivered);
                totalEnergyCollected += delivered;
                worker->resetCarriedEnergy();
                std::cout << "Energy delivered to base: " << delivered << " units" << std::endl;
            }
        }
    }
}

void Model::handleBoundaries(Agent& agent) {
    auto coords = agent.getCoordinates();
    double x = coords[0];
    double y = coords[1];
    
    if (x < 0 || x > mapWidth || y < 0 || y > mapHeight) {
        agent.cheng_direction_and_ame();
        
        if (x < 0) agent.setCoordinates(0, y);
        if (x > mapWidth) agent.setCoordinates(mapWidth, y);
        if (y < 0) agent.setCoordinates(x, 0);
        if (y > mapHeight) agent.setCoordinates(x, mapHeight);
    }
}

void Model::removeDeadAgents() {
    int initialCount = agents.size();
    agents.erase(
        std::remove_if(agents.begin(), agents.end(),
            [](const std::unique_ptr<Agent>& agent) {
                return !agent->isAlive();
            }),
        agents.end()
    );
    agentsDied += (initialCount - agents.size());
}

int Model::getAliveAgents() const {
    return std::count_if(agents.begin(), agents.end(),
        [](const std::unique_ptr<Agent>& agent) {
            return agent->isAlive();
        });
}

void Model::printStatistics() const {
    std::cout << "=== Simulation Statistics ===" << std::endl;
    std::cout << "Steps completed: " << stepsCompleted << std::endl;
    std::cout << "Alive agents: " << getAliveAgents() << std::endl;
    std::cout << "Agents died: " << agentsDied << std::endl;
    std::cout << "Energy collected: " << totalEnergyCollected << std::endl;
    std::cout << "Food consumed: " << foodConsumed << std::endl;
    std::cout << "Food remaining: " << foods.size() << std::endl;
    std::cout << "Base energy: " << base.getEnergy() << std::endl;
    
    int scouts = 0, workers = 0;
    for (const auto& agent : agents) {
        if (dynamic_cast<Scout*>(agent.get())) scouts++;
        else if (dynamic_cast<Worker*>(agent.get())) workers++;
    }
    std::cout << "Scouts: " << scouts << ", Workers: " << workers << std::endl;
    std::cout << "=============================" << std::endl;
}

void Model::displayMap() const {
    const int width = 50;
    const int height = 20;
    
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));
    
    int baseX = static_cast<int>((base.getCoordinates()[0] / mapWidth) * width);
    int baseY = static_cast<int>((base.getCoordinates()[1] / mapHeight) * height);
    if (baseX >= 0 && baseX < width && baseY >= 0 && baseY < height) {
        grid[baseY][baseX] = 'B';
    }
    
    for (const auto& agent : agents) {
        if (agent->isAlive()) {
            auto coords = agent->getCoordinates();
            int x = static_cast<int>((coords[0] / mapWidth) * width);
            int y = static_cast<int>((coords[1] / mapHeight) * height);
            
            if (x >= 0 && x < width && y >= 0 && y < height) {
                if (dynamic_cast<Scout*>(agent.get())) {
                    grid[y][x] = 'S';
                } else if (dynamic_cast<Worker*>(agent.get())) {
                    grid[y][x] = 'W';
                }
            }
        }
    }
    
    for (const auto& food : foods) {
        if (food.is_energy()) {
            auto coords = food.getCoordinates();
            int x = static_cast<int>((coords[0] / mapWidth) * width);
            int y = static_cast<int>((coords[1] / mapHeight) * height);
            
            if (x >= 0 && x < width && y >= 0 && y < height) {
                grid[y][x] = 'F';
            }
        }
    }
    
    std::cout << "Simulation Map:" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << "Legend: B=Base, S=Scout, W=Worker, F=Food, .=Empty" << std::endl;
}