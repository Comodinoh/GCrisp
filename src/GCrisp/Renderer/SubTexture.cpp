#include "SubTexture.h"
#include <GCrisp/Core/Application.h>

namespace GCrisp::Graphics
{
SubTexture2D::SubTexture2D(const AssetID& textureID, const glm::vec2& min,
						   const glm::vec2& max)
	: m_TextureID(textureID)
{
	m_TexCoords[0] = {min.x, min.y};
	m_TexCoords[1] = {max.x, min.y};
	m_TexCoords[2] = {max.x, max.y};
	m_TexCoords[3] = {min.x, max.y};
}

/*SubTexture2D* SubTexture2D::CreateFromCoords(const AssetID& textureID, const
glm::vec2& pos, const glm::vec2& spriteSize)
{
	Reference<Texture2D> texture =
Application::Get().GetAssetsManager().FetchAsset<Texture2D>(textureID); const
glm::vec2& textureSize = texture->GetSpec().Size; glm::vec2 min = { (pos.x *
spriteSize.x) / textureSize.x, (pos.y * spriteSize.y) / textureSize.y };
	glm::vec2 max = { ((pos.x + 1) * spriteSize.x) / textureSize.x, ((pos.y + 1)
* spriteSize.y) / textureSize.y }; return new SubTexture2D(textureID, min, max);
}*/
} // namespace GCrisp::Graphics
