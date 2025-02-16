#include "gcpch.h"

#include "Renderer2D.h"

#include <GCrisp/Core/Application.h>

#include "Renderer.h"
#include "Buffer.h"
#include <glm/glm.hpp>

namespace GCrisp
{
    namespace Graphics2D
    {
        void Init()
        {
            GC_PROFILE_FUNC();
            s_Data = new Data();

            auto& app = Application::Get();
            s_Data->QuadVA.reset(app.GetGraphicsCreator()->CreateVertexArray());
            s_Data->QuadVA->Bind();

            float quadVerts[] = {
                /* 0.0,  0.5, 0.0,*/
                /* 0.5, -0.5, 0.0,*/
                /*-0.5, -0.5, 0.0*/
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
            };

            Reference<Graphics::VertexBuffer> quadVB;
            quadVB.reset(app.GetGraphicsCreator()->CreateVertexBuffer(quadVerts, sizeof(quadVerts)));

            quadVB->SetLayout(
                {
                    {"a_Position", Graphics::ShaderDataType::Float3},
                    {"a_TexCoord", Graphics::ShaderDataType::Float2}
                }
            );
            s_Data->QuadVA->AddVertexBuffer(quadVB);

            uint32_t quadIndices[] = {
                0, 1, 2,
                2, 3, 0,
            };

            Reference<Graphics::IndexBuffer> quadIB;
            quadIB.reset(app.GetGraphicsCreator()->CreateIndexBuffer(quadIndices, sizeof(quadIndices)));
            s_Data->QuadVA->SetIndexBuffer(quadIB);

            s_Data->TextureShader = app.GetAssetsManager().FetchShader("Texture.glsl");
            //
            // constexpr unsigned char whitePixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};
            // app.GetAssetsManager().LoadRawTexture2D("WhiteTexture", whitePixel, {1, 1, 4});

            app.GetAssetsManager().LoadTexture2D("WhiteTexture.png");

            s_Data->WhiteTexture = app.GetAssetsManager().FetchTexture("WhiteTexture.png");
        }

        void Shutdown()
        {
            GC_PROFILE_FUNC();
            delete s_Data;
        }

        void BeginRender(Graphics::Camera& camera)
        {
            s_Data->TextureShader->Bind();
            s_Data->TextureShader->UploadMat4("u_ViewProj", camera.GetViewProj());
        }

        void EndRender()
        {
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            //TODO: implement shader bound checking system
            s_Data->TextureShader->UploadVec4("u_Color", color);

            s_Data->WhiteTexture->Bind();
            s_Data->TextureShader->UploadInt("u_Texture", 0);

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(
                glm::mat4(1.0f), {size.x, size.y, 1.0f});
            s_Data->TextureShader->UploadMat4("u_Transform", transform);

            s_Data->QuadVA->Bind();
            Graphics::DrawIndexed(s_Data->QuadVA);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Graphics::Texture>& texture, const glm::vec4& tint)
        {

            s_Data->TextureShader->UploadVec4("u_Color", tint);

            texture->Bind();
            s_Data->TextureShader->UploadInt("u_Texture", 0);

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(
                glm::mat4(1.0f), {size.x, size.y, 1.0f});
            s_Data->TextureShader->UploadMat4("u_Transform", transform);

            s_Data->QuadVA->Bind();
            Graphics::DrawIndexed(s_Data->QuadVA);
        }
    }
}
