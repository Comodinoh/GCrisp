#pragma once

#include "Buffer.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

namespace GCrisp
{
    namespace Graphics
    {
        typedef unsigned char stbi_uc;

        class Creator
        {
        public:
            virtual API* CreateAPI() = 0;

            virtual Shader* CreateShader(const ShaderSpec& spec) = 0;
            virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) = 0;
            virtual IndexBuffer* CreateIndexBuffer(uint32_t* indices, uint32_t count) = 0;
            virtual VertexArray* CreateVertexArray() = 0;
            virtual Texture2D* CreateTexture2D(const stbi_uc* data, const TextureSpec& spec) = 0;
        };
    }
}
