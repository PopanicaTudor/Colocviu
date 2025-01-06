#include "Workshop.h"

#include <iostream>
#include <fstream>

// Constructor
Workshop::Workshop(const std::string& name, const std::string& date, double cost, const std::string& topic, int participantLimit, const std::string& city)
    : Event(name, date, cost, city), topic(topic), participantLimit(participantLimit) 
{
    saveEventToCSV(city); // Save event to CSV
}

// Destructor
Workshop::~Workshop() {}

// Afișarea detaliilor evenimentului
void Workshop::displayDetails() const
{
    Event::displayDetails();
    std::cout << "Tema: " << topic << "\nLimita participanti: " << participantLimit << "\n";
}

// Acțiunea specifică evenimentului
void Workshop::performEventAction() const
{
    std::cout << "Alaturati-va atelierului cu tema: " << topic << "!\n";
}

// Salvarea evenimentului într-un fișier CSV
void Workshop::saveEventToCSV(const std::string &city) const
{
    std::string filePath = "../data/events/" + city + ".csv";

    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << name << "," << date << "," << cost << "," << "Workshop" << ",\"Workshop Topic: " << topic << ",Participants Limit: " << participantLimit << "\"\n";
        file.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fisierului " << filePath << "\n";
    }
}