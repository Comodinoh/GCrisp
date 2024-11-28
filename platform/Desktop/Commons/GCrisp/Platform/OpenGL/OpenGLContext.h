#pragma once

#include <GCrisp/Core/Core.h>
#include <GCrisp/Renderer/Context.h>
#include <GLFW/glfw3.h>


struct GLFWwindow;

namespace GCrisp {

namespace Graphics{


class OpenGLContext : public Context
{
public:
  OpenGLContext(GLFWwindow* window_handle) : m_WindowHandle(window_handle) {GC_CORE_ASSERT(window_handle, "Provided invalid window handle! (nullptr)");};

  virtual void Init() override;
  virtual void SwapBuffers() override;
private:
  GLFWwindow* m_WindowHandle;

};

}

}

