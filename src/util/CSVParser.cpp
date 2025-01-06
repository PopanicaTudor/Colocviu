#include "CSVParser.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

CSVParser::CSVParser(const std::string &filename) : filename(filename) {}

// Metodă pentru citirea datelor din fișierul CSV
std::vector<std::map<std::string, std::string>> CSVParser::readCSV()
{
    std::vector<std::map<std::string, std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    std::vector<std::string> headers;

    // Citim antetul
    if (std::getline(file, line))
    {
        std::stringstream headerStream(line);
        std::string header;
        while (std::getline(headerStream, header, ','))
        {
            header.erase(std::remove_if(header.begin(), header.end(), ::isspace), header.end());
            headers.push_back(header);
        }
    }

    // Citim fiecare linie de date
    while (std::getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::map<std::string, std::string> row;

        for (size_t i = 0; i < headers.size(); ++i)
        {
            if (std::getline(lineStream, cell, ','))
            {
                cell.erase(std::remove_if(cell.begin(), cell.end(), ::isspace), cell.end());
                row[headers[i]] = cell;
            }
            else
            {
                row[headers[i]] = "";
            }
        }

        data.push_back(row);
    }

    file.close();
    return data;
}