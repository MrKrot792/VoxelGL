#pragma once

// std
#include <cstdint>

class FPSCounter
{
  private:
    double start = 0;
    double end = 0;

    uint32_t frame_count = 0;
    uint32_t old_frame_count = 0;

    double seconds_count = 0;

  public:
    void Start();
    void End();

    uint32_t GetFPS();    // Every 1 second
    float GetMediumFPS(); // Every frame
    float GetDelta();     // Get frame difference
};
