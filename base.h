#ifndef BASE_H
#define BASE_H

#include <array>

class Base {
private:
    int energy;
    std::array<int, 2> coordinates;
    int rad;

public:
    Base(int e, int x, int y, int r);

    int getRadius() const;
    int getEnergy() const;
    std::array<int, 2> getCoordinates() const;
    
    int create();
    bool is_energy() const;
    void receiveEnergy(int amount); // получение энергии 
};

#endif // BASE_H