#include "chunk.hpp"
#include "chunk_manager.hpp"
#include "fps_count.hpp"
#include "glad/glad.h"
#include "shader.hpp"
#include "window.hpp"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

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

void processInput(GLFWwindow *window);
void printMatrix(glm::mat4 matrix);
void keyEsc();

int width = 800;
int height = 600;

float lastX = 400, lastY = 300;

glm::vec3 cameraPos = glm::vec3(0, 2, 0);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = 0, pitch = 0;
bool firstMouse = true;

double deltaTime = 0;

unsigned int FPS = 0;

bool isOn = false;

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

    ChunkManager &chunkManager = ChunkManager::getInstance();

    int size = 8;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                int x = i - size / 2;
                int y = j - size / 2;
                int z = k - size / 2;

                chunkManager.addChunk(Chunk(glm::vec3(x * 16, y * 16, z * 16)));
            }
        }
    }

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window::window, true);
    ImGui_ImplOpenGL3_Init();

    while (!Window::windowShouldClose())
    {
        fps.Start();
        processInput(Window::window);
        Window::pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // IMGUI WINDOW BEGINS HERE
        ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Once);

        ImGui::Begin("Debug information\n");

        ImGui::SeparatorText("Position:");
        ImGui::Text("X: (%f)", cameraPos.x);
        ImGui::Text("Y: (%f)", cameraPos.y);
        ImGui::Text("Z: (%f)", cameraPos.z);

        ImGui::SeparatorText("Pointing to:");
        ImGui::Text("X: (%f)", cameraFront.x);
        ImGui::Text("Y: (%f)", cameraFront.y);
        ImGui::Text("Z: (%f)", cameraFront.z);

        ImGui::SeparatorText("Rotation:");
        ImGui::Text("Pitch: (%f)", pitch);
        ImGui::Text("Yaw: (%f)", yaw);

        ImGui::SeparatorText("FPS stuff:");
        ImGui::Text("Delta: (%f)", fps.GetDelta());
        ImGui::Text("FPS: (%d)", FPS);
        ImGui::Text("Medium FPS: (%f)", fps.GetMediumFPS());

        ImGui::End();
        // AND ENDS HERE

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // 3D stuff
        // Matrices creation
        // glm::vec3 direction;
        // direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        // direction.y = sin(glm::radians(pitch));
        // direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        glm::mat4 projection;
        glm::vec2 dimensions = Window::getDimensions();
        projection = glm::perspective(glm::radians(90.0f), dimensions.x / dimensions.y, 0.1f, 1000.f);

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + glm::normalize(cameraFront), cameraUp);

        // Sending them to GPU
        shader.setMatrix4(std::string("projection"), projection);
        shader.setMatrix4(std::string("view"), view);

        for (auto i : chunkManager.chunks)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            shader.setVec3(std::string("color"), glm::vec3(.5, .4, .2));
            i.draw();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader.setVec3(std::string("color"), glm::vec3(0, 0, 0));
            i.draw();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Window::swapBuffers();
        fps.End();
        deltaTime = fps.GetDelta();

        if (fps.GetFPS() != FPS)
            std::cout << "[INFO] | FPS: " << fps.GetFPS() << std::endl;

        FPS = fps.GetFPS();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Window::terminate();
    return 0;
}

enum STATE
{
    JUST_PRESSED,
    JUST_RELEASED,
    NONE,
};

int key = 0;
int state = 0;

void processInput(GLFWwindow *window)
{
    // TODO: Abstract into a class
    int newKey = Window::getKey(GLFW_KEY_ESCAPE);
    if (key == newKey)
    {
        state = STATE::NONE;
    }
    else if (key != newKey)
    {
        if (key == 0 && newKey == 1)
        {
            state = STATE::JUST_PRESSED;
        }

        else if (key == 1 && newKey == 0)
        {
            state = STATE::JUST_RELEASED;
        }
    }

    key = newKey;

    if(state == STATE::JUST_PRESSED)
        keyEsc();

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
    if (!isOn)
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

        if (pitch > 89.99f)
            pitch = 89.99f;
        if (pitch < -89.99f)
            pitch = -89.99f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFront = glm::normalize(direction);
    }
}

void keyEsc()
{

    if (isOn)
    {
        isOn = false;
        Window::setMouseInputMode(GLFW_CURSOR_DISABLED);
    }
    else
    {
        isOn = true;
        Window::setMouseInputMode(GLFW_CURSOR_NORMAL);
    }
}
