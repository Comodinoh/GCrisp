#include <gcpch.h>
#include "Application.h"

#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/KeyEvent.h>
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
}

Application::~Application() 
{
  s_Instance = nullptr;
  Graphics::Renderer::Shutdown();
}

void Application::Run()
{
  while(m_Running)
  {
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
  Graphics::Renderer::SetViewport({0, 0}, {m_Window->GetWidth(), m_Window->GetHeight()});
  return true;
}

}
