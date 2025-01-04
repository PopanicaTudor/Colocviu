#include "Barista.h"

Barista::Barista(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour)
    : Employee(firstName, lastName, "Barista", startHour, endHour) {}

Barista::~Barista() {}

void Barista::displayInfo() const
{
    std::cout << "[Barista] ";
    Employee::displayInfo();
}