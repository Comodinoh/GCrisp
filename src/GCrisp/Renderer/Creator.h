#pragma once

#include "Buffer.h"
#include "GCrisp/Renderer/Renderer.h"

namespace gcrisp{

namespace Graphics{

class Creator
{
public:
  virtual Graphics::API* CreateAPI() = 0;
  virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) = 0;
  virtual IndexBuffer*  CreateIndexBuffer(uint32_t* indices, uint32_t size) = 0;
};

}

}
