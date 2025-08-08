#include "log.hpp"

#include <ctime>
#include <iostream>

std::string Log::getTimeStamp()
{
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
    return buf;
}

void Log::log(Log::LogLevel level, const std::string message)
{
    std::string prefix;

    switch (level)
    {
    case Log::LogLevel::INFO:
        prefix = "\033[32m[INFO]\033[0m";
        break;
    case Log::LogLevel::WARNING:
        prefix = "\033[33m[WARNING]\033[0m";
        break;
    case Log::LogLevel::ERROR:
        prefix = "\033[31m[ERROR]\033[0m";
        break;
    }

    std::cout << prefix << " | " << Log::getTimeStamp() << " | " << message << "\n";
}

void Log::logWithValue(Log::LogLevel level, const std::string message, std::string value)
{
    std::string prefix;

    switch (level)
    {
    case Log::LogLevel::INFO:
        prefix = "\033[32m[INFO]\033[0m";
        break;
    case Log::LogLevel::WARNING:
        prefix = "\033[33m[WARNING]\033[0m";
        break;
    case Log::LogLevel::ERROR:
        prefix = "\033[31m[ERROR]\033[0m";
        break;
    }

    std::cout << prefix << " | " << Log::getTimeStamp() << " | " << message << " | " << value << "\n";
}
