#pragma once

#include "GCrisp/Events/ApplicationEvent.h"
#include "GCrisp/GWindow.h"
#include <GCrisp/Core.h>
#include <GCrisp/LayerStack.h>
#include <GCrisp/Events/Event.h>

namespace gcrisp {

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
  inline Window& getWindow() {return *m_Window;} 
private:
  bool OnWindowClose(WindowCloseEvent& e);

  static Application* s_Instance;
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  LayerStack m_LayerStack;
};

Application* CreateApplication();


};

