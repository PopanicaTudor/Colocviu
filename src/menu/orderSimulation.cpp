#include "orderSimulation.h"
#include "../inventory/product.h"
#include "../order/order.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

void orderSimulation(std::string selectedCity, std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
{
    std::cout << "\n\tSimulare comanda pentru " << selectedCity << ":\n";

    std::string clientFirstName;
    std::string clientLastName;
    std::vector<Product> orderProducts;
    std::string orderDate;

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
                               [&productName](const std::unique_ptr<Product> &product)
                               {
                                   return product->getName() == productName;
                               });

        if (it != products.end())
        {
            int quantity;
            std::cout << "Cantitate: ";
            std::cin >> quantity;

            if ((*it)->getStock() >= quantity)
            {
                // Adăugăm produsul comandat
                orderProducts.push_back(Product((*it)->getName(), (*it)->getPrice(), quantity));
                // Reducem stocul produsului
                (*it)->setStock((*it)->getStock() - quantity);
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
    Product::updateProductCSV(products, productsFilePath);
}