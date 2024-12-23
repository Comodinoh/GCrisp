#pragma once

#include <glm/matrix.hpp>

namespace GCrisp{

namespace Graphics{

class Shader
{
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual void UploadMat4(const std::string& name, const glm::mat4& data) const = 0;
};

}

}
