#include "GLContext.h"
#include <gcpch.h>

#include <Vane/Core/Base.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Vane {
namespace Graphics {
void GLContext::Init() const {
    VANE_PROFILE_FUNC();
    glfwMakeContextCurrent(m_Spec.WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    VANE_CORE_ASSERT(status, "Could not load glad from GLFW!");
}

void GLContext::SwapBuffers() const { glfwSwapBuffers(m_Spec.WindowHandle); }
} // namespace Graphics
} // namespace Vane
