#pragma once

#include <GCrisp/Renderer/VertexArray.h>

namespace GCrisp
{
namespace Graphics
{
class GLVertexArray : public VertexArray
{
  public:
	GLVertexArray();
	virtual ~GLVertexArray() override;

	virtual void Bind() const override;
	virtual void UnBind() const override;

	virtual void
	AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) override;
	virtual void
	SetIndexBuffer(const Reference<IndexBuffer>& vertexBuffer) override;

	inline virtual Reference<IndexBuffer> GetIndexBuffer() const override
	{
		return m_IndexBuffer;
	};

  private:
	std::vector<Reference<VertexBuffer>> m_VertexBuffers;
	Reference<IndexBuffer>				 m_IndexBuffer;

	uint32_t m_RendererID;
};
} // namespace Graphics
} // namespace GCrisp
