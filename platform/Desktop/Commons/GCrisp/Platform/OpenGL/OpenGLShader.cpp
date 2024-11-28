#include "OpenGLShader.h"

#include <glad/glad.h>

namespace GCrisp{

namespace Graphics{

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
  int vertexID = glCreateShader(GL_VERTEX_SHADER);
  int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexID, vertexSrc, vertexSrc, );

}

void OpenGLShader::Bind() const
{

}

void OpenGLShader::UnBind() const
{

}

}

}
