#include "OpenGLAPI.h"

#include "GCrisp/Renderer/Renderer.h"

namespace GCrisp{

namespace Graphics{

void OpenGLAPI::Init()
{
  s_RendererBackend = Backend::OpenGL;
}

}

}
