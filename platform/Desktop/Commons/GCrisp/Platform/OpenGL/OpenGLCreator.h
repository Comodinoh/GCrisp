#pragma once

#include <GCrisp/Renderer/Creator.h>

namespace GCrisp
{
    namespace Graphics
    {
        class OpenGLCreator : public Creator
        {
        public:
            virtual API* CreateAPI() override;

            virtual Shader* CreateShader(const ShaderSpec& spec) override;
            virtual VertexBuffer* CreateVertexBuffer(const VertexBufferSpec& spec) override;
            virtual IndexBuffer* CreateIndexBuffer(const IndexBufferSpec& spec) override;
            virtual VertexArray* CreateVertexArray() override;
            virtual Texture2D* CreateTexture2D(const stbi_uc* data, const TextureSpec& spec) override;
        };
    }
}
