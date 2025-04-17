#pragma once
#include "GCrisp/Core/UUID.h"

namespace GCrisp
{
    using AssetID = UUID;

    enum class AssetType
    {
        Unknown = 0, Texture2D, Shader
    };

    static std::string_view StringFromAssetType(AssetType type)
    {
        switch (type)
        {
        case AssetType::Texture2D:
            {
                return "Texture2D";
            }
        case AssetType::Shader:
            {
                return "Shader";
            }
        default:
            {
                return "Unknown";
            };
        }
    }

    struct AssetMetadata
    {
        AssetType Type;
        std::string Path;
    };

    class Asset
    {
    public:
        virtual ~Asset() = default;

        virtual AssetType GetType() const = 0;

        virtual bool operator==(const Asset& rhs) const
        {
            return m_ID == rhs.GetID();
        }

        inline AssetID GetID() const { return m_ID; }
        inline bool HasValidID() const {return m_ID != 0;}

        inline void SetID(AssetID newID) {m_ID = newID;}
    protected:
        AssetID m_ID = UUID(0);
    };
}
