#pragma once

#include <GCrisp/Renderer/Texture.h>

namespace GCrisp{

using stbi_uc = unsigned char;

class AssetsManager
{
public:

public:
  AssetsManager();
  ~AssetsManager();

  void LoadTexture2D(const std::string& path);
  void LoadRawTexture2D(const std::string& name, const unsigned char* data, const Graphics::TextureSpec& spec);

  inline Reference<Graphics::Texture2D>& FetchTexture2D(const std::string& name) const {return (Reference<Graphics::Texture2D>&)FetchTexture(name);}
  Reference<Graphics::Texture>& FetchTexture(const std::string& name) const;


  inline Reference<Graphics::Texture2D>& FetchRawTexture2D(const std::string& name) const {return (Reference<Graphics::Texture2D>&)FetchRawTexture(name);}
  Reference<Graphics::Texture>& FetchRawTexture(const std::string& name) const;
private:
  mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedTextures;
  mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedRawTextures;
  
  static Reference<Graphics::Texture> s_DefaultTexture;
};

}
