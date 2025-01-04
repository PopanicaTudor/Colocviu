#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>
#include <map>

class CSVParser
{
public:
    // Constructor pentru inițializarea cu un nume de fișier
    CSVParser(const std::string &filename);

    // Metodă pentru citirea datelor din fișierul CSV
    std::vector<std::map<std::string, std::string>> readCSV();

private:
    std::string filename; // Numele fișierului CSV
};

#endif