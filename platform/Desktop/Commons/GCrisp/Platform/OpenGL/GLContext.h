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
            GLContext(GLFWwindow* window_handle) : m_WindowHandle(window_handle)
            {
                GC_CORE_ASSERT(window_handle, "Provided invalid window handle! (nullptr)");
            };

            virtual void Init() const override;
            virtual void SwapBuffers() const override;

            virtual std::string GetRendererName() const override;
            virtual std::string GetVendorName() const override;
            virtual std::string GetVersion() const override;
            virtual std::string GetSLVersion() const override;

        private:
            GLFWwindow* m_WindowHandle;
        };
    }
}
