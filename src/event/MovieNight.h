#ifndef MOVIE_NIGHT_H
#define MOVIE_NIGHT_H

#include "Event.h"

class MovieNight : public Event
{
private:
    std::string movieTitle;
    std::string startTime;

public:
    MovieNight(const std::string& name, const std::string& date, double cost, const std::string& movieTitle, const std::string& startTime, const std::string& city);
    ~MovieNight();

    void displayDetails() const override;
    void performEventAction() const override;
    void saveEventToCSV(const std::string& filePath) const override;
};

#endif