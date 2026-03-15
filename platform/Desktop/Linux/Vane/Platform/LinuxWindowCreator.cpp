#include <Vane/Core/Base.h>
#include <Vane/Core/GWindow.h>
#include <Vane/Platform/OpenGL/GLWindow.h>

namespace Vane {

Window* Window::Create(const WindowSpecification& spec) {
    switch (spec.Backend) {
    case Backend::None: {
    }
    case Backend::OpenGL: {
        return new GLWindow(spec);
    }
    default:
        VANE_CORE_ASSERT(false, "Unknown Backend!");
        return nullptr;
    }
}

} // namespace Vane
