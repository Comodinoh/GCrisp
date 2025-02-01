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
  virtual void UploadMat3(const std::string& name, const glm::mat3& data) const = 0;
  virtual void UploadVec4(const std::string& name, const glm::vec4& data) const = 0;
  virtual void UploadVec3(const std::string& name, const glm::vec3& data) const = 0;
  virtual void UploadInt(const std::string& name, int data)               const = 0;
  virtual void UploadFloat(const std::string& name, float data)           const = 0;
  virtual void UploadBool(const std::string& name, bool data)             const = 0;
};

}

}
