#include "GCrisp/Core.h"
#include <GCrisp/GWindow.h>

#ifdef GC_WIN32
#include <DirectXWindow.h>
#endif
#include <VulkanWindow.h>
#include <OpenGLWindow.h>

namespace gcrisp{

Window* Window::Create(const RendererType rendererType, const WindowProps& props)
{
  #ifdef GC_POSIX
  if(rendererType == DirectX)
  {
    GC_CORE_ERROR("Tried creating window with invalid DirectX renderer on Linux!");
    GC_ASSERT(false);
    return nullptr;
  }
  #endif

  switch(rendererType)
  {
    case OpenGL:
      {
        return new OpenGLWindow(props);
      }
    /**
    case DirectX:
      {
        return new DirectXWindow(props);
      }
    case Vulkan:
      {
        return new VulkanWindow(props);
      }
    **/ // Ignore the others for now
  }
}


}
