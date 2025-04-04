#pragma once

#include <GCrisp/Core/Core.h>
#include <GCrisp/Renderer/Context.h>
#include <GLFW/glfw3.h>


namespace GCrisp
{
    namespace Graphics
    {
        class GLContext : public Context
        {
        public:
            GLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
            {
                GC_CORE_ASSERT(windowHandle, "Provided invalid window handle! (nullptr)");
            };

            virtual void Init() const override;
            virtual void SwapBuffers() const override;

        private:
            GLFWwindow* m_WindowHandle;
        };
    }
}
