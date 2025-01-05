#include "employeeChoices.h"
#include "../employee/employee.h"
#include "../employee/Manager.h"
#include "../employee/Barista.h"
#include "../employee/Waiter.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

void employeeChoice1(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees)
{
    std::string firstName, lastName, role, startHour, endHour;
    std::cout << "Prenume: ";
    std::cin >> firstName;
    std::cout << "Nume: ";
    std::cin >> lastName;
    std::cout << "Job (Manager, Barista, Waiter): ";
    std::cin >> role;
    std::cout << "Ora incepere program: ";
    std::cin >> startHour;
    std::cout << "Ora sfarsit program: ";
    std::cin >> endHour;

    std::unique_ptr<Employee> newEmployee;

    if (role == "Manager")
    {
        newEmployee = std::make_unique<Manager>(firstName, lastName, startHour, endHour);
    }
    else if (role == "Barista")
    {
        newEmployee = std::make_unique<Barista>(firstName, lastName, startHour, endHour);
    }
    else if (role == "Waiter")
    {
        newEmployee = std::make_unique<Waiter>(firstName, lastName, startHour, endHour);
    }
    else
    {
        std::cerr << "Rol necunoscut. Angajatul nu a fost adaugat.\n";
    }

    // Adaugă angajatul în vector
    employees.push_back(std::move(newEmployee));

    // Adaugă angajatul în CSV
    Employee::addEmployeeToCSV(*employees.back(), employeesFilePath);

    std::cout << "Angajat adaugat cu succes!\n";
}

void employeeChoice2(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees)
{
    std::string firstName, lastName;
    std::cout << "Prenume: ";
    std::cin >> firstName;
    std::cout << "Nume: ";
    std::cin >> lastName;

    auto it = std::remove_if(employees.begin(), employees.end(),
                             [&firstName, &lastName](const std::unique_ptr<Employee> &employee)
                             {
                                 return employee->getFirstName() == firstName &&
                                        employee->getLastName() == lastName;
                             });

    if (it != employees.end())
    {
        employees.erase(it, employees.end());
        std::cout << "Angajat sters cu succes!\n";
    }
    else
    {
        std::cout << "Angajatul nu a fost gasit.\n";
    }

    // Actualizează fișierul CSV
    Employee::updateEmployeeCSV(employees, employeesFilePath);
}

void employeeChoice3(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees)
{
    std::string firstName, lastName;
    std::cout << "Prenume: ";
    std::cin >> firstName;
    std::cout << "Nume: ";
    std::cin >> lastName;

    auto it = std::find_if(employees.begin(), employees.end(),
                           [&firstName, &lastName](const std::unique_ptr<Employee> &employee)
                           {
                               return employee->getFirstName() == firstName &&
                                      employee->getLastName() == lastName;
                           });

    if (it != employees.end())
    {
        // Angajatul există
        std::cout << "Angajatul \"" << (*it)->getFirstName() << " " << (*it)->getLastName() << "\" a fost gasit.\n";
        std::cout << "Job actual: " << (*it)->getRole() << ". Doriti sa modificati? (da/nu): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "da")
        {
            std::string newRole;
            std::cout << "Job nou (Manager, Barista, Waiter): ";
            std::cin >> newRole;

            // Creează un nou obiect pentru rolul specificat
            std::unique_ptr<Employee> newEmployee;

            if (newRole == "Manager")
            {
                newEmployee = std::make_unique<Manager>((*it)->getFirstName(), (*it)->getLastName(), (*it)->getStartHour(), (*it)->getEndHour());
            }
            else if (newRole == "Barista")
            {
                newEmployee = std::make_unique<Barista>((*it)->getFirstName(), (*it)->getLastName(), (*it)->getStartHour(), (*it)->getEndHour());
            }
            else if (newRole == "Waiter")
            {
                newEmployee = std::make_unique<Waiter>((*it)->getFirstName(), (*it)->getLastName(), (*it)->getStartHour(), (*it)->getEndHour());
            }
            else
            {
                std::cerr << "Rol necunoscut. Modificarea a fost anulata.\n";
            }

            // Înlocuiește obiectul vechi cu cel nou
            *it = std::move(newEmployee);
            std::cout << "Rol modificat cu succes!\n";
        }

        std::cout << "Ora incepere actuala: " << (*it)->getStartHour() << ". Doriti sa modificati? (da/nu): ";
        std::cin >> choice;

        if (choice == "da")
        {
            std::string newStartHour;
            std::cout << "Ora incepere noua: ";
            std::cin >> newStartHour;
            (*it)->setStartHour(newStartHour);
        }

        std::cout << "Ora sfarsit actuala: " << (*it)->getEndHour() << ". Doriti sa modificati? (da/nu): ";
        std::cin >> choice;

        if (choice == "da")
        {
            std::string newEndHour;
            std::cout << "Ora sfarsit noua: ";
            std::cin >> newEndHour;
            (*it)->setEndHour(newEndHour);
        }

        // Actualizează fișierul CSV
        Employee::updateEmployeeCSV(employees, employeesFilePath);
    }
    else
    {
        // Angajatul nu există
        std::cout << "Angajatul nu a fost gasit.\n";
    }
}

void employeeChoice4(std::string selectedCity, std::vector<std::unique_ptr<Employee>> &employees)
{
    if (employees.empty())
    {
        std::cout << "Nu exista angajati in " << selectedCity << ".\n";
    }
    else
    {
        std::cout << "Toti angajatii din " << selectedCity << ":\n";

        // Afiseaza toti managerii
        bool hasManagers = false;
        std::cout << "\nManageri:\n";
        for (const auto &employee : employees)
        {
            if (dynamic_cast<Manager *>(employee.get()))
            {
                employee->displayInfo();
                hasManagers = true;
            }
        }
        if (!hasManagers)
        {
            std::cout << "Nu exista manageri in " << selectedCity << ".\n";
        }

        // Afiseaza toti barista
        bool hasBaristas = false;
        std::cout << "\nBarista:\n";
        for (const auto &employee : employees)
        {
            if (dynamic_cast<Barista *>(employee.get()))
            {
                employee->displayInfo();
                hasBaristas = true;
            }
        }
        if (!hasBaristas)
        {
            std::cout << "Nu exista barista in " << selectedCity << ".\n";
        }

        // Afiseaza toti ospatarii
        bool hasWaiters = false;
        std::cout << "\nOspatari:\n";
        for (const auto &employee : employees)
        {
            if (dynamic_cast<Waiter *>(employee.get()))
            {
                employee->displayInfo();
                hasWaiters = true;
            }
        }
        if (!hasWaiters)
        {
            std::cout << "Nu exista ospatari in " << selectedCity << ".\n";
        }
    }
}