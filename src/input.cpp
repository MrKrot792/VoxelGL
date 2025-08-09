#include "input.hpp"
#include <unordered_map>
#include <utility>

namespace Input
{
void whenKeyPressedDo(int key, keyActionBindingFun fun)
{
    Input::keysActionsBindings.insert(std::make_pair(key, fun));
}
void input(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    for (auto i : Input::keysActionsBindings)
    {
        // If inputed key has an asigned function
        if (i.first == key)
        {
            // Then do it
            i.second(action, mods);
        }
    }
}
}; // namespace Input
