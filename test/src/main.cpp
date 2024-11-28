#include <GCrisp/Core/Input.h>
#include <GCrisp/GCrisp.h>

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test"){}
  
  ~TestLayer()
  {
  }

  void OnUpdate() override
  { 
    if (GCrisp::Input::IsKeyPressed(GCrisp::Input::W)) {
      GC_INFO("W!");
    }
  }

  void OnEvent(GCrisp::Event& e) override
  {
    GC_TRACE("{0}", e);
  }
};

class TestApplication : public GCrisp::Application
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

GCrisp::Application* GCrisp::CreateApplication()
{
  return new TestApplication();
}

