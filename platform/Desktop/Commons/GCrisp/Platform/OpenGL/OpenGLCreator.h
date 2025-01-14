#pragma once

#include <GCrisp/Renderer/Creator.h>

namespace GCrisp{

namespace Graphics{

class OpenGLCreator : public Creator
{
public:
  virtual API*          CreateAPI() override;

  virtual Shader*       CreateShader(std::string* const vertexSrc, std::string* const fragmentSrc) override;
  virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size)                         override;
  virtual IndexBuffer*  CreateIndexBuffer(uint32_t* indices, uint32_t size)                        override;
  virtual VertexArray*  CreateVertexArray()                                                        override;
};

}

}
