#pragma once

#include <GCrisp/Renderer/Texture.h>

namespace GCrisp{

namespace Graphics{

typedef unsigned char stbi_uc;

class OpenGLTexture : public Texture2D
{
public:
  OpenGLTexture(const stbi_uc* data, const TextureSpec& spec);
  virtual ~OpenGLTexture();

  virtual void Bind(int slot) const override;
  virtual void SetMagFiltering(TextureFilter filtering) const override;
  virtual void SetMinFiltering(TextureFilter filtering) const override;
private:
  uint32_t m_RendererID;
};

}

}
