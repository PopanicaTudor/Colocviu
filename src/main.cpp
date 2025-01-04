#include <iostream>
#include "util/CSVParser.h"
#include "employee/Employee.h"
#include "employee/Manager.h"
#include "employee/Barista.h"
#include "employee/Waiter.h"
#include "inventory/Product.h"
#include "order/Order.h"
#include "event/Event.h"
#include "event/MovieNight.h"
#include "event/Workshop.h"
#include "event/CoffeeTasting.h"
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>

std::string selectCity()
{
    while (true)
    {
        std::cout << "\n\tSelectati orasul pentru gestionare:\n";
        std::cout << "1. Bucuresti\n";
        std::cout << "2. Cluj-Napoca\n";
        std::cout << "3. Timisoara\n";
        std::cout << "4. Iasi\n";
        std::cout << "5. Brasov\n";
        std::cout << "6. Inchidere program\n";
        std::cout << "Optiune: ";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            return "Bucuresti";
        case 2:
            return "Cluj-Napoca";
        case 3:
            return "Timisoara";
        case 4:
            return "Iasi";
        case 5:
            return "Brasov";
        case 6:
            exit(0);
        default:
            std::cerr << "Optiune invalida. Reincercati!\n";
        }
    }
}

int main()
{
    std::string selectedCity;

    while (true)
    {
        selectedCity = selectCity();
        std::cout << "\nAti selectat orasul: " << selectedCity << "\n";

        // Actualizare calea fisierelor pentru orasul selectat
        std::string employeesFilePath = "../data/employees/" + selectedCity + ".csv";
        std::string productsFilePath = "../data/products/" + selectedCity + ".csv";
        std::string eventsFilePath = "../data/events/" + selectedCity + ".csv";

        // Check if the employees file is empty and add header if necessary
        std::ifstream infile(employeesFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(employeesFilePath);
            outfile << "FirstName,LastName,Role,StartHour,EndHour\n";
        }
        infile.close();

        // Check if the products file is empty and add header if necessary
        infile.open(productsFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(productsFilePath);
            outfile << "Name,Price,Stock\n";
        }
        infile.close();

        // Create a CSVParser instance
        CSVParser parser(employeesFilePath);

        // Read employees from the CSV file
        std::vector<std::map<std::string, std::string>> employeeData = parser.readCSV();

        // Store employees
        std::vector<std::unique_ptr<Employee>> employees;

        // Parse and create Employee objects
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

        // Read products from the CSV file
        parser = CSVParser(productsFilePath);
        std::vector<std::map<std::string, std::string>> productData = parser.readCSV();

        // Store products
        std::vector<std::unique_ptr<Product>> products;
        for (const auto &row : productData)
        {
            products.push_back(std::make_unique<Product>(
                row.at("Name"),
                std::stod(row.at("Price")),
                std::stoi(row.at("Stock"))));
        }

        // Check if the events file is empty and add header if necessary
        infile.open(eventsFilePath);
        if (infile.peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream outfile(eventsFilePath);
            outfile << "Name,Date,Cost,Type,AdditionalInfo\n";
        }

        // Main menu loop
        while (true)
        {
            std::cout << "\n\tMeniu principal pentru " << selectedCity << ":\n";
            std::cout << "1. Gestionare angajati\n";
            std::cout << "2. Gestionare produse\n";
            std::cout << "3. Simulare comanda\n";
            std::cout << "4. Organizare eveniment\n";
            std::cout << "5. Inapoi la selectare oras\n";
            std::cout << "Optiune: ";

            int mainChoice;
            std::cin >> mainChoice;

            if (mainChoice == 1)
            {
                // Employee management menu
                while (true)
                {
                    std::cout << "\n\tMeniu gestionare angajati pentru " << selectedCity << ":\n";
                    std::cout << "1. Adaugare angajat nou\n";
                    std::cout << "2. Stergere angajat existent\n";
                    std::cout << "3. Modificare angajat existent\n";
                    std::cout << "4. Afisare angajati\n";
                    std::cout << "5. Inapoi la meniul principal\n";
                    std::cout << "Optiune: ";

                    int empChoice;
                    std::cin >> empChoice;

                    if (empChoice == 1)
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
                    else if (empChoice == 2)
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
                    else if (empChoice == 3)
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
                    else if (empChoice == 4)
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
                // Product management menu loop
                while (true)
                {
                    std::cout << "\n\tMeniu gestionare produse pentru " << selectedCity << ":\n";
                    std::cout << "1. Adaugare produs nou\n";
                    std::cout << "2. Stergere produs existent\n";
                    std::cout << "3. Modificare produs existent\n";
                    std::cout << "4. Afisare produse\n";
                    std::cout << "5. Inapoi la meniul principal\n";
                    std::cout << "Optiune: ";

                    int prodChoice;
                    std::cin >> prodChoice;

                    if (prodChoice == 1)
                    {
                        std::string name;
                        double price;
                        int stock;
                        std::cout << "Nume produs: ";
                        std::cin >> name;
                        std::cout << "Pret produs: ";
                        std::cin >> price;
                        std::cout << "Stoc produs: ";
                        std::cin >> stock;

                        auto newProduct = std::make_unique<Product>(name, price, stock);
                        products.push_back(std::move(newProduct));

                        // Adaugă produsul în CSV
                        Product::addProductToCSV(*products.back(), productsFilePath);
                    }
                    else if (prodChoice == 2)
                    {
                        std::string name;
                        std::cout << "Nume produs: ";
                        std::cin >> name;

                        auto it = std::remove_if(products.begin(), products.end(),
                                                 [&name](const std::unique_ptr<Product> &product)
                                                 {
                                                     return product->getName() == name;
                                                 });

                        if (it != products.end())
                        {
                            products.erase(it, products.end());
                            std::cout << "Produs sters.\n";
                        }
                        else
                        {
                            std::cout << "Produsul nu a fost gasit.\n";
                        }

                        // Actualizează fișierul CSV
                        std::vector<std::unique_ptr<Product>> productPtrs;
                        for (auto &product : products)
                        {
                            productPtrs.push_back(std::make_unique<Product>(*product));
                        }
                        Product::updateProductCSV(productPtrs, productsFilePath);
                    }
                    else if (prodChoice == 3)
                    {
                        std::string name;
                        std::cout << "Nume produs: ";
                        std::cin >> name;

                        auto it = std::find_if(products.begin(), products.end(),
                                               [&name](const std::unique_ptr<Product> &product)
                                               {
                                                   return product->getName() == name;
                                               });

                        if (it != products.end())
                        {
                            // Produsul există
                            std::cout << "Produsul \"" << (*it)->getName() << "\" a fost gasit.\n";
                            std::cout << "Pret actual: " << (*it)->getPrice() << " RON. Doriti sa modificati? (da/nu): ";
                            std::string choice;
                            std::cin >> choice;

                            if (choice == "da")
                            {
                                double newPrice;
                                std::cout << "Pret nou: ";
                                std::cin >> newPrice;
                                (*it)->setPrice(newPrice);
                            }

                            std::cout << "Stoc actual: " << (*it)->getStock() << ". Doriti sa modificati? (da/nu): ";
                            std::cin >> choice;

                            if (choice == "da")
                            {
                                int newStock;
                                std::cout << "Stoc nou: ";
                                std::cin >> newStock;
                                (*it)->setStock(newStock);
                            }

                            // Actualizează fișierul CSV
                            std::vector<std::unique_ptr<Product>> productPtrs;
                            for (auto &product : products)
                            {
                                productPtrs.push_back(std::make_unique<Product>(*product));
                            }
                            Product::updateProductCSV(productPtrs, productsFilePath);
                        }
                        else
                        {
                            // Produsul nu există
                            std::cout << "Produsul \"" << name << "\" nu a fost gasit. Doriti sa-l adaugati? (da/nu): ";
                            std::string choice;
                            std::cin >> choice;

                            if (choice == "da")
                            {
                                std::string name;
                                double price;
                                int stock;
                                std::cout << "Nume produs: ";
                                std::cin >> name;
                                std::cout << "Pret produs: ";
                                std::cin >> price;
                                std::cout << "Stoc produs: ";
                                std::cin >> stock;

                                auto newProduct = std::make_unique<Product>(name, price, stock);
                                products.push_back(std::move(newProduct));

                                // Adaugă produsul în CSV
                                Product::addProductToCSV(*products.back(), productsFilePath);
                            }
                        }
                    }
                    else if (prodChoice == 4)
                    {
                        if (products.empty())
                        {
                            std::cout << "Nu exista produse in " << selectedCity << ".\n";
                        }
                        else
                        {
                            std::cout << "Toate produsele din " << selectedCity << ":\n";
                            for (const auto &product : products)
                            {
                                product->displayProduct();
                            }
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
            else if (mainChoice == 3)
            {
                std::cout << "\n\tSimulare comanda pentru " << selectedCity << ":\n";

                std::string clientFirstName;
                std::string clientLastName;
                std::vector<Product> orderProducts;
                std::string orderDate;

                // Încărcăm produsele din CSV
                std::vector<Product> products = Product::loadProductsFromCSV(productsFilePath);

                // Citim numele clientului
                std::cout << "Prenume client: ";
                std::cin >> clientFirstName;

                std::cout << "Nume client: ";
                std::cin >> clientLastName;

                // Citim data comenzii
                std::cout << "Data comenzii (ZZ/LL/AAAA): ";
                std::cin >> orderDate;

                // Adăugăm produse în comandă
                while (true)
                {
                    std::string productName;
                    std::cout << "Nume produs: ";
                    std::cin >> productName;

                    auto it = std::find_if(products.begin(), products.end(),
                                           [&productName](const Product &product)
                                           {
                                               return product.getName() == productName;
                                           });

                    if (it != products.end())
                    {
                        int quantity;
                        std::cout << "Cantitate: ";
                        std::cin >> quantity;

                        if (it->getStock() >= quantity)
                        {
                            // Adăugăm produsul comandat
                            orderProducts.push_back(Product(it->getName(), it->getPrice(), quantity));
                            // Reducem stocul produsului
                            it->setStock(it->getStock() - quantity);
                        }
                        else
                        {
                            std::cout << "Stoc insuficient!\n";
                        }
                    }
                    else
                    {
                        std::cout << "Produsul nu a fost gasit.\n";
                    }

                    // Continuăm sau ieșim
                    std::cout << "\nAdauga alt produs? (da/nu): ";
                    std::string choice;
                    std::cin >> choice;

                    while (choice != "da" && choice != "nu")
                    {
                        std::cout << "Optiune invalida. Reincercati!\n";
                        std::cout << "Adauga alt produs? (da/nu): ";
                        std::cin >> choice;
                    }

                    if (choice == "nu")
                    {
                        break;
                    }
                }

                // Creăm comanda
                Order order(clientFirstName, clientLastName, orderProducts, productsFilePath, orderDate, selectedCity);

                // Comanda este finalizată cu reducerea aplicată dacă este cazul
                std::cout << "\nComanda finalizata!\n\n";
                order.printOrderDetails();

                // Actualizăm stocurile în fișierul CSV
                std::vector<std::unique_ptr<Product>> productPtrs;
                for (auto &product : products)
                {
                    productPtrs.push_back(std::make_unique<Product>(product));
                }
                Product::updateProductCSV(productPtrs, productsFilePath);
            }
            else if (mainChoice == 4)
            {
                std::cout << "\n\tOrganizare eveniment pentru " << selectedCity << ":\n";

                std::unique_ptr<Event> event;

                std::string eventName;
                std::string eventDate;
                double eventCost;

                std::vector<std::string> coffeeTypes;
                std::string topic;
                int participantLimit = 0;
                std::string movieTitle;
                std::string startTime;

                std::cout << "\n\tSelectati tipul de eveniment:\n";
                std::cout << "1. Degustare de cafea\n";
                std::cout << "2. Atelier\n";
                std::cout << "3. Seara de film\n";
                std::cout << "4. Anulare\n";
                std::cout << "Optiune: ";

                int eventChoice;
                std::cin >> eventChoice;

                // Selectați tipul de eveniment
                if (eventChoice == 1)
                {
                    int noOfTypes;

                    std::cout << "Numar tipuri de cafea: ";
                    std::cin >> noOfTypes;

                    for (int i = 0; i < noOfTypes; i++)
                    {
                        std::string type;

                        std::cout << "Tip cafea " << i + 1 << ": ";
                        std::cin >> type;
                        coffeeTypes.push_back(type);
                    }
                }
                else if (eventChoice == 2)
                {
                    std::cout << "Subiect: ";
                    std::cin.ignore(); // Clear the newline character left in the buffer
                    std::getline(std::cin, topic);
                    std::cout << "Numar maxim participanti: ";
                    std::cin >> participantLimit;
                }
                else if (eventChoice == 3)
                {
                    std::cout << "Titlu film: ";
                    std::cin.ignore(); // Clear the newline character left in the buffer
                    std::getline(std::cin, movieTitle);
                    std::cout << "Ora incepere: ";
                    std::cin >> startTime;
                }
                else if (eventChoice == 4)
                {
                    break;
                }
                else
                {
                    std::cout << "Optiune invalida. Reincercati!\n";
                    break;
                }

                // Citire nume eveniment
                std::cout << "Nume eveniment: ";
                std::cin.ignore(); // Clear the newline character left in the buffer
                std::getline(std::cin, eventName);

                // Verificare dată eveniment
                time_t now = time(0);
                tm *ltm = localtime(&now);

                time_t eventTime;
                do
                {
                    // Citire dată eveniment
                    std::cout << "Data eveniment (ZZ/LL/AAAA): ";
                    std::cin >> eventDate;

                    struct tm eventTm = {};
                    std::istringstream ss(eventDate);
                    if (!(ss >> std::get_time(&eventTm, "%d/%m/%Y")))
                    {
                        std::cout << "Format invalid. Introduceti o data valida!\n";
                        continue;
                    }

                    eventTime = mktime(&eventTm);

                    if (difftime(eventTime, now) < 0)
                    {
                        std::cout << "Data evenimentului nu poate fi in trecut. Introduceti o data valida!\n";
                    }
                } while (difftime(eventTime, now) < 0);

                // Citire cost eveniment
                std::cout << "Cost eveniment: ";
                std::cin >> eventCost;

                // Creare obiect eveniment
                if (eventChoice == 1)
                {
                    event = std::make_unique<CoffeeTasting>(eventName, eventDate, eventCost, coffeeTypes, selectedCity);
                    event->displayDetails();
                }
                else if (eventChoice == 2)
                {
                    event = std::make_unique<Workshop>(eventName, eventDate, eventCost, topic, participantLimit, selectedCity);
                    event->displayDetails();
                }
                else if (eventChoice == 3)
                {
                    event = std::make_unique<MovieNight>(eventName, eventDate, eventCost, movieTitle, startTime, selectedCity);
                    event->displayDetails();
                }
                
                // Efectuează acțiunea evenimentului dacă este este acceași zi
                if (difftime(eventTime, now) == 0)
                {
                    event->performEventAction();
                }
            }
            else if (mainChoice == 5)
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