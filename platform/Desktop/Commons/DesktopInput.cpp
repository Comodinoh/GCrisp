#include "GLFW/glfw3.h"
#include <GCrisp/Application.h>
#include <GCrisp/Input.h>

namespace gcrisp{

bool Input::IsKeyPressed(const int keycode)
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(const int button)
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
  GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPointer());

  double x, y;

  glfwGetCursorPos(window, &x, &y);

  return {(float)x, (float)y};
}

} 
