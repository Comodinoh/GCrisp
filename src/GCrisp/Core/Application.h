#pragma once

#include <GCrisp/Assets/AssetsManager.h>
#include <GCrisp/Core/Base.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/LayerStack.h>
#include <GCrisp/Core/Timing.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/Event.h>

namespace GCrisp {
class Application {
public:
    Application();

    virtual ~Application();

    void Exit();

    void Restart();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);

    void PushOverlay(Layer* overlay);

    static inline Application& Get() { return *s_Instance; }
    inline Window& GetWindow() const { return *m_Window; }
    inline Timer& GetFrameTimer() { return m_FrameTimer; }
    inline AssetsManager& GetAssetsManager() { return *m_AssetsManager; }

private:
    bool OnWindowClose(WindowCloseEvent& e);

    bool OnWindowResize(WindowResizeEvent& e);

private:
    ScopedPtr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
    Timer m_FrameTimer;
    ScopedPtr<AssetsManager> m_AssetsManager;
    static Application* s_Instance;
};

Application* CreateApplication();
}; // namespace GCrisp
