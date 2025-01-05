#include "eventChoices.h"

#include <iostream>
#include <vector>
#include <string>

void eventChoice1(std::vector<std::string> &coffeeTypes)
{
    int noOfTypes;

    std::cout << "Numar tipuri de cafea: ";
    std::cin >> noOfTypes;

    for (int i = 0; i < noOfTypes; i++)
    {
        std::string type;

        std::cout << "Tip cafea " << i + 1 << ": ";
        std::cin >> type;
        coffeeTypes.push_back(type);
    }
}

void eventChoice2(std::string &topic, int &participantLimit)
{
    std::cout << "Subiect: ";
    std::cin.ignore(); // Clear the newline character left in the buffer
    std::getline(std::cin, topic);
    std::cout << "Numar maxim participanti: ";
    std::cin >> participantLimit;
}

void eventChoice3(std::string &movieTitle, std::string &startTime)
{
    std::cout << "Titlu film: ";
    std::cin.ignore(); // Clear the newline character left in the buffer
    std::getline(std::cin, movieTitle);
    std::cout << "Ora incepere: ";
    std::cin >> startTime;
}