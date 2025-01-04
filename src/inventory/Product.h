#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Product
{
private:
    std::string name;
    double price;
    int stock;

public:
    // Constructor implicit
    Product();

    // Constructor de copiere
    Product(const Product &other);

    // Constructor cu parametri
    Product(const std::string &name, double price, int stock);

    // Setters
    void setName(const std::string &name);
    void setPrice(double price);
    void setStock(int stock);

    // Getters
    std::string getName() const;
    double getPrice() const;
    int getStock() const;

    // Metodă pentru a afișa informații despre produs
    void displayProduct() const;

    static std::vector<Product> loadProductsFromCSV(const std::string &filePath);
    static void addProductToCSV(const Product &product, const std::string &filePath);
    static void updateProductCSV(const std::vector<std::unique_ptr<Product>> &products, const std::string &filePath);
};

#endif