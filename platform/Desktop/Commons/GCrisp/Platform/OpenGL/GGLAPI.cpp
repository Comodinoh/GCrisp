#include "GGLAPI.h"

#include <glad/glad.h>

namespace GCrisp
{
    namespace Graphics
    {
        // hack: fuck GLAPI. It's already defined in glad...
#undef GLAPI
        void GLAPI::Init()
        {
            GC_PROFILE_FUNC();

             glEnable(GL_DEPTH_TEST);
             glEnable(GL_BLEND);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // TODO: Figure out blending + depth testing
        }

        void GLAPI::Clear(const glm::vec4& color) const
        {
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void GLAPI::SetViewport(const glm::vec2& pos, const glm::vec2& size) const
        {
            glViewport(pos.x, pos.y, size.x, size.y);
        }


        void GLAPI::DrawIndexed(const Reference<VertexArray>& vertexArray) const
        {
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }

        void GLAPI::DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t count) const
        {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
    }

#define GLAPI extern
}
