#include "GCrisp/Events/ApplicationEvent.h"
#include "GCrisp/Events/Event.h"
#include "GCrisp/GWindow.h"
#include <GCrisp/Application.h>
#include <GCrisp/Events/KeyEvent.h>

namespace gcrisp{

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() 
{
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(BIND_FN(OnEvent));

}

Application::~Application() 
{
}

void Application::Run()
{
  while(m_Running)
  {
    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event& e)
{
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));
  
  GC_CORE_TRACE("{0}", e);
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
  m_Running = false;
  return true;
}

}
