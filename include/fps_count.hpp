#pragma once

// std
#include <cstdint>

class FPSCounter
{
  private:
    static double start;
    static double end;

    static double seconds_count;

    static uint32_t frame_count;
    static uint32_t old_frame_count;

  public:
    FPSCounter() = delete;
    FPSCounter(const FPSCounter &) = delete;
    FPSCounter &operator=(const FPSCounter &) = delete;

    static void Start();
    static void End();

    static uint32_t GetFPS();     // Every 1 second
    static double GetMediumFPS(); // Every frame
    static double GetDelta();     // Get frame difference
};
