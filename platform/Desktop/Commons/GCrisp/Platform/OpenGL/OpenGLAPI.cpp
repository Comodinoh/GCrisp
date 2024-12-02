#include "OpenGLAPI.h"

#include "GCrisp/Renderer/Renderer.h"

namespace GCrisp{

namespace Graphics{

void OpenGLAPI::Init()
{
  s_RendererBackend = Backend::OpenGL;
}

GLenum OpenGLAPI::FromShaderDataTypeToOpenGLType(ShaderDataType type) const
{
  switch(type)
  {
    case ShaderDataType::Float:   return GL_FLOAT;
    case ShaderDataType::Float2:  return GL_FLOAT;
    case ShaderDataType::Float3:  return GL_FLOAT;
    case ShaderDataType::Float4:  return GL_FLOAT;
    case ShaderDataType::Mat3:    return GL_FLOAT;
    case ShaderDataType::Mat4:    return GL_FLOAT;
    case ShaderDataType::Int:     return GL_INT;
    case ShaderDataType::Int2:    return GL_INT;
    case ShaderDataType::Int3:    return GL_INT;
    case ShaderDataType::Int4:    return GL_INT;
    case ShaderDataType::Bool:    return GL_BOOL;
  }
  
  GC_CORE_ASSERT(false, "Unknown ShaderDataType for OpenGL data type conversion!");
  return 0;
}

}

}
