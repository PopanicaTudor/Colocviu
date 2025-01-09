#include "CSVParser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

CSVParser::CSVParser(const std::string &filename)
    : filename(filename) {}

std::vector<std::map<std::string, std::string>> CSVParser::readCSV(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::vector<std::map<std::string, std::string>> rows;
    std::string line;
    std::vector<std::string> headers;

    // Read headers
    if (std::getline(file, line))
    {
        headers = parseLine(line);
    }

    // Read data
    while (std::getline(file, line))
    {
        std::vector<std::string> values = parseLine(line);
        if (values.size() == headers.size())
        {
            std::map<std::string, std::string> row;
            for (size_t i = 0; i < headers.size(); ++i)
            {
                row[headers[i]] = values[i];
            }
            rows.push_back(row);
        }
    }

    file.close();
    return rows;
}

std::vector<std::string> CSVParser::parseLine(const std::string &line)
{
    std::vector<std::string> result;
    std::istringstream stream(line);
    std::string cell;
    bool insideQuotes = false;
    std::string current;

    for (char ch : line)
    {
        if (ch == '"' && !insideQuotes)
        {
            insideQuotes = true;
        }
        else if (ch == '"' && insideQuotes)
        {
            insideQuotes = false;
        }
        else if (ch == ',' && !insideQuotes)
        {
            result.push_back(current);
            current.clear();
        }
        else
        {
            current += ch;
        }
    }

    if (!current.empty())
    {
        result.push_back(current);
    }

    return result;
}
