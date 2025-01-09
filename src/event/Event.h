#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Event
{
protected:
    std::string name;
    std::string date;
    double cost;
    std::string city;

public:
    Event(const std::string& name, const std::string& date, double cost, const std::string &city);
    virtual ~Event();

    std::string getName() const;
    std::string getDate() const;
    double getCost() const;
    std::string getCity() const;

    void setName(const std::string& name);
    void setDate(const std::string& date);
    void setCost(double cost);
    void setCity(const std::string &city);

    virtual void displayDetails() const = 0;
    virtual void performEventAction() const = 0;
    virtual void saveEventToCSV(const std::string &filePath) const = 0;

    static void updateEventCSV(const std::vector<std::unique_ptr<Event>> &events, const std::string &filePath);
};

#endif