#include "CoffeeTasting.h"
#include <iostream>
#include <fstream>

// Constructor
CoffeeTasting::CoffeeTasting(const std::string& name, const std::string& date, double cost, const std::vector<std::string>& coffeeTypes)
    : Event(name, date, cost, city), coffeeTypes(coffeeTypes)
{
    saveEventToCSV("events.csv");
}

// Destructor
CoffeeTasting::~CoffeeTasting() {}

// Display details
void CoffeeTasting::displayDetails() const
{
    Event::displayDetails();
    std::cout << "Tipuri cafea: ";
    for (const auto& type : coffeeTypes)
    {
        std::cout << type << " ";
    }
    std::cout << "\n";
}

// Perform action
void CoffeeTasting::performEventAction() const
{
    std::cout << "Bucurati-va de degustarea de cafea!\n";
}

// Save event to CSV
void CoffeeTasting::saveEventToCSV(const std::string &city) const
{
    std::string filePath = "../data/events/" + city + ".csv";

    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << name << "," << date << "," << cost;
        for (const auto& type : coffeeTypes)
        {
            file << "," << type;
        }
        file << "\n";
        file.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fisierului " << filePath << "\n";
    }
}