#include <gcpch.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/Core/Application.h>
#include <GLFW/glfw3.h>

namespace GCrisp{

namespace Input{

bool IsKeyPressed(const KeyCode keycode)
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool IsMouseButtonPressed(const int button)
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<float, float> GetMousePosition()
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  double x, y;

  glfwGetCursorPos(window, &x, &y);

  return {(float)x, (float)y};
}

}

} 
