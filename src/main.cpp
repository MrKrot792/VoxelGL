#include "chunk.hpp"
#include "glad/glad.h"
#include "include/fps_count.hpp"
#include "shader.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>

// Crazy glm stuff
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

// std
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

void processInput(GLFWwindow *window);
void printMatrix(glm::mat4 matrix);

int width = 800;
int height = 600;

float lastX = 400, lastY = 300;

glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 6.f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = 0, pitch = 0;
bool firstMouse = true;

double deltaTime = 0;

unsigned int FPS = 0;

int main(void)
{
    Window::Init();

    // GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[ERROR] | Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    std::vector<Chunk> chunks;

    chunks.push_back(Chunk(glm::vec3(0, 0, 0)));
    chunks.push_back(Chunk(glm::vec3(16, 0, 0)));

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, 3, (void *)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    FPSCounter fps;

    while (!Window::windowShouldClose())
    {
        fps.Start();
        processInput(Window::window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // 3D stuff
        // Matrices creation
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        glm::mat4 projection;
        glm::vec2 dimensions = Window::getDimensions();
        projection = glm::perspective(glm::radians(90.0f), dimensions.x / dimensions.y, 0.1f, 1000.f);

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + glm::normalize(direction), cameraUp);

        // Sending them to GPU
        shader.setMatrix4(std::string("projection"), projection);
        shader.setMatrix4(std::string("view"), view);

        for (auto i : chunks)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            shader.setVec3(std::string("color"), glm::vec3(.5, .4, .2));
            i.draw();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader.setVec3(std::string("color"), glm::vec3(0, 0, 0));
            i.draw();
        }

        Window::swapBuffers();
        Window::pollEvents();
        fps.End();
        deltaTime = fps.GetDelta();

        if (fps.GetFPS() != FPS)
            std::cout << "[INFO] | FPS: " << fps.GetFPS() << std::endl;

        FPS = fps.GetFPS();
    }

    Window::terminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (Window::getKey(GLFW_KEY_H) == GLFW_PRESS)
    {
        GLenum errorCode = glGetError();

        std::string error;

        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_NO_ERROR:
            error = "NO_ERROR";
            break;
        }

        std::cout << "[INFO] | Error: " << error << std::endl;
    }

    float cameraSpeed = 5.f * deltaTime; // adjust accordingly
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    glm::vec3 cameraRealUp = glm::normalize(glm::cross(cameraFront, cameraRight));

    if (Window::getKey(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        cameraSpeed = 15.f * deltaTime;
    }

    if (Window::getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * -cameraRealUp;
    }

    if (Window::getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraRealUp;
    }

    if (Window::getKey(GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;

    if (Window::getKey(GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;

    if (Window::getKey(GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraRight * cameraSpeed;

    if (Window::getKey(GLFW_KEY_D) == GLFW_PRESS)
        cameraPos -= -cameraRight * cameraSpeed;
}

void Window::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}
