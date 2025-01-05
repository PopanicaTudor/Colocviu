#ifndef WAITER_H
#define WAITER_H

#include "Employee.h"

class Waiter : public Employee
{
private:
    double hourlyRate = 10.0;

public:
    Waiter(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour);
    ~Waiter() override;

    void displayInfo() const override;
    double calculateDailySalary() const override;
};

#endif