#pragma once

namespace GCrisp{

namespace Graphics{

class Shader
{
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
};

}

}
