#include "fps_count.hpp"
#include <GLFW/glfw3.h>

double FPSCounter::start = 0.0;
double FPSCounter::end = 0.0;
double FPSCounter::seconds_count = 0.0;
uint32_t FPSCounter::frame_count = 0;
uint32_t FPSCounter::old_frame_count = 0;

void FPSCounter::Start()
{
    start = glfwGetTime();   
}

void FPSCounter::End()
{
    end = glfwGetTime();   
}

uint32_t FPSCounter::GetFPS()
{
    if(seconds_count >= 1.0)
    {
        seconds_count = 0;
        old_frame_count = frame_count;
        frame_count = 0;

        return old_frame_count;
    }

    seconds_count += FPSCounter::GetDelta();
    frame_count++;

    return old_frame_count;
}

double FPSCounter::GetMediumFPS()
{
    double difference = FPSCounter::GetDelta();
    return 1.0 / difference;
}

double FPSCounter::GetDelta()
{
    double difference = end - start;
    return difference;
}
