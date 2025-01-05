#include "util/selectCity.h"
#include "util/storeEmployees.h"
#include "util/storeProducts.h"
#include "menu/menu.h"
#include "menu/employeeChoices.h"
#include "menu/productChoices.h"
#include "menu/orderSimulation.h"
#include "menu/eventOrganizer.h"
#include "menu/eventChoices.h"
#include "menu/reportGenerator.h"

#include <iostream>
#include <fstream>
#include <memory>

int main()
{
    /// Selectarea orașului
    std::string selectedCity;

    while (true)
    {
        selectedCity = selectCity();
        std::cout << "\nAti selectat orasul: " << selectedCity << "\n";

        /// Căile fișierelor CSV pentru angajați, produse, evenimente și rapoarte
        const std::string employeesFilePath = "../data/employees/" + selectedCity + ".csv";
        const std::string productsFilePath = "../data/products/" + selectedCity + ".csv";
        const std::string eventsFilePath = "../data/events/" + selectedCity + ".csv";
        const std::string reportsFilePath = "../data/reports/" + selectedCity + ".csv";

        /// Verificăm dacă fișierele CSV sunt goale și adăugăm antetele dacă este necesar
        // Fișierul pentru angajați
        std::ifstream infile(employeesFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(employeesFilePath);
            outfile << "FirstName,LastName,Role,StartHour,EndHour\n";
        }
        infile.close();

        // Fișierul pentru produse
        infile.open(productsFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(productsFilePath);
            outfile << "Name,Price,Stock\n";
        }
        infile.close();

        // Fișierul pentru evenimente
        infile.open(eventsFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(eventsFilePath);
            outfile << "Name,Date,Cost,Type,AdditionalInfo\n";
        }

        // Fișierul pentru rapoarte
        infile.open(reportsFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(reportsFilePath);
            outfile << "Date,EmployeeCost,OrderCost,EventCost,TotalCost,TotalIncome,Profit\n";
        }

        /// Stocăm datele
        // Stochează angajații
        std::vector<std::unique_ptr<Employee>> employees = storeEmployees(employeesFilePath);

        // Stochează produsele
        std::vector<std::unique_ptr<Product>> products = storeProducts(productsFilePath);

        /// Meniul principal
        while (true)
        {
            int mainChoice = mainMenu(selectedCity);

            if (mainChoice == 1)
            {
                /// Meniul de gestionare a angajaților
                while (true)
                {
                    int empChoice = employeesMenu(selectedCity);

                    if (empChoice == 1)
                    {
                        employeeChoice1(employeesFilePath, employees);
                    }
                    else if (empChoice == 2)
                    {
                        employeeChoice2(employeesFilePath, employees);
                    }
                    else if (empChoice == 3)
                    {
                        employeeChoice3(employeesFilePath, employees);
                    }
                    else if (empChoice == 4)
                    {
                        employeeChoice4(selectedCity, employees);
                    }
                    else if (empChoice == 5)
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Optiune invalida. Reincercati!\n";
                    }
                }
            }
            else if (mainChoice == 2)
            {
                /// Meniul de gestionare a produselor
                while (true)
                {
                    int prodChoice = productsMenu(selectedCity);

                    if (prodChoice == 1)
                    {
                        productChoice1(productsFilePath, products);
                    }
                    else if (prodChoice == 2)
                    {
                        productChoice2(productsFilePath, products);
                    }
                    else if (prodChoice == 3)
                    {
                        productChoice3(productsFilePath, products);
                    }
                    else if (prodChoice == 4)
                    {
                        productChoice4(selectedCity, products);
                    }
                    else if (prodChoice == 5)
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Optiune invalida. Reincercati!\n";
                    }
                }
            }
            else if (mainChoice == 3)
            {
                /// Simularea unei comenzi
                orderSimulation(selectedCity, productsFilePath, products);
            }
            else if (mainChoice == 4)
            {
                /// Organizarea unui eveniment
                eventOrganizer(selectedCity);
            }
            else if (mainChoice == 5)
            {
                /// Generarea unui raport
                reportGenerator(selectedCity, employeesFilePath, productsFilePath, eventsFilePath, reportsFilePath);
            }
            else if (mainChoice == 6)
            {
                break;
            }
            else
            {
                std::cout << "Optiune invalida. Reincercati!\n";
            }
        }
    }

    return 0;
}