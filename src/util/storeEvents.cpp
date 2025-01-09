#include "StoreEvents.h"
#include "../util/CSVParser.h"
#include "../event/CoffeeTasting.h"
#include "../event/Workshop.h"
#include "../event/MovieNight.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

// Funcție pentru a stoca evenimentele din fișierul CSV
std::vector<std::unique_ptr<Event>> storeEvents(std::string eventsFilePath)
{
    // Citirea evenimentelor din fișierul CSV
    CSVParser parser(eventsFilePath);
    std::vector<std::map<std::string, std::string>> eventData = parser.readCSV(eventsFilePath);

    // Popularea vectorului de evenimente
    std::vector<std::unique_ptr<Event>> events;
    for (const auto &row : eventData)
    {
        std::string name = row.at("Name");
        std::string date = row.at("Date");
        double cost = std::stod(row.at("Cost"));
        std::string type = row.at("Type");

        if (type == "Coffee Tasting")
        {
            std::vector<std::string> coffeeTypes;
            std::string additionalInfo = row.at("AdditionalInfo");
            std::istringstream iss(additionalInfo);
            std::string coffeeTypesStr;

            std::getline(iss, coffeeTypesStr, ' ');
            std::getline(iss, coffeeTypesStr, ' ');
            std::string coffeeType;
            while (std::getline(iss, coffeeType, ' '))
            {
                if (!coffeeType.empty() && coffeeType.back() == ',')
                {
                    coffeeType.pop_back();
                }
                coffeeTypes.push_back(coffeeType);
            }

            events.push_back(std::make_unique<CoffeeTasting>(name, date, cost, coffeeTypes));
        }
        else if (type == "Workshop")
        {
            std::string additionalInfo = row.at("AdditionalInfo");
            std::istringstream iss(additionalInfo);
            std::string topic;
            int participantLimit;

            std::getline(iss, topic, ' ');
            std::getline(iss, topic, ' ');
            std::getline(iss, topic, ',');

            std::string participantsLimitStr;
            std::getline(iss, participantsLimitStr, ' ');
            std::getline(iss, participantsLimitStr, ' ');
            std::getline(iss, participantsLimitStr);
            participantLimit = std::stoi(participantsLimitStr);

            events.push_back(std::make_unique<Workshop>(name, date, cost, topic, participantLimit));
        }
        else if (type == "Movie Night")
        {
            std::string additionalInfo = row.at("AdditionalInfo");
            std::istringstream iss(additionalInfo);
            std::string movieTitle;
            std::string startTime;

            std::getline(iss, movieTitle, ' ');
            std::getline(iss, movieTitle, ' ');
            std::getline(iss, movieTitle, ',');

            std::getline(iss, startTime, ' ');
            std::getline(iss, startTime);

            events.push_back(std::make_unique<MovieNight>(name, date, cost, movieTitle, startTime));
        }
    }

    return events;
}