#pragma once

#include <string>

namespace Log
{
enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

std::string getTimeStamp();
void log(LogLevel level, const std::string message);
void logWithValue(LogLevel level, const std::string message, std::string value);
} // namespace Log
