#pragma once

#include <GLFW/glfw3.h>

// std
#include <cstdint>

class FPSCounter
{
  private:
    double start;
    double end;

    GLFWwindow* window;

  public:
    FPSCounter(GLFWwindow *window);

    void Start();
    void End();

    uint32_t GetFPS();    // Every 1 second
    float GetMediumFPS(); // Every frame
};
