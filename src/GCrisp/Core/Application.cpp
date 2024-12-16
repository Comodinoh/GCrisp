#include <gcpch.h>
#include "Application.h"

#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GCrisp/Platform/OpenGL/OpenGLBuffer.h>
#include <GCrisp/Renderer/Renderer.h>

namespace GCrisp{

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application() 
{
  GC_CORE_ASSERT(!s_Instance, "Application instance cannot be null!")
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create(Graphics::Backend::OpenGL));
  m_Window->SetEventCallback(BIND_FN(OnEvent));

  Graphics::Renderer::Init();

  m_VertexArray.reset(GetGraphicsCreator()->CreateVertexArray());

    float vertices[] = 
    {
     -1.0,  1.0, 0.0,   1.0, 0.0, 0.0, 1.0,
     -1.0, -1.0, 0.0,   0.0, 1.0, 0.0, 1.0,
      1.0,  1.0, 0.0,   0.0, 0.0, 1.0, 1.0,
      1.0, -1.0, 0.0,   1.0, 1.0, 1.0, 1.0
    };

    m_VertexBuffer.reset(GetGraphicsCreator()->CreateVertexBuffer(vertices, sizeof(vertices)));

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
    m_IndexBuffer.reset(GetGraphicsCreator()->CreateIndexBuffer(indices, sizeof(indices)));
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

    auto& app = Application::Get();

    m_Shader.reset(Application::Get().GetGraphicsCreator()->CreateShader(&vertexSrc, &fragmentSrc));
}

Application::~Application() 
{
  s_Instance = nullptr;
}

void Application::Run()
{
  while(m_Running)
  {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shader->Bind();
    m_VertexArray->Bind();
    
    glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

    for(Layer* layer : m_LayerStack)
    {
      layer->OnUpdate();
    }
    m_Window->OnUpdate();
  }
}

void Application::PushLayer(Layer* layer)
{
  m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
  m_LayerStack.PushOverlay(overlay);
}

void Application::OnEvent(Event& e)
{
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));
  dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(OnWindowResize));
  

  for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
  {
    (*--it)->OnEvent(e);
    if(e.Handled)
      break;
  }
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
  m_Running = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
  glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
  return true;
}

}
