#ifndef STOREEVENTS_H
#define STOREEVENTS_H

#include "../event/Event.h"

#include <vector>
#include <memory>
#include <string>

std::vector<std::unique_ptr<Event>> storeEvents(std::string eventsFilePath);

#endif