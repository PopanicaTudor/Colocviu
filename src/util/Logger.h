#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

/// Clasa Logger; Concept de Singleton (Design Pattern)
class Logger
{
private:
    static Logger *instance;
    static std::mutex mutex;
    std::ofstream logFile;

    // Constructor privat pentru a preveni crearea de obiecte
    Logger();

public:
    // Ștergem constructorul de copiere și operatorul de atribuire pentru a preveni clonarea obiectelor Logger
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    // Metoda pentru a obține instanța Logger
    static Logger *getInstance();

    // Metoda pentru a scrie un mesaj de tip Log in fișierul log.txt
    void log(const std::string &message);

    // Destructor
    ~Logger();
};

#endif