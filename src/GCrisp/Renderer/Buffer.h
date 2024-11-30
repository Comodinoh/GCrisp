#pragma once

namespace GCrisp{

namespace Graphics{

enum class ShaderDataType
{
  None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool

};

struct BufferElements
{
  std::string Name;
  ShaderDataType Type;
  size_t Offset;
  size_t Size;

  BufferElements(const std::string& name, ShaderDataType& type) : Name(name), Type(type), Size(0), Offset(0)
  {
  }
};

class BufferLayout
{
public:
  inline const std::vector<BufferElements>& GetElements() const {return m_Elements;}
private:
  std::vector<BufferElements> m_Elements;
};

class VertexBuffer  
{
public:
  virtual ~VertexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

};

class IndexBuffer 
{
public:
  virtual ~IndexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
};

}

}
