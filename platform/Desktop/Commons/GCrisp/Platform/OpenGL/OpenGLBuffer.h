#pragma once

#include <GCrisp/Renderer/Buffer.h>

namespace GCrisp {

namespace Graphics{

class OpenGLVertexBuffer : public VertexBuffer 
{
public:
  OpenGLVertexBuffer(float* vertices, uint32_t size);
  virtual ~OpenGLVertexBuffer();

  virtual void Bind() const override;
  virtual void UnBind() const override;

  virtual const BufferLayout& GetLayout() const override {return m_Layout;}
  virtual void SetLayout(const BufferLayout& layout) override {m_Layout = layout;}
private:
  BufferLayout m_Layout;
  uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
  OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
  virtual ~OpenGLIndexBuffer();

  virtual void Bind() const override;
  virtual void UnBind() const override;

  inline virtual uint32_t GetCount() const override{return m_Count;};
private:
  uint32_t m_RendererID;
  uint32_t m_Count;
};

}

} // namespace gcrisp
