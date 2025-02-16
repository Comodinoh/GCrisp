#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Renderer/Renderer2D.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Core/CameraController.h>
#include <GLFW/glfw3.h>

using namespace GCrisp;

class TestLayer : public Layer
{
public:
    TestLayer() : Layer("Test"), m_CameraController(16.0f / 9.0f)
    {
        auto& app = Application::Get();
        m_VertexArray.reset(app.GetGraphicsCreator()->CreateVertexArray());

        float vertices[] =
        {
            0.5, 0.5, 0.0, 1.0, 1.0,
            0.5, -0.5, 0.0, 1.0, 0.0,
            -0.5, -0.5, 0.0, 0.0, 0.0,
            -0.5, 0.5, 0.0, 0.0, 1.0,
        };

        m_VertexBuffer.reset(app.GetGraphicsCreator()->CreateVertexBuffer(vertices, sizeof(vertices)));

        Graphics::BufferLayout layout =
        {
            {"a_Position", Graphics::ShaderDataType::Float3},
            {"a_TexCoord", Graphics::ShaderDataType::Float2}
        };

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };
        m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer(indices, sizeof(indices)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    ~TestLayer()
    {
    }

    void OnUpdate(const ProcessedTime& delta) override
    {
        // GC_CORE_INFO("Elapsed time: {0}", static_cast<float>(delta));
        // Warning: movement will get messy while the camera is rotating

        m_CameraController.OnUpdate(delta);

        Graphics::Clear({0, 0, 0, 1});

        auto shader = Application::Get().GetAssetsManager().FetchShader("Texture.glsl");

        shader->Bind();
        Reference<Graphics::Texture>& texture = Application::Get().GetAssetsManager().FetchTexture(
            "default_texture.png");
        texture->Bind();
        shader->UploadInt("u_Texture", 0);
        shader->UploadVec4("u_Color", glm::vec4(1.0f));

        Graphics::BeginRender(m_CameraController.GetCamera());
        Graphics::Submit(m_VertexArray, shader);
        Graphics::EndRender();


        // Graphics2D::BeginRender(m_CameraController.GetCamera());
        //
        // Graphics2D::DrawQuad({0, 0, 0}, {1, 1}, texture);
        //
        // Graphics2D::EndRender();
    }

    void OnEvent(GCrisp::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

private:
    Reference<Graphics::VertexBuffer> m_VertexBuffer;
    Reference<Graphics::IndexBuffer> m_IndexBuffer;
    Reference<Graphics::VertexArray> m_VertexArray;

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
