#pragma once

#include "OpenGLContext.h"

#include <GCrisp/Core/GWindow.h>

struct GLFWwindow;

namespace GCrisp
{
    class OpenGLWindow : public Window
    {
    public:
        OpenGLWindow(const Graphics::Backend& backend, const WindowProps& props);
        virtual ~OpenGLWindow();

        virtual void OnUpdate() override;

        inline virtual void* GetWindowPointer() override { return m_Window; };
        inline virtual Graphics::Context* GetContext() override { return m_Context; };

        virtual void SetResizable(bool enabled) override;

        virtual void SetVSync(bool enabled) override;

    protected:
        GLFWwindow* m_Window;
        Graphics::OpenGLContext* m_Context;

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
}
