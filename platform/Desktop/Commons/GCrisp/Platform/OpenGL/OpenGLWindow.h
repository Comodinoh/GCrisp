#pragma once

#include "GCrisp/Platform/OpenGL/OpenGLContext.h"
#include "GCrisp/Renderer/Renderer.h"
#include <GCrisp/Core/Core.h>
#include <GCrisp/Core/GWindow.h>

struct GLFWwindow;

namespace GCrisp{

class OpenGLWindow : public Window
{
public:
  OpenGLWindow(const Graphics::Backend& backend, const WindowProps& props);
  virtual ~OpenGLWindow();

  virtual void OnUpdate() override;

  inline virtual void*              GetWindowPointer() override {return m_Window;};
  inline virtual Graphics::Context* GetContext() override {return m_Context;};

  virtual void SetVSync(bool enabled) override;
  virtual bool HasVSync() const override;
protected:
  GLFWwindow* m_Window;
  Graphics::OpenGLContext* m_Context;

  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
};

}
