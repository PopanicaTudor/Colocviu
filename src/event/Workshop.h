#ifndef WORKSHOP_H
#define WORKSHOP_H

#include "Event.h"

class Workshop : public Event
{
private:
    std::string topic;
    int participantLimit;

public:
    Workshop(const std::string& name, const std::string& date, double cost, const std::string& topic, int participantLimit);
    ~Workshop();

    void displayDetails() const override;
    void performEventAction() const override;
    void saveEventToCSV(const std::string& filePath) const;
};

#endif