#ifndef EVENTCHOICES_H
#define EVENTCHOICES_H

#include "../event/event.h"
#include "../event/movieNight.h"
#include "../event/workshop.h"
#include "../event/coffeeTasting.h"

void eventChoice1(std::vector<std::string> &coffeeTypes);
void eventChoice2(std::string &topic, int &participantLimit);
void eventChoice3(std::string &movieTitle, std::string &startTime);

#endif