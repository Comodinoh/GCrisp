#pragma once

#include <GCrisp/Renderer/VertexArray.h>

namespace GCrisp{

namespace Graphics{

class OpenGLVertexArray : public VertexArray
{
public:
  OpenGLVertexArray();

  virtual void Bind()   const override;
  virtual void UnBind() const override;

  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) override;

  inline virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override {return m_IndexBuffer;};
private:
  std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
  std::shared_ptr<IndexBuffer> m_IndexBuffer;

  uint32_t m_RendererID;
};

}

}
