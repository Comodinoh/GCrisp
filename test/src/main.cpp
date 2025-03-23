#include <GCrisp/GCrisp.h>
#include <GLFW/glfw3.h>

using namespace GCrisp;

class TestLayer : public Layer
{
public:
    TestLayer() : Layer("Test"), m_CameraController(16.0f / 9.0f,  5){
        // auto& app = Application::Get();
        // m_VertexArray.reset(app.GetGraphicsCreator()->CreateVertexArray());
        //
        // float vertices[] =
        // {
        //     0.5, 0.5, 0.0, 1.0, 1.0,
        //     0.5, -0.5, 0.0, 1.0, 0.0,
        //     -0.5, -0.5, 0.0, 0.0, 0.0,
        //     -0.5, 0.5, 0.0, 0.0, 1.0,
        // };
        //
        // m_VertexBuffer.reset(app.GetGraphicsCreator()->CreateVertexBuffer({vertices, sizeof(vertices)}));
        //
        // Graphics::BufferLayout layout =
        // {
        //     {"a_Position", Graphics::ShaderDataType::Float3},
        //     {"a_TexCoord", Graphics::ShaderDataType::Float2}
        // };
        //
        // m_VertexBuffer->SetLayout(layout);
        // m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        //
        // uint32_t indices[] =
        // {
        //     0, 1, 2,
        //     2, 3, 0
        // };
        // m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer({indices, sizeof(indices)}));
        // m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        m_SubTexture = std::shared_ptr<Graphics::SubTexture2D>(Graphics::SubTexture2D::CreateFromCoords(AssetsManager::GetDefaultTexture(), {2, 2}, {256, 256 }));
    }

    void OnUpdate(const ProcessedTime& delta) override
    {
        GC_PROFILE_FUNC();
        // GC_CORE_INFO("Elapsed time: {0}", static_cast<float>(delta));
        // Warning: movement will get messy while the camera is rotating

        {
            GC_PROFILE_SCOPE("Camera Update - TestLayer")
            m_CameraController.OnUpdate(delta);
        }

        Graphics::Clear({0, 0, 0, 1});

        // auto shader = Application::Get().GetAssetsManager().FetchShader("TextureBatchSlots.glsl");
        // Reference<Graphics::Texture>& texture = Application::Get().GetAssetsManager().FetchTexture("default_texture.png");

        // {
        //     GC_PROFILE_SCOPE("Render Prep - TestLayer");
        //     shader->Bind();
        //     texture->Bind();
        //     shader->UploadInt("u_Texture", 0);
        //     shader->UploadVec4("u_Color", glm::vec4(1.0f));
        // }

        // {
        //     GC_PROFILE_SCOPE("Render Begin - TestLayer");
        //     Graphics::BeginRender(m_CameraController.GetCamera());
        // }
        //
        // {
        //     GC_PROFILE_SCOPE("Geometry Submit - TestLayer");
        //     Graphics::Submit(m_VertexArray, shader);
        // }
        //
        // {
        //     GC_PROFILE_SCOPE("Render End - TestLayer");
        //     Graphics::EndRender();
        // }

        {
            GC_PROFILE_SCOPE("Render2D Begin - TestLayer");
            Graphics2D::BeginRender(m_CameraController.GetCamera());
        }

        {
            GC_PROFILE_SCOPE("Render2D Draw - TestLayer");
            // Graphics2D::DrawQuad({-0.6, -0.6}, {1, 1}, texture);
            // Graphics2D::DrawQuad({1.4, 1.4}, {1, 1}, texture, {1, 0.8, 0.8, 1});
            // Graphics2D::DrawQuad({0, 0},  {1, 1}, {1, 0, 0, 1});
            // Graphics2D::DrawQuad({-0.5, -0.5}, {0.5, 0.5}, {1, 0, 0, 1});
            // for (int y = -80;y<80;y++)
            // {
            //     for (int x = -80; x<80;x++)
            //     {
            //         Graphics2D::DrawQuad(glm::vec2(x, y)*0.50f, {0.25, 0.25}, {1, 0, 0, 1});
            //     }
            // }

            Graphics2D::DrawQuadST({ {-0.5f, -0.5f}, {1.0f, 1.0f} }, m_SubTexture);
            Graphics2D::DrawQuad({ { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.9f } });

        }

        {
            GC_PROFILE_SCOPE("Render2D End - TestLayer");
            Graphics2D::EndRender();
        }
    }

    void OnEvent(GCrisp::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

private:
    // Reference<Graphics::VertexBuffer> m_VertexBuffer;
    // Reference<Graphics::IndexBuffer> m_IndexBuffer;
    // Reference<Graphics::VertexArray> m_VertexArray;
    Reference<Graphics::SubTexture2D> m_SubTexture;

    OrthoCameraController m_CameraController;
};

class TestApplication : public GCrisp::Application
{
public:
    TestApplication()
    {
        PushLayer(new TestLayer());
    }

    ~TestApplication()
    {
    }
};

GCrisp::Application* GCrisp::CreateApplication()
{
    return new TestApplication();
}
