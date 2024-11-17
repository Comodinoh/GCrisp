#pragma once

#include <GCrisp/Core.h>
#include <GCrisp/GWindow.h>

struct GLFWwindow;

namespace gcrisp{

class OpenGLWindow : public Window
{
public:
  OpenGLWindow(const WindowProps& props); 
  virtual ~OpenGLWindow();

  void OnUpdate() override;

  void SetVSync(bool enabled) override;
  bool HasVSync() const override;
protected:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
};

}
