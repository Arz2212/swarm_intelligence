#ifndef AGENT_H
#define AGENT_H
#include <array>

class agent
{
private:
    double speed;
    std::array<double, 2> coordinates;
    int ame; // цель поиска (база еда может определенный тип еды)
    double direction; // направление куда агент движеться 
    const int radius; // радиус на котором его слышно
    int distA; // расстояние до базы
    int distB; // растояние до еды
    int energy;


public:
    agent(int x, int y, double speed, int radius)
    
    
    // Виртуальный деструктор для корректного удаления объектов дочерних классов
    virtual ~agent() = default;
    // Обмен информацией с другим агентом
    bool operator > (agent& other);

    // Геттеры
    std::array<double, 2> getPosition() const;
    int getEnergy() const;
    bool isAlive() const;
    int getdistA() const;
    int getdistB() const;
    
    // проверка нахождения рядом 
    bool agent_near(agent& other) const;
    void base_hear(Food& other) const;
    void food_hear(Food& other) const;
    void cheng_direction(agent& other); 
    // Сеттеры и утилиты
    void setTarget(int ame, int dist);
    void addEnergy(int amount);
    void Moovе(); 
    
};






#endif // AGENT_H