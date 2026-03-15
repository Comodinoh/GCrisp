#pragma once

#include <Vane/Core/GWindow.h>

#define MAX_TEXTURE_SLOTS 32
#define MAX_SHADER_TYPES 2

// Used for the graphics objects create system to facilitate writing out
// everything
#define VANE_GRAPHICS_CREATE_DECL(x) static ::Vane::Graphics::x* Create(void);
#define VANE_GRAPHICS_CREATE_DECL_WITH_SPEC2(x, y)                               \
    static ::Vane::Graphics::x* Create(const VANE_CONCAT(y, Specification&)    \
                                             spec);
#define VANE_GRAPHICS_CREATE_DECL_WITH_SPEC(x)                                   \
    VANE_GRAPHICS_CREATE_DECL_WITH_SPEC2(x, x)

// We're doing all of this to not compile the GL parts if you don't want to or
// your platform doesn't support it. It's the same with the other: Vulkan,
// DirectX, etc.
#ifdef VANE_OPENGL
#define VANE_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x)                                 \
    case Vane::Backend::OpenGL: {                                            \
        return new VANE_CONCAT(GL, x)(spec);                                     \
        break;                                                                 \
    }
#define VANE_GRAPHICS_CREATE_OPENGL(x)                                           \
    case Vane::Backend::OpenGL: {                                            \
        return new VANE_CONCAT(GL, x)();                                         \
        break;                                                                 \
    }
#else
#define VANE_GRAPHICS_CREATE_OPENGL(x)
#define VANE_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x)
#endif

#define VANE_GRAPHICS_CREATE_IMPL(x)                                             \
    ::Vane::Graphics::x* x::Create() {                                       \
        switch (Vane::Window::GetBackend()) {                                \
            VANE_GRAPHICS_CREATE_OPENGL(x);                                      \
        default:                                                               \
            return nullptr;                                                    \
        }                                                                      \
    }

#define VANE_GRAPHICS_CREATE_IMPL_WITH_SPEC2(x, y)                               \
    ::Vane::Graphics::x* x::Create(const VANE_CONCAT(y, Specification&)        \
                                         spec) {                               \
        switch (Vane::Window::GetBackend()) {                                \
            VANE_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x);                            \
        default:                                                               \
            return nullptr;                                                    \
        }                                                                      \
    }

#define VANE_GRAPHICS_CREATE_IMPL_WITH_SPEC(x)                                   \
    VANE_GRAPHICS_CREATE_IMPL_WITH_SPEC2(x, x)
