#pragma once

#include "GLFW/glfw3.h"
#include <GCrisp/Core.h>
#include <GCrisp/GWindow.h>

struct GLFWwindow;

namespace gcrisp{

class LinuxWindow : public Window
{
public:
  LinuxWindow(const WindowProps& props);
  virtual ~LinuxWindow();

  void OnUpdate() override;

  inline unsigned int GetWidth() const override {return m_Data.Width;}
  inline unsigned int GetHeight() const override {return m_Data.Height;}

  inline void SetEventCallback(const EventCallbackFunc& callback) override {m_Data.EventCallback = callback;}
  void SetVSync(bool enabled) override;
  bool HasVSync() const override;
private:
  GLFWwindow* m_Window;

  struct WindowData
  {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallbackFunc EventCallback;
  };

  WindowData m_Data;

  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
};

}
