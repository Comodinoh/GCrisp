#pragma once

#include <GCrisp/Renderer/VertexArray.h>
#include <glm/glm.hpp>

namespace GCrisp{

namespace Graphics{

enum class Backend
{
  None = 0, OpenGL = 1
};

class API
{
public:
  ~API() = default;

  virtual void Init() = 0;

  virtual void Clear(const glm::vec4& color) const = 0;

  virtual void SetViewport(const glm::vec2& pos, const glm::vec2& size) const = 0;

  virtual void Draw(const Reference<VertexArray>& vertexArray) const = 0;

  inline static Backend GetBackend() {return s_RendererBackend;}
protected:
  static Backend s_RendererBackend;
};

class Renderer
{
public:
  static void Init();
  static void Shutdown();

  static void Clear(const glm::vec4& color);
  static void SetViewport(const glm::vec2& pos, const glm::vec2& size);
  static void Submit(const Reference<VertexArray>& vertexArray);

  inline static Backend GetBackend() {return API::GetBackend();}
private:
  static std::unique_ptr<API> s_RenderAPI;
};

}

}
