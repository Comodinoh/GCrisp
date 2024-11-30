#include <gcpch.h>
#include "OpenGLContext.h"

#include <GCrisp/Core/Core.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GCrisp{

namespace Graphics{

void OpenGLContext::Init()
{
  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  GC_CORE_ASSERT(status, "Could not load glad from GLFW!");
}

void OpenGLContext::SwapBuffers()
{
  glfwSwapBuffers(m_WindowHandle);
}

}

}
