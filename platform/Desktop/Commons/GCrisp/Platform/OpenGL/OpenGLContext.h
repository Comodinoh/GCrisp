#pragma once

#include <GCrisp/Renderer/Context.h>
#include <GLFW/glfw3.h>


struct GLFWwindow;

namespace gcrisp {

namespace Graphics{


class OpenGLContext : public Context
{
public:
  OpenGLContext(GLFWwindow* window_handle) : m_WindowHandle(window_handle) {GC_ASSERT(window_handle);};

  virtual void Init() override;
  virtual void SwapBuffers() override;
private:
  GLFWwindow* m_WindowHandle;

};

}

}

