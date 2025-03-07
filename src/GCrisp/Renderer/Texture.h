#pragma once
#include "GCrisp/Assets/Assets.h"

namespace GCrisp
{
    namespace Graphics
    {
        struct TextureSpec
        {
            uint32_t Width, Height;
            uint32_t channels;
        };

        enum class TextureFilter
        {
            None = 0, Nearest, Linear
        };

        class Texture : public Asset
        {
        public:
            virtual ~Texture() = default;

            inline const TextureSpec& GetSpec() const { return m_Spec; }

            virtual void Bind(int slot = 0) const = 0;

            virtual void SetMagFiltering(TextureFilter filtering) const = 0;
            virtual void SetMinFiltering(TextureFilter filtering) const = 0;

            virtual AssetType GetType() const override {return AssetType::Texture2D;};
        protected:
            TextureSpec m_Spec;
        };

        class Texture2D : public Texture
        {
        };
    }
}
