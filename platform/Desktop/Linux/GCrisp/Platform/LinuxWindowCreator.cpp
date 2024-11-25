#include "GCrisp/Core/Log.h"
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Platform/OpenGL/OpenGLWindow.h>

namespace gcrisp{

Window* Window::Create(Graphics::Backend backend, const WindowProps& props)
{
  switch(backend)
  {
    case Graphics::Backend::None:
      {
        GC_ERROR("{0} doesn't currently support headless mode", ENGINE_NAME);
        GC_ASSERT(false);
      }
    case Graphics::Backend::OpenGL:
      {
        return new OpenGLWindow(backend, props);
      }
    /**case Vulkan:
      {
        return new VulkanWindow(props);
      }**/
  }
}

}
