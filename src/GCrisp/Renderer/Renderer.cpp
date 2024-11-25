#include "Renderer.h"

#include <GCrisp/Core/Application.h>
#include <memory>

namespace gcrisp{

namespace Graphics{

std::unique_ptr<API> Renderer::s_RenderAPI = nullptr;
Backend API::s_RendererBackend = Backend::None;

void Renderer::Init()
{
  s_RenderAPI = std::unique_ptr<API>(Application::Get().GetGraphicsCreator()->CreateAPI());
  s_RenderAPI->Init();
  GC_CORE_INFO("Initialized renderer!");
}

void Renderer::Shutdown()
{

}

}

}
