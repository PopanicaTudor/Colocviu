#include "Event.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

// Constructor
Event::Event(const std::string& name, const std::string& date, double cost, const std::string &city)
    : name(name), date(date), cost(cost), city(city) {}

// Destructor
Event::~Event() {}

// Getters
std::string Event::getName() const
{
    return name;
}

std::string Event::getDate() const
{
    return date;
}

double Event::getCost() const
{
    return cost;
}

std::string Event::getCity() const
{
    return city;
}

// Setters
void Event::setName(const std::string& name)
{
    this->name = name;
}

void Event::setDate(const std::string& date)
{
    this->date = date;
}

void Event::setCost(double cost)
{
    this->cost = cost;
}

void Event::setCity(const std::string &city)
{
    this->city = city;
}

// Afișarea detaliilor evenimentului
void Event::displayDetails() const
{
    std::cout << "Eveniment: " << name << ", Data: " << date << ", Cost: " << cost << " RON";
}

// Reimprospatarea evenimentelor în fișierul CSV
void Event::updateEventCSV(const std::vector<std::unique_ptr<Event>> &events,const std::string &filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << "Name,Date,Cost,Type,Details\n";
        file.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fisierului " << filePath << "\n";
    }

    for (const auto &event : events)
    {
        event->saveEventToCSV(filePath);
    }
}