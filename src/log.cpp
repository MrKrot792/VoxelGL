#include "log.hpp"

#include <ctime>
#include <iostream>
#include <string>

inline std::string Log::getTimeStamp()
{
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
    return buf;
}

inline std::string Log::getPrefix(Log::LogLevel logLevel)
{
    std::string prefix;

    switch (logLevel)
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
    case Log::LogLevel::MESSAGE:
        prefix = "\033[34m[MESSAGE]\033[0m";
        break;
    }

    return prefix;
}

void Log::log(Log::LogLevel level, const std::string message)
{
    std::string prefix = Log::getPrefix(level);
    std::cout << prefix << " | " << Log::getTimeStamp() << " | " << message << "\n";
}

void Log::logWithValue(Log::LogLevel level, const std::string message, std::string value)
{
    std::string prefix = Log::getPrefix(level);
    std::cout << prefix << " | " << Log::getTimeStamp() << " | " << message << " | " << value << "\n";
}
void Log::message(const std::string message)
{
    std::string prefix = Log::getPrefix(Log::LogLevel::MESSAGE);
    std::cout << prefix << " | " << Log::getTimeStamp() << " | " << message << "\n";
}
