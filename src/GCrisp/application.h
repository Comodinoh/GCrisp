#pragma once

#include <GCrisp/core.h>

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

