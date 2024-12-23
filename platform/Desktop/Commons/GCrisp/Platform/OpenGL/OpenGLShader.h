#pragma once

#include <GCrisp/Renderer/Shader.h>

namespace GCrisp {

namespace Graphics {

class OpenGLShader : public Shader
{
public:
  OpenGLShader(const std::string* const vertexSrc, const std::string* const fragmentSrc);
  virtual ~OpenGLShader();

  virtual void Bind() const override;
  virtual void UnBind() const override;

  virtual void UploadMat4(const std::string& name, const glm::mat4& data) const override;
  virtual void UploadVec3(const std::string& name, const glm::vec3& data) const override;
  virtual void UploadVec4(const std::string& name, const glm::vec4& data) const override;
private:
  uint32_t m_RendererID;
};

}

}
