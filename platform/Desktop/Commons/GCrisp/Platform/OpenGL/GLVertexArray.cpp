#include "GLVertexArray.h"
#include <gcpch.h>

#include <GCrisp/Core/Core.h>
#include <glad/glad.h>

namespace GCrisp {
namespace Graphics {
static GLenum FromShaderDataTypeToOpenGLType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    default:
        GC_CORE_ASSERT(
            false, "Unknown ShaderDataType for OpenGL data type conversion!");
        return 0;
    }
}

GLVertexArray::GLVertexArray() {
    GC_PROFILE_FUNC();
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

GLVertexArray::~GLVertexArray() {
    GC_PROFILE_FUNC();
    glDeleteVertexArrays(1, &m_RendererID);
}

void GLVertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void GLVertexArray::UnBind() const { glBindVertexArray(0); }

void GLVertexArray::AddVertexBuffer(
    const Reference<VertexBuffer>& vertexBuffer) {
    GC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                   "Vertex buffer has no layout!")

    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    const BufferLayout& layout = vertexBuffer->GetLayout();
    uint32_t i = 0;
    for (const BufferElement& element : layout.GetElements()) {
        GC_CORE_INFO("{0}, {1}, {2}", element.Count, layout.GetStride(),
                     element.Offset);
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, element.Count, FromShaderDataTypeToOpenGLType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
            reinterpret_cast<const void*>(element.Offset));
        i++;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void GLVertexArray::SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) {
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}
} // namespace Graphics
} // namespace GCrisp
