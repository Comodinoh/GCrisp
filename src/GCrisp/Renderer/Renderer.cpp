#include "Renderer.h"

#include <GCrisp/Core/Core.h>
#include <GCrisp/Core/Application.h>
#include <memory>

namespace GCrisp{

namespace Graphics{

Backend API::s_RendererBackend = Backend::None;

void Init()
{
  s_RenderAPI = std::unique_ptr<API>(Application::Get().GetGraphicsCreator()->CreateAPI());
  s_RenderAPI->Init();
  GC_CORE_INFO("Initialized renderer!");
}

void Shutdown()
{
  s_RenderAPI.reset();
  s_RenderAPI = nullptr;
}

void Clear(const glm::vec4& color)
{
  s_RenderAPI->Clear(color);
}

void SetViewport(const glm::vec2& pos, const glm::vec2& size)
{
    s_RenderAPI->SetViewport(pos, size);
}

void BeginRender(Camera& camera)
{
  camera.Project();
}

void EndRender()
{

}

void Submit(const Reference<VertexArray>& vertexArray)
{
  s_RenderAPI->Draw(vertexArray);
}


}

}
