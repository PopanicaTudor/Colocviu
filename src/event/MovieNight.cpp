#include "MovieNight.h"
#include <iostream>
#include <fstream>

// Constructor
MovieNight::MovieNight(const std::string& name, const std::string& date, double cost, const std::string& movieTitle, const std::string& startTime, const std::string& city)
    : Event(name, date, cost, city), movieTitle(movieTitle), startTime(startTime)
{
    saveEventToCSV(city); // Save event to CSV
}

// Destructor
MovieNight::~MovieNight() {}

// Display details
void MovieNight::displayDetails() const
{
    Event::displayDetails();
    std::cout << "Titlu film: " << movieTitle << "\nOra incepere: " << startTime << "\n";
}

// Perform action
void MovieNight::performEventAction() const
{
    std::cout << "Bucurati-va de filmul \"" << movieTitle << "\"!\n";
}

// Save event to CSV
void MovieNight::saveEventToCSV(const std::string &city) const
{
    std::string filePath = "../data/events/" + city + ".csv";

    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << name << "," << date << "," << cost << "," << "Movie Night" << ",\"Movie Name: " << movieTitle << ",Hour: " << startTime << "\"\n";
        file.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fisierului " << filePath << "\n";
    }
}