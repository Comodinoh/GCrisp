#pragma once

#include <GCrisp/Renderer/Buffer.h>

namespace GCrisp {

namespace Graphics{

class OpenGLVertexBuffer : public VertexBuffer 
{
public:
  OpenGLVertexBuffer(const VertexBufferSpec& spec);
  virtual ~OpenGLVertexBuffer() override;

  virtual void Bind() const override;
  virtual void UnBind() const override;

  virtual void UploadSubData(uint32_t size, const void* data) override;

  virtual const BufferLayout& GetLayout() const override {return m_Layout;}
  virtual void SetLayout(const BufferLayout& layout) override {m_Layout = layout;}
private:
  BufferLayout m_Layout;
  uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
  OpenGLIndexBuffer(const IndexBufferSpec& spec);
  virtual ~OpenGLIndexBuffer() override;

  virtual void Bind() const override;
  virtual void UnBind() const override;

  inline virtual uint32_t GetCount() const override{return m_Count;};
private:
  uint32_t m_RendererID;
  uint32_t m_Count;
};

}

}
