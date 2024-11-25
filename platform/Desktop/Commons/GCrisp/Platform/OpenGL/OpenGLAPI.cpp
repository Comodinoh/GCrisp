#include "OpenGLAPI.h"
#include "GCrisp/Renderer/Renderer.h"

namespace gcrisp{

namespace Graphics{

void OpenGLAPI::Init()
{
  s_RendererBackend = Backend::OpenGL;
}

}

}
