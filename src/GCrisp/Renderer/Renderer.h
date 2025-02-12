#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <glm/glm.hpp>

namespace GCrisp{

namespace Graphics{

enum class Backend
{
  None = 0, OpenGL = 1
};

struct Data
{
  glm::mat4 ViewProjMatrix;
};

class API
{
public:
  virtual ~API() = default;

  virtual void Init() = 0;

  virtual void Clear(const glm::vec4& color) const = 0;

  virtual void SetViewport(const glm::vec2& pos, const glm::vec2& size) const = 0;

  virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) const = 0;

  inline static Backend GetBackend() {return s_RendererBackend;}
protected:
  static Backend s_RendererBackend;
};

void Init();
void Shutdown();

void Clear(const glm::vec4& color);
void SetViewport(const glm::vec2& pos, const glm::vec2& size);

void DrawIndexed(const Reference<VertexArray>& vertexArray);

void BeginRender(Camera& camera);
void EndRender();

void Submit(const Reference<VertexArray>& vertexArray, const Reference<Shader>& shader);


inline Backend GetBackend() {return API::GetBackend();}

static ScopedPtr<API>  s_RenderAPI;
static ScopedPtr<Data> s_Data;

}

}
