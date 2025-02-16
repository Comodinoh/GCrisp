#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Core/Core.h>
#include <GCrisp/Platform/OpenGL/OpenGLWindow.h>

namespace GCrisp
{
    Window* Window::Create(const Graphics::Backend& backend, const WindowProps& props)
    {
        switch (backend)
        {
        case Graphics::Backend::OpenGL:
            {
                return new OpenGLWindow(backend, props);
            }
        default:
            {
                GC_CORE_ASSERT(false, "Unknown Backend!");
                return nullptr;
            }
        /**case Vulkan:
          {
            return new VulkanWindow(props);
          }**/
        }
    }
}
