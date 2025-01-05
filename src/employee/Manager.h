#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee
{
private:
    double hourlyRate = 25.0;

public:
    Manager(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour);
    ~Manager() override;

    void displayInfo() const override;
    double calculateDailySalary() const override;
};

#endif