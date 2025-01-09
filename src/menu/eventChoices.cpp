#include "EventChoices.h"
#include "Menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

void eventChoice1(std::string eventsFilePath, std::vector<std::unique_ptr<Event>> &events)
{
    std::cout << "\n\tOrganizare eveniment:\n";

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

    int eventChoice = eventOrganizerMenu();

    // Selectați tipul de eveniment
    if (eventChoice == 1)
    {
        eventOrganizerChoice1(coffeeTypes);
    }
    else if (eventChoice == 2)
    {
        eventOrganizerChoice2(topic, participantLimit);
    }
    else if (eventChoice == 3)
    {
        eventOrganizerChoice3(movieTitle, startTime);
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
        event = std::make_unique<CoffeeTasting>(eventName, eventDate, eventCost, coffeeTypes);
    }
    else if (eventChoice == 2)
    {
        event = std::make_unique<Workshop>(eventName, eventDate, eventCost, topic, participantLimit);
    }
    else if (eventChoice == 3)
    {
        event = std::make_unique<MovieNight>(eventName, eventDate, eventCost, movieTitle, startTime);
    }

    // Afișare detaliile evenimentului
    event->displayDetails();

    // Adăugare eveniment în vector
    events.push_back(std::move(event));

    // Salvare eveniment în fișierul CSV
    Event::updateEventCSV(events, eventsFilePath);
}

void eventChoice2(std::string eventsFilePath, std::vector<std::unique_ptr<Event>> &events)
{
    std::cout << "\n\tStergere eveniment:\n";

    std::string eventName;
    std::string eventDate;

    std::cout << "Nume eveniment: ";
    std::cin.ignore();
    std::getline(std::cin, eventName);

    std::cout << "Data eveniment (ZZ/LL/AAAA): ";
    std::cin >> eventDate;

    auto it = std::find_if(events.begin(), events.end(),
                           [&eventName, &eventDate](const std::unique_ptr<Event> &event)
                           {
                               return event->getName() == eventName &&
                                      event->getDate() == eventDate;
                           });
    
    if (it != events.end())
    {
        events.erase(it);
        std::cout << "Eveniment sters cu succes!\n";
    }
    else
    {
        throw std::runtime_error("Evenimentul nu a fost gasit.");
    }

    // Actualizează fișierul CSV
    Event::updateEventCSV(events, eventsFilePath);
}

void eventChoice3(std::string selectedCity, std::vector<std::unique_ptr<Event>> &events)
{
    std::cout << "\n\tEvenimente organizate in " << selectedCity << ":\n";

    if (events.empty())
    {
        std::cout << "Nu exista evenimente organizate in " << selectedCity << ".\n";
    }
    else
    {
        for (const auto &event : events)
        {
            event->displayDetails();
        }
    }
}