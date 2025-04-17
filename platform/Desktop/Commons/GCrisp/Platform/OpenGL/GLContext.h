#pragma once

#include <GCrisp/Core/Core.h>
#include <GCrisp/Renderer/Context.h>
#include <GLFW/glfw3.h>


namespace GCrisp
{
    namespace Graphics
    {
        struct GLContextSpecification
        {
            GLFWwindow* WindowHandle;
        };

        class GLContext : public Context
        {
        public:
            GLContext(const ContextSpecification& spec) : m_Spec((GLFWwindow*)spec.WindowHandle)
            {
                GC_CORE_ASSERT(spec.WindowHandle, "Provided invalid window handle! (nullptr)");
            };

            virtual void Init() const override;
            virtual void SwapBuffers() const override;

        private:
            GLContextSpecification m_Spec;
        };
    }
}
