#include "GLBuffer.h"
#include <gcpch.h>

#include <GCrisp/Core/Log.h>
#include <glad/glad.h>

namespace GCrisp
{
namespace Graphics
{
GLVertexBuffer::GLVertexBuffer(const VertexBufferSpecification& spec)
{
	GC_PROFILE_FUNC();
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	glBufferData(GL_ARRAY_BUFFER, spec.Size, spec.Vertices,
				 spec.DrawType == DrawType::Static ? GL_STATIC_DRAW
												   : GL_DYNAMIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer()
{
	GC_PROFILE_FUNC();
	glDeleteBuffers(1, &m_RendererID);
}

void GLVertexBuffer::Bind() const
{
	GC_PROFILE_FUNC();
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void GLVertexBuffer::UnBind() const
{
	GC_PROFILE_FUNC();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::UploadSubData(uint32_t size, const void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

GLIndexBuffer::GLIndexBuffer(const IndexBufferSpecification& spec)
{
	GC_PROFILE_FUNC();
	m_Count = spec.Size / sizeof(uint32_t);

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, spec.Size, spec.Indices,
				 spec.DrawType == DrawType::Static ? GL_STATIC_DRAW
												   : GL_DYNAMIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer()
{
	GC_PROFILE_FUNC();
	glDeleteBuffers(1, &m_RendererID);
}

void GLIndexBuffer::Bind() const
{
	GC_PROFILE_FUNC();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void GLIndexBuffer::UnBind() const
{
	GC_PROFILE_FUNC();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // namespace Graphics
} // namespace GCrisp
