#ifndef POKEMON_H
#define POKEMON_H
#include <string>

class Pokemon {
private:
    std::string name;
    std::string typeOne;
    std::string typeTwo;
    int total;
    int hp;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
    int generation;
    bool legendary;

public:
    Pokemon(std::string name, std::string typeOne, std::string typeTwo, int total, int hp, int attack, int defense, int specialAttack, int specialDefense, int speed, int generation, std::string legendary);

    std::string getName();
    std::string getTypeOne();
    std::string getTypeTwo();
    int getTotal();
    int getHP();
    int getAttack();
    int getDefense();
    int getSpecialAttack();
    int getSpecialDefense();
    int getSpeed();
    int getGeneration();
    void setLegendary(std::string legendary);
};

#endif // POKEMON_H
