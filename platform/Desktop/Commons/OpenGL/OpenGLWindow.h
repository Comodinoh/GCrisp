#pragma once

#include "GCrisp/GWindow.h"
#include <GCrisp/Core.h>

struct GLFWwindow;

namespace gcrisp{

class OpenGLWindow : public Window
{
public:
  OpenGLWindow(const WindowProps& props); 
  virtual ~OpenGLWindow();

  virtual void OnUpdate() override;

  inline virtual void* GetWindowPointer() override {return m_Window;};
  inline virtual GraphicsContext* GetContext() override {return m_Context;};

  virtual void SetVSync(bool enabled) override;
  virtual bool HasVSync() const override;
protected:
  GLFWwindow* m_Window;
  GraphicsContext* m_Context;

  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
};

}
