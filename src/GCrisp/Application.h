#pragma once

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

private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

Application* CreateApplication();


};

