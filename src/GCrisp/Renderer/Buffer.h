#pragma once

namespace GCrisp{

namespace Graphics{

enum class ShaderDataType : uint8_t
{
  None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool,


};

struct BufferElement
{
  std::string    Name;
  ShaderDataType Type;
  uint32_t       Offset;
  uint32_t       Size;
  uint8_t        Count;

  BufferElement(const std::string& name, ShaderDataType& type) : Name(name), Type(type), Size(GetDataTypeSize(type)), Offset(0), Count(GetElementCount(type))
  {
  }

  static uint32_t GetDataTypeSize(ShaderDataType& type)
  {
    switch(type)
    {
      case ShaderDataType::Float:  return 4;
      case ShaderDataType::Float2: return 4*2;
      case ShaderDataType::Float3: return 4*3;
      case ShaderDataType::Float4: return 4*4;
      case ShaderDataType::Mat3:   return 4*3*3;
      case ShaderDataType::Mat4:   return 4*4*4;
      case ShaderDataType::Int:    return 4;
      case ShaderDataType::Int2:   return 4*2;
      case ShaderDataType::Int3:   return 4*3;
      case ShaderDataType::Int4:   return 4*4;
      case ShaderDataType::Bool:   return 1;
    }

    GC_CORE_ASSERT(false, "Unknownw ShaderDataType!");
    return 0;
  }
  static uint32_t GetElementCount(ShaderDataType& type)
  {
    switch(type)
    { 
      case ShaderDataType::Float:  return 1;
      case ShaderDataType::Float2: return 2;
      case ShaderDataType::Float3: return 3;
      case ShaderDataType::Float4: return 4;
      case ShaderDataType::Mat3:   return 3*3;
      case ShaderDataType::Mat4:   return 4*4;
      case ShaderDataType::Int:    return 1;
      case ShaderDataType::Int2:   return 2;
      case ShaderDataType::Int3:   return 3;
      case ShaderDataType::Int4:   return 4;
      case ShaderDataType::Bool:   return 1; 
    }

    GC_CORE_ASSERT(false, "Unknownw ShaderDataType!");
    return 0;
  }
};

class BufferLayout
{
public:
  BufferLayout(std::initializer_list<BufferElement>& bufferElements) : m_Elements(bufferElements)
  {
  }

  inline const std::vector<BufferElement>& GetElements() const {return m_Elements;}
private:
  std::vector<BufferElement> m_Elements;
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
