#include <gcpch.h>

#include "AssetsManager.h"
#include <GCrisp/Core/Application.h>

#include <stb_image.h>

namespace GCrisp
{
    Reference<Graphics::Texture> AssetsManager::s_DefaultTexture = nullptr;

    AssetsManager::~AssetsManager()
    {
        s_DefaultTexture.reset();
    }

    void AssetsManager::Init()
    {
        LoadTexture2D("default_texture.png");
        LoadShader("Texture.glsl");

        s_DefaultTexture = FetchTexture2D("default_texture.png");
    }


    void AssetsManager::LoadTexture2D(const std::string& name)
    {
        std::string path = "assets/textures/" + name;
        int width, height;
        int channels;

        stbi_set_flip_vertically_on_load(1);

        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GC_CORE_ASSERT(data, "Failed to load image!");

        Reference<Graphics::Texture2D> texture = std::shared_ptr<Graphics::Texture2D>(
            GCrisp::Application::Get().GetGraphicsCreator()->CreateTexture2D(data,
                                                                             {
                                                                                 (uint32_t)width, (uint32_t)height,
                                                                                 (uint32_t)channels
                                                                             }));

        m_CachedTextures[name] = texture;
    }

    void AssetsManager::LoadRawTexture2D(const std::string& name, const stbi_uc* data,
                                         const Graphics::TextureSpec& spec)
    {
        GC_CORE_ASSERT(data, "Provided null image to load!");
        m_CachedRawTextures[name] = std::shared_ptr<Graphics::Texture2D>(
            GCrisp::Application::Get().GetGraphicsCreator()->CreateTexture2D(data, spec));
    }

    Reference<Graphics::Texture>& AssetsManager::FetchTexture(const std::string& path) const
    {
        auto iter = m_CachedTextures.find(path);
        if (iter == m_CachedTextures.end())
        {
            return s_DefaultTexture;
        }
        return iter->second;
    }

    Reference<Graphics::Texture>& AssetsManager::FetchRawTexture(const std::string& name) const
    {
        auto iter = m_CachedRawTextures.find(name);
        if (iter == m_CachedRawTextures.end())
        {
            return s_DefaultTexture;
        }
        return iter->second;
    }

    void AssetsManager::LoadShader(const std::string& name)
    {
        std::string path = "assets/shaders/" + name;
        std::ifstream file;

        file.open(path, std::iostream::openmode::_S_in | std::iostream::openmode::_S_bin);
        if (!file.is_open())
        {
            GC_CORE_ERROR("Could not open file '{0}'", path);
            return;
        }

        std::string source;
        uint32_t size;

        file.seekg(0, std::ios::end);
        size = file.tellg();

        source.resize(size);

        file.seekg(0, std::ios::beg);

        file.read(&source[0], size);

        Reference<Graphics::Shader> shader;
        if (path.ends_with(".glsl"))
        {
            std::pair<Graphics::ShaderType, std::string> pairs[3];

            const char* token = "//type";
            size_t tokenL = strlen(token);
            size_t pos = source.find(token, 0);
            int i = 0;
            int size = 0;
            while (pos != std::string::npos)
            {
                size++;

                const char* cr;
#if defined(GC_WIN32)
                cr = "\r\n";
#elif defined(GC_POSIX)
                cr = "\n";
#endif
                size_t eol = source.find_first_of(cr, pos);
                size_t start = pos + tokenL + 1;
                std::string type = source.substr(start, eol - start);
                Graphics::ShaderType formattedType = Graphics::ShaderTypeFromString(type);

                size_t nextPos = source.find_first_not_of(cr, eol);
                GC_CORE_ASSERT(nextPos != std::string::npos, "Encountered syntax error!");
                pos = source.find(token, nextPos);

                pairs[i] = {
                    formattedType,
                    (pos == std::string::npos) ? source.substr(nextPos) : source.substr(nextPos, pos - nextPos)
                };
                i++;
            }
            shader.reset(Application::Get().GetGraphicsCreator()->CreateShader({pairs, size}));
        }
        else
        {
            if (path.ends_with(".vert"))
            {
                shader.reset(Application::Get().GetGraphicsCreator()->CreateShader(
                    {
                        {Graphics::SHADER_VERTEX, source}
                    }
                ));
            }
            else if (path.ends_with(".frag"))
            {
                shader.reset(Application::Get().GetGraphicsCreator()->CreateShader(
                    {
                        {Graphics::SHADER_FRAGMENT, source}
                    }
                ));
            }
            else
            {
                GC_CORE_ERROR(
                    "Could not identify shader called '{0}' with no correct extension! ('.glsl', '.vert', '.frag')");
                GC_ASSERT(false, "Error while loading shader!");
            }
        }

        m_CachedShaders[name] = shader;

        file.close();
    }

    Reference<Graphics::Shader>& AssetsManager::FetchShader(const std::string& name) const
    {
        auto iter = m_CachedShaders.find(name);
        if (iter == m_CachedShaders.end())
        {
            GC_CORE_ERROR("Shader named '{0}' could not be found!", name);
            GC_CORE_ASSERT(false, "Error while fetching shader!");
        }

        return iter->second;
    }
}
