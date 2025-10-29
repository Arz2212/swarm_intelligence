#include <iostream>
#include <cassert>
#include "food.h"

int main() {
    std::cout << "start\n";

    // Test 1: базовая инициализация
    {
        Food f(10, 3, 4);
        assert(f.getEnergy() == 10);
        auto c = f.getCoordinates();
        assert(c[0] == 3 && c[1] == 4);
        std::cout << "Test 1 passed: initialization OK\n";
    }

    // Test 2: уменьшение энергии
    {
        Food f(5, 0, 0);
        f.consumeEnergy();
        assert(f.getEnergy() == 4);
        std::cout << "Test 2 passed: energy decreased by 1\n";
    }

    // Test 3: энергия не уходит в минус
    {
        Food f(1, 0, 0);
        f.consumeEnergy();
        f.consumeEnergy(); // вторая попытка
        assert(f.getEnergy() == 0);
        std::cout << "Test 3 passed: energy not negative\n";
    }

    // Test 4: isDepleted() работает
    {
        Food f(2, 0, 0);
        assert(!f.isDepleted());
        f.consumeEnergy();
        f.consumeEnergy();
        assert(f.isDepleted());
        std::cout << "Test 4 passed: depletion detection OK\n";
    }

    // Test 5: consumeEnergy() возвращает правильные значения
    {
        Food f(2, 0, 0);
        int r1 = f.consumeEnergy(); // должно быть 1 (есть энергия)
        int r2 = f.consumeEnergy(); // теперь 0 (истощено)
        int r3 = f.consumeEnergy(); // остаётся 0
        assert(r1 == 1 && r2 == 0 && r3 == 0);
        std::cout << "Test 5 passed: consumeEnergy() return values OK\n";
    }

    // Test 6: координаты стабильны
    {
        Food f(3, 100, 200);
        auto c = f.getCoordinates();
        assert(c[0] == 100 && c[1] == 200);
        f.consumeEnergy();
        f.consumeEnergy();
        f.consumeEnergy();
        auto c2 = f.getCoordinates();
        assert(c2[0] == 100 && c2[1] == 200);
        std::cout << "Test 6 passed: coordinates remain constant\n";
    }

    // Test 7: полное истощение после n шагов
    {
        Food f(3, 0, 0);
        f.consumeEnergy();
        f.consumeEnergy();
        f.consumeEnergy();
        assert(f.isDepleted());
        std::cout << "Test 7 passed: full depletion after n steps\n";
    }

    // Test 8: consumeEnergy() с нулевой энергией
    {
        Food f(0, 0, 0);
        int r = f.consumeEnergy();
        assert(r == 0 && f.getEnergy() == 0);
        std::cout << "Test 8 passed: consumeEnergy() safe at zero energy\n";
    }

    // Test 9: большой запас энергии
    {
        Food f(1000, 10, 10);
        for (int i = 0; i < 1000; ++i) {
            f.consumeEnergy();
        }
        assert(f.isDepleted());
        std::cout << "Test 9 passed: handles large energy correctly\n";
    }

    // Test 10: независимость экземпляров
    {
        Food f1(5, 1, 1);
        Food f2(10, 2, 2);
        f1.consumeEnergy();
        assert(f1.getEnergy() == 4);
        assert(f2.getEnergy() == 10);
        std::cout << "Test 10 passed: instances independent\n";
    }

    std::cout << "=== All Food tests passed successfully ===\n";
    return 0;
}



g++ main.cpp food.cpp -o main.exe