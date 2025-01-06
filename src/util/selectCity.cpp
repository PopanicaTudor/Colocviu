#include "selectCity.h"

#include <iostream>
#include <string>

// Selectează orașul pentru gestionare
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