#pragma once

#include <chrono>
#include <cstdint>
#include <random>

class RandomGenerator
{
  public:
    static int64_t RandomNumber(int64_t min, int64_t max)
    {
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    };
};
