#include <gcpch.h>
#include "GLShader.h"

#include <GCrisp/Renderer/GraphicsCore.h>
#include <glad/glad.h>
#include <GCrisp/Core/Log.h>
#include <glm/gtc/type_ptr.hpp>

namespace GCrisp
{
    namespace Graphics
    {
        static inline GLenum GLShaderFromGC(ShaderType type)
        {
            switch (type)
            {
            case SHADER_VERTEX: return GL_VERTEX_SHADER;
            case SHADER_FRAGMENT: return GL_FRAGMENT_SHADER;
            default: return 0;
            }
        }

        GLShader::GLShader(const ShaderSpecification& spec)
        {
            GC_PROFILE_FUNC();
            uint32_t programID = glCreateProgram();

            uint32_t IDs[MAX_SHADER_TYPES];


            // We compile the vertex source if the provided pointer isn't null
            int shaderIndex = 0;
            for (auto&& [type, source] : spec.shaders)
            {
                GC_CORE_ASSERT(!StringFromShaderType(type).empty(), "ShaderType string cannot be empty!");
                GLenum glType = GLShaderFromGC(type);
                uint32_t id = glCreateShader(glType);

                const char* cSource = source.c_str();

                glShaderSource(id, 1, &cSource, NULL);
                glCompileShader(id);

                GLint status;

                glGetShaderiv(id, GL_COMPILE_STATUS, &status);
                if (status == GL_FALSE)
                {
                    GLint maxLength;
                    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

                    GLchar* infoLog = (GLchar*)calloc(maxLength, sizeof(GLchar));
                    glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);

                    glDeleteShader(id);

                    GC_CORE_ERROR("Failed to compile {0} shader. Please refer to the logs below:",
                                  StringFromShaderType(type));
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
            if (status == GL_FALSE)
            {
                GLint maxLength;
                glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

                GLchar* infoLog = (GLchar*)calloc(maxLength, sizeof(GLchar));
                glGetProgramInfoLog(programID, maxLength, &maxLength, infoLog);

                glDeleteProgram(programID);

                for (int i = 0; i < shaderIndex; i++)
                {
                    uint32_t id = IDs[i];
                    glDeleteShader(id);
                }


                GC_CORE_ERROR(std::string(infoLog));
                GC_CORE_ASSERT(false, "Failed to link shader program!");
                return;
            }

            glUseProgram(programID);


            for (int i = 0; i < shaderIndex; i++)
            {
                uint32_t id = IDs[i];
                glDetachShader(programID, id);
                glDeleteShader(id);
            }

            m_RendererID = programID;
        }

        GLShader::~GLShader()
        {
            GC_PROFILE_FUNC();
            glDeleteProgram(m_RendererID);
        }

        void GLShader::Bind() const
        {
            glUseProgram(m_RendererID);
        }

        void GLShader::UploadMat4(const std::string& name, const glm::mat4& data)
        {
            GLint location = GetUniformLocation(name);
            glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
        }

        void GLShader::UploadMat3(const std::string& name, const glm::mat3& data)
        {
            GLint location = GetUniformLocation(name);
            glUniformMatrix3fv(location, 1, false, glm::value_ptr(data));
        }

        void GLShader::UploadVec3(const std::string& name, const glm::vec3& data)
        {
            GLint location = GetUniformLocation(name);
            glUniform3fv(location, 1, glm::value_ptr(data));
        }

        void GLShader::UploadVec4(const std::string& name, const glm::vec4& data)
        {
            GLint location = GetUniformLocation(name);
            glUniform4fv(location, 1, glm::value_ptr(data));
        }


        void GLShader::UploadInt(const std::string& name, int data)
        {
            GLint location = GetUniformLocation(name);
            glUniform1iv(location, 1, &data);
        }

        void GLShader::UploadInt(const std::string& name, int* data, int count)
        {
            GLint location = GetUniformLocation(name);
            glUniform1iv(location, count, data);
        }

        void GLShader::UploadFloat(const std::string& name, float data)
        {
            GLint location = GetUniformLocation(name);
            glUniform1fv(location, 1, &data);
        }

        void GLShader::UploadBool(const std::string& name, bool data)
        {
            GLint location = GetUniformLocation(name);
            int dataI = data;
            glUniform1iv(location, 1, &dataI);
        }

        int GLShader::GetUniformLocation(const std::string& name)
        {
            auto it = m_UniformLocationCache.find(name);
            if (it == m_UniformLocationCache.end())
            {
                int location = glGetUniformLocation(m_RendererID, name.c_str());
                m_UniformLocationCache[name] = location;
                return location;
            }
            return it->second;
        }

        void GLShader::UnBind() const
        {
            glUseProgram(0);
        }
    }
}
