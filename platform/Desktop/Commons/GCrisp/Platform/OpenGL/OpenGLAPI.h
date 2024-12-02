#pragma once

#include "GCrisp/Renderer/Renderer.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace GCrisp{

namespace Graphics{


class OpenGLAPI : public API
{
public:
  virtual void Init() override; 

  GLenum FromShaderDataTypeToOpenGLType(ShaderDataType type) const;
};

}

}
