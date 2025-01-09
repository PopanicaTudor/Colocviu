#include "CoffeeTasting.h"

#include <iostream>
#include <fstream>

// Constructor
CoffeeTasting::CoffeeTasting(const std::string& name, const std::string& date, double cost, const std::vector<std::string>& coffeeTypes)
    : Event(name, date, cost, city), coffeeTypes(coffeeTypes) {}

// Destructor
CoffeeTasting::~CoffeeTasting() {}

// Afișarea detaliilor evenimentului
void CoffeeTasting::displayDetails() const
{
    Event::displayDetails();
    std::cout << ", Tipuri cafea: " << coffeeTypes.front();
    for (size_t i = 1; i < coffeeTypes.size(); i++)
    {
        std::cout << ", " << coffeeTypes[i];
    }
    std::cout << "\n";
}

// Acțiunea specifică evenimentului
void CoffeeTasting::performEventAction() const
{
    std::cout << "Bucurati-va de degustarea de cafea!\n";
}

// Salvarea evenimentului într-un fișier CSV
void CoffeeTasting::saveEventToCSV(const std::string &filePath) const
{
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << name << "," << date << "," << cost << "," << "Coffee Tasting";

        file << ",\"Coffee Types: " << coffeeTypes.front();
        for (size_t i = 1; i < coffeeTypes.size(); i++)
        {
            file << ", " << coffeeTypes[i];
        }
        file << "\"\n";
        file.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fisierului " << filePath << "\n";
    }
}