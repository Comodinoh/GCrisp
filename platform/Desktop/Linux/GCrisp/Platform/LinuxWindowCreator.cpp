#include <GCrisp/Core/Base.h>
#include <GCrisp/Core/GWindow.h>
#include <GCrisp/Platform/OpenGL/GLWindow.h>

namespace GCrisp {

Window* Window::Create(const WindowSpecification& spec) {
    switch (spec.Backend) {
    case Backend::None: {
    }
    case Backend::OpenGL: {
        return new GLWindow(spec);
    }
    default:
        GC_CORE_ASSERT(false, "Unknown Backend!");
        return nullptr;
    }
}

} // namespace GCrisp
