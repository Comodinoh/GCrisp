#include <gcpch.h>
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace GCrisp{

namespace Graphics{

OpenGLTexture2D::OpenGLTexture2D(const stbi_uc* data, const TextureSpec& spec)
{
  m_Spec.Width = spec.Width;
  m_Spec.Height = spec.Height;

  glGenTextures(1, &m_RendererID);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);
  
  glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = spec.channels > 3 ? GL_RGBA : GL_RGB; 

  glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB8, spec.Width, spec.Height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

}

}
