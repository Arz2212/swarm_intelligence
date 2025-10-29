
#include <iostream>
#include <cassert>

// Class "Food"
class Food {
    int energy;
    int x, y;

public:
    Food(int energy_, int x_, int y_) : energy(energy_), x(x_), y(y_) {}

    int getEnergy() const { return energy; }
    int getX() const { return x; }
    int getY() const { return y; }

    bool operator==(const Food& other) const {
        return energy == other.energy && x == other.x && y == other.y;
    }
    void consumeEnergy(int amount) {
        if (amount < 0) return; 
        energy -= amount;
        if (energy < 0) energy = 0;
    }
};

int main() {
    std::setlocale(LC_ALL, "C");

    std::cout << "Testing class Food..." << std::endl;

    Food a(10, 2, 3);
    Food b(10, 2, 3);
    Food c(5, 1, 1);

    assert(a.getEnergy() == 10);
    assert(a.getX() == 2);
    assert(a.getY() == 3);


    std::cout << "All tests passed successfully!" << std::endl;
    std::cout.flush();

    system("pause");
    return 0;
}
