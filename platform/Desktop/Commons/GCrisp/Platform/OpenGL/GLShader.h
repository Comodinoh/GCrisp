#pragma once

#include <GCrisp/Renderer/Shader.h>

namespace GCrisp
{
    namespace Graphics
    {
        class GLShader : public Shader
        {
            typedef unsigned int GLenum;

        public:
            GLShader(const ShaderSpecification& spec);
            virtual ~GLShader();

            virtual void Bind() const override;
            virtual void UnBind() const override;

            virtual void UploadMat4(const std::string& name, const glm::mat4& data) override;
            virtual void UploadMat3(const std::string& name, const glm::mat3& data) override;
            virtual void UploadVec4(const std::string& name, const glm::vec4& data) override;
            virtual void UploadVec3(const std::string& name, const glm::vec3& data) override;
            virtual void UploadInt(const std::string& name, int data) override;
            virtual void UploadInt(const std::string& name, int* data, int count) override;
            virtual void UploadFloat(const std::string& name, float data) override;
            virtual void UploadBool(const std::string& name, bool data) override;
        private:
            uint32_t m_RendererID;

            std::unordered_map<std::string, int> m_UniformLocationCache;

        private:
            int GetUniformLocation(const std::string& name);
        };
    }
}
