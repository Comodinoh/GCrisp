#include "OpenGLAPI.h"

#include "GCrisp/Renderer/Renderer.h"
#include <glad/glad.h>

namespace GCrisp
{
  namespace Graphics
  {
    void OpenGLAPI::Init()
    {
      s_RendererBackend = Backend::OpenGL;

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLAPI::Clear(const glm::vec4& color) const
    {
      glClearColor(color.r, color.g, color.b, color.a);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLAPI::SetViewport(const glm::vec2& pos, const glm::vec2& size) const
    {
      glViewport(pos.x, pos.y, size.x, size.y);
    }


    void OpenGLAPI::DrawIndexed(const Reference<VertexArray>& vertexArray) const
    {
      glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
  }
}
