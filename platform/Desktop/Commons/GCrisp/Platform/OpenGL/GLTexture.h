#pragma once

#include <GCrisp/Renderer/Texture.h>

namespace GCrisp
{
namespace Graphics
{
typedef unsigned char stbi_uc;

class GLTexture2D : public Texture2D
{
  public:
	GLTexture2D(const TextureSpecification& spec);
	virtual ~GLTexture2D();

	virtual void Bind(int slot) const override;
	virtual void SetMagFiltering(TextureFilter filtering) const override;
	virtual void SetMinFiltering(TextureFilter filtering) const override;

  private:
	uint32_t m_RendererID;
};
} // namespace Graphics
} // namespace GCrisp
