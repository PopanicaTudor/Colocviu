#include "Manager.h"

Manager::Manager(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour)
    : Employee(firstName, lastName, "Manager", startHour, endHour) {}

Manager::~Manager() {}

// Afiseaza informatiile despre manager, rescriind metoda din clasa de baza
void Manager::displayInfo() const
{
    std::cout << "[Manager] ";
    Employee::displayInfo();
}

double Manager::calculateDailySalary() const
{
    return calculateWorkedHours(startHour, endHour) * hourlyRate;
}