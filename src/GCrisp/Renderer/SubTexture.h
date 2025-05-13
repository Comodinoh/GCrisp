#pragma once

#include <GCrisp/Assets/Assets.h>
#include <GCrisp/Core/Application.h>
#include <GCrisp/Renderer/Texture.h>
#include <glm/glm.hpp>

namespace GCrisp::Graphics {
// TODO: Should we represent these as 'assets' too?
class SubTexture2D {
  public:
    SubTexture2D(const AssetID& textureID, const glm::vec2& min,
                 const glm::vec2& max);
    virtual ~SubTexture2D() = default;

    inline AssetID& GetTextureID() { return m_TextureID; }
    inline const AssetID& GetTextureID() const { return m_TextureID; }

    inline const glm::vec2* GetTextureCoords() const { return m_TexCoords; }

    static SubTexture2D* CreateFromCoords(const AssetID& textureID,
                                          const glm::vec2& pos,
                                          const glm::vec2& spriteSize) {
        Reference<Texture2D> texture =
            Application::Get().GetAssetsManager().FetchAsset<Texture2D>(
                textureID);
        const glm::vec2& textureSize = texture->GetSpec().Size;
        glm::vec2 min = {(pos.x * spriteSize.x) / textureSize.x,
                         (pos.y * spriteSize.y) / textureSize.y};
        glm::vec2 max = {((pos.x + 1) * spriteSize.x) / textureSize.x,
                         ((pos.y + 1) * spriteSize.y) / textureSize.y};
        return new SubTexture2D(textureID, min, max);
    }

  private:
    AssetID m_TextureID;

    glm::vec2 m_TexCoords[4];
};
} // namespace GCrisp::Graphics