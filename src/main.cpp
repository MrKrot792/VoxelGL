#include "include/glad/glad.h"
#include "shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

// std
#include <iostream>
#include <ostream>
#include <string>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void printMatrix(glm::mat4 matrix);

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfwSwapInterval(0); // Turn off vsync

    // Antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // GLFW window
    int width = 800;
    int height = 600;
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // float vertices[] = {
    //     0.5f,  0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //    -0.5f, -0.5f, 0.0f,
    //    -0.5f,  0.5f, 0.0f
    // };

    float vertices[] = {
        // x, y, z
        -0.5f, -0.5f, -0.5f, // 0: левый нижний задний
        0.5f,  -0.5f, -0.5f, // 1: правый нижний задний
        0.5f,  0.5f,  -0.5f, // 2: правый верхний задний
        -0.5f, 0.5f,  -0.5f, // 3: левый верхний задний
        -0.5f, -0.5f, 0.5f,  // 4: левый нижний передний
        0.5f,  -0.5f, 0.5f,  // 5: правый нижний передний
        0.5f,  0.5f,  0.5f,  // 6: правый верхний передний
        -0.5f, 0.5f,  0.5f   // 7: левый верхний передний
    };

    unsigned int indices[] = {// Задняя грань
                              0, 1, 2, 2, 3, 0,

                              // Передняя грань
                              4, 5, 6, 6, 7, 4,

                              // Левая грань
                              0, 3, 7, 7, 4, 0,

                              // Правая грань
                              1, 5, 6, 6, 2, 1,

                              // Нижняя грань
                              0, 1, 5, 5, 4, 0,

                              // Верхняя грань
                              3, 2, 6, 6, 7, 3};

    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    int samples;
    glGetIntegerv(GL_SAMPLES, &samples);
    std::cout << "Samples: " << samples << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        shader.use();

        // 3D stuff
        // Matrices creation
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(15.f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.5f, 1.0f, 1.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // Sending them to GPU
        shader.setMatrix4(std::string("projection"), projection);
        shader.setMatrix4(std::string("model"), model);
        shader.setMatrix4(std::string("view"), view);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    std::cout << "Changed \'" << glfwGetWindowTitle(window) << "\' window's size." << " New size is: " << width
              << " X, " << height << " Y" << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
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

        std::cout << error << std::endl;
    }
}

void printMatrix(glm::mat4 matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix[j][i] << " ";
        }

        std::cout << std::endl;
    }
}
