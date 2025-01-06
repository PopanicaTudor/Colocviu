#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

/// Clasa Manager, derivată din clasa Employee; Concept de moștenire
class Manager : public Employee
{
private:
    double hourlyRate = 25.0;

public:
    Manager(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour);
    ~Manager() override; // Override pentru destructorul clasei de bază

    void displayInfo() const override; // Override pentru metoda virtuală din clasa de bază
    double calculateDailySalary() const override; // Override pentru metoda virtuală pură din clasa de bază
};

#endif