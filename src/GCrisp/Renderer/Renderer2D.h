#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <glm/glm.hpp>

#include "Texture.h"

namespace GCrisp::Graphics
{
    struct RendererProp;
}

namespace GCrisp
{
    namespace Graphics2D
    {
        struct QuadVertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 TexCoord;
            float TextureID;
        };

        struct Data
        {
            Reference<Graphics::VertexArray> QuadVA;
            Reference<Graphics::VertexBuffer> QuadVB;
            AssetID TextureShader;

            QuadVertex* Vertices;
            QuadVertex* CurrentVertex;

            AssetID* TextureSlots = nullptr;
            AssetID WhiteTexture;

            uint32_t QuadIndexCount = 0;
            int TextureSlotCount = 1;
            uint32_t DrawCalls = 0;

            uint32_t MaxVertexCount = 0;
            uint32_t MaxIndexCount = 0;
            uint32_t MaxQuadCount = 0;
        };

        struct Renderer2DProp
        {
            uint32_t MaxQuadCount = 1000;
        };

        void Init(const Graphics::RendererProp& prop);
        void Shutdown();

        void BeginRender(Graphics::Camera& camera);
        void EndRender();
        void Flush();
      
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){DrawQuad({position.x, position.y, 0}, size, color);}

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const AssetID& texture, const glm::vec4& tint);
        inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const AssetID& texture) {DrawQuad(position, size, texture, {1.0f, 1.0f, 1.0f, 1.0f});}
        inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const AssetID& texture, const glm::vec4& tint) {DrawQuad({position.x, position.y, 0.0f}, size, texture, tint);}
        inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const AssetID& texture){DrawQuad({position.x, position.y, 0}, size, texture);}

        static Data* s_Data;
    }
}
