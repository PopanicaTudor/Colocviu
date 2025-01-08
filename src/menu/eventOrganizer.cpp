#include "EventOrganizer.h"
#include "EventChoices.h"
#include "../event/Event.h"
#include "../event/MovieNight.h"
#include "../event/Workshop.h"
#include "../event/CoffeeTasting.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>

void eventOrganizer(std::string selectedCity)
{
    std::cout << "\n\tOrganizare eveniment pentru " << selectedCity << ":\n";

    std::unique_ptr<Event> event;

    std::string eventName;
    std::string eventDate;
    double eventCost;
    struct tm eventTm = {};
    bool isValidDate = false;

    std::vector<std::string> coffeeTypes;
    std::string topic;
    int participantLimit = 0;
    std::string movieTitle;
    std::string startTime;

    int eventChoice = eventMenu(selectedCity);

    // Selectați tipul de eveniment
    if (eventChoice == 1)
    {
        eventChoice1(coffeeTypes);
    }
    else if (eventChoice == 2)
    {
        eventChoice2(topic, participantLimit);
    }
    else if (eventChoice == 3)
    {
        eventChoice3(movieTitle, startTime);
    }
    else
    {
        return;
    }

    // Citire nume eveniment
    std::cout << "Nume eveniment: ";
    std::cin.ignore(); // Clear the newline character left in the buffer
    std::getline(std::cin, eventName);
    if (eventName.empty())
    {
        throw std::invalid_argument("Numele evenimentului nu poate fi gol!");
    }

    // Citire data eveniment
    do
    {
        std::cout << "Data eveniment (ZZ/LL/AAAA): ";
        std::cin >> eventDate;

        std::stringstream ss(eventDate);
        if (ss >> std::get_time(&eventTm, "%d/%m/%Y"))
        {
            isValidDate = true;
        }
        else
        {
            std::cout << "Format invalid. Introduceti o data valida!\n";
        }
    } while (!isValidDate);

    // Citire cost eveniment
    std::cout << "Cost eveniment: ";
    std::cin >> eventCost;
    if (eventCost < 0)
    {
        throw std::invalid_argument("Costul evenimentului nu poate fi negativ!");
    }

    // Creare obiect eveniment
    if (eventChoice == 1)
    {
        event = std::make_unique<CoffeeTasting>(eventName, eventDate, eventCost, coffeeTypes, selectedCity);
        event->displayDetails();
    }
    else if (eventChoice == 2)
    {
        event = std::make_unique<Workshop>(eventName, eventDate, eventCost, topic, participantLimit, selectedCity);
        event->displayDetails();
    }
    else if (eventChoice == 3)
    {
        event = std::make_unique<MovieNight>(eventName, eventDate, eventCost, movieTitle, startTime, selectedCity);
        event->displayDetails();
    }
}