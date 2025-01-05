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
    std::cout << "Pret produs: ";
    std::cin >> price;
    std::cout << "Stoc produs: ";
    std::cin >> stock;

    auto newProduct = std::make_unique<Product>(name, price, stock);
    products.push_back(std::move(newProduct));

    // Adaugă produsul în CSV
    Product::addProductToCSV(*products.back(), productsFilePath);
}

void productChoice2(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
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

void productChoice3(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products)
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

void productChoice4(std::string selectedCity, std::vector<std::unique_ptr<Product>> &products)
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