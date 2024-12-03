#pragma once


#include <GCrisp/Renderer/Creator.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/LayerStack.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Events/ApplicationEvent.h>

namespace GCrisp {

class Application
{
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);


  static inline Application& Get() {return *s_Instance;}
  inline Window& GetWindow() {return *m_Window;} 
  inline Graphics::Creator* GetGraphicsCreator() const {return m_Window->GetCreator();}
private:
  bool OnWindowClose(WindowCloseEvent& e);
private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  LayerStack m_LayerStack;
  static Application* s_Instance;
};

Application* CreateApplication();


};

