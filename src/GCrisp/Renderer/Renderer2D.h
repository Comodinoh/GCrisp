#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <glm/glm.hpp>

namespace GCrisp{

namespace Graphics2D{

struct Data
{
  Reference<Graphics::VertexArray> QuadVA;
  Reference<Graphics::Shader> ColorShader;
};

void Init();
void Shutdown();

void BeginRender(Graphics::Camera& camera);
void EndRender();

void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

static Data* s_Data;



}

}
