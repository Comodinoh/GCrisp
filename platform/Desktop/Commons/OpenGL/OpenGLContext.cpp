#include "OpenGLContext.h"
#include <GCrisp/Core/Core.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gcrisp{

void OpenGLContext::Init()
{
  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  GC_ASSERT(status);
}

void OpenGLContext::SwapBuffers()
{
  glfwSwapBuffers(m_WindowHandle);
}

}
