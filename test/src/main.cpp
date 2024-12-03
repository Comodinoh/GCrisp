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
    std::string vertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 0) in vec4 a_Color;

      out vec3 v_Position;
      out vec4 v_Color;

      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = vec4(a_Position, 1.0);
      }
    )";
    std::string fragmentSrc = R"(
      
    )";

    auto& app = Application::Get();

    m_Shader.reset(Application::Get().GetGraphicsCreator()->CreateShader(&vertexSrc, &fragmentSrc));

    float vertices[] = 
    {
        -0.5, 0.5, 0.0, 
        0.0, -0.5, 0.0,
        0.5, 0.5, 0.0
    };

    m_VertexBuffer.reset(app.GetGraphicsCreator()->CreateVertexBuffer(vertices, 9));


    Graphics::BufferLayout layout = 
    {
        {"a_Position", ShaderDataType::Float3},
        {"a_Color", ShaderDataType::Float4}
    };

    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    int32_t indices[3] =
    {
        0, 1, 2
    };

    // Idk why but ccls marks it as error if not casting
    m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer((uint32_t*)indices, sizeof(indices) / sizeof(uint32_t)));
  }
  
  ~TestLayer()
  {

  }

  void OnUpdate() override
  { 
  }

  void OnEvent(GCrisp::Event& e) override
  {
    GC_TRACE("{0}", e);
  }

private:
  std::shared_ptr<Graphics::Shader> m_Shader;
  std::shared_ptr<Graphics::VertexBuffer> m_VertexBuffer;
  std::shared_ptr<Graphics::IndexBuffer> m_IndexBuffer;
  std::shared_ptr<Graphics::VertexArray> m_VertexArray;
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

