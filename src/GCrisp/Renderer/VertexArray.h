#pragma once

#include "Buffer.h"

namespace GCrisp{

namespace Graphics{

class VertexArray
{
public:
  virtual ~VertexArray() = default;

  virtual void Bind()   const = 0;
  virtual void UnBind() const = 0;

  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer)   = 0;
};


}

}
