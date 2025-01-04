#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "../inventory/Product.h"

class Order
{
private:
    static constexpr double profitMargin = 0.2;
    std::string customerFirstName;
    std::string customerLastName;
    std::vector<Product> products;
    double totalCost;
    std::string date;
    std::string city;

    // Updates the product stock in the CSV file
    void updateProductStock(const std::string &filePath);

    // Calculates the total cost of the order
    void calculateTotalCost();

    // Helper function for date conversion
    time_t stringToDate(const std::string &date) const;

public:
    // Constructor
    Order(const std::string &customerFirstName, const std::string &customerLastName, const std::vector<Product> &products, const std::string &filePath, const std::string &date, const std::string &city);

    // Constructor for loading orders from CSV
    Order(const std::string &customerFirstName, const std::string &customerLastName, const std::vector<Product> &products, const std::string &date);

    // Getters
    std::string getCustomerFirstName() const;
    std::string getCustomerLastName() const;
    std::vector<Product> getProducts() const;
    double getTotalCost() const;
    double calculateProfit() const;
    std::string getDate() const;
    std::string getCity() const;

    // Print order details
    void printOrderDetails() const;

    // Save order to CSV
    void saveOrderToCSV(const std::string &city) const;

    // Load orders from CSV
    static std::vector<Order> loadOrdersFromCSV(const std::string &filePath);

    // Check if the client is loyal
    bool isLoyalCustomer(const std::vector<Order> &orderHistory) const;

    // Apply discount to the order
    void applyDiscount(double discountRate);
};

#endif