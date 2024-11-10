#pragma once


namespace gcrisp {

class Application
{
public:
  Application();
  virtual ~Application();

  void Run();
};

Application* CreateApplication();


}

