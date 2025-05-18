#pragma once

#include "RendererBase.h"

namespace GCrisp::Graphics {
struct ContextSpecification {
    void* WindowHandle;
};

class Context {
  public:
    Context() = default;
    virtual ~Context() {}

    virtual void Init() const = 0;

    virtual void SwapBuffers() const = 0;

    GC_GRAPHICS_CREATE_DECL_WITH_SPEC(Context)
};
} // namespace GCrisp::Graphics
