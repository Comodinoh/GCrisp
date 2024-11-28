#pragma once

namespace GCrisp{

namespace Graphics{

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
