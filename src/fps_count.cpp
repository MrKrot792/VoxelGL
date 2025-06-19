#include "fps_count.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

FPSCounter::FPSCounter(GLFWwindow *window)
{
    this->window = window;
}

void FPSCounter::Start()
{
    this->start = glfwGetTime();   
}

void FPSCounter::End()
{
    this->end = glfwGetTime();   
}

uint32_t FPSCounter::GetFPS()
{
    return 0;
}

float FPSCounter::GetMediumFPS()
{
    double difference = this->end - this->start;

    return 1.0 / difference;
}
