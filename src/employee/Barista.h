#ifndef BARISTA_H
#define BARISTA_H

#include "Employee.h"

class Barista : public Employee
{
private:
    double hourlyRate = 15.0;

public:
    Barista(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour);
    ~Barista() override;

    void displayInfo() const override;
    double calculateDailySalary() const override;
};

#endif