#include "Application.h"

#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/Input.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gcrisp{

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application() 
{
  GC_ASSERT(!s_Instance)
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create(OpenGL));
  m_Window->SetEventCallback(BIND_FN(OnEvent));

}

Application::~Application() 
{
}

void Application::Run()
{
  while(m_Running)
  {

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

}