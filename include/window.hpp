#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <sys/types.h>

class Window
{
  private:
    static uint vsync; // Turned off
    static uint antialiasingLevel;

    static uint width;
    static uint height;

  public:
    static GLFWwindow *window;
    static int Init();

    static int windowShouldClose();
    static void windowHint(int hint, int value);

    static void framebuffer_size_callback(GLFWwindow *window, int _width, int _height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    static glm::vec2 getDimensions();

    static void swapBuffers();
    static void pollEvents();
    static void terminate();

    static int getKey(int key);

    Window() = delete;
};
