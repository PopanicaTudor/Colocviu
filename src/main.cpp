/// Includerea fișierelor header
#include "util/SelectCity.h"
#include "util/StoreEmployees.h"
#include "util/StoreProducts.h"
#include "menu/Menu.h"
#include "menu/EmployeeChoices.h"
#include "menu/ProductChoices.h"
#include "menu/OrderSimulation.h"
#include "menu/EventOrganizer.h"
#include "menu/EventChoices.h"
#include "menu/ReportGenerator.h"
#include "util/Logger.h"

/// Includerea bibliotecilor necesare
#include <iostream>
#include <fstream>
#include <memory>

/// Funcția principală
int main()
{
    /// Inițializarea logger-ului; Concept de Singleton (Design Pattern)
    Logger *logger;

    try
    {
        logger = Logger::getInstance();
        logger->log("Program started");
    }
    catch(const std::exception& e)
    {
        std::cerr << "A aparut o eroare la initializarea logger-ului: " << e.what() << "\n";
    }

    /// Selectarea orașului
    std::string selectedCity;

    // Folosire block-uri try-throw-catch pentru a trata excepțiile care pot apărea în timpul rulării programului; Concept de exceptions
    try
    {

        while (true)
        {
            try
            {
                selectedCity = selectCity();
                std::cout << "\nAti selectat orasul: " << selectedCity << "\n";

                logger->log("Selected city: " + selectedCity);
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la selectarea orasului: " << e.what() << "\n";

                logger->log("Error selecting city: " + std::string(e.what()));
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

                logger->log("Checked employees file");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru angajati: " << e.what() << "\n";

                logger->log("Error checking employees file: " + std::string(e.what()));
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

                logger->log("Checked products file");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru produse: " << e.what() << "\n";

                logger->log("Error checking products file: " + std::string(e.what()));
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

                logger->log("Checked events file");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru evenimente: " << e.what() << "\n";

                logger->log("Error checking events file: " + std::string(e.what()));
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

                logger->log("Checked reports file");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la verificarea fisierului pentru rapoarte: " << e.what() << "\n";

                logger->log("Error checking reports file: " + std::string(e.what()));
            }

            /// Stocăm datele
            // Stochează angajații
            std::vector<std::unique_ptr<Employee>> employees;
            try
            {
                employees = storeEmployees(employeesFilePath);

                logger->log("Stored employees");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la stocarea angajatilor: " << e.what() << "\n";

                logger->log("Error storing employees: " + std::string(e.what()));
            }

            // Stochează produsele
            std::vector<std::unique_ptr<Product>> products;
            try
            {
                products = storeProducts(productsFilePath);

                logger->log("Stored products");
            }
            catch (const std::exception &e)
            {
                std::cerr << "A aparut o eroare la stocarea produselor: " << e.what() << "\n";

                logger->log("Error storing products: " + std::string(e.what()));
            }

            /// Meniul principal
            while (true)
            {
                // Alegerea unei opțiuni din meniul principal
                int mainChoice;
                try
                {
                    mainChoice = mainMenu(selectedCity);

                    logger->log("Selected main menu option: " + std::to_string(mainChoice));
                }
                catch (const std::exception &e)
                {
                    std::cerr << "A aparut o eroare la afisarea meniului principal: " << e.what() << "\n";

                    logger->log("Error selecting main menu option: " + std::string(e.what()));
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

                            logger->log("Selected employees menu option: " + std::to_string(empChoice));
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "A aparut o eroare la afisarea meniului pentru angajati: " << e.what() << "\n";

                            logger->log("Error selecting employees menu option: " + std::string(e.what()));
                            continue;
                        }

                        if (empChoice == 1)
                        {
                            try
                            {
                                employeeChoice1(employeesFilePath, employees);

                                logger->log("Executed employees menu option 1");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 1 pentru angajati: " << e.what() << "\n";

                                logger->log("Error executing employees menu option 1: " + std::string(e.what()));
                            }
                        }
                        else if (empChoice == 2)
                        {
                            try
                            {
                                employeeChoice2(employeesFilePath, employees);

                                logger->log("Executed employees menu option 2");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 2 pentru angajati: " << e.what() << "\n";

                                logger->log("Error executing employees menu option 2: " + std::string(e.what()));
                            }
                        }
                        else if (empChoice == 3)
                        {
                            try
                            {
                                employeeChoice3(employeesFilePath, employees);

                                logger->log("Executed employees menu option 3");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 3 pentru angajati: " << e.what() << "\n";

                                logger->log("Error executing employees menu option 3: " + std::string(e.what()));
                            }
                        }
                        else if (empChoice == 4)
                        {
                            try
                            {
                                employeeChoice4(selectedCity, employees);

                                logger->log("Executed employees menu option 4");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 4 pentru angajati: " << e.what() << "\n";

                                logger->log("Error executing employees menu option 4: " + std::string(e.what()));
                            }
                        }
                        else if (empChoice == 5)
                        {
                            logger->log("Exited employees menu");
                            break;
                        }
                        else
                        {
                            std::cout << "Optiune invalida. Reincercati!\n";
                            logger->log("Invalid employees menu option selected");
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

                            logger->log("Selected products menu option: " + std::to_string(prodChoice));
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "A aparut o eroare la afisarea meniului pentru produse: " << e.what() << "\n";

                            logger->log("Error selecting products menu option: " + std::string(e.what()));
                            continue;
                        }

                        if (prodChoice == 1)
                        {
                            try
                            {
                                productChoice1(productsFilePath, products);

                                logger->log("Executed products menu option 1");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 1 pentru produse: " << e.what() << "\n";

                                logger->log("Error executing products menu option 1: " + std::string(e.what()));
                            }
                        }
                        else if (prodChoice == 2)
                        {
                            try
                            {
                                productChoice2(productsFilePath, products);

                                logger->log("Executed products menu option 2");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 2 pentru produse: " << e.what() << "\n";

                                logger->log("Error executing products menu option 2: " + std::string(e.what()));
                            }
                        }
                        else if (prodChoice == 3)
                        {
                            try
                            {
                                productChoice3(productsFilePath, products);

                                logger->log("Executed products menu option 3");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 3 pentru produse: " << e.what() << "\n";

                                logger->log("Error executing products menu option 3: " + std::string(e.what()));
                            }
                        }
                        else if (prodChoice == 4)
                        {
                            try
                            {
                                productChoice4(selectedCity, products);

                                logger->log("Executed products menu option 4");
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "A aparut o eroare la executarea optiunii 4 pentru produse: " << e.what() << "\n";

                                logger->log("Error executing products menu option 4: " + std::string(e.what()));
                            }
                        }
                        else if (prodChoice == 5)
                        {
                            logger->log("Exited products menu");
                            break;
                        }
                        else
                        {
                            std::cout << "Optiune invalida. Reincercati!\n";
                            logger->log("Invalid products menu option selected");
                        }
                    }
                }
                else if (mainChoice == 3)
                {
                    /// Simularea unei comenzi
                    try
                    {
                        orderSimulation(selectedCity, productsFilePath, products);

                        logger->log("Executed order simulation");
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "A aparut o eroare la simularea comenzii: " << e.what() << "\n";

                        logger->log("Error executing order simulation: " + std::string(e.what()));
                    }
                }
                else if (mainChoice == 4)
                {
                    /// Organizarea unui eveniment
                    try
                    {
                        eventOrganizer(selectedCity);

                        logger->log("Executed event organizer");
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "A aparut o eroare la organizarea evenimentului: " << e.what() << "\n";

                        logger->log("Error executing event organizer: " + std::string(e.what()));
                    }
                }
                else if (mainChoice == 5)
                {
                    /// Generarea unui raport
                    try
                    {
                        reportGenerator(selectedCity, employeesFilePath, productsFilePath, eventsFilePath, reportsFilePath);

                        logger->log("Executed report generator");
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "A aparut o eroare la generarea raportului: " << e.what() << "\n";

                        logger->log("Error executing report generator: " + std::string(e.what()));
                    }
                }
                else if (mainChoice == 6)
                {
                    logger->log("Exited main menu");
                    logger->log("Program ended\n");
                    break;
                }
                else
                {
                    std::cout << "Optiune invalida. Reincercati!\n";
                    logger->log("Invalid main menu option selected");
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "A aparut o eroare neasteptata: " << e.what() << "\n";

        logger->log("Unexpected error: " + std::string(e.what()));
    }

    return 0;
}