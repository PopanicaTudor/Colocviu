#ifndef EVENTCHOICES_H
#define EVENTCHOICES_H

#include "../event/Event.h"
#include "../event/MovieNight.h"
#include "../event/Workshop.h"
#include "../event/CoffeeTasting.h"
#include "EventOrganizerChoices.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

void eventChoice1(std::string eventsFilePath, std::vector<std::unique_ptr<Event>> &events);
void eventChoice2(std::string eventsFilePath, std::vector<std::unique_ptr<Event>> &events);
void eventChoice3(std::string selectedCity, std::vector<std::unique_ptr<Event>> &events);

#endif