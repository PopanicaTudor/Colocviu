#include "../util/CSVParser.h"
#include "../employee/Employee.h"
#include "../employee/Manager.h"
#include "../employee/Barista.h"
#include "../employee/Waiter.h"

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

std::vector<std::unique_ptr<Employee>> storeEmployees(std::string employeesFilePath)
{
    // Citește angajații din fișierul CSV
    CSVParser parser(employeesFilePath);
    std::vector<std::map<std::string, std::string>> employeeData = parser.readCSV();

    // Populează vectorul de angajați
    std::vector<std::unique_ptr<Employee>> employees;

    // Parsează și creează obiecte Employee
    for (const auto &row : employeeData)
    {
        const std::string &role = row.at("Role");

        if (role == "Manager")
        {
            employees.push_back(std::make_unique<Manager>(
                row.at("FirstName"),
                row.at("LastName"),
                row.at("StartHour"),
                row.at("EndHour")));
        }
        else if (role == "Barista")
        {
            employees.push_back(std::make_unique<Barista>(
                row.at("FirstName"),
                row.at("LastName"),
                row.at("StartHour"),
                row.at("EndHour")));
        }
        else if (role == "Waiter")
        {
            employees.push_back(std::make_unique<Waiter>(
                row.at("FirstName"),
                row.at("LastName"),
                row.at("StartHour"),
                row.at("EndHour")));
        }
        else
        {
            std::cerr << "Job necunoscut: " << role << " pentru angajatul "
                      << row.at("FirstName") << " " << row.at("LastName") << "\n";
        }
    }

    return employees;
}
