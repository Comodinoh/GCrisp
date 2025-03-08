#include <gcpch.h>
#include "GLContext.h"

#include <GCrisp/Core/Core.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GCrisp
{
    namespace Graphics
    {
        void GLContext::Init() const
        {
            GC_PROFILE_FUNC();
            glfwMakeContextCurrent(m_WindowHandle);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            GC_CORE_ASSERT(status, "Could not load glad from GLFW!");
        }

        void GLContext::SwapBuffers() const
        {
            glfwSwapBuffers(m_WindowHandle);
        }

        std::string GLContext::GetRendererName() const
        {
            return (char*)glGetString(GL_RENDERER);
        }

        std::string GLContext::GetVendorName() const
        {
            return (char*)glGetString(GL_VENDOR);
        }


        std::string GLContext::GetVersion() const
        {
            return (char*)glGetString(GL_VERSION);
        }

        std::string GLContext::GetSLVersion() const
        {
            return (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        }
    }
}
