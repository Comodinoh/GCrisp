#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/SubTexture.h>
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

        struct QuadProp
        {
            QuadProp(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& tint = { 1.0f, 1.0f, 1.0f, 1.0f }) : Position(pos), Size(size), Tint(tint) {}
            QuadProp(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& tint = { 1.0f, 1.0f, 1.0f, 1.0f }) : Position(pos.x, pos.y, 0.0f), Size(size), Tint(tint) {}

            glm::vec3 Position;
            glm::vec2 Size;
            glm::vec4 Tint;
        };

        void Init(const Graphics::RendererProp& prop);
        void Shutdown();

        void BeginRender(Graphics::Camera& camera);
        void EndRender();
        void Flush();
      
        void DrawQuad(const QuadProp& prop);

        /*
        * Draws a textured quad 
        */
        void DrawQuadT(const QuadProp& prop, const AssetID& texture);

        /*
        * Draws a quad textured from a sub texture region
        */
        void DrawQuadST(const QuadProp& prop, const Reference<Graphics::SubTexture2D>& subTexture);


        static Data* s_Data;
    }
}
