#include "Buffer.h"

#ifdef VANE_OPENGL
#include <Vane/Platform/OpenGL/GLBuffer.h>
#endif

namespace Vane::Graphics {
VANE_GRAPHICS_CREATE_IMPL_WITH_SPEC(VertexBuffer);
VANE_GRAPHICS_CREATE_IMPL_WITH_SPEC(IndexBuffer);
} // namespace Vane::Graphics
