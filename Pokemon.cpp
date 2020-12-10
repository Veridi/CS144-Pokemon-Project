#include "pokemon.h"


Pokemon::Pokemon(std::string name, std::string typeOne, std::string typeTwo, int total, int hp, int attack, int defense, int specialAttack, int specialDefense, int speed, int generation, std::string legendary)
{
    this->name = name;
    this->typeOne = typeOne;
    this->typeTwo = typeTwo;
    this->total = total;
    this->hp = hp;
    this->attack = attack;
    this->defense = defense;
    this->specialAttack = specialAttack;
    this->specialDefense = specialDefense;
    this->speed = speed;
    this->generation = generation;
    setLegendary(legendary);
};

std::string Pokemon::getName()
{
    return name;
}

std::string Pokemon::getTypeOne()
{
    return typeOne;
}

std::string Pokemon::getTypeTwo()
{
    return typeTwo;
}

int Pokemon::getTotal()
{
    return total;
}

int Pokemon::getHP()
{
    return hp;
}

int Pokemon::getAttack()
{
    return attack;
}

int Pokemon::getDefense()
{
    return defense;
}

int Pokemon::getSpecialAttack()
{
    return specialAttack;
}

int Pokemon::getSpecialDefense()
{
    return specialDefense;
}

int Pokemon::getSpeed()
{
    return speed;
}

int Pokemon::getGeneration()
{
    return generation;
}

void Pokemon::setLegendary(std::string legendary)
{
    if(legendary == "True")
    {
        this->legendary = true;
    }
    else
    {
        this->legendary = false;
    }
}