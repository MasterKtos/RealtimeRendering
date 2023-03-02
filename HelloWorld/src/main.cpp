#include "App.h"
#include "glm/trigonometric.hpp"


// ugly workaround for callbacks
// -----------------------------
float lastX = 0, lastY = 0;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

App app;

int main()
{
    app.ScreenWidth = 1366;
    app.ScreenHeight = 768;
    app.Init();

    app.Run();
    app.Terminate();

    return 0;
}

// Callback implementations
// ------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if(app.mouseEnabled) return;

    float xpos = (float)xposIn;
    float ypos = (float)yposIn;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    // reversed since y-coordinates go from bottom to top
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

//    app.camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        if(app.mouseEnabled) {
            glfwSetCursorPos(window, app.ScreenWidth/2, app.ScreenHeight/2);
            lastX = app.ScreenWidth/2;
            lastY = app.ScreenHeight/2;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, app.ScreenWidth/2, app.ScreenHeight/2);
            lastX = app.ScreenWidth/2;
            lastY = app.ScreenHeight/2;
        }
        app.mouseEnabled = !app.mouseEnabled;
    }
}
