#include "Order.h"
#include "../inventory/Product.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

namespace fs = std::filesystem;

// Constructor
Order::Order(const std::string &customerFirstName, const std::string &customerLastName, const std::vector<Product> &products,
             const std::string &filePath, const std::string &date, const std::string &city)
    : customerFirstName(customerFirstName), customerLastName(customerLastName), products(products), totalCost(0), date(date), city(city)
{
    calculateTotalCost();
    updateProductStock(filePath);

    // Verifică dacă clientul este fidel
    std::vector<Order> orderHistory = loadOrdersFromCSV(city);

    if (isLoyalCustomer(orderHistory))
    {
        std::cout << customerFirstName << " " << customerLastName << " este client fidel! Se aplica o reducere de 25%.\n";
        applyDiscount(0.25); // 25% discount
    }

    // Salvează comanda în fișier
    saveOrderToCSV(city);
}

// Constructor pentru încărcarea comenzilor din CSV
Order::Order(const std::string &customerFirstName, const std::string &customerLastName, const std::vector<Product> &products, const std::string &date)
    : customerFirstName(customerFirstName), customerLastName(customerLastName), products(products), totalCost(0), date(date)
{
    calculateTotalCost();
}

// Calcularea costului total al comenzii
void Order::calculateTotalCost()
{
    totalCost = 0;
    for (const auto &product : products)
    {
        totalCost += product.getPrice() * product.getStock();
    }
}

// Funcție pentru conversia datei în format string (ZZ/LL/AAAA)
time_t Order::stringToDate(const std::string& date) const
{
    struct tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date: " + date);
    }
    return mktime(&tm);
}

// Actualizează stocul produselor în fișierul CSV
void Order::updateProductStock(const std::string &filePath)
{
    std::vector<Product> allProducts = Product::loadProductsFromCSV(filePath);

    for (const auto &orderedProduct : products)
    {
        auto it = std::find_if(allProducts.begin(), allProducts.end(), [&](const Product &p) {
            return p.getName() == orderedProduct.getName();
        });

        if (it != allProducts.end())
        {
            if (it->getStock() >= orderedProduct.getStock())
            {
                it->setStock(it->getStock() - orderedProduct.getStock());
            }
            else
            {
                std::cerr << "Eroare: Stoc insuficient pentru produsul " << orderedProduct.getName() << "!\n";
            }
        }
        else
        {
            std::cerr << "Eroare: Produsul " << orderedProduct.getName() << " nu a fost gasit in inventar!\n";
        }
    }

    std::vector<std::unique_ptr<Product>> allProductsPtr;
    for (auto &product : allProducts)
    {
        allProductsPtr.push_back(std::make_unique<Product>(std::move(product)));
    }
    Product::updateProductCSV(allProductsPtr, filePath);
}

// Getter for client first name
std::string Order::getCustomerFirstName() const
{
    return customerFirstName;
}

// Getter for client last name
std::string Order::getCustomerLastName() const
{
    return customerLastName;
}

// Getter for products
std::vector<Product> Order::getProducts() const
{
    return products;
}

// Getter for total cost
double Order::getTotalCost() const
{
    return totalCost;
}

// Getter for date
std::string Order::getDate() const
{
    return date;
}

// Method to calculate profit
double Order::calculateProfit() const
{
    return totalCost * profitMargin;
}

// Afișarea detaliilor comenzii
void Order::printOrderDetails() const
{
    std::cout << "Prenume client: " << customerFirstName << std::endl;
    std::cout << "Nume client: " << customerLastName << std::endl;
    std::cout << "Produse: \n";
    for (const auto &product : products)
    {
        std::cout << "Produs: " << product.getName() << ", Pret: " << product.getPrice() << ", Cantitate: " << product.getStock() << std::endl;
    }
    std::cout << "Cost total: " << std::fixed << std::setprecision(2) << totalCost << " RON" << std::endl;
    std::cout << "Profit: " << std::fixed << std::setprecision(2) << calculateProfit() << " RON" << std::endl;
}

// Salvarea comenzii într-un fișier CSV
void Order::saveOrderToCSV(const std::string &city) const
{
    std::string directoryPath = "../data/orders/" + city;
    fs::create_directories(directoryPath);

    int orderNumber = std::distance(fs::directory_iterator(directoryPath), fs::directory_iterator());
    std::string filePath = directoryPath + "/Order" + std::to_string(orderNumber + 1) + ".csv";

    std::ofstream outFile(filePath);
    if (!outFile)
    {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return;
    }

    // Detaliile comenzii
    outFile << "Customer First Name," << customerFirstName << "\n";
    outFile << "Customer Last Name," << customerLastName << "\n";
    outFile << "Total Cost," << totalCost << "\n";
    outFile << "Profit," << calculateProfit() << "\n";
    outFile << "Date," << date << "\n";
    outFile << "Loyality Discount," << (isLoyalCustomer(loadOrdersFromCSV(city)) ? "Yes" : "No") << "\n";

    // Produsele comandate
    outFile << "Product,Price,Quantity\n";
    for (const auto &product : products)
    {
        outFile << product.getName() << "," << product.getPrice() << "," << product.getStock() << "\n";
    }

    outFile.close();
    std::cout << "Comanda a fost salvata in: " << filePath << std::endl;
}

// Funcție pentru a încărca comenzile din fișierul CSV
std::vector<Order> Order::loadOrdersFromCSV(const std::string &city)
{
    std::vector<Order> orders;
    std::string directoryPath = "../data/orders/" + city;

    // Verifică dacă directorul există
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        std::cerr << "Eroare: Directorul " << directoryPath << " nu exista sau nu este valid.\n";
        return orders;
    }

    // Parcurge toate fișierele din director
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".csv")
        {
            std::string filePath = entry.path().string();
            std::ifstream file(filePath);

            if (!file.is_open())
            {
                std::cerr << "Eroare la deschiderea fisierului: " << filePath << "\n";
                continue;
            }

            // Citim datele din fișier
            std::string line, customerFirstName, customerLastName, date;

            while (std::getline(file, line))
            {
                if (line == "Product,Price,Quantity")
                {
                    break;
                }

                if (line.find("Customer First Name") != std::string::npos)
                {
                    customerFirstName = line.substr(line.find(',') + 1);
                }
                else if (line.find("Customer Last Name") != std::string::npos)
                {
                    customerLastName = line.substr(line.find(',') + 1);
                }
                else if (line.find("Date") != std::string::npos)
                {
                    date = line.substr(line.find(',') + 1);
                }
            }

            // Creează un obiect Order și adaugă-l în vector
            orders.emplace_back(customerFirstName, customerLastName, std::vector<Product>{}, date);

            file.close();
        }
    }

    return orders;
}

// Verifică dacă clientul este fidel
bool Order::isLoyalCustomer(const std::vector<Order>& orderHistory) const
{
    time_t now = time(0);
    int orderCount = 0;

    for (const auto& order : orderHistory)
    {
        if (order.getCustomerFirstName() == customerFirstName && order.getCustomerLastName() == customerLastName)
        {
            double daysDifference = difftime(now, stringToDate(order.getDate())) / (60 * 60 * 24);

            if (daysDifference <= 30)
            {
                orderCount++;
                if (orderCount >= 5)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Aplică discountul comenzii
void Order::applyDiscount(double discountRate)
{
    totalCost *= (1 - discountRate);
}