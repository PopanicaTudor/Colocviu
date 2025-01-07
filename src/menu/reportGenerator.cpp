#include "ReportGenerator.h"
#include "../report/Report.h"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

void reportGenerator(std::string selectedCity, std::string employeesFilePath, std::string productsFilePath, std::string eventsFilePath, std::string reportsFilePath)
{
    std::cout << "\n\tGenerare raport pentru " << selectedCity << ":\n";

    std::string reportDate;
    struct tm reportTm = {};
    bool isValidDate = false;

    do
    {
        std::cout << "Data raport (ZZ/LL/AAAA): ";
        std::cin >> reportDate;

        std::stringstream ss(reportDate);
        if (ss >> std::get_time(&reportTm, "%d/%m/%Y"))
        {
            isValidDate = true;
        }
        else
        {
            std::cerr << "Format invalid. Introduceti o data valida!\n";
        }
    } while (!isValidDate);

    // Creare obiect raport
    Report report(reportDate, selectedCity, employeesFilePath, productsFilePath, eventsFilePath);

    // Afisare raport
    report.displayReport();

    // Salvare raport in fisier
    report.saveReportToCSV(reportsFilePath);
}