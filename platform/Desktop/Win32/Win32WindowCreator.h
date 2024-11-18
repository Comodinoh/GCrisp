#pragma once

#include "OpenGLWindow.h"
#include <GCrisp/GWindow.h>

namespace gcrisp{

Window* Window::Create(const RendererType rendererType, const WindowProps& props)
{
  switch(rendererType)
  {
    case OpenGL:
    {
      return new OpenGLWindow(props);
    }
  }
}

}
