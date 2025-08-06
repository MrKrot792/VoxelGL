#include "fps_count.hpp"
#include <GLFW/glfw3.h>

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
    if(seconds_count >= 1.0)
    {
        this->seconds_count = 0;
        this->old_frame_count = this->frame_count;
        this->frame_count = 0;

        return old_frame_count;
    }

    seconds_count += GetDelta();
    frame_count++;

    return old_frame_count;
}

double FPSCounter::GetMediumFPS()
{
    double difference = this->GetDelta();
    return 1.0 / difference;
}

double FPSCounter::GetDelta()
{
    double difference = this->end - this->start;
    return difference;
}
