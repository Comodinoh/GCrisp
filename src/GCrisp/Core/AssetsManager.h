#pragma once

#include <GCrisp/Renderer/Texture.h>
#include <GCrisp/Renderer/Shader.h>

namespace GCrisp{

using stbi_uc = unsigned char;

class AssetsManager
{
public:

public:
  AssetsManager();
  ~AssetsManager();

  // Texture loading/fetching
  void LoadTexture2D(const std::string& path);
  void LoadRawTexture2D(const std::string& name, const unsigned char* data, const Graphics::TextureSpec& spec);

  inline Reference<Graphics::Texture2D>& FetchTexture2D(const std::string& name) const {return (Reference<Graphics::Texture2D>&)FetchTexture(name);}
  Reference<Graphics::Texture>& FetchTexture(const std::string& name) const;


  inline Reference<Graphics::Texture2D>& FetchRawTexture2D(const std::string& name) const {return (Reference<Graphics::Texture2D>&)FetchRawTexture(name);}
  Reference<Graphics::Texture>& FetchRawTexture(const std::string& name) const;

  // Shader loading/fetching
  void LoadShader(const std::string& path);
  Reference<Graphics::Shader>& FetchShader(const std::string& name) const;

private:
  mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedTextures;
  mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedRawTextures;

  mutable std::unordered_map<std::string, Reference<Graphics::Shader>>  m_CachedShaders;
  
  static Reference<Graphics::Texture> s_DefaultTexture;
};

}
