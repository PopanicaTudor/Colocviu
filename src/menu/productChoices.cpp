#include "productChoices.h"
#include "../inventory/product.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

void productChoice1(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
{
    std::string name;
    double price;
    int stock;
    std::cout << "Nume produs: ";
    std::cin >> name;
    std::cin.ignore();
    std::getline(std::cin, name);

    if (name.empty())
    {
        throw std::invalid_argument("Numele produsului nu poate fi gol.");
    }

    std::cout << "Pret produs: ";
    std::cin >> price;
    if (price <= 0)
    {
        throw std::invalid_argument("Pretul produsului trebuie sa fie mai mare decat zero.");
    }

    std::cout << "Stoc produs: ";
    std::cin >> stock;
    if (stock < 0)
    {
        throw std::invalid_argument("Stocul produsului nu poate fi negativ.");
    }

    auto newProduct = std::make_unique<Product>(name, price, stock);
    products.push_back(std::move(newProduct));

    // Adaugă produsul în CSV
    Product::addProductToCSV(*products.back(), productsFilePath);
}

void productChoice2(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
{
    std::string name;
    std::cout << "Nume produs: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (name.empty())
    {
        throw std::invalid_argument("Numele produsului nu poate fi gol.");
    }

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
        throw std::runtime_error("Produsul nu a fost gasit.");
    }

    // Actualizează fișierul CSV
    std::vector<std::unique_ptr<Product>> productPtrs;
    for (auto &product : products)
    {
        productPtrs.push_back(std::make_unique<Product>(*product));
    }
    Product::updateProductCSV(productPtrs, productsFilePath);
}

void productChoice3(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
{
    std::string name;
    std::cout << "Nume produs: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (name.empty())
    {
        throw std::invalid_argument("Numele produsului nu poate fi gol.");
    }

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
            if (newPrice <= 0)
            {
                throw std::invalid_argument("Pretul nou trebuie sa fie mai mare decat zero.");
            }
            (*it)->setPrice(newPrice);
        }

        std::cout << "Stoc actual: " << (*it)->getStock() << ". Doriti sa modificati? (da/nu): ";
        std::cin >> choice;

        if (choice == "da")
        {
            int newStock;
            std::cout << "Stoc nou: ";
            std::cin >> newStock;
            if (newStock < 0)
            {
                throw std::invalid_argument("Stocul nou nu poate fi negativ.");
            }
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
            std::cin.ignore();
            std::getline(std::cin, name);

            if (name.empty())
            {
                throw std::invalid_argument("Numele produsului nu poate fi gol.");
            }

            std::cout << "Pret produs: ";
            std::cin >> price;

            if (price <= 0)
            {
                throw std::invalid_argument("Pretul produsului trebuie sa fie mai mare decat zero.");
            }

            std::cout << "Stoc produs: ";
            std::cin >> stock;

            if (stock < 0)
            {
                throw std::invalid_argument("Stocul produsului nu poate fi negativ.");
            }

            auto newProduct = std::make_unique<Product>(name, price, stock);
            products.push_back(std::move(newProduct));

            // Adaugă produsul în CSV
            Product::addProductToCSV(*products.back(), productsFilePath);
        }
    }
}

void productChoice4(std::string selectedCity, std::vector<std::unique_ptr<Product>> &products)
{
    if (products.empty())
    {
        throw std::runtime_error("Nu exista produse in " + selectedCity + ".");
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