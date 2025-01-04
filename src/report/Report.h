#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <unordered_map>

class Report
{
private:
    std::string date;
    std::string city;
    std::string ordersFilePath;
    std::string eventsFilePath;
    const double profitMargin = 0.2; // 20% profit din venituri

public:
    // Constructor
    Report(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath);

    // Metoda pentru calcularea costurilor din comenzi pe baza unei date
    double calculateOrderCosts(const std::string& date, const std::string& city, const std::string& ordersFilePath);

    // Metoda pentru calcularea costurilor din evenimente pe baza unei date
    double calculateEventCosts(const std::string& date, const std::string& city, const std::string& eventsFilePath);

    // Metoda pentru calcularea costurilor totale pe baza unei date
    double calculateTotalCosts(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath);

    // Metoda pentru calcularea veniturilor totale pe baza unei date
    double calculateTotalIncome(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath);

    // Metoda pentru calcularea profitului pe baza unei date
    double calculateProfit(const std::string& date, const std::string& city, const std::string& ordersFilePath, const std::string& eventsFilePath);

    // Metoda pentru afisarea raportului
    void displayReport();

    // Metoda pentru afisarea raportului in fisier
    void saveReportToCSV(const std::string& reportFilePath);
};

#endif