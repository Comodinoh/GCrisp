#pragma once

#include <GCrisp/Renderer/Creator.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/Core.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Renderer/Context.h>

namespace GCrisp{

using EventCallbackFunc = std::function<void(Event&)>;

struct WindowData
{
  std::string Title;
  uint32_t Width, Height;
  bool VSync;
  bool Resizable;

  EventCallbackFunc EventCallback;
};

struct WindowProps
{
  std::string Title;
  uint32_t Width, Height;
  bool Resizable;

  WindowProps(const std::string& title = ENGINE_NAME,
              uint32_t width = 1280,
              uint32_t height = 720, bool resizable = true) : Title(title), Width(width), Height(height), Resizable(resizable) {}
};

class Window
{
public:
  Window(const Graphics::Backend& backend) : m_Backend(backend) {}
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  inline Graphics::Creator*         GetCreator() const {return m_GraphicsCreator;}
  inline Graphics::Backend          GetBackend() {return m_Backend;}
  inline uint32_t                   GetWidth() const {return m_Data.Width;}
  inline uint32_t                   GetHeight() const {return m_Data.Height;}

  virtual void SetResizable(bool enabled) = 0;
  inline bool IsResizable() const {return m_Data.Resizable;}
  

  inline virtual void* GetWindowPointer() = 0;
  inline virtual Graphics::Context* GetContext() = 0;

  virtual void SetVSync(bool enabled) = 0;
  inline bool HasVSync() const {return m_Data.VSync;}

  void SetEventCallback(const EventCallbackFunc& callback) {m_Data.EventCallback = callback;};

  static Window* Create(const Graphics::Backend& backend, const WindowProps& props = WindowProps());

protected:
  WindowData         m_Data;
  Graphics::Backend  m_Backend;
  Graphics::Creator* m_GraphicsCreator;
};

}
