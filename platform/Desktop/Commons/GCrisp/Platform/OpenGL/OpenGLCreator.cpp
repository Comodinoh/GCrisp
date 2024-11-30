#include <gcpch.h>
#include "OpenGLCreator.h"

#include "OpenGLAPI.h"
#include "OpenGLShader.h"
#include "OpenGLBuffer.h"

namespace GCrisp{

namespace Graphics{

API* OpenGLCreator::CreateAPI()
{
  return new OpenGLAPI();
}

Shader* OpenGLCreator::CreateShader(std::string* const vertexSrc, std::string* const fragmentSrc)
{
  return (Shader*)new OpenGLShader(vertexSrc, fragmentSrc);
}

VertexBuffer* OpenGLCreator::CreateVertexBuffer(float* vertices, uint32_t size)
{
  return new OpenGLVertexBuffer(vertices, size);
}

IndexBuffer* OpenGLCreator::CreateIndexBuffer(uint32_t* indices, uint32_t size)
{
  return new OpenGLIndexBuffer(indices, size);
}

}

}
