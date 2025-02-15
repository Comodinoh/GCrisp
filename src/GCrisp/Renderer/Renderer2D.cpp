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


            std::string vertexSrc = R"(
                #version 330 core

                in vec3 a_Position;

                uniform mat4 u_ViewProj;
                uniform mat4 u_Transform;

                void main()
                {
                  gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
                }
          )";
            std::string fragmentSrc = R"(
                #version 330 core

                out vec4 fragColor;

                uniform vec4 u_Color;

                void main()
                {
                  fragColor = vec4(u_Color);
                }
          )";
            s_Data->ColorShader.reset(app.GetGraphicsCreator()->CreateShader(
                {
                    {Graphics::SHADER_VERTEX, vertexSrc.c_str()},
                    {Graphics::SHADER_FRAGMENT, fragmentSrc.c_str()}
                }
            ));

            s_Data->TextureShader = app.GetAssetsManager().FetchShader("Texture.glsl");
        }

        void Shutdown()
        {
            delete s_Data;
        }

        void BeginRender(Graphics::Camera& camera)
        {
            s_Data->ColorShader->Bind();
            s_Data->ColorShader->UploadMat4("u_ViewProj", camera.GetViewProj());

            s_Data->TextureShader->Bind();
            s_Data->TextureShader->UploadMat4("u_ViewProj", camera.GetViewProj());
        }

        void EndRender()
        {
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            //TODO: implement shader bound checking system
            s_Data->ColorShader->Bind();
            s_Data->ColorShader->UploadVec4("u_Color", color);

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(
                glm::mat4(1.0f), {size.x, size.y, 1.0f});
            s_Data->ColorShader->UploadMat4("u_Transform", transform);

            s_Data->QuadVA->Bind();
            Graphics::DrawIndexed(s_Data->QuadVA);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Graphics::Texture>& texture)
        {
            s_Data->TextureShader->Bind();
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
