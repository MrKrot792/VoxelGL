#pragma once

#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <sys/types.h>

namespace Window
{

inline unsigned int vsync = 0; // Turned off
inline unsigned int antialiasingLevel = 4;

inline unsigned int width = 800;
inline unsigned int height = 600;

inline GLFWwindow *window;

int Init();

int windowShouldClose();
void windowHint(int hint, int value);

void framebuffer_size_callback(GLFWwindow *window, int _width, int _height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void glfw_error_callback(int error, const char *description);

void setMouseInputMode(int value);

glm::vec2 getDimensions();

void swapBuffers();
void pollEvents();
void terminate();

int getKey(int key);

}; // namespace Window
