class Base {
private:
    int energy;
    std::array<int, 2> coordinates; // x, y
    int rad;

public:
    Base(int e, int x, int y, int r);
    int getRadius() const;
    int getEnergy() const; // возврат количества энергии
    int create();  // уменьшает энергию на 1 и создает агента
    bool is_energy() const; // проверка осталась ли еда 
    std::array<int, 2> getCoordinates() const; // возврат координат 
};