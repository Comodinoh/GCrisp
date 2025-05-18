#include "Renderer.h"
#include "gcpch.h"

#include "Renderer2D.h"

#include <GCrisp/Core/Application.h>
#include <GCrisp/Core/Base.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <GCrisp/Platform/OpenGL/GGLAPI.h>

namespace GCrisp::Graphics {
GC_GRAPHICS_CREATE_IMPL(API);

void Init(const RendererProp& prop) {
    GC_PROFILE_FUNC();
    auto* api = API::Create();

    GC_INFO("{0}", (char*)api);

    s_RenderAPI = std::unique_ptr<API>{api};
    // s_Data = std::make_unique<Data>();

    s_RenderAPI->Init();
    GC_CORE_INFO("Initialized Renderer!");

    Application::Get().GetAssetsManager().Init();

    Graphics2D::Init(prop);
    GC_CORE_INFO("Initialized Renderer2D!");
}

void Shutdown() {
    Graphics2D::Shutdown();

    s_RenderAPI.reset();
    s_Data.reset();

    s_RenderAPI = nullptr;
    s_Data = nullptr;
}

void Clear(const glm::vec4& color) { s_RenderAPI->Clear(color); }

void SetViewport(const glm::vec2& pos, const glm::vec2& size) {
    s_RenderAPI->SetViewport(pos, size);
}

void DrawIndexed(const Reference<VertexArray>& vertexArray) {
    s_RenderAPI->DrawIndexed(vertexArray);
}

void DrawIndexed(uint32_t count) {
    s_RenderAPI->DrawIndexed(count);
}

void BeginRender(Camera& camera) {
    // "cache" the View projection matrix for the scene we're currently
    // rendering
    s_Data->ViewProjMatrix = camera.GetViewProj();
}

void EndRender() {}

void Submit(const Reference<VertexArray>& vertexArray,
            const Reference<Shader>& shader, const glm::mat4& transform) {
    shader->Bind();
    shader->UploadMat4("u_ViewProj", s_Data->ViewProjMatrix);
    shader->UploadMat4("u_Transform", transform);

    vertexArray->Bind();
    DrawIndexed(vertexArray);
}

// RenderThread::~RenderThread()
// {
// }
//
// void RenderThread::Update()
// {
//     std::unique_lock<std::mutex> lock(m_Mutex);
//     // glfwMakeContextCurrent(NULL);
//     Application::Get().GetWindow().TransferContext();
//     for (int i = 0;i <m_Queue.size();i++)
//     {
//         RenderCommand& command = m_Queue[i];
//
//         command.Shader->Bind();
//         command.Shader->UploadMat4("u_Transform", command.Transform);
//         command.Shader->UploadMat4("u_ViewProj", s_Data->ViewProjMatrix);
//
//         DrawIndexed(command.VertexArray);
//     }
//     m_Queue.clear();
//
//     Application::Get().GetWindow().GetContext()->SwapBuffers();
// }
//
// void RenderThread::Queue(const RenderCommand& command)
// {
//     std::unique_lock<std::mutex> lock(m_Mutex);
//     m_Queue.emplace_back(command.Shader, command.VertexArray,
//     command.Transform);
// }
} // namespace GCrisp::Graphics
