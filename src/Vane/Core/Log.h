#pragma once

#include <Vane/Core/Base.h>
// clang-format off
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
// clang-format on

namespace Vane {
class Log {
public:
    static void Init();

    static void Shutdown();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
        return s_CoreLogger;
    }

    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
        return s_ClientLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
}; // namespace Vane

// Core log macros
#define VANE_CORE_FATAL(...) ::Vane::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define VANE_CORE_ERROR(...) ::Vane::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VANE_CORE_WARN(...) ::Vane::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VANE_CORE_INFO(...) ::Vane::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VANE_CORE_TRACE(...) ::Vane::Log::GetCoreLogger()->trace(__VA_ARGS__)

// App log macros
#define VANE_ERROR(...) ::Vane::Log::GetClientLogger()->error(__VA_ARGS__)
#define VANE_WARN(...) ::Vane::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VANE_INFO(...) ::Vane::Log::GetClientLogger()->info(__VA_ARGS__)
#define VANE_TRACE(...) ::Vane::Log::GetClientLogger()->trace(__VA_ARGS__)
