#include <gcpch.h>
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <GCrisp/Core/Log.h>
#include <glm/gtc/type_ptr.hpp>

namespace GCrisp{

namespace Graphics{

OpenGLShader::OpenGLShader(const std::string* const vertexSrc, const std::string* const fragmentSrc)
{
  int vertexID;
  int fragmentID;

  const GLchar* source;
  GLint status;

  // We compile the vertex source if the provided pointer isn't null
  if(vertexSrc)
  {
    vertexID = glCreateShader(GL_VERTEX_SHADER);

    source = vertexSrc->c_str();

    glShaderSource(vertexID, 1, &source, NULL);

    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
      GLint maxLength;
      glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &maxLength);

      GLchar infoLog[maxLength];
      glGetShaderInfoLog(vertexID, maxLength, &maxLength, infoLog);

      glDeleteShader(vertexID);

      GC_CORE_ERROR(std::string(infoLog));
      GC_CORE_ASSERT(false, "Failed to compile vertex shader!");
      return;
    }
  }

  if(fragmentSrc)
  {
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    source = fragmentSrc->c_str();

    glShaderSource(fragmentID, 1, &source, 0);

    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
      GLint maxLength;
      glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &maxLength);

      GLchar infoLog[maxLength];
      glGetShaderInfoLog(fragmentID, maxLength, &maxLength, infoLog);

      glDeleteShader(fragmentID);
      if(vertexID) glDeleteShader(vertexID);

      GC_CORE_ERROR(std::string(infoLog));
      GC_CORE_ASSERT(false, "Failed to compile fragment shader!");
      return;
    }

    int programID = glCreateProgram();

    if(vertexID) glAttachShader(programID, vertexID);
    if(fragmentID) glAttachShader(programID, fragmentID);

    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
      GLint maxLength;
      glGetProgramiv(fragmentID, GL_INFO_LOG_LENGTH, &maxLength);

      GLchar infoLog[maxLength];
      glGetProgramInfoLog(fragmentID, maxLength, &maxLength, infoLog);

      glDeleteProgram(programID);

      if(vertexID) glDeleteShader(vertexID);
      if(fragmentID) glDeleteShader(fragmentID);


      GC_CORE_ERROR(std::string(infoLog));
      GC_CORE_ASSERT(false, "Failed to link shader program!");
      return;
    }

    glUseProgram(programID);

    glDetachShader(programID, vertexID);
    glDetachShader(programID, fragmentID);

    m_RendererID = programID;
  }  
}

OpenGLShader::~OpenGLShader()
{
  glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
  glUseProgram(m_RendererID);
}

void OpenGLShader::UploadMat4(const std::string& name, const glm::mat4& data) const
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
}

void OpenGLShader::UploadVec3(const std::string& name, const glm::vec3& data) const
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniform3fv(location, 1, glm::value_ptr(data));
}

void OpenGLShader::UploadVec4(const std::string& name, const glm::vec4& data) const
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniform4fv(location, 1, glm::value_ptr(data));
}

void OpenGLShader::UnBind() const
{
  glUseProgram(0);
}

}

}
