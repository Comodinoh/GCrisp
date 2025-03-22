#include "GGLAPI.h"

#include <glad/glad.h>

namespace GCrisp
{
    namespace Graphics
    {
        void GGLAPI::Init()
        {
            GC_PROFILE_FUNC();
            s_RendererBackend = Backend::OpenGL;

             glEnable(GL_DEPTH_TEST);
             glEnable(GL_BLEND);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // TODO: Figure out blending + depth testing
        }

        void GGLAPI::Clear(const glm::vec4& color) const
        {
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void GGLAPI::SetViewport(const glm::vec2& pos, const glm::vec2& size) const
        {
            glViewport(pos.x, pos.y, size.x, size.y);
        }


        void GGLAPI::DrawIndexed(const Reference<VertexArray>& vertexArray) const
        {
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }

        void GGLAPI::DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t count) const
        {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
    }
}
