#ifndef EVENTCHOICES_H
#define EVENTCHOICES_H

#include "../event/Event.h"
#include "../event/MovieNight.h"
#include "../event/Workshop.h"
#include "../event/CoffeeTasting.h"

void eventChoice1(std::vector<std::string> &coffeeTypes);
void eventChoice2(std::string &topic, int &participantLimit);
void eventChoice3(std::string &movieTitle, std::string &startTime);

#endif