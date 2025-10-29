#include <iostream>
#include <array>
#include <cassert>

class Food {
private:
    int energy;
    std::array<int, 2> coordinates; // координаты записанные как масив

public:
    // Конструктор
    Food(int e, int x, int y) : energy(e), coordinates{x, y} {}

    // возврат числа энергии
    int getEnergy() const { return energy; }
    // уменьшение числа энергии по запросу агента 
    int consumeEnergy() {
        energy -= 1;
        if (energy < 0) {
            energy = 0;
            return 0;
        }
        return energy > 0 ? 1 : 0;
    }
    // Проверка закончилась ли энергия
    bool isDepleted() const { return energy == 0; }

    // Получение координат
    std::array<int, 2> getCoordinates() const {
        return coordinates;
    }
};

int main() {

    std::cout << "start" << std::endl;

    Food f1(5, 2, 3);
    assert(f1.getEnergy() == 5);
    auto coords1 = f1.getCoordinates();
    assert(coords1[0] == 2 && coords1[1] == 3);

    int res1 = f1.consumeEnergy();

    assert(f1.getEnergy() == 4);
    assert(res1 == 1);

    Food f2(1, 0, 0);
    int res2 = f2.consumeEnergy();
    assert(f2.getEnergy() == 0);
    assert(res2 == 0);

    assert(f2.isDepleted() == true);
    assert(f1.isDepleted() == false);

    Food f3(10, 7, 8);
    auto coords2 = f3.getCoordinates();
    assert(coords2[0] == 7 && coords2[1] == 8);

    Food f4(3, 1, 1);
    assert(f4.consumeEnergy() == 1);
    assert(f4.consumeEnergy() == 1); 
    assert(f4.consumeEnergy() == 0); 
    assert(f4.isDepleted() == true);

    Food f5(2, 5, 5);
    auto coords3 = f5.getCoordinates();
    assert(coords3[0] == 5 && coords3[1] == 5);

    assert(f5.consumeEnergy() == 1); 
    assert(f5.consumeEnergy() == 0); 
    assert(f5.consumeEnergy() == 0); 

    Food f6(0, 10, 10);
    assert(f6.getEnergy() == 0);
    assert(f6.isDepleted() == true);
    assert(f6.consumeEnergy() == 0);

    Food f7(5, 9, 3);
    f7.consumeEnergy();
    auto coords4 = f7.getCoordinates();
    assert(coords4[0] == 9 && coords4[1] == 3);

    std::cout << "+" << std::endl;
    return 0;
}
