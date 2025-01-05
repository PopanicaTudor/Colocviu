#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Employee
{
protected:
    std::string firstName;
    std::string lastName;
    std::string role;
    std::string startHour;
    std::string endHour;

public:
    Employee(const std::string &firstName, const std::string &lastName, const std::string &role, const std::string &startHour, const std::string &endHour);
    virtual ~Employee();

    virtual void displayInfo() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getRole() const;
    std::string getStartHour() const;
    std::string getEndHour() const;

    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setRole(const std::string &role);
    void setStartHour(const std::string &startHour);
    void setEndHour(const std::string &endHour);

    static void addEmployeeToCSV(const Employee &employee, const std::string &filePath);
    static void updateEmployeeCSV(const std::vector<std::unique_ptr<Employee>> &employees, const std::string &filePath);
    static std::vector<std::unique_ptr<Employee>> readEmployeesFromCSV(const std::string &filePath);

    static int extractHour(const std::string &time);
    static int calculateWorkedHours(const std::string &startHour, const std::string &endHour);
    virtual double calculateDailySalary() const = 0;
};

#endif