#pragma once

#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/SubTexture.h>
#include <GCrisp/Renderer/VertexArray.h>
#include <glm/glm.hpp>

#include "Texture.h"

namespace GCrisp::Graphics
{
struct RendererProp;
}

namespace GCrisp::Graphics2D
{
struct QuadVertex {
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float	  TextureID;
};

struct Limits {
	uint32_t MaxVertexCount = 0;
	uint32_t MaxIndexCount	= 0;
	uint32_t MaxQuadCount	= 0;
};

struct Data {
	Reference<Graphics::VertexArray>  QuadVA;
	Reference<Graphics::VertexBuffer> QuadVB;
	AssetID							  TextureShader;

	QuadVertex* Vertices;
	QuadVertex* CurrentVertex;

	glm::vec4 VertexPositions[4];

	AssetID* TextureSlots = nullptr;
	AssetID	 WhiteTexture;

	uint32_t QuadIndexCount	  = 0;
	int		 TextureSlotCount = 1;
	uint32_t DrawCalls		  = 0;

	Limits RendererLimits;
};

struct QuadProp {
	QuadProp(const glm::vec3& pos, const glm::vec2& size,
			 const glm::vec4& tint = {1.0f, 1.0f, 1.0f, 1.0f})
		: Position(pos), Size(size), Tint(tint)
	{
	}
	QuadProp(const glm::vec2& pos, const glm::vec2& size,
			 const glm::vec4& tint = {1.0f, 1.0f, 1.0f, 1.0f})
		: Position(pos.x, pos.y, 0.0f), Size(size), Tint(tint)
	{
	}

	glm::vec3 Position;
	glm::vec2 Size;
	glm::vec4 Tint;
};

static Data* s_Data;

void Init(const Graphics::RendererProp& prop);
void Shutdown();

inline const Limits& GetLimits()
{
	return s_Data->RendererLimits;
}

void BeginRender(Graphics::Camera& camera);
void EndRender();
void Flush();

void DrawQuad(const QuadProp& prop);

/*
 * Draws a normal quad with an xy-axis rotation in radians
 */
void DrawQuadR(const QuadProp& prop, const float rotation);

/*
 * Draws a textured quad
 */
void DrawQuadT(const QuadProp& prop, const AssetID& texture);

/*
 * Draws a textured quad with an xy-axis rotation in radians
 */
void DrawQuadRT(const QuadProp& prop, const AssetID& texture,
				const float rotation);

/*
 * Draws a quad textured from a sub texture region
 */
void DrawQuadST(const QuadProp&							 prop,
				const Reference<Graphics::SubTexture2D>& subTexture);

/*
 * Draws a quad textured from a sub texture region with an xy-axis rotation in
 * radians
 */
void DrawQuadRST(const QuadProp&						  prop,
				 const Reference<Graphics::SubTexture2D>& subTexture,
				 const float							  rotation);

} // namespace GCrisp::Graphics2D
