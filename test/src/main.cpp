#include "GCrisp/Input.h"
#include <GCrisp/Gcrisp.h>

class TestLayer : public gcrisp::Layer
{
public:
  TestLayer() : gcrisp::Layer("Test"){}
  
  ~TestLayer()
  {
  }

  void OnUpdate() override
  { 
    if (gcrisp::Input::IsKeyPressed(gcrisp::Input::W)) {
      GC_INFO("W!");
    }
  }

  void OnEvent(gcrisp::Event& e) override
  {
    GC_TRACE("{0}", e);
  }
};

class TestApplication : public gcrisp::Application
{
public:
  TestApplication()
  {
    PushLayer(new TestLayer());
  }

  ~TestApplication()
  {

  }
};

gcrisp::Application* gcrisp::CreateApplication()
{
  return new TestApplication();
}

