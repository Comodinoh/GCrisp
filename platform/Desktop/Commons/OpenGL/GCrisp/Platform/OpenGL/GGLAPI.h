#pragma once

#include "GCrisp/Renderer/Renderer.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"

namespace GCrisp {
namespace Graphics {
class GLAPI : public API {
  public:
    virtual void Init() override;

    virtual void Clear(const glm::vec4& color) const override;

    virtual void SetViewport(const glm::vec2& pos,
                             const glm::vec2& size) const override;

    virtual void
    DrawIndexed(const Reference<VertexArray>& vertexArray) const override;

    virtual void DrawIndexed(uint32_t count) const override;
};
} // namespace Graphics
} // namespace GCrisp
