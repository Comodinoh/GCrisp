#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <glm/glm.hpp>

#include "Texture.h"

namespace GCrisp
{
    namespace Graphics2D
    {
        struct Data
        {
            Reference<Graphics::VertexArray> QuadVA;
            Reference<Graphics::Shader> ColorShader;
            Reference<Graphics::Shader> TextureShader;
        };

        void Init();
        void Shutdown();

        void BeginRender(Graphics::Camera& camera);
        void EndRender();

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad({position.x, position.y, 0}, size, color);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Graphics::Texture>& texture);

        inline void DrawQuad(const glm::vec2& position, const glm::vec2& size,
                             const Reference<Graphics::Texture>& texture)
        {
            DrawQuad({position.x, position.y, 0}, size, texture);
        }


        static Data* s_Data;
    }
}
