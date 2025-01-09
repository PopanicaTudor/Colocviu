#ifndef EVENTORGANIZERCHOICES_H
#define EVENTORGANIZERCHOICES_H

#include "../event/Event.h"
#include "../event/MovieNight.h"
#include "../event/Workshop.h"
#include "../event/CoffeeTasting.h"

void eventOrganizerChoice1(std::vector<std::string> &coffeeTypes);
void eventOrganizerChoice2(std::string &topic, int &participantLimit);
void eventOrganizerChoice3(std::string &movieTitle, std::string &startTime);

#endif