#include <gcpch.h>
#include "Application.h"

#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/Timing.h>

namespace GCrisp
{
  Application* Application::s_Instance = nullptr;

  Application::Application()
  {
    ProcessedTime delta;
    {
      ScopedTimer timer(steady_clock::now(), delta);
      GC_CORE_ASSERT(!s_Instance, "Application instance cannot be not null!")
      s_Instance = this;

      m_Window = std::unique_ptr<Window>(Window::Create(Graphics::Backend::OpenGL));
      m_Window->SetEventCallback(GC_BIND_FN1(Application::OnEvent));

      m_AssetsManager = std::make_unique<AssetsManager>();

      GC_CORE_ASSERT(m_AssetsManager, "AssetsManager should not be null!");

      Graphics::Init();
    }

    GC_CORE_INFO("Took {0} seconds to initialize application.", delta.GetSeconds());
  }

  Application::~Application()
  {
    s_Instance = nullptr;
    Graphics::Shutdown();
  }

  void Application::Run()
  {
    while (m_Running)
    {
      ProcessedTime elapsed;
      m_FrameTimer.ProcessTime(elapsed, steady_clock::now());

      for (Layer* layer : m_LayerStack)
      {
        layer->OnUpdate(elapsed);
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

    dispatcher.Dispatch<WindowCloseEvent>(GC_BIND_FN1(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(GC_BIND_FN1(Application::OnWindowResize));


    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
      (*--it)->OnEvent(e);
      if (e.Handled)
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
    Graphics::SetViewport({0, 0}, {e.GetNewWidth(), e.GetNewHeight()});
    return false;
  }
}
