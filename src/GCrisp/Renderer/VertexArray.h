
#ifndef _VERTEX_ARRAY_
#define _VERTEX_ARRAY_
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/GraphicsCore.h>

namespace GCrisp::Graphics
{
class VertexArray
{
  public:
	virtual ~VertexArray() = default;

	virtual void Bind() const	= 0;
	virtual void UnBind() const = 0;

	virtual void
	AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer)			= 0;
	virtual void SetIndexBuffer(const Reference<IndexBuffer>& vertexBuffer) = 0;

	inline virtual Reference<IndexBuffer> GetIndexBuffer() const = 0;

	GC_GRAPHICS_CREATE_DECL(VertexArray);
};
} // namespace GCrisp::Graphics

#endif
