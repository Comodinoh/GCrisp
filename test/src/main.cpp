#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GLFW/glfw3.h>

using namespace GCrisp;

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test"), m_Camera(Graphics::Camera({{0, 0, 0}, {0, 0, 0}, glm::mat4(1.0f), glm::mat4(1.0f), 1.0f}))
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

      uniform mat4 mvp;

      void main()
      {
        position = mvp * vec4(a_Position, 1.0);
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
        fragColor = position;
      }
    )";


    m_Shader.reset(app.GetGraphicsCreator()->CreateShader(&vertexSrc, &fragmentSrc));
  }
  
  ~TestLayer()
  {

  }

  void OnUpdate(const Timer& timer) override
  { 
    float delta = timer.GetElapsedTime().GetSecondsF();
    // Warning: movement will get messy while the camera is rotating
    glm::vec3 direction = glm::vec3(0);
    if(Input::IsKeyPressed(Input::W))
    {
      direction.y += 1;
    }
    if(Input::IsKeyPressed(Input::S))
    {
      direction.y -= 1;
    }
    if(Input::IsKeyPressed(Input::D))
    {
      direction.x += 1;
    }
    if(Input::IsKeyPressed(Input::A))
    {
      direction.x -= 1;
    }

    float speed = 0.025f;
    glm::vec3 velocity = glm::length(direction) != 0 ? glm::normalize(direction)*speed : glm::vec3();
    m_Camera.GetSpecification().Position += velocity;
    

    Graphics::Renderer::Clear({0, 0, 0, 1});

    auto& window = Application::Get().GetWindow();

    m_Camera.GetSpecification().AspectRatio = window.GetWidth()/window.GetHeight();


    m_Camera.Project(Graphics::Camera::OrthographicProjection());

    m_Shader->Bind();
    m_Shader->UploadMat4("mvp", m_Camera.GetSpecification().GetViewProj());

    Graphics::Renderer::Draw(m_VertexArray);
  }

  void OnEvent(GCrisp::Event& e) override
  {
    EventDispatcher dispatcher(e);
    
    dispatcher.Dispatch<WindowResizeEvent>(GC_BIND_FN1(TestLayer::OnWindowResize));
  }


  bool OnWindowResize(WindowResizeEvent& e) 
  {
    m_Camera.OnResize(e.GetNewWidth(), e.GetNewHeight());
    return false;
  }


private:
  std::shared_ptr<Graphics::Shader> m_Shader;
  std::shared_ptr<Graphics::VertexBuffer> m_VertexBuffer;
  std::shared_ptr<Graphics::IndexBuffer> m_IndexBuffer;
  std::shared_ptr<Graphics::VertexArray> m_VertexArray;

  Graphics::Camera m_Camera;
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

