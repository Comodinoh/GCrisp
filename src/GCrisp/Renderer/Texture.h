#pragma once

#include "GraphicsCore.h"
#include <GCrisp/Assets/Assets.h>
#include <glm/glm.hpp>
#include <stb_image.h>
// using namespace GCrisp::Graphics;

namespace GCrisp::Graphics {
struct TextureSpecification {
    stbi_uc* Data;
    glm::vec2 Size;
    uint32_t channels;
};

enum class TextureFilter { None = 0, Nearest, Linear };

class Texture : public Asset {
  public:
    virtual ~Texture() = default;

    inline const TextureSpecification& GetSpec() const { return m_Spec; }

    virtual void Bind(int slot = 0) const = 0;

    virtual void SetMagFiltering(TextureFilter filtering) const = 0;
    virtual void SetMinFiltering(TextureFilter filtering) const = 0;

    virtual AssetType GetType() const override { return AssetType::Texture2D; };

  protected:
    TextureSpecification m_Spec;
};

class Texture2D : public Texture {
  public:
    GC_GRAPHICS_CREATE_DECL_WITH_SPEC2(Texture2D, Texture)
};
} // namespace GCrisp::Graphics
