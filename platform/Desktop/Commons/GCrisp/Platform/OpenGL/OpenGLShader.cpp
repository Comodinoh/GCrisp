#include <gcpch.h>
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <GCrisp/Core/Log.h>
#include <glm/gtc/type_ptr.hpp>

namespace GCrisp{

namespace Graphics{

static inline GLenum GLShaderFromGC(ShaderType type)
{
  switch(type)
  {
    case SHADER_VERTEX: return GL_VERTEX_SHADER;
    case SHADER_FRAGMENT: return GL_FRAGMENT_SHADER;
    default: return 0;
  }
}

OpenGLShader::OpenGLShader(const ShaderSpec& spec)
{
  uint32_t programID = glCreateProgram();

  uint32_t IDs[3];


  // We compile the vertex source if the provided pointer isn't null
  int shaderIndex = 0;
  for(auto&&[type, source] : spec.shaders)
  {
    GLenum glType = GLShaderFromGC(type);
    uint32_t id = glCreateShader(glType);

    const char* cSource = source.c_str();

    glShaderSource(id, 1, &cSource, NULL);
    glCompileShader(id);

    GLint status;

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
      GLint maxLength;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

      GLchar infoLog[maxLength];
      glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);

      glDeleteShader(id);

      GC_CORE_ERROR("Failed to compile {0} shader. Please refer to the logs below:", StringFromShaderType(type));
      GC_CORE_ERROR(std::string(infoLog));
      GC_CORE_ASSERT(false, "Error occurred during shader compilation!");
      return;
    }

    IDs[shaderIndex] = id;
    glAttachShader(programID, id);

    shaderIndex++;
  }


  glLinkProgram(programID);

  GLint status;

  glGetProgramiv(programID, GL_LINK_STATUS, &status);
  if(status == GL_FALSE)
  {
   GLint maxLength;
   glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

   GLchar infoLog[maxLength];
   glGetProgramInfoLog(programID, maxLength, &maxLength, infoLog);

   glDeleteProgram(programID);

  for(int i = 0;i<shaderIndex;i++)
  {
     uint32_t id = IDs[i];
     glDeleteShader(id);
    
   }


   GC_CORE_ERROR(std::string(infoLog));
   GC_CORE_ASSERT(false, "Failed to link shader program!");
   return;
  }

  glUseProgram(programID);


  for(int i = 0;i<shaderIndex;i++)
  {
    uint32_t id = IDs[i];
    glDetachShader(programID, id);
    glDeleteShader(id);
  }

  m_RendererID = programID;
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

void OpenGLShader::UploadMat3(const std::string& name, const glm::mat3& data) const
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniformMatrix3fv(location, 1, false, glm::value_ptr(data));
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


void OpenGLShader::UploadInt(const std::string& name, int data) const 
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniform1iv(location, 1, &data);
}

void OpenGLShader::UploadFloat(const std::string& name, float data) const 
{ 
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  glUniform1fv(location, 1, &data);
}

void OpenGLShader::UploadBool(const std::string& name, bool data) const 
{
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  int dataI = data;
  glUniform1iv(location, 1, &dataI);
}

void OpenGLShader::UnBind() const
{
  glUseProgram(0);
}

}

}
