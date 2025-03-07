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

        VertexBuffer* OpenGLCreator::CreateVertexBuffer(const VertexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new OpenGLVertexBuffer(spec);
        }

        IndexBuffer* OpenGLCreator::CreateIndexBuffer(const IndexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new OpenGLIndexBuffer(spec);
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
