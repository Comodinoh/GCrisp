#pragma once

#include <GCrisp/Renderer/Texture.h>

namespace GCrisp{

namespace Graphics{

typedef unsigned char stbi_uc;

class OpenGLTexture2D : public Texture2D
{
public:
  OpenGLTexture2D(const stbi_uc* data, const TextureSpec& spec);
  virtual ~OpenGLTexture2D();

  virtual void Bind() const override;
  virtual void SetMagFiltering(TextureFilter filtering) const override;
  virtual void SetMinFiltering(TextureFilter filtering) const override;
private:
  uint32_t m_RendererID;
};

}

}
