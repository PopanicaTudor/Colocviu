#include "Product.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Constructor implicit
Product::Product() : name(""), price(0.0), stock(0) {}

// Constructor de copiere
Product::Product(const Product &other)
    : name(other.name), price(other.price), stock(other.stock) {}

// Constructor cu parametri
Product::Product(const std::string &name, double price, int stock)
    : name(name), price(price), stock(stock) {}

// Getters
std::string Product::getName() const
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

int Product::getStock() const
{
    return stock;
}

// Setters
void Product::setName(const std::string &name)
{
    this->name = name;
}

void Product::setPrice(double price)
{
    this->price = price;
}

void Product::setStock(int stock)
{
    this->stock = stock;
}

// Metodă pentru a afișa informații despre produs
void Product::displayProduct() const
{
    std::cout << "Produs: " << name
              << ", Pret: " << price
              << ", Stoc: " << stock << std::endl;
}

// Funcție pentru a citi produsele din fișierul CSV
std::vector<Product> Product::loadProductsFromCSV(const std::string &filePath)
{
    std::vector<Product> products;
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Eroare: Nu s-a putut deschide fisierul " << filePath << "!\n";
        return products;
    }

    // Citim linia de antet
    std::getline(file, line);

    // Citim fiecare linie de produs
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name;
        double price;
        int stock;

        std::getline(ss, name, ',');
        ss >> price;
        ss.ignore();
        ss >> stock;

        products.emplace_back(name, price, stock);
    }

    file.close();
    return products;
}

// Adaugă un produs în fișierul CSV
void Product::addProductToCSV(const Product &product, const std::string &filePath)
{
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << product.getName() << "," << product.getPrice() << "," << product.getStock() << "\n";
        file.close();
    }
    else
    {
        std::cerr << "Fisierul nu putut fi deschis pentru scriere!\n";
    }
}

// Actualizează complet fișierul CSV cu lista de produse
void Product::updateProductCSV(const std::vector<std::unique_ptr<Product>> &products, const std::string &filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        // Scrie antetul fișierului
        file << "Name,Price,Stock\n";

        // Scrie fiecare produs
        for (const auto &product : products)
        {
            file << product->getName() << "," << product->getPrice() << "," << product->getStock() << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Fisierul nu putut fi deschis pentru actualizare!\n";
    }
}