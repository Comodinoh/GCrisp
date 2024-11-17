#pragma once

#include <GCrisp/Events/Event.h>
#include <GCrisp/Core.h>

struct GLFWwindow;

namespace gcrisp{

using EventCallbackFunc = std::function<void(Event&)>;

enum RendererType
{
  OpenGL,
  DirectX,
  Vulkan
};

struct WindowData
{
  std::string Title;
  uint Width, Height;
  bool VSync;

  EventCallbackFunc EventCallback;
};

struct WindowProps
{
  std::string Title;
  uint Width, Height;

  WindowProps(const std::string& title = ENGINE_NAME, 
              uint width = 1280, 
              uint height = 720) : Title(title), Width(width), Height(height) {}
};

class Window
{
public:
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  inline uint GetWidth() const {return m_Data.Width;};
  inline uint GetHeight() const {return m_Data.Height;};

  inline virtual void* GetWindowPointer() = 0;

  void SetEventCallback(const EventCallbackFunc& callback) {m_Data.EventCallback = callback;};
  virtual void SetVSync(bool enabled) = 0;
  virtual bool HasVSync() const = 0;

  static Window* Create(const RendererType rendererType, const WindowProps& props = WindowProps());

protected:
  WindowData m_Data;
};

}
