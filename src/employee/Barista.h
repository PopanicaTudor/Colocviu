#ifndef BARISTA_H
#define BARISTA_H

#include "Employee.h"

class Barista : public Employee
{
public:
    Barista(const std::string &firstName, const std::string &lastName, const std::string &startHour, const std::string &endHour);
    ~Barista() override;

    void displayInfo() const override;
};

#endif