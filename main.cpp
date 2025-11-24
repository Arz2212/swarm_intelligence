#include <iostream>
#include <chrono>
#include <thread>
#include "Model.h"

using namespace std;


int main() {
    cout << "=== Ant Colony Simulation System ===" << endl;
    cout << "Starting simulation..." << endl;
    
    Model model(800, 800);
    
    model.initializeSimulation(0, 1000, 2);

    
    cout << "\nPress Enter to start step-by-step simulation..." << endl;
    cin.get();
    
    const int totalSteps = 10000;
    
    for (int step = 1; step <= totalSteps; step+= 1) {
        
        model.displayMap();
        model.simulateStep();
        
        this_thread::sleep_for(chrono::milliseconds(400));
        
        if (model.getAliveAgents() == 0) {
            cout << "All agents have died. Simulation ending early." << endl;
            break;
        }
        
        if (model.getRemainingFood() == 0) {
            cout << "All food has been consumed. Simulation ending early." << endl;
            break;
        }
    }
    
    
    
    return 0;
}