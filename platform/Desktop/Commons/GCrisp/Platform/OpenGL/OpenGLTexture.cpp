#include <gcpch.h>
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace GCrisp
{
    namespace Graphics
    {
        OpenGLTexture::OpenGLTexture(const stbi_uc* data, const TextureSpec& spec)
        {
            m_Spec.Width = spec.Width;
            m_Spec.Height = spec.Height;

            glGenTextures(1, &m_RendererID);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);

            glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


            GLenum format = spec.channels > 3 ? GL_RGBA : GL_RGB;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spec.Width, spec.Height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        OpenGLTexture::~OpenGLTexture()
        {
            glDeleteTextures(1, &m_RendererID);
        }

        void OpenGLTexture::Bind(int slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);
        }

        void OpenGLTexture::SetMagFiltering(TextureFilter filtering = TextureFilter::None) const
        {
            GLenum glFiltering;
            switch (filtering)
            {
            case TextureFilter::Linear:
                {
                    glFiltering = GL_LINEAR;
                    break;
                }
            case TextureFilter::Nearest:
                {
                    glFiltering = GL_NEAREST;
                    break;
                }
            case TextureFilter::None:
                {
                    glFiltering = GL_NEAREST;
                }
            }
            glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, glFiltering);
        }

        void OpenGLTexture::SetMinFiltering(TextureFilter filtering = TextureFilter::None) const
        {
            GLenum glFiltering;
            switch (filtering)
            {
            case TextureFilter::Linear:
                {
                    glFiltering = GL_LINEAR;
                    break;
                }
            case TextureFilter::Nearest:
                {
                    glFiltering = GL_NEAREST;
                    break;
                }
            case TextureFilter::None:
                {
                    glFiltering = GL_LINEAR;
                }
            }
            glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, glFiltering);
        }
    }
}
