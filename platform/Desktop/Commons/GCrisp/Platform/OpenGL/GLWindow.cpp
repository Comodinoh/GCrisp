#include <gcpch.h>
#include "GLWindow.h"

#include <GCrisp/Platform/OpenGL/GLCreator.h>
#include <GCrisp/Platform/OpenGL/GLContext.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/MouseEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace GCrisp
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* desc)
    {
        GC_CORE_ERROR("GLFW Error: {0}: {1}", error, desc);
    }

    GLWindow::GLWindow(const Graphics::Backend& backend, const WindowProps& props) : Window(backend)
    {
        Init(props);
    }

    GLWindow::~GLWindow()
    {
        Shutdown();
    }

    void GLWindow::Init(const WindowProps& props)
    {
        GC_PROFILE_FUNC();
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.Resizable = props.Resizable;


        GC_CORE_INFO("Creating GLFW window {0} ({1}, {2})", props.Title, props.Width, props.Height);


        if (!s_GLFWInitialized)
        {
            GC_PROFILE_SCOPE("glfwInit - OpenGLWindow");
            int success = glfwInit();
            GC_CORE_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);

            s_GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_RESIZABLE, props.Resizable);

        {
            GC_PROFILE_SCOPE("glfwCreateWindow - OpenGLWindow");
            m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        }

        m_Context = new Graphics::GLContext(m_Window);
        m_Context->Init();

        m_GraphicsSpec = GraphicsSpec{(char*)glGetString(GL_RENDERER),
            (char*)glGetString(GL_VENDOR),
            (char*)glGetString(GL_VERSION),
            (char*)glGetString(GL_SHADING_LANGUAGE_VERSION)};

        GC_CORE_INFO("Initialized OpenGL context:");
        GC_CORE_INFO("   Vendor: {0}", m_GraphicsSpec.Vendor);
        GC_CORE_INFO("   Renderer: {0}", m_GraphicsSpec.Renderer);
        GC_CORE_INFO("   OpenGL Version: {0}", m_GraphicsSpec.Version);
        GC_CORE_INFO("   GLSL Version: {0}", m_GraphicsSpec.SLVersion);

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set up GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowMinimizeEvent event(iconified == GLFW_TRUE ? true : false);
            data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowFocusEvent event(focused == GLFW_TRUE ? true : false);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            // This case is usually never reached in newer GLFW versions and it's generally better to never use it
            case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOff, double yOff)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOff, (float)yOff);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        m_GraphicsCreator = new Graphics::GLCreator();
    }


    void GLWindow::Shutdown()
    {
        GC_PROFILE_FUNC();
        glfwDestroyWindow(m_Window);
    }

    void GLWindow::OnUpdate()
    {
        GC_PROFILE_FUNC();
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void GLWindow::SetResizable(bool enabled)
    {
        GC_PROFILE_FUNC();
        glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_TRUE : GLFW_FALSE);
        m_Data.Resizable = enabled;
    }

    void GLWindow::SetVSync(bool enabled)
    {
        GC_PROFILE_FUNC();
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }
}
