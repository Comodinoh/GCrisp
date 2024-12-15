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
  bool           Normalized;

  BufferElement() = default;
  BufferElement(const std::string& name, const ShaderDataType& type, bool normalized = false) : 
    Name(name), Type(type), Size(GetDataTypeSize(type)), Offset(0), Count(GetElementCount(type)), Normalized(normalized)
  {
  }

  static uint32_t GetDataTypeSize(const ShaderDataType& type)
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

    GC_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
  static uint32_t GetElementCount(const ShaderDataType& type)
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

    GC_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
};

class BufferLayout
{
public:
  BufferLayout() = default;
  BufferLayout(std::initializer_list<BufferElement> bufferElements) : m_Elements(bufferElements)
  {
    CalculateStride();
  }

  const std::vector<BufferElement>& GetElements() const {return m_Elements;}
  inline uint32_t GetStride() const {return m_Stride;}
private:
  void CalculateStride()
  {
    uint32_t offset = 0;
    m_Stride = 0;
    for(BufferElement& element : m_Elements)
    {
      element.Offset = offset;
      offset += element.Size;
      m_Stride += element.Size;
    }
  }
private:
  std::vector<BufferElement> m_Elements;
  uint32_t m_Stride = 0;
};

class VertexBuffer  
{
public:
  virtual ~VertexBuffer() = default;

  virtual void Bind()   const = 0;
  virtual void UnBind() const = 0;

  virtual const BufferLayout& GetLayout() const = 0;
  virtual void SetLayout(const BufferLayout& layout) = 0;
};

class IndexBuffer 
{
public:
  virtual ~IndexBuffer() = default;

  virtual void Bind()   const = 0;
  virtual void UnBind() const = 0;
};

}

}
