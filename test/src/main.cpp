#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>

using namespace GCrisp;
using namespace GCrisp::Graphics;

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test")
  {
  }
  
  ~TestLayer()
  {

  }

  void OnUpdate() override
  { 
  }

  void OnEvent(GCrisp::Event& e) override
  {
  }

private:
};

class TestApplication : public GCrisp::Application
{
public:
  ~TestApplication()
  {
  }
};

GCrisp::Application* GCrisp::CreateApplication()
{
  return new TestApplication();
}

