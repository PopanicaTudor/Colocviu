#ifndef EMPLOYEECHOICES_H 
#define EMPLOYEECHOICES_H

#include "../employee/Employee.h"

#include <string>
#include <vector>
#include <memory>

void employeeChoice1(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees);
void employeeChoice2(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees);
void employeeChoice3(std::string employeesFilePath, std::vector<std::unique_ptr<Employee>> &employees);
void employeeChoice4(std::string selectedCity, std::vector<std::unique_ptr<Employee>> &employees);

#endif