#include <GCrisp/Core.h>
#include "OpenGLWindow.h"
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/MouseEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include "GCrisp/GWindow.h"
#include "GLFW/glfw3.h"
#include "OpenGL/OpenGLContext.h"


namespace gcrisp{

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* desc)
{
  GC_CORE_ERROR("GLFW Error: {0}: {1}", error, desc);
}

OpenGLWindow::OpenGLWindow(const WindowProps& props)
{
  Init(props);
}

OpenGLWindow::~OpenGLWindow()
{
  Shutdown();
}

void OpenGLWindow::Init(const WindowProps& props)
{
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  GC_CORE_INFO("Creating OpenGL window {0} ({1}, {2})", props.Title, props.Width, props.Height);


  if(!s_GLFWInitialized)
  {
    int success = glfwInit();
    GC_ASSERT(success);
    
    glfwSetErrorCallback(GLFWErrorCallback);

    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

  m_Context = new OpenGLContext(m_Window);
  m_Context->Init();
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  //Set up GLFW callbacks
  glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

    WindowResizeEvent event(width, height);
    data.Width = width;
    data.Height = height;
    data.EventCallback(event);
  });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

    switch (action) {
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
      case GLFW_REPEAT:
      {
          KeyPressedEvent event(key, 1);
          data.EventCallback(event);
          break;
      }
    }
  });

  glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

    switch (action) {
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

  glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOff, double yOff) {
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

    MouseScrolledEvent event((float)xOff, (float)yOff);
    data.EventCallback(event);
  });

  glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

    MouseMovedEvent event((float)xPos, (float)yPos);
    data.EventCallback(event);
  });
}


void OpenGLWindow::Shutdown()
{
  glfwDestroyWindow(m_Window);
}

void OpenGLWindow::OnUpdate()  
{
  glfwPollEvents();
  m_Context->SwapBuffers();
}

void OpenGLWindow::SetVSync(bool enabled)
{
  if(enabled)
  {
    glfwSwapInterval(1);
  }else
  {
    glfwSwapInterval(0);
  }

  m_Data.VSync = enabled;
}

bool OpenGLWindow::HasVSync() const 
{
  return m_Data.VSync;
}

}

