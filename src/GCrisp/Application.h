#pragma once

#include <GCrisp/Core.h>
#include <GCrisp/Events/Event.h>

namespace gcrisp {

class Application
{
public:
  Application();
  virtual ~Application();

  void Run();
};

Application* CreateApplication();


};

