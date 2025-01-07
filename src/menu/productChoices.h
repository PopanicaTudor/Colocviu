#ifndef PRODUCTCHOICES_H
#define PRODUCTCHOICES_H

#include "../inventory/Product.h"

#include <string>
#include <vector>
#include <memory>

void productChoice1(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products);
void productChoice2(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products);
void productChoice3(std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products);
void productChoice4(std::string selectedCity, std::vector<std::unique_ptr<Product>> &products);

#endif