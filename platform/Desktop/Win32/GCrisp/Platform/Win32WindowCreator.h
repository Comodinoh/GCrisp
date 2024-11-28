#pragma once

#include <OpenGL/OpenGLWindow.h>
#include <GCrisp/GWindow.h>

namespace GCrisp{

window* window::create(const renderertype renderertype, const windowprops& props)
{
  switch(renderertype)
  {
    case opengl:
    {
      return new openglwindow(props);
    }
  }
}

}
