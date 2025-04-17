#pragma once

#include <GCrisp/Core/GWindow.h>

#define MAX_TEXTURE_SLOTS 32
#define MAX_SHADER_TYPES 2

// Used for the graphics objects create system to facilitate writing out everything
#define GC_GRAPHICS_CREATE_DECL(x) static ::GCrisp::Graphics::x* Create(void);
#define GC_GRAPHICS_CREATE_DECL_WITH_SPEC2(x, y) static ::GCrisp::Graphics::x* Create (const GC_CONCAT(y, Specification&) spec);
#define GC_GRAPHICS_CREATE_DECL_WITH_SPEC(x) GC_GRAPHICS_CREATE_DECL_WITH_SPEC2(x, x)

// We're doing all of this to not compile the GL parts if you don't want to or your platform doesn't support it.
// It's the same with the other: Vulkan, DirectX, etc.
#ifdef GC_OPENGL
#define GC_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x) case GCrisp::Backend::OpenGL:\
			{\
				return new GC_CONCAT(GL, x)(spec);\
				break;\
			}
#define GC_GRAPHICS_CREATE_OPENGL(x) case GCrisp::Backend::OpenGL:\
			{\
				return new GC_CONCAT(GL, x)();\
				break;\
			}
#else
#define GC_GRAPHICS_CREATE_OPENGL(x)
#define GC_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x)
#endif

#define GC_GRAPHICS_CREATE_IMPL(x) ::GCrisp::Graphics::x* x::Create() \
	{\
		switch(GCrisp::Window::GetBackend()) \
		{\
			GC_GRAPHICS_CREATE_OPENGL(x);\
			default: return nullptr;\
		}\
	}


#define GC_GRAPHICS_CREATE_IMPL_WITH_SPEC2(x, y) ::GCrisp::Graphics::x* x::Create(const GC_CONCAT(y, Specification&) spec) \
	{\
		switch(GCrisp::Window::GetBackend()) \
		{\
			GC_GRAPHICS_CREATE_OPENGL_WITH_SPEC(x);\
			default: return nullptr;\
		}\
	}

#define GC_GRAPHICS_CREATE_IMPL_WITH_SPEC(x) GC_GRAPHICS_CREATE_IMPL_WITH_SPEC2(x, x)