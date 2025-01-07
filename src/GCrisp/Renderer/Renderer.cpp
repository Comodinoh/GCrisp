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
  s_Data = std::make_unique<Data>();

  s_RenderAPI->Init();
  GC_CORE_INFO("Initialized renderer!");
}

void Shutdown()
{
  s_RenderAPI.reset();
  s_Data.reset();

  s_RenderAPI = nullptr;
  s_Data = nullptr;
}

void Clear(const glm::vec4& color)
{
  s_RenderAPI->Clear(color);
}

void SetViewport(const glm::vec2& pos, const glm::vec2& size)
{
  s_RenderAPI->SetViewport(pos, size);
}

void DrawIndexed(const Reference<VertexArray>& vertexArray)
{
  s_RenderAPI->DrawIndexed(vertexArray);
}

void BeginRender(Camera& camera)
{
  // "cache" the View projection matrix for the scene we're currently rendering
  s_Data->ViewProjMatrix = camera.GetViewProj();
}

void EndRender()
{

}

void Submit(const Reference<VertexArray>& vertexArray, const Reference<Shader>& shader)
{
  shader->Bind();
  shader->UploadMat4("u_ViewProj", s_Data->ViewProjMatrix);

  vertexArray->Bind();
  DrawIndexed(vertexArray);
}


}

}
