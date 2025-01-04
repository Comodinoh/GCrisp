#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Core/CameraController.h>
#include <GLFW/glfw3.h>

using namespace GCrisp;

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test"), m_CameraController(16.0f/9.0f)
  {
    auto& app = Application::Get();
    m_VertexArray.reset(app.GetGraphicsCreator()->CreateVertexArray());

    float vertices[] = 
    {
      0.0,  0.5, 0.0,   1.0, 0.0, 0.0, 1.0,
      0.5, -0.5, 0.0,   0.0, 1.0, 0.0, 1.0,
     -0.5, -0.5, 0.0,   0.0, 0.0, 1.0, 1.0,
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
    };
    m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer(indices, sizeof(indices)));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
      #version 330 core

      in vec3 a_Position;
      in vec4 a_Color;

      out vec4 color;
      out vec4 position;

      uniform mat4 u_ViewProj;

      void main()
      {
        position = u_ViewProj * vec4(a_Position, 1.0);
        color = a_Color;
        gl_Position = position;
      }
    )";
    std::string fragmentSrc = R"(
      #version 330 core

      in vec4 color;
      in vec4 position;

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

  void OnUpdate(const ProcessedTime& delta) override
  { 
    /*GC_CORE_INFO("Elapsed time: {0}", (float)delta);*/
    // Warning: movement will get messy while the camera is rotating
    
    m_CameraController.OnUpdate(delta);
    
    Graphics::Clear({0, 0, 0, 1});
    Graphics::BeginRender(m_CameraController.GetCamera());

    m_Shader->Bind();
    m_Shader->UploadMat4("u_ViewProj", m_CameraController.GetCamera().GetViewProj());


    Graphics::Submit(m_VertexArray);

    Graphics::EndRender();
  }

  void OnEvent(GCrisp::Event& e) override
  {
    m_CameraController.OnEvent(e);
  }




private:
  Reference<Graphics::Shader> m_Shader;
  Reference<Graphics::VertexBuffer> m_VertexBuffer;
  Reference<Graphics::IndexBuffer> m_IndexBuffer;
  Reference<Graphics::VertexArray> m_VertexArray;

  OrthoCameraController m_CameraController;
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

