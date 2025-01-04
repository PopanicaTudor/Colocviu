#ifndef COFFEE_TASTING_H
#define COFFEE_TASTING_H

#include "Event.h"
#include <vector>

class CoffeeTasting : public Event
{
private:
    std::vector<std::string> coffeeTypes;

public:
    CoffeeTasting(const std::string& name, const std::string& date, double cost, const std::vector<std::string>& coffeeTypes);
    ~CoffeeTasting();

    void displayDetails() const override;
    void performEventAction() const override;
    void saveEventToCSV(const std::string& filePath) const;
};

#endif