#pragma once

#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <sys/types.h>

namespace Window
{

inline uint vsync = 0; // Turned off
inline uint antialiasingLevel = 4;

inline uint width = 800;
inline uint height = 600;

inline GLFWwindow *window;

int Init();

int windowShouldClose();
void windowHint(int hint, int value);

void framebuffer_size_callback(GLFWwindow *window, int _width, int _height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

glm::vec2 getDimensions();

void swapBuffers();
void pollEvents();
void terminate();

int getKey(int key);

}; // namespace Window
