#include "eventOrganizer.h"
#include "eventChoices.h"
#include "../event/event.h"
#include "../event/movieNight.h"
#include "../event/workshop.h"
#include "../event/coffeeTasting.h"

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

    // Verificare dată eveniment
    time_t now = time(0);
    tm *ltm = localtime(&now);

    time_t eventTime;
    do
    {
        // Citire dată eveniment
        std::cout << "Data eveniment (ZZ/LL/AAAA): ";
        std::cin >> eventDate;

        struct tm eventTm = {};
        std::istringstream ss(eventDate);
        if (!(ss >> std::get_time(&eventTm, "%d/%m/%Y")))
        {
            std::cout << "Format invalid. Introduceti o data valida!\n";
            continue;
        }
    } while (difftime(eventTime, now) < 0);

    // Citire cost eveniment
    std::cout << "Cost eveniment: ";
    std::cin >> eventCost;

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

    // Creare currentDate dupa formatul DD/MM/YYYY
    std::string currentDate = std::to_string(ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(1900 + ltm->tm_year);

    // Efectuează acțiunea evenimentului dacă este este acceași zi
    if (eventDate == currentDate)
    {
        event->performEventAction();
    }
}