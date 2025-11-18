#include <iostream>
#include <chrono>
#include <thread>
#include "Model.h"

using namespace std;

void clearScreen() {
    // Простой способ очистки экрана для Windows
    system("cls");
}

void displayStepInfo(const Model& model, int step) {
    clearScreen();
    cout << "=== Ant Colony Simulation ===" << endl;
    cout << "Step: " << step << endl;
    cout << "=============================" << endl;
    model.printStatistics();
    cout << endl;
    model.displayMap();
}

int main() {
    cout << "=== Ant Colony Simulation System ===" << endl;
    cout << "Starting simulation..." << endl;
    
    // Создаем модель с картой 800x600 для лучшего отображения
    Model model(800, 600);
    
    // Инициализируем симуляцию
    model.initializeSimulation(20, 30, 10);
    
    cout << "\nPress Enter to start step-by-step simulation..." << endl;
    cin.get();
    
    // Количество шагов для симуляции
    const int totalSteps = 200;
    
    // Пошаговая симуляция
    for (int step = 1; step <= totalSteps; step++) {
        displayStepInfo(model, step);
        
        // Выполняем один шаг симуляции
        model.simulateStep();
        
        // Пауза между шагами (500 миллисекунд)
        this_thread::sleep_for(chrono::milliseconds(500));
        
        // Проверяем, остались ли живые агенты
        if (model.getAliveAgents() == 0) {
            cout << "All agents have died. Simulation ending early." << endl;
            break;
        }
        
        // Проверяем, осталась ли еда
        if (model.getRemainingFood() == 0) {
            cout << "All food has been consumed. Simulation ending early." << endl;
            break;
        }
    }
    
    // Финальный вывод
    clearScreen();
    cout << "=== FINAL SIMULATION RESULTS ===" << endl;
    model.printStatistics();
    model.displayMap();
    
    cout << "\n=== Simulation completed ===" << endl;
    cout << "Total steps simulated: " << model.getSteps() << endl;
    cout << "Total energy collected: " << model.getTotalEnergy() << endl;
    cout << "Press Enter to exit..." << endl;
    cin.get();
    
    return 0;
}