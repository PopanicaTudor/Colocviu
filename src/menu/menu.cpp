#include "menu.h"
#include "../inventory/product.h"
#include "../order/order.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

int mainMenu(std::string city)
{
    std::cout << "\n\tMeniu principal pentru " << city << ":\n";
    std::cout << "1. Gestionare angajati\n";
    std::cout << "2. Gestionare produse\n";
    std::cout << "3. Simulare comanda\n";
    std::cout << "4. Organizare eveniment\n";
    std::cout << "5. Generare raport\n";
    std::cout << "6. Inapoi la selectare oras\n";
    std::cout << "Optiune: ";

    int mainChoice;
    std::cin >> mainChoice;

    return mainChoice;
}

int employeesMenu(std::string city)
{
    std::cout << "\n\tMeniu gestionare angajati pentru " << city << ":\n";
    std::cout << "1. Adaugare angajat nou\n";
    std::cout << "2. Stergere angajat existent\n";
    std::cout << "3. Modificare angajat existent\n";
    std::cout << "4. Afisare angajati\n";
    std::cout << "5. Inapoi la meniul principal\n";
    std::cout << "Optiune: ";

    int empChoice;
    std::cin >> empChoice;

    return empChoice;
}

int productsMenu(std::string city)
{
    std::cout << "\n\tMeniu gestionare produse pentru " << city << ":\n";
    std::cout << "1. Adaugare produs nou\n";
    std::cout << "2. Stergere produs existent\n";
    std::cout << "3. Modificare produs existent\n";
    std::cout << "4. Afisare produse\n";
    std::cout << "5. Inapoi la meniul principal\n";
    std::cout << "Optiune: ";

    int prodChoice;
    std::cin >> prodChoice;

    return prodChoice;
}

int eventMenu(std::string city)
{
    std::cout << "\n\tSelectati tipul de eveniment:\n";
    std::cout << "1. Degustare de cafea\n";
    std::cout << "2. Atelier\n";
    std::cout << "3. Seara de film\n";
    std::cout << "4. Anulare\n";
    std::cout << "Optiune: ";

    int eventChoice;
    std::cin >> eventChoice;

    return eventChoice;
}