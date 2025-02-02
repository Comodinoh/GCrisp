#include <gcpch.h>

#include "AssetsManager.h"
#include <GCrisp/Core/Application.h>

#include <stb_image.h>

namespace GCrisp {

Reference<Graphics::Texture> AssetsManager::s_DefaultTexture = nullptr;


AssetsManager::AssetsManager()
{
  LoadTexture2D("textures/default_texture.png");
  s_DefaultTexture = FetchTexture2D("textures/default_texture.png");
}

AssetsManager::~AssetsManager()
{
  s_DefaultTexture.reset();
}

void AssetsManager::LoadTexture2D(const std::string& name) 
{
  std::string path = "assets/" + name;
  int width, height;
  int channels;

  stbi_set_flip_vertically_on_load(1);

  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  GC_CORE_ASSERT(data, "Failed to load image!");

  Reference<Graphics::Texture2D> texture = std::shared_ptr<Graphics::Texture2D>(GCrisp::Application::Get().GetGraphicsCreator()->CreateTexture2D(data, {(uint32_t)width, (uint32_t)height, (uint32_t)channels}));

  m_CachedTextures[path] = texture;
}

void AssetsManager::LoadRawTexture2D(const std::string& name, const stbi_uc* data, const Graphics::TextureSpec& spec)
{
  GC_CORE_ASSERT(data, "Provided null image to load!");
  m_CachedRawTextures[name] = std::shared_ptr<Graphics::Texture2D>(GCrisp::Application::Get().GetGraphicsCreator()->CreateTexture2D(data, spec));
}

Reference<Graphics::Texture>& AssetsManager::FetchTexture(const std::string& path) const
{
  auto iter = m_CachedTextures.find(std::string("assets/" + path));
  if(iter == m_CachedTextures.end()) 
  {
    return s_DefaultTexture;
  }
  return iter->second;
}

Reference<Graphics::Texture>& AssetsManager::FetchRawTexture(const std::string& name) const
{
  auto iter = m_CachedRawTextures.find(name);
  if(iter == m_CachedRawTextures.end())  
  {
    return s_DefaultTexture;
  }
  return iter->second;
}


}

