#include "window.hpp"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

// std
#include <cstdio>
#include <iostream>
#include <sys/types.h>

int Window::Init()
{
    Window::vsync = 0;
    Window::antialiasingLevel = 4;

    Window::width = 800;
    Window::height = 600;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfwWindowHint(GLFW_SAMPLES, Window::antialiasingLevel);

    glfwSetErrorCallback(Window::glfw_error_callback);

    Window::window = glfwCreateWindow(Window::width, Window::height, "Learn OpenGL", NULL, NULL);
    if (Window::window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window!");
        std::cerr << "Failed to create window!" << std::endl;
    }

    glfwMakeContextCurrent(Window::window);

    glfwSwapInterval(Window::vsync);

    glfwSetFramebufferSizeCallback(Window::window, Window::framebuffer_size_callback);
    glfwSetCursorPosCallback(Window::window, Window::mouse_callback);

    Window::setMouseInputMode(GLFW_CURSOR_DISABLED);

    return 0;
}

int Window::windowShouldClose()
{
    int result = glfwWindowShouldClose(Window::window);
    return result;
}

void Window::windowHint(int hint, int value)
{
    glfwWindowHint(hint, value);
}

void Window::framebuffer_size_callback(GLFWwindow *window, int _width, int _height)
{
    std::cout << "[INFO] | " << "Changed \'" << glfwGetWindowTitle(window) << "\' window's size."
              << " New size is: " << _width << " X, " << _height << " Y" << std::endl;
    glViewport(0, 0, _width, _height);

    Window::width = _width;
    Window::height = _height;
}

glm::vec2 Window::getDimensions()
{
    glm::vec2 result = glm::vec2(Window::width, Window::height);
    return result;
}

void Window::swapBuffers()
{
    glfwSwapBuffers(Window::window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::terminate()
{
    glfwTerminate();
}

int Window::getKey(int key)
{
    return glfwGetKey(Window::window, key);
}

void Window::glfw_error_callback(int error, const char *description)
{
    std::cerr << "[ERROR] | GLFW error happened: " << description << "\nError code: " << error << "\n";
}

void Window::setMouseInputMode(int value)
{
    glfwSetInputMode(Window::window, GLFW_CURSOR,
                     value); // TODO: Remove this line, and move it to the class
}
