#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>

using namespace GCrisp;

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test")
  {
    auto& app = Application::Get();
    m_VertexArray.reset(app.GetGraphicsCreator()->CreateVertexArray());

    float vertices[] = 
    {
     -1.0,  1.0, 0.0,   1.0, 0.0, 0.0, 1.0,
     -1.0, -1.0, 0.0,   0.0, 1.0, 0.0, 1.0,
      1.0,  1.0, 0.0,   0.0, 0.0, 1.0, 1.0,
      1.0, -1.0, 0.0,   1.0, 1.0, 1.0, 1.0
    };

    m_VertexBuffer.reset(app.GetGraphicsCreator()->CreateVertexBuffer(vertices, sizeof(vertices)));

    Graphics::BufferLayout layout = 
    {
        {"a_Position", Graphics::ShaderDataType::Float3},
        {"a_Color", Graphics::ShaderDataType::Float4}
    };

    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    uint32_t indices[] =
    {
        0, 1, 2,
        2, 1, 3
    };
    m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer(indices, sizeof(indices)));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
      #version 330 core

      in vec3 a_Position;
      in vec4 a_Color;

      out vec4 color;
      out vec3 position;

      void main()
      {
        position = (a_Position+1.0)*0.5;
        color = a_Color;
        gl_Position = vec4(a_Position, 1.0);
      }
    )";
    std::string fragmentSrc = R"(
      #version 330 core

      in vec4 color;
      in vec3 position;

      out vec4 fragColor;

      void main()
      {
        fragColor = color;
      }
    )";


    m_Shader.reset(app.GetGraphicsCreator()->CreateShader(&vertexSrc, &fragmentSrc));
  }
  
  ~TestLayer()
  {

  }

  void OnUpdate() override
  { 
    Graphics::Renderer::Clear({1, 0, 0, 1});

    m_Shader->Bind();
    Graphics::Renderer::Draw(m_VertexArray);
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

