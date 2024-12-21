#include "Renderer.h"

#include <GCrisp/Core/Core.h>
#include <GCrisp/Core/Application.h>
#include <memory>

namespace GCrisp{

namespace Graphics{

std::unique_ptr<API> Renderer::s_RenderAPI;
Backend API::s_RendererBackend = Backend::None;

void Renderer::Init()
{
  s_RenderAPI = std::unique_ptr<API>(Application::Get().GetGraphicsCreator()->CreateAPI());
  s_RenderAPI->Init();
  GC_CORE_INFO("Initialized renderer!");
}

void Renderer::Shutdown()
{
  s_RenderAPI.reset();
  s_RenderAPI = nullptr;
}

void Renderer::Clear(const glm::vec4& color)
{
  s_RenderAPI->Clear(color);
}

void Renderer::SetViewport(const glm::vec2& pos, const glm::vec2& size)
{
    s_RenderAPI->SetViewport(pos, size);
}

void Renderer::Draw(const std::shared_ptr<VertexArray>& vertexArray)
{
  s_RenderAPI->Draw(vertexArray);
}


}

}
