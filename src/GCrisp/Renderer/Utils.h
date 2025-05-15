#pragma once

#include "Shader.h"

namespace GCrisp::Graphics {

// ---- Shader ----

static std::string StringFromShaderType(const ShaderType& type) {
    switch (type) {
    case SHADER_VERTEX: {
        return "vertex";
    }
    case SHADER_FRAGMENT: {
        return "fragment";
    }
    default: {
        GC_CORE_ASSERT(false, "Unknown shader type!");
        return "";
    }
    }
}
static ShaderType ShaderTypeFromString(const std::string& type) {
    if (type == "vertex")
        return SHADER_VERTEX;
    if (type == "fragment" || type == "pixel")
        return SHADER_FRAGMENT;
    GC_CORE_ASSERT(false, "Unknown shader type!");
    return SHADER_NONE;
}

// ---- Asset ----

static std::string_view StringFromAssetType(AssetType type) {
    switch (type) {
    case AssetType::Texture2D: {
        return "Texture2D";
    }
    case AssetType::Shader: {
        return "Shader";
    }
    default: {
        return "Unknown";
    };
    }
}

} // namespace GCrisp::Graphics
