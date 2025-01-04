#include "Employee.h"
#include "Manager.h"
#include "Barista.h"
#include "Waiter.h"
#include <iostream>
#include <sstream>
#include <fstream>

Employee::Employee(const std::string &firstName, const std::string &lastName, const std::string &role, const std::string &startHour, const std::string &endHour)
    : firstName(firstName), lastName(lastName), role(role), startHour(startHour), endHour(endHour) {}

Employee::~Employee() {}

void Employee::displayInfo() const
{
    std::cout << "Nume: " << firstName << " " << lastName
              << ", Program: " << startHour << " - " << endHour << "\n";
}

std::string Employee::getFirstName() const
{
    return firstName;
}

std::string Employee::getLastName() const
{
    return lastName;
}

std::string Employee::getRole() const
{
    return role;
}

std::string Employee::getStartHour() const
{
    return startHour;
}

std::string Employee::getEndHour() const
{
    return endHour;
}

void Employee::setFirstName(const std::string &firstName)
{
    this->firstName = firstName;
}

void Employee::setLastName(const std::string &lastName)
{
    this->lastName = lastName;
}

void Employee::setRole(const std::string &role)
{
    this->role = role;
}

void Employee::setStartHour(const std::string &startHour)
{
    this->startHour = startHour;
}

void Employee::setEndHour(const std::string &endHour)
{
    this->endHour = endHour;
}

// Adaugă un nou angajat în fișierul CSV
void Employee::addEmployeeToCSV(const Employee &employee, const std::string &filePath)
{
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << employee.getFirstName() << "," << employee.getLastName() << "," << employee.getRole() << ","
             << employee.getStartHour() << "," << employee.getEndHour() << "\n";
        file.close();
    }
    else
    {
        std::cerr << "Fisierul nu putut fi deschis pentru scriere!\n";
    }
}

// Actualizează complet fișierul CSV cu lista angajaților
void Employee::updateEmployeeCSV(const std::vector<std::unique_ptr<Employee>> &employees, const std::string &filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        // Scrie antetul fișierului
        file << "FirstName,LastName,Role,StartHour,EndHour\n";

        // Scrie fiecare angajat
        for (const auto &employee : employees)
        {
            file << employee->getFirstName() << "," << employee->getLastName() << "," << employee->getRole() << ","
                 << employee->getStartHour() << "," << employee->getEndHour() << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Fisierul nu putut fi deschis pentru actualizare!\n";
    }
}

std::vector<std::unique_ptr<Employee>> Employee::readEmployeesFromCSV(const std::string &filePath)
{
    std::vector<std::unique_ptr<Employee>> employees;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Fisierul nu a putut fi deschis pentru citire: " << filePath << "\n";
        return employees;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue; // Sări peste antet
        }

        std::istringstream ss(line);
        std::string firstName, lastName, role, startHour, endHour;

        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, role, ',');
        std::getline(ss, startHour, ',');
        std::getline(ss, endHour, ',');

        if (role == "Manager")
        {
            employees.push_back(std::make_unique<Manager>(firstName, lastName, startHour, endHour));
        }
        else if (role == "Barista")
        {
            employees.push_back(std::make_unique<Barista>(firstName, lastName, startHour, endHour));
        }
        else if (role == "Waiter")
        {
            employees.push_back(std::make_unique<Waiter>(firstName, lastName, startHour, endHour));
        }
        else
        {
            std::cerr << "Rol necunoscut pentru angajat: " << firstName << " " << lastName << "\n";
        }
    }

    file.close();
    return employees;
}