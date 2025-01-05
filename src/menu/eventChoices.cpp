#include "eventChoices.h"

#include <iostream>
#include <vector>
#include <string>

void eventChoice1(std::vector<std::string> &coffeeTypes)
{
    int noOfTypes;

    std::cout << "Numar tipuri de cafea: ";
    if (!(std::cin >> noOfTypes))
    {
        throw std::runtime_error("Eroare la citirea numarului de tipuri de cafea.");
    }

    for (int i = 0; i < noOfTypes; i++)
    {
        std::string type;

        std::cout << "Tip cafea " << i + 1 << ": ";
        std::cin.ignore();
        if (!std::getline(std::cin, type))
        {
            throw std::runtime_error("Eroare la citirea tipului de cafea.");
        }
        coffeeTypes.push_back(type);
    }
}

void eventChoice2(std::string &topic, int &participantLimit)
{
    std::cout << "Subiect: ";
    std::cin.ignore();
    if (!std::getline(std::cin, topic))
    {
        throw std::runtime_error("Eroare la citirea subiectului.");
    }
    std::cout << "Numar maxim participanti: ";
    if (!(std::cin >> participantLimit))
    {
        throw std::runtime_error("Eroare la citirea numarului maxim de participanti.");
    }
}

void eventChoice3(std::string &movieTitle, std::string &startTime)
{
    std::cout << "Titlu film: ";
    std::cin.ignore();
    if (!std::getline(std::cin, movieTitle))
    {
        throw std::runtime_error("Eroare la citirea titlului filmului.");
    }
    std::cout << "Ora incepere: ";
    if (!(std::cin >> startTime))
    {
        throw std::runtime_error("Eroare la citirea orei de incepere.");
    }
}