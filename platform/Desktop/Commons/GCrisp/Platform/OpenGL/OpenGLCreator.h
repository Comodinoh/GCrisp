#pragma once

#include "GCrisp/Renderer/Buffer.h"
#include <GCrisp/Renderer/Creator.h>

namespace gcrisp{

namespace Graphics{

class OpenGLCreator : public Creator
{
public:
  virtual API*          CreateAPI() override;
  virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) override;
  virtual IndexBuffer*  CreateIndexBuffer(uint32_t* indices, uint32_t size) override;
};

}

}
