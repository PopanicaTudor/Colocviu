#include "Event.h"
#include <fstream>

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

// Display event details
void Event::displayDetails() const
{
    std::cout << "Eveniment: " << name << "\nData: " << date << "\nCost: " << cost << " RON\n";
}