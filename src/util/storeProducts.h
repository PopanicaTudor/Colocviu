#ifndef STOREPRODUCTS_H
#define STOREPRODUCTS_H

#include "../inventory/Product.h"

#include <memory>
#include <vector>
#include <string>

std::vector<std::unique_ptr<Product>> storeProducts(std::string productsFilePath);

#endif