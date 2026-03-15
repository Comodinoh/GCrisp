#pragma once
#include <Vane/Renderer/Buffer.h>
#include <Vane/Renderer/RendererBase.h>

namespace Vane::Graphics {
class VertexArray {
  public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;

    virtual void
    AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Reference<IndexBuffer>& vertexBuffer) = 0;

    inline virtual Reference<IndexBuffer> GetIndexBuffer() const = 0;

    VANE_GRAPHICS_CREATE_DECL(VertexArray)
};
} // namespace Vane::Graphics
