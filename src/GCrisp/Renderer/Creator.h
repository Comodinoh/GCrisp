#pragma once

#include "Buffer.h"

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

namespace GCrisp
{
namespace Graphics
{
typedef unsigned char stbi_uc;

class Creator
{
  public:
	virtual ~Creator() = default;

	virtual API* CreateAPI() = 0;

	virtual Shader* CreateShader(const ShaderSpecification& spec) = 0;
	virtual VertexBuffer*
	CreateVertexBuffer(const VertexBufferSpecification& spec) = 0;
	virtual IndexBuffer*
	CreateIndexBuffer(const IndexBufferSpecification& spec)				   = 0;
	virtual VertexArray* CreateVertexArray()							   = 0;
	virtual Texture2D*	 CreateTexture2D(const stbi_uc*				 data,
										 const TextureSpecification& spec) = 0;
};

static Creator* s_GraphicsCreator = nullptr;

static inline Creator* GetCreator()
{
	return s_GraphicsCreator;
}
} // namespace Graphics
} // namespace GCrisp
