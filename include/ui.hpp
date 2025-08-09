#pragma once
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

#include <sys/types.h>

namespace UI
{
void initialize(GLFWwindow *win);
void draw(glm::vec3 cameraPos, glm::vec3 cameraFront, uint FPS, float pitch, float yaw);
void render();
void destroy();
}; // namespace UI
