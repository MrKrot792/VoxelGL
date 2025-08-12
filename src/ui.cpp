#include "ui.hpp"

#include "fps_count.hpp"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

#include "glm/vec3.hpp"
#include <tracy/Tracy.hpp>

void UI::init(GLFWwindow *win)
{
    ZoneScoped;
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init();
}

void UI::draw(glm::vec3 cameraPos, glm::vec3 cameraFront, float pitch, float yaw)
{
    ZoneScopedC(0x00ff00);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // IMGUI WINDOW BEGINS HERE
    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Once);
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
    ImGui::Text("Delta: (%f)", FPSCounter::GetDelta());
    ImGui::Text("FPS: (%d)", FPSCounter::GetFPS());
    ImGui::Text("Medium FPS: (%f) ", FPSCounter::GetMediumFPS());

    ImGui::End();
    // AND ENDS HERE
}

void UI::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
