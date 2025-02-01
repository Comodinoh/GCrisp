#pragma once

namespace GCrisp{

namespace Graphics{

struct TextureSpec{
  uint32_t Width, Height;
  uint32_t channels;
};

enum class TextureFilter
{
  None = 0, Nearest, Linear
};

class Texture
{
public:
  virtual ~Texture() = default;

  inline const TextureSpec& GetSpec() const {return m_Spec;}

  virtual void Bind() const = 0;

  virtual void SetMagFiltering(TextureFilter filtering) const = 0;
  virtual void SetMinFiltering(TextureFilter filtering) const = 0;
protected:
  TextureSpec m_Spec;
};

class Texture2D : public Texture
{
};


}

}
