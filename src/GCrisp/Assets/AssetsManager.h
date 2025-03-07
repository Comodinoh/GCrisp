#pragma once

#include <GCrisp/Renderer/Texture.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Assets/Assets.h>



namespace GCrisp
{
    using stbi_uc = unsigned char;

    class AssetsManager
    {
    public:
        AssetsManager() = default;
        ~AssetsManager();

        static AssetID GetDefaultTexture() {return s_DefaultTexture;}

        void Init();

        template<class T>
        inline Reference<T> FetchAsset(const AssetID& asset)
        {
            Reference<Asset> ref;
            FetchAssetInternal(asset, ref);
            return std::static_pointer_cast<T>(ref);
        }
        AssetMetadata& FetchMetadata(const AssetID& asset);

        bool IsAssetValid(const AssetID& asset) const;
        bool IsAssetLoaded(const AssetID& asset) const;

        AssetID LoadAsset(const AssetMetadata& metadata);
        Reference<Asset> ImportAsset(const AssetMetadata& metadata) const;

        Reference<Asset> ReloadAsset(const AssetID& asset);

        void UnloadAsset(const AssetID& asset) const;
        void UnloadMetadata(const AssetID& asset) const;

        Graphics::Texture2D* LoadTexture2D(const std::string& path) const;
        Graphics::Texture2D* LoadRawTexture2D(const unsigned char* data, const Graphics::TextureSpec& spec) const;

        Graphics::Shader* LoadShader(const std::string& path) const;
        Graphics::Shader* LoadShader(const Graphics::ShaderSpec& spec) const;
    private:
        void FetchAssetInternal(const AssetID& id, Reference<Asset>& asset);
    private:
        mutable std::unordered_map<AssetID, AssetMetadata> m_AssetRegistry;
        mutable std::unordered_map<AssetID, Reference<Asset>> m_Assets;
        //
        // mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedTextures;
        // mutable std::unordered_map<std::string, Reference<Graphics::Texture>> m_CachedRawTextures;
        //
        // mutable std::unordered_map<std::string, Reference<Graphics::Shader>> m_CachedShaders;

        static AssetID s_DefaultTexture;
    };


}
