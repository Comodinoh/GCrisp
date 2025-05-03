#include <gcpch.h>

#include "AssetsManager.h"
#include <GCrisp/Core/Application.h>

#include <stb_image.h>

#include "GCrisp/Core/UUID.h"

namespace GCrisp
{
AssetID AssetsManager::s_DefaultTexture = UUID();

AssetsManager::~AssetsManager()
{
	GC_PROFILE_FUNC();
	s_DefaultTexture = UUID();
}

void AssetsManager::Init()
{
	GC_PROFILE_FUNC();
	s_DefaultTexture = LoadAsset({AssetType::Texture2D, "default_texture.png"});
}

AssetMetadata& AssetsManager::FetchMetadata(const AssetID& asset)
{
	GC_PROFILE_FUNC();
	auto iter = m_AssetRegistry.find(asset);

	GC_CORE_ASSERT(iter != m_AssetRegistry.end(),
				   "Non existent asset id in registry");

	return iter->second;
}

bool AssetsManager::IsAssetValid(const AssetID& asset) const
{
	GC_PROFILE_FUNC();
	return m_AssetRegistry.find(asset) != m_AssetRegistry.end();
}

bool AssetsManager::IsAssetLoaded(const AssetID& asset) const
{
	GC_PROFILE_FUNC();
	return m_Assets.find(asset) != m_Assets.end();
}

AssetID AssetsManager::LoadAsset(const AssetMetadata& metadata)
{
	GC_PROFILE_FUNC();
	const AssetID uuid = AssetID::Generate();
	// while (IsAssetValid(uuid))
	// {
	//     GC_CORE_TRACE("AssetsManager::LoadAsset - Waiting for valid asset");
	//     uuid = AssetID();
	// }

	const Reference<Asset>& asset = ImportAsset(metadata);
	m_Assets[uuid]				  = asset;
	m_AssetRegistry[uuid]		  = metadata;

	GC_CORE_TRACE(
		"AssetsManager::LoadAsset - Loaded Asset with ID: {0}, Path: {1} and "
		"Type: {2}",
		uuid.Get(), metadata.Path, StringFromAssetType(metadata.Type));

	return uuid;
}

Reference<Asset> AssetsManager::ImportAsset(const AssetMetadata& metadata) const
{
	switch (metadata.Type) {
	case AssetType::Texture2D: {
		Graphics::Texture2D* texP = LoadTexture2D(metadata.Path);
		if (!texP) {
			return m_Assets.find(s_DefaultTexture)->second;
		}

		return std::shared_ptr<Graphics::Texture2D>(texP);
	}
	case AssetType::Shader: {
		// TODO: Add default debug shader when loaded shader isn't valid (maybe)
		// or crash the program
		return std::shared_ptr<Graphics::Shader>(LoadShader(metadata.Path));
	}
	case AssetType::Unknown: {
		GC_CORE_ASSERT(false, "Unknown asset type!");
	}
	}
	return nullptr;
}

Reference<Asset> AssetsManager::ReloadAsset(const AssetID& asset)
{
	AssetMetadata&	 metadata = FetchMetadata(asset);
	Reference<Asset> assetRef = ImportAsset(metadata);

	m_Assets[asset] = assetRef;

	return assetRef;
}

void AssetsManager::UnloadAsset(const AssetID& asset) const
{
	m_Assets.erase(asset);
}

void AssetsManager::UnloadMetadata(const AssetID& asset) const
{
	m_AssetRegistry.erase(asset);
	UnloadAsset(asset);
	AssetID::Destroy(asset);
}

void AssetsManager::FetchAssetInternal(const AssetID&	 id,
									   Reference<Asset>& asset)
{
	GC_PROFILE_FUNC();
	if (!IsAssetValid(id)) {
		asset = nullptr;
	}

	if (IsAssetLoaded(id)) {
		asset = m_Assets[id];
	} else {
		asset = ReloadAsset(id);
	}
}

Graphics::Texture2D* AssetsManager::LoadTexture2D(const std::string& name) const
{
	GC_PROFILE_FUNC();
	std::string path = "assets/textures/" + name;
	int			width, height;
	int			channels;

	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	GC_CORE_VERIFY(data, "Failed to load '{0}' image!", name);

	return Graphics::Texture2D::Create({
		data,
		{width, height},
		(uint32_t)channels
	  });
}

Graphics::Texture2D* AssetsManager::LoadRawTexture2D(
	const Graphics::TextureSpecification& spec) const
{
	GC_PROFILE_FUNC();
	GC_CORE_ASSERT(spec.Data, "Provided null image to load!");
	return Graphics::Texture2D::Create(spec);
}

Graphics::Shader* AssetsManager::LoadShader(const std::string& name) const
{
	GC_PROFILE_FUNC();
	std::string	  path = "assets/shaders/" + name;
	std::ifstream file;

	file.open(path, std::ios_base::in | std::ios_base::binary);
	if (!file.is_open()) {
		GC_CORE_ERROR("Could not open file '{0}'", path);
		return nullptr;
	}

	std::string source;
	uint32_t	size;

	file.seekg(0, std::ios::end);
	size = file.tellg();

	source.resize(size);

	file.seekg(0, std::ios::beg);

	file.read(&source[0], size);

	Graphics::Shader* shader = nullptr;
	if (path.ends_with(".glsl")) {
		std::pair<Graphics::ShaderType, std::string> pairs[3];

		const char* token  = "//type";
		size_t		tokenL = strlen(token);
		size_t		pos	   = source.find(token, 0);
		if (pos == std::string::npos) {
			GC_CORE_ERROR(
				"Could not parse shader '{0}' type. Please add '//type "
				"[shader/fragment]' at the start of your shader",
				path);
			return nullptr;
		}
		int i	  = 0;
		int sizeI = 0;
		while (pos != std::string::npos) {
			sizeI++;

			const char* cr;
#if defined(GC_WIN32)
			cr = "\r\n";
#elif defined(GC_POSIX)
			cr = "\n";
#endif
			size_t				 eol   = source.find_first_of(cr, pos);
			size_t				 start = pos + tokenL + 1;
			std::string			 type  = source.substr(start, eol - start);
			Graphics::ShaderType formattedType =
				Graphics::ShaderTypeFromString(type);

			size_t nextPos = source.find_first_not_of(cr, eol);
			GC_CORE_ASSERT(nextPos != std::string::npos,
						   "Encountered syntax error!");
			pos = source.find(token, nextPos);

			pairs[i] = {formattedType,
						(pos == std::string::npos)
							? source.substr(nextPos)
							: source.substr(nextPos, pos - nextPos)};
			i++;
		}
		shader = Graphics::Shader::Create({pairs, sizeI});
	} else {
		if (path.ends_with(".vert")) {
			shader = Graphics::Shader::Create({
				{Graphics::SHADER_VERTEX, source}
			 });
		} else if (path.ends_with(".frag")) {
			shader = Graphics::Shader::Create({
				{Graphics::SHADER_FRAGMENT, source}
			   });
		} else {
			GC_CORE_ERROR(
				"Could not identify shader called '{0}' with no correct "
				"extension! ('.glsl', '.vert', '.frag')");
			return nullptr;
		}
	}

	file.close();

	return shader;
}

Graphics::Shader*
AssetsManager::LoadShader(const Graphics::ShaderSpecification& spec) const
{
	return Graphics::Shader::Create(spec);
}
} // namespace GCrisp
