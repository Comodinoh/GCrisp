#include <gcpch.h>
#include "GLBuffer.h"

#include <glad/glad.h>
#include <GCrisp/Core/Log.h>

namespace GCrisp
{
    namespace Graphics
    {
        OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

            glBufferData(GL_ARRAY_BUFFER, spec.Size, spec.Vertices, spec.DrawType == DrawType::Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        }

        OpenGLVertexBuffer::~OpenGLVertexBuffer()
        {
            GC_PROFILE_FUNC();
            glDeleteBuffers(1, &m_RendererID);
        }

        void OpenGLVertexBuffer::Bind() const
        {
            GC_PROFILE_FUNC();
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }

        void OpenGLVertexBuffer::UnBind() const
        {
            GC_PROFILE_FUNC();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void OpenGLVertexBuffer::UploadSubData(uint32_t size, const void* data)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }

        OpenGLIndexBuffer::OpenGLIndexBuffer(const IndexBufferSpec& spec)
        {
            GC_PROFILE_FUNC();
            m_Count = spec.Size / sizeof(uint32_t);

            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, spec.Size, spec.Indices, spec.DrawType == DrawType::Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        }

        OpenGLIndexBuffer::~OpenGLIndexBuffer()
        {
            GC_PROFILE_FUNC();
            glDeleteBuffers(1, &m_RendererID);
        }

        void OpenGLIndexBuffer::Bind() const
        {
            GC_PROFILE_FUNC();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }

        void OpenGLIndexBuffer::UnBind() const
        {
            GC_PROFILE_FUNC();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}
