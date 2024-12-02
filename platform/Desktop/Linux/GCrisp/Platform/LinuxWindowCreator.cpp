#include "GCrisp/Core/Log.h"
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Platform/OpenGL/OpenGLWindow.h>

namespace GCrisp{

Window* Window::Create(const Graphics::Backend& backend, const WindowProps& props)
{
  switch(backend)
  {
    case Graphics::Backend::None:
      {
        GC_CORE_ASSERT(false, "No headless backend found!");
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
