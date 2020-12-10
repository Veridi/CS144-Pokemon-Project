#include "pokemon.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <ostream>
#include <algorithm>

#include <typeinfo>

int searchByName(std::vector<Pokemon> list, std::string pokemonName)
{
    int i = 0;
    while (list[i].getName() != pokemonName)
    {
        i++;
    }
    return i + 1;
}

bool compareByDefense(Pokemon first, Pokemon second)
{
    if (first.getDefense() < second.getDefense())
    {
        return false;
    }
    else if (first.getDefense() > second.getDefense())
    {
        return true;
    }
    else
    {
        return 0;
    }
}

bool compareByAttack(Pokemon first, Pokemon second)
{
    if (first.getAttack() < second.getAttack())
    {
        return false;
    }
    else if (first.getAttack() > second.getAttack())
    {
        return true;
    }
    else
    {
        return compareByDefense(first, second);
    }
}

bool compareByHP(Pokemon first, Pokemon second)
{
    if (first.getHP() < second.getHP())
    {
        return false;
    }
    else if (first.getHP() > second.getHP())
    {
        return true;
    }
    else
    {
        return compareByAttack(first, second);
    }
}

bool compareByName(Pokemon first, Pokemon second)
{
    if (first.getName() > second.getName())
    {
        return false;
    }
    else if (first.getName() < second.getName())
    {
        return true;
    }
    else
    {
        return compareByHP(first, second);
    }
}

void printList(std::vector<Pokemon> list)
{
    for (Pokemon &thePokemon : list)
    {
        std::cout << thePokemon.getName() << std::endl;
    }
}

void writeToFile(std::ofstream & file, std::vector<Pokemon> list)
{
    file.open("sorted.txt");
    for (Pokemon &thePokemon : list)
    {
        file << thePokemon.getName() << "," << thePokemon.getHP() << "," << thePokemon.getAttack() << "," << thePokemon.getDefense() << "\n";
    }
    file.close();
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);

    std::ifstream file("./Pokemon.csv");
    //QFile file("pokemon.csv");

    if(!file.is_open())
    //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "ERROR" << std::endl;
        //QTextStream(stdout) << "Error" << Qt::endl;
    }

    std::string pokedexNumber, name, typeOne, typeTwo, total, hp, attack, defense, specialAttack, specialDefense, speed, generation, legendary;

    getline(file, pokedexNumber, ',');
    getline(file, name, ',');
    getline(file, typeOne, ',');
    getline(file, typeTwo, ',');
    getline(file, total, ',');
    getline(file, hp, ',');
    getline(file, attack, ',');
    getline(file, defense, ',');
    getline(file, specialAttack, ',');
    getline(file, specialDefense, ',');
    getline(file, speed, ',');
    getline(file, generation, ',');
    getline(file, legendary);

    std::vector<Pokemon> pokemon;
    
    while(!file.eof())
    {
        getline(file, pokedexNumber, ',');
        getline(file, name, ',');
        getline(file, typeOne, ',');
        getline(file, typeTwo, ',');
        getline(file, total, ',');
        getline(file, hp, ',');
        getline(file, attack, ',');
        getline(file, defense, ',');
        getline(file, specialAttack, ',');
        getline(file, specialDefense, ',');
        getline(file, speed, ',');
        getline(file, generation, ',');
        getline(file, legendary, '\n');

        pokemon.push_back(Pokemon(name, typeOne, typeTwo, stoi(total), stoi(hp), stoi(attack), stoi(defense), stoi(specialAttack), stoi(specialDefense), stoi(speed), stoi(generation), legendary));
    }

    file.close();

    std::ofstream fileName;
    
    int choice;
    std::string pokemonData;
    std::cout << "What would you like to do?\n\t'1' for search by name.\n\t'2' for search by HP range.\n\t'3' for search by Attack range.\n\t'4' for search by Defense range.\n\t'5' to search for a specific pokemon." << std::endl;
    std::cin >> choice;
    if(choice == 1)
    {
        std::sort(pokemon.begin(), pokemon.end(), compareByName);
        writeToFile(fileName, pokemon);

        char start;
        char end;
        std::vector<std::string> list;
        std::string delimiter = ",";

        std::cout << "Please enter the letter you would like to start the search at: " << std::endl;
        std::cin >> start;
        std::cout << "Please enter the letter you would like to end the search at: " << std::endl;
        std::cin >> end;

        std::ifstream file("./sorted.txt");

        if(!file.is_open())
        //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << "ERROR" << std::endl;
            //QTextStream(stdout) << "Error" << Qt::endl;
        }

        while(getline(file, pokemonData))
        {
            pokemonData = pokemonData.substr(0, pokemonData.find(delimiter));
            if (pokemonData.at(0) >= toupper(start) && pokemonData.at(0) <= toupper(end))
            {
                list.push_back(pokemonData);
            }
        }

        file.close();

        for (std::string &thePokemon : list)
        {
            std::cout << thePokemon << std::endl;
        }
    }
    else if(choice == 2)
    {
        std::sort(pokemon.begin(), pokemon.end(), compareByHP);
        writeToFile(fileName, pokemon);
        
        std::string delimiter = ",";
        std::string high;
        std::string low;
        std::vector<std::string> list;

        std::cout << "Please enter the lower range of HP: ";
        std::cin >> low;
        std::cout << "Please enter the higher range of HP: ";
        std::cin >> high;

        std::ifstream file("./sorted.txt");

        if(!file.is_open())
        //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << "ERROR" << std::endl;
            //QTextStream(stdout) << "Error" << Qt::endl;
        }

        while(getline(file, pokemonData))
        {
            std::string theName = pokemonData.substr(0, pokemonData.find(delimiter));
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length());
            int theHP = std::stoi(pokemonData.substr(0, pokemonData.find(",")));
            if(theHP >= std::stoi(low) && theHP <= std::stoi(high))
            {
                list.push_back(theName);
            }
        }

        file.close();

        for (std::string &thePokemon : list)
        {
            std::cout << thePokemon << std::endl;
        }
    }
    else if(choice == 3)
    {
        std::sort(pokemon.begin(), pokemon.end(), compareByAttack);
        writeToFile(fileName, pokemon);

        std::string delimiter = ",";
        std::string high;
        std::string low;
        std::vector<std::string> list;

        std::cout << "Please enter the lower range of Attack: ";
        std::cin >> low;
        std::cout << "Please enter the higher range of Attack: ";
        std::cin >> high;

        std::ifstream file("./sorted.txt");

        if(!file.is_open())
        //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << "ERROR" << std::endl;
            //QTextStream(stdout) << "Error" << Qt::endl;
        }

        while(getline(file, pokemonData))
        {
            std::string theName = pokemonData.substr(0, pokemonData.find(delimiter));
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length()); //Remove the name
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length()); //Remove the HP
            int theAttack = std::stoi(pokemonData.substr(0, pokemonData.find(",")));
            if(theAttack >= std::stoi(low) && theAttack <= std::stoi(high))
            {
                list.push_back(theName);
            }
        }

        file.close();

        for (std::string &thePokemon : list)
        {
            std::cout << thePokemon << std::endl;
        }
    }
    else if(choice == 4)
    {
        std::sort(pokemon.begin(), pokemon.end(), compareByDefense);
        writeToFile(fileName, pokemon);
        
        std::string delimiter = ",";
        std::string high;
        std::string low;
        std::vector<std::string> list;

        std::cout << "Please enter the lower range of Defense: ";
        std::cin >> low;
        std::cout << "Please enter the higher range of Defense: ";
        std::cin >> high;

        std::ifstream file("./sorted.txt");

        if(!file.is_open())
        //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << "ERROR" << std::endl;
            //QTextStream(stdout) << "Error" << Qt::endl;
        }

        while(getline(file, pokemonData))
        {
            std::string theName = pokemonData.substr(0, pokemonData.find(delimiter));
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length()); //Remove the name
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length()); //Remove the HP
            pokemonData = pokemonData.erase(0, pokemonData.find(delimiter) + delimiter.length()); //Remove the Attack
            int theDefense = std::stoi(pokemonData.substr(0, pokemonData.find(",")));
            if(theDefense >= std::stoi(low) && theDefense <= std::stoi(high))
            {
                list.push_back(theName);
            }
        }

        file.close();

        for (std::string &thePokemon : list)
        {
            std::cout << thePokemon << std::endl;
        }
    }

    else if(choice == 5)
    {
        std::string theName;
        int pokedexNumber;

        std::cout << "Would you like to search by name or by Pokedex number?\n\t'1' for by name.\n\t'2' for by Pokedex number.\n";
        std::cin >> choice;
        if(choice == 1)
        {
            std::cout << "Please input the name: ";
            std::cin >> theName;
            pokedexNumber = searchByName(pokemon, theName);
        }
        else if(choice == 2)
        {
            std::cout << "Please input the Pokedex number: ";
            std::cin >> pokedexNumber;
        }
        pokedexNumber--;
        Pokemon thePokemon = pokemon[pokedexNumber];
        std::cout << thePokemon.getName() << std::endl;
        std::cout << "\tHealth Points: " << thePokemon.getHP() << std::endl;
        std::cout << "\tAttack: " << thePokemon.getAttack() << std::endl;
        std::cout << "\tDefense: " << thePokemon.getDefense() << std::endl;
        std::cout << "\tSpecial Attack: " << thePokemon.getSpecialAttack() << std::endl;
        std::cout << "\tSpecial Defense: " << thePokemon.getSpecialDefense() << std::endl;
        std::cout << "\tSpeed: " << thePokemon.getSpeed() << std::endl;
    }

/*
    QPieSeries *series1 = new QPieSeries();
    series1->setName("Fire");
    for(int i = 0; i < 800; i++)
    {
        std::cout << i << std::endl;
        if(pokemon[i].getTypeOne() == "Fire")
        {
            std::cout << pokemon[i].getTypeOne() << std::endl;
            series1->append(QString::fromStdString(pokemon[i].getTypeTwo()), 100);
        }
        if(pokemon[i].getTypeTwo() == "Fire")
        {
            std::cout << pokemon[i].getTypeTwo() << std::endl;
            series1->append(QString::fromStdString(pokemon[i].getTypeTwo()), 100);
        }
        else
        {
            std::cout << "Not fire." << std::endl;
        }
    }

    DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();

    MainWindow w;
    QChartView *chartView = new QChartView(donutBreakdown);
    chartView->setRenderHint(QPainter::Antialiasing);
    w.setCentralWidget(chartView);
    w.resize(800, 500);
    w.show(); //Leave commented until I actually have a window to print
    return a.exec();
*/
}