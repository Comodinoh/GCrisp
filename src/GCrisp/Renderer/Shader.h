#pragma once

#include "GraphicsCore.h"
#include <glm/matrix.hpp>
#include <GCrisp/Assets/Assets.h>

namespace GCrisp::Graphics
{
    enum ShaderType
    {
        SHADER_NONE = 0, SHADER_VERTEX, SHADER_FRAGMENT
    };

    static std::string StringFromShaderType(const ShaderType& type)
    {
        switch (type)
        {
        case SHADER_VERTEX:
            {
                return "vertex";
            }
        case SHADER_FRAGMENT:
            {
                return "fragment";
            }
        default:
            {
                GC_CORE_ASSERT(false, "Unknown shader type!");
                return "";
            }
        }
    }

    static ShaderType ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return SHADER_VERTEX;
        if (type == "fragment" || type == "pixel")
            return SHADER_FRAGMENT;
        GC_CORE_ASSERT(false, "Unknown shader type!");
        return SHADER_NONE;
    }

    struct ShaderSpecification
    {
        std::unordered_map<ShaderType, std::string> shaders;

        ShaderSpecification(const std::initializer_list<std::pair<ShaderType, std::string>>& pairs)
        {
            for (const auto& pair : pairs)
            {
                shaders[pair.first] = pair.second;
            }
        }

        ShaderSpecification(const std::pair<ShaderType, std::string> pairs[], int size)
        {
            for (int i = 0; i < size; i++)
            {
                auto pair = pairs[i];
                shaders[pair.first] = pair.second;
            }
        }
    };

    class Shader : public Asset
    {
    public:

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void UploadMat4(const std::string& name, const glm::mat4& data) = 0;
        virtual void UploadMat3(const std::string& name, const glm::mat3& data) = 0;
        virtual void UploadVec4(const std::string& name, const glm::vec4& data) = 0;
        virtual void UploadVec3(const std::string& name, const glm::vec3& data) = 0;
        virtual void UploadInt(const std::string& name, int data) = 0;
        virtual void UploadInt(const std::string& name, int* data, int count) = 0;
        virtual void UploadFloat(const std::string& name, float data) = 0;
        virtual void UploadBool(const std::string& name, bool data) = 0;

        virtual AssetType GetType() const override {return AssetType::Shader;};

        GC_GRAPHICS_CREATE_DECL_WITH_SPEC(Shader);
    };
}
