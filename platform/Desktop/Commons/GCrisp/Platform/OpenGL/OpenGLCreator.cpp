#include "OpenGLCreator.h"
#include "OpenGLBuffer.h"
#include "OpenGLAPI.h"

#include <GCrisp/Renderer/Buffer.h>

namespace GCrisp{

namespace Graphics{

API* OpenGLCreator::CreateAPI()
{
  return new OpenGLAPI();
}

Shader* OpenGLCreator::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
  // TODO: Implement shader opengl code
  return nullptr;
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
