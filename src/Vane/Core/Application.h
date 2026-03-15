#pragma once

#include <Vane/Assets/AssetsManager.h>
#include <Vane/Core/Base.h>
#include <Vane/Core/GWindow.h>
#include <Vane/Core/LayerStack.h>
#include <Vane/Core/Timing.h>
#include <Vane/Events/ApplicationEvent.h>
#include <Vane/Events/Event.h>

namespace Vane {
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
}; // namespace Vane
