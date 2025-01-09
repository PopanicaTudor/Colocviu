#include "MovieNight.h"

#include <iostream>
#include <fstream>

// Constructor
MovieNight::MovieNight(const std::string& name, const std::string& date, double cost, const std::string& movieTitle, const std::string& startTime)
    : Event(name, date, cost, city), movieTitle(movieTitle), startTime(startTime) { std::cout << "Movie creat: " << name << std::endl; }

// Destructor
MovieNight::~MovieNight() {}

// Afișarea detaliilor evenimentului
void MovieNight::displayDetails() const
{
    Event::displayDetails();
    std::cout << ", Titlu film: " << movieTitle << ", Ora incepere: " << startTime << "\n";
}

// Acțiunea specifică evenimentului
void MovieNight::performEventAction() const
{
    std::cout << "Bucurati-va de filmul \"" << movieTitle << "\"!\n";
}

// Salvarea evenimentului într-un fișier CSV
void MovieNight::saveEventToCSV(const std::string &filePath) const
{
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