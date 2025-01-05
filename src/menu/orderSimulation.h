#ifndef ORDERSIMULATION_H
#define ORDERSIMULATION_H

#include "../inventory/product.h"

#include <string>
#include <vector>
#include <memory>

void orderSimulation(std::string selectedCity, std::string productsFilePath, std::vector<std::unique_ptr<Product>> &products);

#endif