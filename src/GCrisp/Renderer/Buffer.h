#pragma once

namespace gcrisp{

namespace Graphics{

class VertexBuffer  
{
public:
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

};

class IndexBuffer 
{
public:
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
};

}

}
