#ifndef MENU_H
#define MENU_H

#include "../inventory/Product.h"

#include <string>
#include <vector>
#include <memory>

int mainMenu(std::string city);
int employeesMenu(std::string city);
int productsMenu(std::string city);
int eventMenu(std::string city);

#endif