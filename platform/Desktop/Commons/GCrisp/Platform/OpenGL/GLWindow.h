#pragma once

#include "GLContext.h"

#include <GCrisp/Core/GWindow.h>

struct GLFWwindow;

namespace GCrisp
{
    class GLWindow : public Window
    {
    public:
        GLWindow(const WindowSpecification& spec) : Window(spec) { GLWindow::Init();}
        virtual ~GLWindow() override {GLWindow::Shutdown();}

        virtual void OnUpdate() override;
        virtual void TransferContext() override;

        //virtual void ConvertWindowCoords(glm::vec3& coords) override;

        inline virtual void* GetWindowPointer() override { return m_Window; };
        // inline virtual Graphics::Context* GetContext() override { return m_Context; };

        virtual void SetResizable(bool enabled) override;

        virtual void SetVSync(bool enabled) override;

    protected:
        GLFWwindow* m_Window;
        Graphics::GLContext* m_Context;

        virtual void Init() override;
        virtual void Shutdown() override;
    };
}
