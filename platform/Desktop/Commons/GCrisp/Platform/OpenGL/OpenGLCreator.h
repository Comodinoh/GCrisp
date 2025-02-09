#pragma once

#include <GCrisp/Renderer/Creator.h>

namespace GCrisp{

namespace Graphics{

class OpenGLCreator : public Creator
{
public:
  virtual API*          CreateAPI() override;

  virtual Shader*       CreateShader(const ShaderSpec& spec) override;
  virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size)                         override;
  virtual IndexBuffer*  CreateIndexBuffer(uint32_t* indices, uint32_t size)                        override;
  virtual VertexArray*  CreateVertexArray()                                                        override;
  virtual Texture2D*    CreateTexture2D(const stbi_uc* data, const TextureSpec& spec)              override;
};

}

}
