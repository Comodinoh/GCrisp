#pragma once

#include <glm/matrix.hpp>

namespace GCrisp
{
  namespace Graphics
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
          return nullptr;
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

    struct ShaderSpec
    {
      std::unordered_map<ShaderType, std::string> shaders;

      ShaderSpec(const std::initializer_list<std::pair<ShaderType, std::string>>& pairs)
      {
        for (auto pair : pairs)
        {
          shaders[pair.first] = pair.second;
        }
      }

      ShaderSpec(const std::pair<ShaderType, std::string> pairs[], int size)
      {
        for (int i = 0; i < size; i++)
        {
          auto pair = pairs[i];
          shaders[pair.first] = pair.second;
        }
      }
    };

    class Shader
    {
    public:
      virtual ~Shader() = default;

      virtual void Bind() const = 0;
      virtual void UnBind() const = 0;

      virtual void UploadMat4(const std::string& name, const glm::mat4& data) = 0;
      virtual void UploadMat3(const std::string& name, const glm::mat3& data) = 0;
      virtual void UploadVec4(const std::string& name, const glm::vec4& data) = 0;
      virtual void UploadVec3(const std::string& name, const glm::vec3& data) = 0;
      virtual void UploadInt(const std::string& name, int data) = 0;
      virtual void UploadFloat(const std::string& name, float data) = 0;
      virtual void UploadBool(const std::string& name, bool data) = 0;
    };
  }
}
