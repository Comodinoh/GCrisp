#pragma once

#include "Buffer.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"

namespace GCrisp{

namespace Graphics{

class Creator
{
public:
  virtual API*          CreateAPI() = 0;

  virtual Shader*       CreateShader(std::string* const vertexSrc, std::string* const fragmentSrc) = 0;
  virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size)                         = 0;
  virtual IndexBuffer*  CreateIndexBuffer(uint32_t* indices, uint32_t count)                       = 0;
  virtual VertexArray*  CreateVertexArray()                                                        = 0;

};

}

}
