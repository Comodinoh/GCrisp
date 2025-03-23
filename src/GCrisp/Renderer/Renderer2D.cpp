#include "gcpch.h"

#include "Renderer2D.h"

#include "GraphicsConstants.h"

#include <GCrisp/Core/Application.h>

#include "Renderer.h"
#include "Buffer.h"
#include <glm/glm.hpp>

namespace GCrisp
{
    namespace Graphics2D
    {
        void Init(const Graphics::RendererProp& prop)
        {
            GC_PROFILE_FUNC();
            s_Data = new Data();

            s_Data->MaxQuadCount = prop.MaxQuadCount;
            s_Data->MaxVertexCount = prop.MaxQuadCount*4;
            s_Data->MaxIndexCount = prop.MaxQuadCount*6;

            auto& app = Application::Get();
            s_Data->QuadVA.reset(app.GetGraphicsCreator()->CreateVertexArray());
            s_Data->QuadVA->Bind();

            s_Data->Vertices = new QuadVertex[s_Data->MaxVertexCount];

            const uint32_t size = s_Data->MaxVertexCount*sizeof(QuadVertex);
            s_Data->QuadVB.reset(app.GetGraphicsCreator()->CreateVertexBuffer(
                {nullptr, size, Graphics::DrawType::Dynamic}
                ));


            s_Data->QuadVB->SetLayout(
                {
                    {"a_Position", Graphics::ShaderDataType::Float3},
                    {"a_Color", Graphics::ShaderDataType::Float4},
                    {"a_TexCoord", Graphics::ShaderDataType::Float2},
                    {"a_TexID", Graphics::ShaderDataType::Float}
                }
            );
            s_Data->QuadVA->AddVertexBuffer(s_Data->QuadVB);

            uint32_t* quadIndices = new uint32_t[s_Data->MaxIndexCount];

            int offset = 0;
            for (int i = 0;i < s_Data->MaxIndexCount; i+= 6)
            {
                quadIndices[i] = offset;
                quadIndices[i+1] = 1+offset;
                quadIndices[i+2] = 2+offset;

                quadIndices[i+3] = 2+offset;
                quadIndices[i+4] = 3+offset;
                quadIndices[i+5] = offset;

                offset += 4;
            }

            uint32_t indicesSize = s_Data->MaxIndexCount * sizeof(uint32_t);
            Reference<Graphics::IndexBuffer> quadIB;
            quadIB.reset(app.GetGraphicsCreator()->CreateIndexBuffer({quadIndices, indicesSize}));
            s_Data->QuadVA->SetIndexBuffer(quadIB);

            delete[] quadIndices;

            s_Data->TextureShader = app.GetAssetsManager().LoadAsset({AssetType::Shader, "TextureBatchSlots.glsl"});
            //
            // constexpr unsigned char whitePixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};
            // app.GetAssetsManager().LoadRawTexture2D("WhiteTexture", whitePixel, {1, 1, 4});

            s_Data->TextureSlots = (AssetID*)calloc(MAX_TEXTURE_SLOTS, sizeof(AssetID));
            s_Data->WhiteTexture = app.GetAssetsManager().LoadAsset({AssetType::Texture2D, "WhiteTexture.png"});
            s_Data->TextureSlots[0] = s_Data->WhiteTexture;
            for (size_t i = 1; i<MAX_TEXTURE_SLOTS;i++)
            {
                s_Data->TextureSlots[i] = AssetID(0);
            }
            s_Data->CurrentVertex = s_Data->Vertices;
        }

        void Shutdown()
        {
            GC_PROFILE_FUNC();
            delete s_Data;
        }

        void BeginRender(Graphics::Camera& camera)
        {
            auto shader = Application::Get().GetAssetsManager().FetchAsset<Graphics::Shader>(s_Data->TextureShader);
            shader->Bind();
            shader->UploadMat4("u_ViewProj", camera.GetViewProj());
        }

        void Flush()
        {
            uint32_t size = (uint8_t*)s_Data->CurrentVertex-(uint8_t*)s_Data->Vertices;
            s_Data->QuadVB->UploadSubData(size, s_Data->Vertices);

            int slots[MAX_TEXTURE_SLOTS];
            for (int i = 0; i < MAX_TEXTURE_SLOTS; i++)
            {
                slots[i] = i;
                if (i < s_Data->TextureSlotCount)
                    Application::Get().GetAssetsManager().FetchAsset<Graphics::Texture2D>(s_Data->TextureSlots[i])->Bind(i);
            }

            auto shader = Application::Get().GetAssetsManager().FetchAsset<Graphics::Shader>(s_Data->TextureShader);

            shader->Bind();
            shader->UploadInt("u_Textures", slots, MAX_TEXTURE_SLOTS);

            s_Data->QuadVA->Bind();
            Graphics::DrawIndexed(s_Data->QuadVA, s_Data->QuadIndexCount);
            s_Data->DrawCalls++;

            s_Data->QuadIndexCount = 0;
            s_Data->TextureSlotCount = 1;

            s_Data->CurrentVertex = s_Data->Vertices;

        }

        void EndRender()
        {
            Flush();
            s_Data->DrawCalls = 0;
        }

        void DrawQuadI(const QuadProp& prop, float textureID, const glm::vec2 texCoords[4])
        {
            s_Data->CurrentVertex->Position = { prop.Position.x, prop.Position.y, prop.Position.z };
            s_Data->CurrentVertex->Color = prop.Tint;
            s_Data->CurrentVertex->TexCoord = texCoords[0];
            s_Data->CurrentVertex->TextureID = textureID;
            s_Data->CurrentVertex++;

            s_Data->CurrentVertex->Position = { prop.Position.x + prop.Size.x, prop.Position.y, prop.Position.z };
            s_Data->CurrentVertex->Color = prop.Tint;
            s_Data->CurrentVertex->TexCoord = texCoords[1];
            s_Data->CurrentVertex->TextureID = textureID;
            s_Data->CurrentVertex++;

            s_Data->CurrentVertex->Position = { prop.Position.x + prop.Size.x, prop.Position.y + prop.Size.y, prop.Position.z };
            s_Data->CurrentVertex->Color = prop.Tint;
            s_Data->CurrentVertex->TexCoord = texCoords[2];
            s_Data->CurrentVertex->TextureID = textureID;
            s_Data->CurrentVertex++;

            s_Data->CurrentVertex->Position = { prop.Position.x, prop.Position.y + prop.Size.y, prop.Position.z };
            s_Data->CurrentVertex->Color = prop.Tint;
            s_Data->CurrentVertex->TexCoord = texCoords[3];
            s_Data->CurrentVertex->TextureID = textureID;
            s_Data->CurrentVertex++;

            s_Data->QuadIndexCount += 6;
        }

        void DrawQuad(const QuadProp& prop)
        {
            if (s_Data->QuadIndexCount >= s_Data->MaxIndexCount || s_Data->TextureSlotCount >= MAX_TEXTURE_SLOTS)
            {
                Flush();
            }

            // s_Data->WhiteTexture->Bind();
            // s_Data->TextureShader->UploadInt("u_Texture", 0);

            glm::vec2 texCoords[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
            DrawQuadI(prop, 0.0f, texCoords);
            
        }

        void DrawQuadT(const QuadProp& prop, const AssetID& texture)
        {
            if (s_Data->QuadIndexCount >= s_Data->MaxIndexCount || s_Data->TextureSlotCount >= MAX_TEXTURE_SLOTS)
            {
                Flush();
            }

            int texID = s_Data->TextureSlotCount;
            for (int i = 0; i<s_Data->TextureSlotCount; i++)
            {
                if (s_Data->TextureSlots[i] == texture)
                {
                    texID = i;
                    break;
                }
            }

            if (texID >= s_Data->TextureSlotCount)
            {
                s_Data->TextureSlots[texID] = texture;
                s_Data->TextureSlotCount++;
            }

            float texIDF = (float)texID;

            glm::vec2 texCoords[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
            DrawQuadI(prop, texIDF, texCoords);
        }

        void DrawQuadST(const QuadProp& prop, const Reference<Graphics::SubTexture2D>& subTexture)
        {
            if (s_Data->QuadIndexCount >= s_Data->MaxIndexCount || s_Data->TextureSlotCount >= MAX_TEXTURE_SLOTS)
            {
                Flush();
            }

            const AssetID texture = subTexture->GetTextureID();

            int texID = s_Data->TextureSlotCount;
            for (int i = 0; i < s_Data->TextureSlotCount; i++)
            {
                if (s_Data->TextureSlots[i] == texture)
                {
                    texID = i;
                    break;
                }
            }

            if (texID >= s_Data->TextureSlotCount)
            {
                s_Data->TextureSlots[texID] = texture;
                s_Data->TextureSlotCount++;
            }

            float texIDF = (float)texID;

            DrawQuadI(prop, texIDF, subTexture->GetTextureCoords());
        }


    }
}
