#include <gcpch.h>
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include <GCrisp/Core/Log.h>

namespace GCrisp
{
    namespace Graphics
    {
        OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
        {
            GC_PROFILE_FUNC();
            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        OpenGLVertexBuffer::~OpenGLVertexBuffer()
        {
            GC_PROFILE_FUNC();
            glDeleteBuffers(1, &m_RendererID);
        }

        void OpenGLVertexBuffer::Bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }

        void OpenGLVertexBuffer::UnBind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size)
        {
            GC_PROFILE_FUNC();
            m_Count = size / sizeof(uint32_t);

            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        }

        OpenGLIndexBuffer::~OpenGLIndexBuffer()
        {
            GC_PROFILE_FUNC();
            glDeleteBuffers(1, &m_RendererID);
        }

        void OpenGLIndexBuffer::Bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }

        void OpenGLIndexBuffer::UnBind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}
