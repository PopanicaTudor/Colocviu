#include "StoreProducts.h"
#include "../util/CSVParser.h"
#include "../inventory/Product.h"

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

// Funcție pentru a stoca produsele din fișierul CSV
std::vector<std::unique_ptr<Product>> storeProducts(std::string productsFilePath)
{
    // Citirea produselor din fișierul CSV
    CSVParser parser(productsFilePath);
    std::vector<std::map<std::string, std::string>> productData = parser.readCSV(productsFilePath);

    // Popularea vectorului de produse
    std::vector<std::unique_ptr<Product>> products;
    for (const auto &row : productData)
    {
        products.push_back(std::make_unique<Product>(
            row.at("Name"),
            std::stod(row.at("Price")),
            std::stoi(row.at("Stock"))));
    }

    return products;
}