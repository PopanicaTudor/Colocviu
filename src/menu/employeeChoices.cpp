#include "EmployeeChoices.h"
#include "../employee/Employee.h"
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

    std::cout << "Ora incepere program (HH:MM): ";
    std::cin >> startHour;

    // Verificare format ora
    if (startHour.size() != 5 || startHour[2] != ':' ||
        !isdigit(startHour[0]) || !isdigit(startHour[1]) ||
        !isdigit(startHour[3]) || !isdigit(startHour[4]))
    {
        throw std::invalid_argument("Formatul orei este invalid. Utilizati HH:MM.");
    }

    int startHourInt = std::stoi(startHour.substr(0, 2));
    if (startHourInt < 0 || startHourInt > 24)
    {
        throw std::invalid_argument("Ora de inceput trebuie sa fie intre 00 si 24.");
    }

    std::cout << "Ora sfarsit program (HH:MM): ";
    std::cin >> endHour;

    // Verificare format ora
    if (endHour.size() != 5 || endHour[2] != ':' ||
        !isdigit(endHour[0]) || !isdigit(endHour[1]) ||
        !isdigit(endHour[3]) || !isdigit(endHour[4]))
    {
        throw std::invalid_argument("Formatul orei este invalid. Utilizati HH:MM.");
    }

    int endHourInt = std::stoi(endHour.substr(0, 2));
    if (endHourInt < 0 || endHourInt > 24)
    {
        throw std::invalid_argument("Ora de sfarsit trebuie sa fie intre 00 si 24.");
    }

    if (endHourInt <= startHourInt)
    {
        throw std::invalid_argument("Ora de sfarsit trebuie sa fie strict mai mare decat ora de inceput.");
    }

    if (firstName.empty() || lastName.empty() || role.empty() || startHour.empty() || endHour.empty())
    {
        throw std::invalid_argument("Toate campurile trebuie completate.");
    }

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
        throw std::invalid_argument("Rol necunoscut. Angajatul nu a fost adaugat.");
    }

    // Adaugă angajatul în vector
    employees.push_back(std::move(newEmployee));

    // Adaugă angajatul în CSV
    try
    {
        Employee::addEmployeeToCSV(*employees.back(), employeesFilePath);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Eroare la adaugarea angajatului in CSV: " + std::string(e.what()));
    }

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
        throw std::runtime_error("Angajatul nu a fost gasit.");
    }

    // Actualizează fișierul CSV
    try
    {
        Employee::updateEmployeeCSV(employees, employeesFilePath);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Eroare la actualizarea fisierului CSV: " + std::string(e.what()));
    }
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
                throw std::invalid_argument("Rol necunoscut. Modificarea a fost anulata.");
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

            // Verificare format ora
            if (newStartHour.size() != 5 || newStartHour[2] != ':' ||
                !isdigit(newStartHour[0]) || !isdigit(newStartHour[1]) ||
                !isdigit(newStartHour[3]) || !isdigit(newStartHour[4]))
            {
                throw std::invalid_argument("Formatul orei este invalid. Utilizati HH:MM.");
            }

            int newStartHourInt = std::stoi(newStartHour.substr(0, 2));
            if (newStartHourInt < 0 || newStartHourInt > 24)
            {
                throw std::invalid_argument("Ora de inceput trebuie sa fie intre 00 si 24.");
            }

            (*it)->setStartHour(newStartHour);
        }

        std::cout << "Ora sfarsit actuala: " << (*it)->getEndHour() << ". Doriti sa modificati? (da/nu): ";
        std::cin >> choice;

        if (choice == "da")
        {
            std::string newEndHour;
            std::cout << "Ora sfarsit noua: ";
            std::cin >> newEndHour;

            // Verificare format ora
            if (newEndHour.size() != 5 || newEndHour[2] != ':' ||
                !isdigit(newEndHour[0]) || !isdigit(newEndHour[1]) ||
                !isdigit(newEndHour[3]) || !isdigit(newEndHour[4]))
            {
                throw std::invalid_argument("Formatul orei este invalid. Utilizati HH:MM.");
            }

            int newEndHourInt = std::stoi(newEndHour.substr(0, 2));
            if (newEndHourInt < 0 || newEndHourInt > 24)
            {
                throw std::invalid_argument("Ora de sfarsit trebuie sa fie intre 00 si 24.");
            }

            if (newEndHourInt <= std::stoi((*it)->getStartHour().substr(0, 2)))
            {
                throw std::invalid_argument("Ora de sfarsit trebuie sa fie strict mai mare decat ora de inceput.");
            }

            (*it)->setEndHour(newEndHour);
        }

        // Actualizează fișierul CSV
        try
        {
            Employee::updateEmployeeCSV(employees, employeesFilePath);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Eroare la actualizarea fisierului CSV: " + std::string(e.what()));
        }
    }
    else
    {
        // Angajatul nu există
        throw std::runtime_error("Angajatul nu a fost gasit.");
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