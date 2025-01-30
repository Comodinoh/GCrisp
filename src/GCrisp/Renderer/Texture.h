#pragma once

namespace GCrisp{

namespace Graphics{

struct TextureSpec{
  uint32_t Width, Height;
  uint32_t channels;
};

class Texture
{
public:
  virtual ~Texture() = default;

  inline const TextureSpec& GetSpec() const {return m_Spec;}

  virtual void Bind() const = 0;
protected:
  TextureSpec m_Spec;
};

class Texture2D : public Texture
{
};


}

}
