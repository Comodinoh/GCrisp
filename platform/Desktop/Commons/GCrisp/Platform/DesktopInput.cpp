#include <gcpch.h>

#include <GCrisp/Core/Input.h>
#include <GCrisp/Core/Application.h>
#include <GLFW/glfw3.h>

namespace GCrisp
{
namespace Input
{
bool IsKeyPressed(const KeyCode keycode)
{
	GC_PROFILE_FUNC();
	GLFWwindow* window = static_cast<GLFWwindow*>(
		Application::Get().GetWindow().GetWindowPointer());

	return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool IsMouseButtonPressed(const int button)
{
	GC_PROFILE_FUNC();
	GLFWwindow* window = static_cast<GLFWwindow*>(
		Application::Get().GetWindow().GetWindowPointer());

	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<float, float> GetMousePosition()
{
	GC_PROFILE_FUNC();
	GLFWwindow* window = static_cast<GLFWwindow*>(
		Application::Get().GetWindow().GetWindowPointer());

	double x, y;

	glfwGetCursorPos(window, &x, &y);

	return {(float)x, (float)y};
}
} // namespace Input
} // namespace GCrisp
