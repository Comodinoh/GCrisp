#pragma once

#include "GCrisp/Renderer/Renderer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

namespace GCrisp{

namespace Graphics{


class OpenGLAPI : public API
{
public:
  virtual void Init() override; 

  virtual void Clear(const glm::vec4& color) const override;

  virtual void SetViewport(const glm::vec2& pos, const glm::vec2& size) const override;

  virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) const override;
};

}

}
