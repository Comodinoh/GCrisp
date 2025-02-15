#include <gcpch.h>
#include "OpenGLContext.h"

#include <GCrisp/Core/Core.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GCrisp
{
    namespace Graphics
    {
        void OpenGLContext::Init() const
        {
            glfwMakeContextCurrent(m_WindowHandle);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            GC_CORE_ASSERT(status, "Could not load glad from GLFW!");
        }

        void OpenGLContext::SwapBuffers() const
        {
            glfwSwapBuffers(m_WindowHandle);
        }

        std::string OpenGLContext::GetRendererName() const
        {
            return (char*)glGetString(GL_RENDERER);
        }

        std::string OpenGLContext::GetVendorName() const
        {
            return (char*)glGetString(GL_VENDOR);
        }


        std::string OpenGLContext::GetVersion() const
        {
            return (char*)glGetString(GL_VERSION);
        }

        std::string OpenGLContext::GetSLVersion() const
        {
            return (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        }
    }
}
