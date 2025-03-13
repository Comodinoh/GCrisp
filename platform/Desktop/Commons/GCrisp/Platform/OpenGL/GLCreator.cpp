#include <gcpch.h>
#include "GLCreator.h"

#include "GGLAPI.h"
#include "GLShader.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLTexture.h"

namespace GCrisp
{
    namespace Graphics
    {
        API* GLCreator::CreateAPI()
        {
            GC_PROFILE_FUNC();
            return new GGLAPI();
        }

        Shader* GLCreator::CreateShader(const ShaderSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new GLShader(spec);
        }

        VertexBuffer* GLCreator::CreateVertexBuffer(const VertexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new OpenGLVertexBuffer(spec);
        }

        IndexBuffer* GLCreator::CreateIndexBuffer(const IndexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new OpenGLIndexBuffer(spec);
        }

        VertexArray* GLCreator::CreateVertexArray()
        {
            GC_PROFILE_FUNC();
            return new GLVertexArray();
        }

        Texture2D* GLCreator::CreateTexture2D(const stbi_uc* data, const TextureSpec& spec)
        {
            GC_PROFILE_FUNC();
            return new GLTexture(data, spec);
        }
    }
}
