#include "GLWindow.h"
#include <gcpch.h>

#include <GCrisp/Core/Application.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include <GCrisp/Events/MouseEvent.h>
#include <GCrisp/Platform/OpenGL/GLContext.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GCrisp {
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* desc) {
    GC_CORE_ERROR("GLFW Error: {0}: {1}", error, desc);
}

void GLWindow::Init() {
    GC_PROFILE_FUNC();

    WindowData& data = m_Spec.Data;

    GC_CORE_INFO("Creating GLFW window {0} ({1}, {2})", data.Title, data.Width,
                 data.Height);

    if (!s_GLFWInitialized) {
        GC_PROFILE_SCOPE("glfwInit - OpenGLWindow");
        int success = glfwInit();
        GC_CORE_ASSERT(success, "Could not initialize GLFW!");

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    // Will only be set on linux
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "gcrisp");

    glfwWindowHint(GLFW_RESIZABLE, data.Resizable); {
        GC_PROFILE_SCOPE("glfwCreateWindow - OpenGLWindow");
        m_Window = glfwCreateWindow((int)data.Width, (int)data.Height,
                                    data.Title.c_str(), nullptr, nullptr);
    }

    m_Context = new Graphics::GLContext({m_Window});
    m_Context->Init();

    int textureSlots = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureSlots);

    m_GraphicsSpec.Vendor = (const char*)glGetString(GL_VENDOR);
    m_GraphicsSpec.Renderer = (const char*)glGetString(GL_RENDERER);
    m_GraphicsSpec.SLVersion =
        (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    int majorVer, minorVer;

    glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
    glGetIntegerv(GL_MINOR_VERSION, &minorVer);

    m_GraphicsSpec.APIVersion = Version(1, majorVer, minorVer);

    GC_CORE_INFO("OpenGL Specifications:");
    GC_CORE_INFO("   Vendor: {0}", m_GraphicsSpec.Vendor);
    GC_CORE_INFO("   Renderer: {0}", m_GraphicsSpec.Renderer);
    GC_CORE_INFO("   OpenGL Version: {0}",
                 m_GraphicsSpec.APIVersion.GetNameNoVariant());
    GC_CORE_INFO("   GLSL Version: {0}", m_GraphicsSpec.SLVersion);

    glfwSetWindowUserPointer(m_Window, &m_Spec.Data);
    SetVSync(data.VSync);

    // Set up GLFW callbacks
    glfwSetWindowSizeCallback(
        m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

    glfwSetWindowIconifyCallback(
        m_Window, [](GLFWwindow* window, int iconified) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowMinimizeEvent event(iconified == GLFW_TRUE);
            data.EventCallback(event);
        });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowFocusEvent event(focused == GLFW_TRUE);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int,
                                    int action, int) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        // This case is usually never reached in newer GLFW versions and
        // it's generally better to never use it
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow* window, int button, int action, int) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

    glfwSetScrollCallback(
        m_Window, [](GLFWwindow* window, double xOff, double yOff) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOff, (float)yOff);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
}

void GLWindow::Shutdown() {
    GC_PROFILE_FUNC();
    glfwDestroyWindow(m_Window);
}

void GLWindow::OnUpdate() {
    GC_PROFILE_FUNC();
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void GLWindow::TransferContext() { glfwMakeContextCurrent(m_Window); }

/*void GLWindow::ConvertWindowCoords(glm::vec3& coords)
{
    auto& app = Application::Get();
    coords.x = (coords.x / app.GetWindow().GetWidth()) * 2 - 1;
    coords.y = (1 - (coords.y / app.GetWindow().GetHeight())) * 2 - 1;
}*/

void GLWindow::SetResizable(bool enabled) {
    GC_PROFILE_FUNC();
    glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_TRUE : GLFW_FALSE);
    m_Spec.Data.Resizable = enabled;
}

void GLWindow::SetVSync(bool enabled) {
    GC_PROFILE_FUNC();
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    m_Spec.Data.VSync = enabled;
}
} // namespace GCrisp
