#include "Waiter.h"

Waiter::Waiter(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour)
    : Employee(firstName, lastName, "Waiter", startHour, endHour) {}

Waiter::~Waiter() {}

void Waiter::displayInfo() const
{
    std::cout << "[Ospatar] ";
    Employee::displayInfo();
}