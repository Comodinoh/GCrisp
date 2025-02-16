#include <gcpch.h>
#include "OpenGLCreator.h"

#include "OpenGLAPI.h"
#include "OpenGLShader.h"
#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLTexture.h"

namespace GCrisp
{
    namespace Graphics
    {
        API* OpenGLCreator::CreateAPI()
        {
            GC_PROFILE_FUNC();
            return new OpenGLAPI();
        }

        Shader* OpenGLCreator::CreateShader(const ShaderSpec& spec)
        {
            GC_PROFILE_FUNC();
            return (Shader*)new OpenGLShader(spec);
        }

        VertexBuffer* OpenGLCreator::CreateVertexBuffer(float* vertices, uint32_t size)
        {
            GC_PROFILE_FUNC();
            return new OpenGLVertexBuffer(vertices, size);
        }

        IndexBuffer* OpenGLCreator::CreateIndexBuffer(uint32_t* indices, uint32_t size)
        {
            GC_PROFILE_FUNC();
            return new OpenGLIndexBuffer(indices, size);
        }

        VertexArray* OpenGLCreator::CreateVertexArray()
        {
            GC_PROFILE_FUNC();
            return new OpenGLVertexArray();
        }

        Texture2D* OpenGLCreator::CreateTexture2D(const stbi_uc* data, const TextureSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new OpenGLTexture(data, spec);
        }
    }
}
