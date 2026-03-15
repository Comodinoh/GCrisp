#pragma once
#include <Vane/Renderer/Creator.h>

namespace Vane {
namespace Graphics {
class VKCreator : public Creator {
  public:
    virtual API* CreateAPI() override;

    virtual Shader* CreateShader(const ShaderSpecification& spec) override;
    virtual VertexBuffer*
    CreateVertexBuffer(const VertexBufferSpecification& spec) override;
    virtual IndexBuffer*
    CreateIndexBuffer(const IndexBufferSpecification& spec) override;
    virtual VertexArray* CreateVertexArray() override;
    virtual Texture2D*
    CreateTexture2D(const stbi_uc* data,
                    const TextureSpecification& spec) override;
};
} // namespace Graphics
} // namespace Vane
