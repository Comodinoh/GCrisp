#pragma once

#include <GCrisp/Core.h>

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

