#pragma once

#include "GLFW/glfw3.h"
#include <GCrisp/Renderer/GraphicsContext.h>


struct GLFWwindow;

namespace gcrisp {


class OpenGLContext : public GraphicsContext
{
public:
  OpenGLContext(GLFWwindow* window_handle) : m_WindowHandle(window_handle) {GC_ASSERT(window_handle);};

  virtual void Init() override;
  virtual void SwapBuffers() override;
private:
  GLFWwindow* m_WindowHandle;

};

}

