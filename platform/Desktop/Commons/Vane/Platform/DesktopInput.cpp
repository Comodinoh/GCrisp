#include <gcpch.h>

#include <Vane/Core/Application.h>
#include <Vane/Core/Input.h>
#include <GLFW/glfw3.h>

namespace Vane {
namespace Input {
bool IsKeyPressed(const KeyCode keycode) {
    VANE_PROFILE_FUNC();
    GLFWwindow* window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetWindowPointer());

    return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool IsMouseButtonPressed(const int button) {
    VANE_PROFILE_FUNC();
    GLFWwindow* window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetWindowPointer());

    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<float, float> GetMousePosition() {
    VANE_PROFILE_FUNC();
    GLFWwindow* window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetWindowPointer());

    double x, y;

    glfwGetCursorPos(window, &x, &y);

    return {(float)x, (float)y};
}
} // namespace Input
} // namespace Vane
