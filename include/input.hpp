#pragma once

#include "GLFW/glfw3.h"

// std
#include <unordered_map>

typedef void(*keyActionBindingFun)(int action, int mods);

namespace Input
{
static std::unordered_map<int, keyActionBindingFun> keysActionsBindings;

void whenKeyPressedDo(int key, keyActionBindingFun fun);
void input(GLFWwindow *window, int key, int scancode, int action, int mods);
}; // namespace Input
