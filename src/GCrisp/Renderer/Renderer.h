#pragma once

namespace gcrisp{

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

  static Backend GetBackend() {return s_RendererBackend;}
protected:
  static Backend s_RendererBackend;
};

class Renderer
{
public:
  static void Init();
  static void Shutdown();

  static Backend GetBackend() {return API::GetBackend();}
private:
  static std::unique_ptr<API> s_RenderAPI;
};

}

}
