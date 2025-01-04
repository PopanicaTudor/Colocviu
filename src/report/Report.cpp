#include "Report.h"
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Report::Report(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath)
    : date(date), city(city), ordersFilePath(ordersFilePath), eventsFilePath(eventsFilePath) {}
// Calcularea costurilor
double Report::calculateOrderCosts(const std::string& date, const std::string& city, const std::string& ordersFilePath)
{
    double totalOrderCost = 0;

    std::string directoryPath = "../data/orders/" + city;

    // Verifică dacă directorul există
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        std::cerr << "Eroare: Directorul " << directoryPath << " nu exista sau nu este valid.\n";
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

            // Citim costul total din fișier
            std::string line, orderCost, orderDate;
            while (std::getline(file, line))
            {
                if (line.find("Total Cost") != std::string::npos)
                {
                    orderCost = line.substr(line.find(',') + 1);
                }
                else if (line.find("Date") != std::string::npos)
                {
                    orderDate = line.substr(line.find(',') + 1);
                    if (orderDate != date)
                    {
                        break;
                    }
                }
            }

            if (orderDate == date)
            {
                totalOrderCost += std::stod(orderCost);
            }

            file.close();
        }
    }

    return totalOrderCost;
}

double Report::calculateEventCosts(const std::string& date, const std::string& city, const std::string& eventsFilePath)
{
    double totalEventCost = 0;

    std::ifstream file(eventsFilePath);

    if (!file.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << eventsFilePath << "\n";
        return totalEventCost;
    }

    // Citim datele din fișier
    std::string line, eventDate, eventCost;
    while (std::getline(file, line))
    {
        if (line.find(date) != std::string::npos)
        {
            std::istringstream ss(line);
            std::string name, cost;
            std::getline(ss, eventDate, ',');
            std::getline(ss, eventDate, ',');
            std::getline(ss, eventCost, ',');

            if (eventDate == date)
            {
                totalEventCost += std::stod(eventCost);
            }
        }
    }

    file.close();

    return totalEventCost;
}

// Calcularea costurilor
double Report::calculateTotalCosts(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath)
{
    double totalOrderCost = calculateOrderCosts(date, city, ordersFilePath);
    double totalEventCost = calculateEventCosts(date, city, eventsFilePath);

    return totalOrderCost * (1 - profitMargin) + totalEventCost;
}

// Calcularea veniturilor
double Report::calculateTotalIncome(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath)
{
    double totalOrderCost = calculateOrderCosts(date, city, ordersFilePath);
    double totalEventCost = calculateEventCosts(date, city, eventsFilePath);

    return totalOrderCost + totalEventCost;
}

// Calcularea profitului
double Report::calculateProfit(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath)
{
    double totalCost = calculateTotalCosts(date, city, ordersFilePath, eventsFilePath);
    double totalIncome = calculateTotalIncome(date, city, ordersFilePath, eventsFilePath);

    return totalIncome - totalCost;
}

// Afisarea raportului
void Report::displayReport()
{
    double totalOrderCost = calculateOrderCosts(date, city, ordersFilePath);
    double totalEventCost = calculateEventCosts(date, city, eventsFilePath);
    double totalCost = calculateTotalCosts(date, city, ordersFilePath, eventsFilePath);
    double totalIncome = calculateTotalIncome(date, city, ordersFilePath, eventsFilePath);
    double profit = calculateProfit(date, city, ordersFilePath, eventsFilePath);

    std::cout << "\nRaport pentru data " << date << " in orasul " << city << ":\n";
    std::cout << "Costuri comenzi: " << totalOrderCost << "\n";
    std::cout << "Costuri evenimente: " << totalEventCost << "\n";
    std::cout << "Costuri totale: " << totalCost << "\n";
    std::cout << "Venituri totale: " << totalIncome << "\n";
    std::cout << "Profit: " << profit << "\n";
}

// Salvarea raportului in fisier
void Report::saveReportToCSV(const std::string& reportFilePath)
{
    double totalOrderCost = calculateOrderCosts(date, city, ordersFilePath);
    double totalEventCost = calculateEventCosts(date, city, eventsFilePath);
    double totalCost = calculateTotalCosts(date, city, ordersFilePath, eventsFilePath);
    double totalIncome = calculateTotalIncome(date, city, ordersFilePath, eventsFilePath);
    double profit = calculateProfit(date, city, ordersFilePath, eventsFilePath);

    std::ofstream file(reportFilePath);

    if (!file.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << reportFilePath << "\n";
        return;
    }

    file << "Date,OrderCost,EventCost,TotalCost,TotalIncome,Profit\n";
    file << date << "," << totalOrderCost << "," << totalEventCost << "," << totalCost << "," << totalIncome << "," << profit << "\n";

    file.close();
}