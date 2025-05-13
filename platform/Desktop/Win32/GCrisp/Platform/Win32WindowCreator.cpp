#include <GCrisp/Core/Core.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Platform/OpenGL/GLWindow.h>

namespace GCrisp {
Window* Window::Create(const WindowSpecification& spec) {
    switch (spec.Backend) {
    case Backend::OpenGL: {
        return new GLWindow(spec);
    }
    default: {
        GC_CORE_ASSERT(false, "Unknown Backend!");
        return nullptr;
    }
        /**case Vulkan:
          {
            return new VulkanWindow(props);
          }**/
    }
}
} // namespace GCrisp
