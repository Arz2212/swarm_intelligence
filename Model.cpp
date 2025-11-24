#include "Model.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Model::Model(double width, double height) 
    : mapWidth(width), mapHeight(height), 
      base(1000, width/2, height/2, 200),
      totalEnergyCollected(0), stepsCompleted(0), 
      agentsDied(0), foodConsumed(0) {
    std::srand(std::time(0));
}

void Model::initializeSimulation(int numScouts, int numWorkers, int numFood) {
    std::cout << "Initializing simulation with " << numScouts << " scouts, " 
              << numWorkers << " workers, and " << numFood << " food sources" << std::endl;
    addFood(2000000000, 90, 90);
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
        addFood(1000000000000 + std::rand() % 20, x, y);
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
    foods.emplace_back(energy, x, y, 50);
}

void Model::checkAgentInteractions() {
    for (size_t i = 0; i < agents.size(); ++i) {
        if (!agents[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < agents.size(); ++j) {
            if (!agents[j]->isAlive()) continue;
            
            // Если агенты рядом
            if (agents[i]->agent_near(*agents[j])) {
                // Было:
                // *agents[i] = *agents[j];
                // *agents[j] = *agents[i];
                
                // Стало:
                agents[i]->interact(*agents[j]);
                agents[j]->interact(*agents[i]);
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
        worker->deliverToBase(base);
}
}
void Model::handleBoundaries(Agent& agent) {
    auto coords = agent.getCoordinates();
    bool bounced = false;
    
    if (coords[0] < 0) { agent.setCoordinates(0, coords[1]); bounced = true; }
    if (coords[0] > mapWidth) { agent.setCoordinates(mapWidth, coords[1]); bounced = true; }
    if (coords[1] < 0) { agent.setCoordinates(coords[0], 0); bounced = true; }
    if (coords[1] > mapHeight) { agent.setCoordinates(coords[0], mapHeight); bounced = true; }

    if (bounced) {
        agent.cheng_direction(); // Разворот на 180
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
