#pragma once

#include <GCrisp/Renderer/Creator.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/LayerStack.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Core/Timer.h>

namespace GCrisp {

class Application
{
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

  static inline Application& Get() {return *s_Instance;}
  inline Window& GetWindow() const {return *m_Window;} 
  inline Timer& GetFrameTimer() {return m_FrameTimer;}
  inline Graphics::Creator* GetGraphicsCreator() const {return m_Window->GetCreator();}
private:
  bool OnWindowClose(WindowCloseEvent& e);
  bool OnWindowResize(WindowResizeEvent& e);
private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  LayerStack m_LayerStack;
  Timer m_FrameTimer;  
  static Application* s_Instance;
};

Application* CreateApplication();


};

