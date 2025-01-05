#ifndef STOREEMPLOYEES_H
#define STOREEMPLOYEES_H

#include "../employee/Employee.h"

#include <memory>
#include <vector>
#include <string>

std::vector<std::unique_ptr<Employee>> storeEmployees(std::string employeesFilePath);

#endif