#include "Logger.h"

#include <iostream>
#include <ctime>

// Inițializarea membrilor statici
Logger *Logger::instance = nullptr;
std::mutex Logger::mutex;

Logger::Logger()
{
    logFile.open("../data/Logs.txt", std::ios::app);
    if (!logFile.is_open())
    {
        // Creăm fișierul log.txt dacă nu există
        std::ofstream createFile("../data/Logs.txt");
        createFile.close();
        logFile.open("../data/Logs.txt", std::ios::app);
        if (!logFile.is_open())
        {
            throw std::runtime_error("Failed to open log file");
        }
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger *Logger::getInstance()
{
    // Blocăm accesul concurent la instanța Logger
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Logger();
    }
    return instance;
}

void Logger::log(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex);

    // Adăugăm timestamp-ul la mesaj
    auto now = std::time(nullptr);
    auto timeStamp = std::localtime(&now);
    char buffer[20];
    std::strftime(buffer, 20, "%d-%m-%Y %H:%M:%S", timeStamp);

    logFile << "[" << buffer << "] " << message << std::endl;
}