#include <gcpch.h>
#include "GLCreator.h"

#include "GGLAPI.h"
#include "GLShader.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLTexture.h"
//
// namespace GCrisp
// {
//     namespace Graphics
//     {
//         API* GLCreator::CreateAPI()
//         {
//             GC_PROFILE_FUNC();
//             return new GLAPI();
//         }
//
//         Shader* GLCreator::CreateShader(const ShaderSpecification& spec)
//         {
//             GC_PROFILE_FUNC();
//             return new GLShader(spec);
//         }
//
//         VertexBuffer* GLCreator::CreateVertexBuffer(const VertexBufferSpecification& spec)
//         {
//             GC_PROFILE_FUNC();
//             return new GLVertexBuffer(spec);
//         }
//
//         IndexBuffer* GLCreator::CreateIndexBuffer(const IndexBufferSpecification& spec)
//         {
//             GC_PROFILE_FUNC();
//             return new GLIndexBuffer(spec);
//         }
//
//         VertexArray* GLCreator::CreateVertexArray()
//         {
//             GC_PROFILE_FUNC();
//             return new GLVertexArray();
//         }
//
//         Texture2D* GLCreator::CreateTexture2D(const stbi_uc* data, const TextureSpecification& spec)
//         {
//             GC_PROFILE_FUNC();
//             return new GLTexture2D(data, spec);
//         }
//     }
// }
