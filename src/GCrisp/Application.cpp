#include "GCrisp/GWindow.h"
#include <GCrisp/Application.h>
#include <GCrisp/Events/KeyEvent.h>

namespace gcrisp{

Application::Application() 
{
  m_Window = std::unique_ptr<Window>(Window::Create());
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

}
