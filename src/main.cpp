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

    try
    {

        while (true)
        {
            try
            {
                selectedCity = selectCity();
                std::cout << "\nAti selectat orasul: " << selectedCity << "\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la selectarea orasului: " << e.what() << "\n";
                continue;
            }

            /// Căile fișierelor CSV pentru angajați, produse, evenimente și rapoarte
            const std::string employeesFilePath = "../data/employees/" + selectedCity + ".csv";
            const std::string productsFilePath = "../data/products/" + selectedCity + ".csv";
            const std::string eventsFilePath = "../data/events/" + selectedCity + ".csv";
            const std::string reportsFilePath = "../data/reports/" + selectedCity + ".csv";

            /// Verificăm dacă fișierele CSV sunt goale și adăugăm antetele dacă este necesar
            std::ifstream infile;

            // Fișierul pentru angajați
            try
            {
                infile.open(employeesFilePath);
                if (infile.peek() == std::ifstream::traits_type::eof())
                {
                    std::ofstream outfile(employeesFilePath);
                    outfile << "FirstName,LastName,Role,StartHour,EndHour\n";
                }
                infile.close();
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru angajati: " << e.what() << "\n";
            }

            // Fișierul pentru produse
            try
            {
                infile.open(productsFilePath);
                if (infile.peek() == std::ifstream::traits_type::eof())
                {
                    std::ofstream outfile(productsFilePath);
                    outfile << "Name,Price,Stock\n";
                }
                infile.close();
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru produse: " << e.what() << "\n";
            }

            // Fișierul pentru evenimente
            try
            {
                infile.open(eventsFilePath);
                if (infile.peek() == std::ifstream::traits_type::eof())
                {
                    std::ofstream outfile(eventsFilePath);
                    outfile << "Name,Date,Cost,Type,AdditionalInfo\n";
                }
                infile.close();
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru evenimente: " << e.what() << "\n";
            }

            // Fișierul pentru rapoarte
            try
            {
                infile.open(reportsFilePath);
                if (infile.peek() == std::ifstream::traits_type::eof())
                {
                    std::ofstream outfile(reportsFilePath);
                    outfile << "Date,EmployeeCost,OrderCost,EventCost,TotalCost,TotalIncome,Profit\n";
                }
                infile.close();
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru rapoarte: " << e.what() << "\n";
            }

            /// Stocăm datele
            // Stochează angajații
            std::vector<std::unique_ptr<Employee>> employees;
            try
            {
                employees = storeEmployees(employeesFilePath);
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la stocarea angajatilor: " << e.what() << "\n";
            }

            // Stochează produsele
            std::vector<std::unique_ptr<Product>> products;
            try
            {
                products = storeProducts(productsFilePath);
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la stocarea produselor: " << e.what() << "\n";
            }

            /// Meniul principal
            while (true)
            {
                // Alegerea unei opțiuni din meniul principal
                int mainChoice;
                try
                {
                    mainChoice = mainMenu(selectedCity);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "A aparut o eroare la afisarea meniului principal: " << e.what() << "\n";
                    continue;
                }

                if (mainChoice == 1)
                {
                    /// Meniul de gestionare a angajaților
                    while (true)
                    {
                        // Alegerea unei opțiuni din meniul angajaților
                        int empChoice;
                        try
                        {
                            empChoice = employeesMenu(selectedCity);
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "A aparut o eroare la afisarea meniului pentru angajati: " << e.what() << "\n";
                            continue;
                        }

                        if (empChoice == 1)
                        {
                            try
                            {
                                employeeChoice1(employeesFilePath, employees);
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 1 pentru angajati: " << e.what() << "\n";
                            }
                        }
                        else if (empChoice == 2)
                        {
                            try
                            {
                                employeeChoice2(employeesFilePath, employees);
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 2 pentru angajati: " << e.what() << "\n";
                            }
                        }
                        else if (empChoice == 3)
                        {
                            try
                            {
                                employeeChoice3(employeesFilePath, employees);
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 3 pentru angajati: " << e.what() << "\n";
                            }
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
                        // Alegerea unei opțiuni din meniul produselor
                        int prodChoice;
                        try
                        {
                            prodChoice = productsMenu(selectedCity);
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "A aparut o eroare la afisarea meniului pentru produse: " << e.what() << "\n";
                            continue;
                            if (prodChoice == 1)
                            {
                                try
                                {
                                    productChoice1(productsFilePath, products);
                                }
                                catch (const std::exception &e)
                                {
                                    std::cerr << "A aparut o eroare la executarea optiunii 1 pentru produse: " << e.what() << "\n";
                                }
                            }
                            else if (prodChoice == 2)
                            {
                                try
                                {
                                    productChoice2(productsFilePath, products);
                                }
                                catch (const std::exception &e)
                                {
                                    std::cerr << "A aparut o eroare la executarea optiunii 2 pentru produse: " << e.what() << "\n";
                                }
                            }
                            else if (prodChoice == 3)
                            {
                                try
                                {
                                    productChoice3(productsFilePath, products);
                                }
                                catch (const std::exception &e)
                                {
                                    std::cerr << "A aparut o eroare la executarea optiunii 3 pentru produse: " << e.what() << "\n";
                                }
                            }
                            else if (prodChoice == 4)
                            {
                                try
                                {
                                    productChoice4(selectedCity, products);
                                }
                                catch (const std::exception &e)
                                {
                                    std::cerr << "A aparut o eroare la executarea optiunii 4 pentru produse: " << e.what() << "\n";
                                }
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
                }
                else if (mainChoice == 3)
                {
                    /// Simularea unei comenzi
                    try
                    {
                        orderSimulation(selectedCity, productsFilePath, products);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "A aparut o eroare la simularea comenzii: " << e.what() << "\n";
                    }
                }
                else if (mainChoice == 4)
                {
                    /// Organizarea unui eveniment
                    try
                    {
                        eventOrganizer(selectedCity);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "A aparut o eroare la organizarea evenimentului: " << e.what() << "\n";
                    }
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "A aparut o eroare neasteptata: " << e.what() << "\n";
    }

    return 0;
}