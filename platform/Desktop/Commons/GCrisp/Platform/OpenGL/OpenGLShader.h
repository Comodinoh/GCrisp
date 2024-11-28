#pragma once

#include <GCrisp/Renderer/Shader.h>

namespace GCrisp {

namespace Graphics {

class OpenGLShader : public Shader
{
public:
  OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

  virtual void Bind() const override;
  virtual void UnBind() const override;
private:
  uint32_t m_RendererID;
};

}

}
