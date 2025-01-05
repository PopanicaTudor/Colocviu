#include "reportGenerator.h"
#include "../report/Report.h"

#include <iostream>
#include <string>

void reportGenerator(std::string selectedCity, std::string employeesFilePath, std::string productsFilePath, std::string eventsFilePath, std::string reportsFilePath)
{
    std::cout << "\n\tGenerare raport pentru " << selectedCity << ":\n";

    std::string reportDate;
    std::cout << "Data raportului (ZZ/LL/AAAA): ";
    std::cin >> reportDate;

    // Creare obiect raport
    Report report(reportDate, selectedCity, employeesFilePath, productsFilePath, eventsFilePath);

    // Afisare raport
    report.displayReport();

    // Salvare raport in fisier
    report.saveReportToCSV(reportsFilePath);
}