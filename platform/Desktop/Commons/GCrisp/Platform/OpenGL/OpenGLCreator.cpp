#include "OpenGLCreator.h"
#include "OpenGLBuffer.h"
#include "OpenGLAPI.h"

#include <GCrisp/Renderer/Buffer.h>

namespace gcrisp{

namespace Graphics{

API* OpenGLCreator::CreateAPI()
{
  return new OpenGLAPI();
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
