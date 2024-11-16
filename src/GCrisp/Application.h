#pragma once

#include "GCrisp/Events/ApplicationEvent.h"
#include "GCrisp/GWindow.h"
#include <GCrisp/Core.h>
#include <GCrisp/Events/Event.h>
#include <memory>

namespace gcrisp {

class Application
{
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

private:
  bool OnWindowClose(WindowCloseEvent& e);

  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

Application* CreateApplication();


};

