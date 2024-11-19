#include <OpenGL/OpenGLWindow.h>

namespace gcrisp{

Window* Window::Create(const RendererType rendererType, const WindowProps& props)
{
  GC_ASSERT(rendererType != DirectX);

  switch(rendererType)
  {
    case OpenGL:
      {
        return new OpenGLWindow(props);
      }
    /**case Vulkan:
      {
        return new VulkanWindow(props);
      }**/
  }
}

}
