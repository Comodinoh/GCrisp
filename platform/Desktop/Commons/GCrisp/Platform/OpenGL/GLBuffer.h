#pragma once

#include <GCrisp/Renderer/Buffer.h>

namespace GCrisp {

namespace Graphics{

class GLVertexBuffer : public VertexBuffer 
{
public:
  GLVertexBuffer(const VertexBufferSpecification& spec);
  virtual ~GLVertexBuffer() override;

  virtual void Bind() const override;
  virtual void UnBind() const override;

  virtual void UploadSubData(uint32_t size, const void* data) override;

  virtual const BufferLayout& GetLayout() const override {return m_Layout;}
  virtual void SetLayout(const BufferLayout& layout) override {m_Layout = layout;}
private:
  BufferLayout m_Layout;
  uint32_t m_RendererID;
};

class GLIndexBuffer : public IndexBuffer
{
public:
  GLIndexBuffer(const IndexBufferSpecification& spec);
  virtual ~GLIndexBuffer() override;

  virtual void Bind() const override;
  virtual void UnBind() const override;

  inline virtual uint32_t GetCount() const override{return m_Count;};
private:
  uint32_t m_RendererID;
  uint32_t m_Count;
};

}

}
